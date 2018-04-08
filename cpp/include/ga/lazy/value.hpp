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

			constexpr operator value_type () const {
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

			value_type const value_;
		};

		template<class ValueType>
		struct is_lazy_expression<value<ValueType> > {
			constexpr static bool value = true;
		};

		template<class ExpressionType>
		struct is_value {
			constexpr static bool value = false;
		};

		template<class ValueType>
		struct is_value<value<ValueType> > {
			constexpr static bool value = true;
		};

		template<class ValueType>
		constexpr value<ValueType> val(ValueType const &arg) {
			return value<ValueType>(arg);
		}

	}

}

#endif // __GA_LAZY_VALUE_HPP__
