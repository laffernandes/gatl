#ifndef __GA_LAZY_CONSTANT_HPP__
#define __GA_LAZY_CONSTANT_HPP__

namespace ga {

	namespace lazy {

		template<default_integral_t Value>
		class constant final : public lazy_expression<constant<Value> > {
		public:

			typedef constant expression_type;

			typedef default_integral_t value_type;

			constexpr constant() = default;
			constexpr constant(constant const &) = default;
			constexpr constant(constant &&) = default;

			constexpr constant & operator=(constant const &) = default;
			constexpr constant & operator=(constant &&) = default;

			constexpr operator value_type() const {
				return Value;
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
		constexpr auto c = constant<Value>();

	}

	namespace common {

		template<default_integral_t Value>
		struct is_lazy_expression<lazy::constant<Value> > {
			constexpr static bool value = true;
		};

		template<default_integral_t Value>
		struct is_lazy_constant<lazy::constant<Value> > {
			constexpr static bool value = true;
		};

	}

}

#endif // __GA_LAZY_CONSTANT_HPP__
