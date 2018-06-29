#ifndef __GA_CORE_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_CORE_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define _GA_CORE_OVERLOAD(SPACE) \
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) dot(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return dot(lhs, rhs, SPACE); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) gp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return gp(lhs, rhs, SPACE); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) hip(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return hip(lhs, rhs, SPACE); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) lcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return lcont(lhs, rhs, SPACE); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) op(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return op(lhs, rhs, SPACE); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression > \
	constexpr decltype(auto) operator^(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return op(lhs, rhs, SPACE); \
	} \
	\
	constexpr decltype(auto) pseudoscalar() { \
		return pseudoscalar(SPACE); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) rcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return rcont(lhs, rhs, SPACE); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) rp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return rp(lhs, rhs, SPACE); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) sp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return sp(lhs, rhs, SPACE); \
	} \
	\
	template<class... Types> \
	constexpr decltype(auto) vector(Types const &... coords) { \
		return vector(SPACE, coords...); \
	}

#endif // __GA_CORE_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
