#ifndef __GA_LAZY_ARITHMETIC_OPERATORS_HPP__
#define __GA_LAZY_ARITHMETIC_OPERATORS_HPP__

namespace ga {

	namespace lazy {

		template<class RightExpressionType>
		constexpr RightExpressionType operator+(lazy_expression<RightExpressionType> const &rhs) {
			return rhs();
		}

		template<class RightExpressionType>
		constexpr decltype(auto) operator-(lazy_expression<RightExpressionType> const &rhs) {
			return detail::multiplication(constant<-1>(), rhs());
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator+(lazy_expression<LeftExpressionType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::addition(lhs(), rhs());
		}

		template<class LeftExpressionType, class RightType, typename std::enable_if<!(is_lazy_expression<RightType>::value || is_clifford_expression<RightType>::value), int>::type = 0>
		constexpr decltype(auto) operator+(lazy_expression<LeftExpressionType> const &lhs, RightType const &rhs) {
			return detail::addition(lhs(), val(rhs));
		}

		template<class LeftType, class RightExpressionType, typename std::enable_if<!(is_lazy_expression<LeftType>::value || is_clifford_expression<LeftType>::value), int>::type = 0>
		constexpr decltype(auto) operator+(LeftType const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::addition(val(lhs), rhs());
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator-(lazy_expression<LeftExpressionType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::addition(lhs(), detail::multiplication(constant<-1>(), rhs()));
		}

		template<class LeftExpressionType, class RightType, typename std::enable_if<!(is_lazy_expression<RightType>::value || is_clifford_expression<RightType>::value), int>::type = 0>
		constexpr decltype(auto) operator-(lazy_expression<LeftExpressionType> const &lhs, RightType const &rhs) {
			return detail::addition(lhs(), detail::multiplication(constant<-1>(), val(rhs)));
		}

		template<class LeftType, class RightExpressionType, typename std::enable_if<!(is_lazy_expression<LeftType>::value || is_clifford_expression<LeftType>::value), int>::type = 0>
		constexpr decltype(auto) operator-(LeftType const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::addition(val(lhs), detail::multiplication(constant<-1>(), rhs()));
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator*(lazy_expression<LeftExpressionType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::multiplication(lhs(), rhs());
		}

		template<class LeftExpressionType, class RightType, typename std::enable_if<!(is_lazy_expression<RightType>::value || is_clifford_expression<RightType>::value), int>::type = 0>
		constexpr decltype(auto) operator*(lazy_expression<LeftExpressionType> const &lhs, RightType const &rhs) {
			return detail::multiplication(lhs(), val(rhs));
		}

		template<class LeftType, class RightExpressionType, typename std::enable_if<!(is_lazy_expression<LeftType>::value || is_clifford_expression<LeftType>::value), int>::type = 0>
		constexpr decltype(auto) operator*(LeftType const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::multiplication(val(lhs), rhs());
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator/(lazy_expression<LeftExpressionType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::multiplication(lhs(), detail::exponentiation(rhs(), constant<-1>()));
		}

		template<class LeftExpressionType, class RightType, typename std::enable_if<!(is_lazy_expression<RightType>::value || is_clifford_expression<RightType>::value), int>::type = 0>
		constexpr decltype(auto) operator/(lazy_expression<LeftExpressionType> const &lhs, RightType const &rhs) {
			return detail::multiplication(lhs(), detail::exponentiation(val(rhs), constant<-1>()));
		}

		template<class LeftType, class RightExpressionType, typename std::enable_if<!(is_lazy_expression<LeftType>::value || is_clifford_expression<LeftType>::value), int>::type = 0>
		constexpr decltype(auto) operator/(LeftType const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::multiplication(val(lhs), detail::exponentiation(rhs(), constant<-1>()));
		}

	}

}

#endif // __GA_LAZY_ARITHMETIC_OPERATORS_HPP__
