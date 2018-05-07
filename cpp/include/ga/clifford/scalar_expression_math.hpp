#ifndef __GA_CLIFFORD_SCALAR_EXPRESSION_MATH_HPP__
#define __GA_CLIFFORD_SCALAR_EXPRESSION_MATH_HPP__

namespace ga {

	namespace clifford {

		using lazy::abs;

		template<class... ElementTypes>
		constexpr decltype(auto) abs(clifford_expression<ElementTypes...> const &arg) {
			return abs(native(arg));
		}

		using lazy::cbrt;

		template<class... ElementTypes>
		constexpr decltype(auto) cbrt(clifford_expression<ElementTypes...> const &arg) {
			return cbrt(native(arg));
		}

		using lazy::exp;

		template<class... ElementTypes, typename std::enable_if<ga::clifford::detail::may_cast_to_native<clifford_expression<ElementTypes...> >::value, int>::type = 0>
		constexpr decltype(auto) exp(clifford_expression<ElementTypes...> const &arg) {
			return exp(native(arg));
		}

		using lazy::sqrt;

		template<class... ElementTypes>
		constexpr decltype(auto) sqrt(clifford_expression<ElementTypes...> const &arg) {
			return sqrt(native(arg));
		}

		using lazy::cos;

		template<class... ElementTypes>
		constexpr decltype(auto) cos(clifford_expression<ElementTypes...> const &arg) {
			return cos(native(arg));
		}

		using lazy::sin;

		template<class... ElementTypes>
		constexpr decltype(auto) sin(clifford_expression<ElementTypes...> const &arg) {
			return sin(native(arg));
		}

		using lazy::tan;

		template<class... ElementTypes>
		constexpr decltype(auto) tan(clifford_expression<ElementTypes...> const &arg) {
			return tan(native(arg));
		}

		using lazy::cosh;

		template<class... ElementTypes>
		constexpr decltype(auto) cosh(clifford_expression<ElementTypes...> const &arg) {
			return cosh(native(arg));
		}

		using lazy::sinh;

		template<class... ElementTypes>
		constexpr decltype(auto) sinh(clifford_expression<ElementTypes...> const &arg) {
			return sinh(native(arg));
		}

		using lazy::tanh;

		template<class... ElementTypes>
		constexpr decltype(auto) tanh(clifford_expression<ElementTypes...> const &arg) {
			return tanh(native(arg));
		}

	}

}

#endif // __GA_CLIFFORD_SCALAR_EXPRESSION_MATH_HPP__
