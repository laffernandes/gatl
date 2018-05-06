#ifndef __GA_LAZY_VALUE_HPP__
#define __GA_LAZY_VALUE_HPP__

namespace ga {

	namespace lazy {

		template<class ValueType>
		class value final : public lazy_expression<value<ValueType> > {
		public:

			typedef value expression_type;

			typedef ValueType value_type;

			constexpr value() :
				value_(0) {
			}

			constexpr value(value const &) = default;
			constexpr value(value &&) = default;

			constexpr value(value_type const &arg) :
				value_(arg) {
			}

			constexpr value & operator=(value const &) = default;
			constexpr value & operator=(value &&) = default;

			constexpr value & operator=(value_type const &arg) {
				value_ = arg;
				return (*this);
			}

			template<class OtherValueType>
			constexpr value & operator=(OtherValueType const &arg) {
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

			constexpr value_type const & get() const {
				return value_;
			}

			constexpr static bool compile_time_defined() {
				return false;
			}

		private:

			value_type value_;
		};

		template<class ValueType, typename std::enable_if<!(is_lazy_expression<ValueType>::value || is_clifford_expression<ValueType>::value), int>::type = 0>
		constexpr decltype(auto) val(ValueType const &arg) {
			return value<ValueType>(arg);
		}

		template<class ExpressionType>
		constexpr decltype(auto) val(lazy_expression<ExpressionType> const &arg) {
			return detail::eval_lazy_expression(arg());
		}

		template<default_integral_t Value>
		constexpr value<default_integral_t> val(lazy_expression<constant<Value> > const &) {
			return value<default_integral_t>(Value);
		}

		template<class ValueType>
		constexpr value<ValueType> val(lazy_expression<value<ValueType> > const &arg) {
			return arg();
		}

	}

	namespace common {

		template<class ValueType>
		struct is_lazy_expression<lazy::value<ValueType> > {
			constexpr static bool value = true;
		};

		template<class ValueType>
		struct is_lazy_value<lazy::value<ValueType> > {
			constexpr static bool value = true;
		};

		template<class ValueType>
		struct common_value_type<lazy::value<ValueType> > {
			typedef ValueType type;
		};

	}

}

#endif // __GA_LAZY_VALUE_HPP__
