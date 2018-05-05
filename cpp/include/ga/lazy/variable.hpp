#ifndef __GA_LAZY_VARIABLE_HPP__
#define __GA_LAZY_VARIABLE_HPP__

namespace ga {

	namespace lazy {

		//TODO Armazenar ponteiro.

		template<id_t Id, class ValueType>
		class variable final : public lazy_expression<variable<Id, ValueType> > {
		public:

			typedef variable expression_type;

			typedef id_t id_type;
			typedef ValueType value_type;

			constexpr variable() :
				value_(0) {
			}

			constexpr variable(variable const &) = default;
			constexpr variable(variable &&) = default;

			constexpr variable(value_type const &arg) :
				value_(arg) {
			}

			constexpr variable & operator=(variable const &) = default;
			constexpr variable & operator=(variable &&) = default;

			constexpr variable & operator=(value_type const &arg) {
				value_ = arg;
				return (*this);
			}

			template<class OtherValueType>
			constexpr variable & operator=(OtherValueType const &arg) {
				value_ = arg;
				return (*this);
			}

			constexpr operator value_type() const {
				return value_;
			}

			template<class OtherValueType>
			constexpr operator OtherValueType() const {
				return value_;
			}

			constexpr static id_type id() {
				return Id;
			}

			constexpr value_type const & get() const {
				return value_;
			}

			constexpr static bool compile_time_defined() {
				return false;
			}

		private:

			value_type value_;
		};

		template<id_t Id, class ValueType, typename std::enable_if<!(is_lazy_expression<ValueType>::value || is_clifford_expression<ValueType>::value), int>::type = 0>
		constexpr decltype(auto) var(ValueType const &arg) {
			return variable<Id, ValueType>(arg);
		}

		template<id_t Id, class ExpressionType>
		constexpr decltype(auto) var(lazy_expression<ExpressionType> const &arg) {
			return var<Id>(detail::cast_to_value(arg).get());
		}

		//TODO Fazer wrapper para clifford_expression. Requer Id composto.

	}

	namespace common {

		template<id_t Id, class ValueType>
		struct is_lazy_expression<lazy::variable<Id, ValueType> > {
			constexpr static bool value = true;
		};

	}

}

#endif // __GA_LAZY_VARIABLE_HPP__
