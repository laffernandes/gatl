#ifndef __GA_UTILS_SIGNED_EUCLIDEAN_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_UTILS_SIGNED_EUCLIDEAN_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define _GA_UTILS_EUCLIDEAN_ALGEBRA_OVERLOAD(SPACE) \
	template <class... Types> \
	constexpr decltype(auto) make_euclidean_vector(Types &&... coords) { \
		return make_euclidean_vector(SPACE, std::move(coords)...); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) project(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return project(lhs, rhs, SPACE); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) reject(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return reject(lhs, rhs, SPACE); \
	}

#endif // __GA_UTILS_SIGNED_EUCLIDEAN_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
