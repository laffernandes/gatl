#ifndef __GA_LAZY_MATH_HPP__
#define __GA_LAZY_MATH_HPP__

namespace ga {

	namespace lazy {

		using std::abs;

		//TODO abs

		using std::cbrt;

		template<class ExpressionType>
		constexpr decltype(auto) cbrt(lazy_expression<ExpressionType> const &arg) {
			return detail::exponentiation(arg(), detail::multiplication(constant<1>(), detail::exponentiation(constant<3>(), constant<-1>())));
		}

		using std::exp;

		//TODO exp
		/*
		template<class ExpressionType>
		constexpr decltype(auto) exp(lazy_expression<ExpressionType> const &arg) {
			return detail::exponentiation(euler_number, arg());
		}
		*/

		using std::pow;

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) pow(lazy_expression<LeftExpressionType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::exponentiation(lhs(), rhs());
		}

		template<class LeftExpressionType, class RightType, typename std::enable_if<!(is_lazy_expression<RightType>::value || is_clifford_expression<RightType>::value), int>::type = 0>
		constexpr decltype(auto) pow(lazy_expression<LeftExpressionType> const &lhs, RightType const &rhs) {
			return detail::exponentiation(lhs(), val(rhs));
		}

		template<class LeftType, class RightExpressionType, typename std::enable_if<!(is_lazy_expression<LeftType>::value || is_clifford_expression<LeftType>::value), int>::type = 0>
		constexpr decltype(auto) pow(LeftType const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::exponentiation(val(lhs), rhs());
		}

		using std::sqrt;

		template<class ExpressionType>
		constexpr decltype(auto) sqrt(lazy_expression<ExpressionType> const &arg) {
			return detail::exponentiation(arg(), detail::multiplication(constant<1>(), detail::exponentiation(constant<2>(), constant<-1>())));
		}

		using std::cos;

		//TODO cos

		using std::sin;

		//TODO sin

		using std::tan;

		template<class ExpressionType>
		constexpr decltype(auto) tan(lazy_expression<ExpressionType> const &arg) {
			return detail::multiplication(sin(arg()), detail::exponentiation(cos(arg()), constant<-1>()));
		}

		using std::cosh;

		//TODO cosh

		using std::sinh;

		//TODO sinh

		using std::tanh;

		template<class ExpressionType>
		constexpr decltype(auto) tanh(lazy_expression<ExpressionType> const &arg) {
			return detail::multiplication(sinh(arg()), detail::exponentiation(cosh(arg()), constant<-1>()));
		}

	}

}

#endif // __GA_LAZY_MATH_HPP__
