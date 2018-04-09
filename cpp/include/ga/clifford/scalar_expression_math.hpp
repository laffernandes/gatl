#ifndef __GA_CLIFFORD_SCALAR_EXPRESSION_MATH_HPP__
#define __GA_CLIFFORD_SCALAR_EXPRESSION_MATH_HPP__

namespace ga {

	namespace clifford {

		using lazy::abs;

		template<class ExpressionType>
		constexpr decltype(auto) abs(clifford_expression<ExpressionType> const &arg) {
			return abs(native(arg));
		}

		using lazy::cbrt;

		template<class ExpressionType>
		constexpr decltype(auto) cbrt(clifford_expression<ExpressionType> const &arg) {
			return cbrt(native(arg));
		}

		using lazy::exp;

		template<class ExpressionType, typename std::enable_if<ga::clifford::detail::may_cast_to_native<ExpressionType>::value, int>::type = 0>
		constexpr decltype(auto) exp(clifford_expression<ExpressionType> const &arg) {
			return exp(native(arg));
		}

		using lazy::sqrt;

		template<class ExpressionType>
		constexpr decltype(auto) sqrt(clifford_expression<ExpressionType> const &arg) {
			return sqrt(native(arg));
		}

		using lazy::cos;

		template<class ExpressionType>
		constexpr decltype(auto) cos(clifford_expression<ExpressionType> const &arg) {
			return cos(native(arg));
		}

		using lazy::sin;

		template<class ExpressionType>
		constexpr decltype(auto) sin(clifford_expression<ExpressionType> const &arg) {
			return sin(native(arg));
		}

		using lazy::tan;

		template<class ExpressionType>
		constexpr decltype(auto) tan(clifford_expression<ExpressionType> const &arg) {
			return tan(native(arg));
		}

		using lazy::cosh;

		template<class ExpressionType>
		constexpr decltype(auto) cosh(clifford_expression<ExpressionType> const &arg) {
			return cosh(native(arg));
		}

		using lazy::sinh;

		template<class ExpressionType>
		constexpr decltype(auto) sinh(clifford_expression<ExpressionType> const &arg) {
			return sinh(native(arg));
		}

		using lazy::tanh;

		template<class ExpressionType>
		constexpr decltype(auto) tanh(clifford_expression<ExpressionType> const &arg) {
			return tanh(native(arg));
		}

	}

}

#endif // __GA_CLIFFORD_SCALAR_EXPRESSION_MATH_HPP__
