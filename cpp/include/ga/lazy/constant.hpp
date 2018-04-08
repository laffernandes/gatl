#ifndef __GA_LAZY_CONSTANT_HPP__
#define __GA_LAZY_CONSTANT_HPP__

namespace ga {

	namespace lazy {

		template<default_integral_t Value>
		class constant final : public lazy_expression<constant<Value> > {
		public:

			typedef constant expression_type;

			typedef default_integral_t value_type;

			constexpr operator value_type() const {
				return Value;
			}

			constexpr operator lazy_expression<constant<Value> > const & () const {
				return *this;
			}

			template<class OtherValueType>
			constexpr operator OtherValueType() const {
				return Value;
			}

			constexpr static value_type get() {
				return Value;
			}

			constexpr static bool compile_time_defined() {
				return true;
			}
		};

		template<default_integral_t Value>
		struct is_lazy_expression<constant<Value> > {
			constexpr static bool value = true;
		};

		template<class ExpressionType>
		struct is_constant {
			constexpr static bool value = false;
		};

		template<default_integral_t Value>
		struct is_constant<constant<Value> > {
			constexpr static bool value = true;
		};

		template<default_integral_t Value>
		constexpr auto c = constant<Value>();

	}

}

#endif // __GA_LAZY_CONSTANT_HPP__
