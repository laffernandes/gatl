#ifndef __GA_LAZY_VARIABLE_HPP__
#define __GA_LAZY_VARIABLE_HPP__

namespace ga {

	namespace lazy {

		//TODO Armazenar ponteiro.

		template<class ValueType, id_t Id, id_t... SubIds>
		class variable final : public lazy_expression<variable<ValueType, Id, SubIds...> > {
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

		template<id_t Id, id_t... SubIds, class ValueType, typename std::enable_if<!(is_lazy_expression<ValueType>::value || is_clifford_expression<ValueType>::value), int>::type = 0>
		constexpr decltype(auto) var(ValueType const &arg) {
			return variable<ValueType, Id, SubIds...>(arg);
		}

		template<id_t Id, id_t... SubIds, class ExpressionType>
		constexpr decltype(auto) var(lazy_expression<ExpressionType> const &arg) {
			return var<Id, SubIds...>(arg());
		}

		template<id_t Id, id_t... SubIds, default_integral_t Value>
		constexpr decltype(auto) var(constant<Value> const &) {
			return constant<Value>();
		}

		template<id_t Id, id_t... SubIds, class ValueType>
		constexpr decltype(auto) var(value<ValueType> const &arg) {
			return var<Id, SubIds...>(arg.get());
		}

		template<id_t Id, id_t... SubIds, class ValueType, id_t CurrentId, id_t... CurrentSubIds>
		constexpr variable<ValueType, CurrentId, CurrentSubIds...> var(variable<ValueType, CurrentId, CurrentSubIds...> const &arg) {
			return arg;
		}

	}

	namespace common {

		template<class ValueType, id_t Id, id_t... SubIds>
		struct is_lazy_expression<lazy::variable<ValueType, Id, SubIds...> > {
			constexpr static bool value = true;
		};

		template<class ValueType, id_t Id, id_t... SubIds>
		struct common_value_type<lazy::variable<ValueType, Id, SubIds...> > {
			typedef ValueType type;
		};

	}

}

#endif // __GA_LAZY_VARIABLE_HPP__
