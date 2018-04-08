#ifndef __GA_LAZY_VARIABLE_HPP__
#define __GA_LAZY_VARIABLE_HPP__

namespace ga {

	namespace lazy {

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

		template<id_t Id, class ValueType>
		struct is_lazy_expression<variable<Id, ValueType> > {
			constexpr static bool value = true;
		};

		template<class ExpressionType>
		struct is_variable {
			constexpr static bool value = false;
		};

		template<id_t Id, class ValueType>
		struct is_variable<variable<Id, ValueType> > {
			constexpr static bool value = true;
		};

		template<id_t Id, class ValueType>
		constexpr variable<Id, ValueType> var(ValueType const &arg) {
			return variable<Id, ValueType>(arg);
		}

	}

}

#endif // __GA_LAZY_VARIABLE_HPP__
