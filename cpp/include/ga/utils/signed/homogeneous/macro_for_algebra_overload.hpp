#ifndef __GA_UTILS_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_UTILS_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define _GA_UTILS_HOMOGENEOUS_ALGEBRA_OVERLOAD(SPACE) \
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) flat_direction(clifford_expression<CoefficientType, Expression> const &arg) { \
		return flat_direction(arg, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) flat_support_vector(clifford_expression<CoefficientType, Expression> const &arg) { \
		return flat_support_vector(arg, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) flat_moment(clifford_expression<CoefficientType, Expression> const &arg) { \
		return flat_moment(arg, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) flat_unit_support_point(clifford_expression<CoefficientType, Expression> const &arg) { \
		return flat_unit_support_point(arg, SPACE); \
	} \
	\
	template <class... Types> \
	constexpr decltype(auto) make_euclidean_vector(Types &&... coords) { \
		return make_euclidean_vector(SPACE, std::move(coords)...); \
	} \
	template <class... Types> \
	constexpr decltype(auto) make_point(Types &&... coords) { \
		return make_point(SPACE, std::move(coords)...); \
	} \
	template<class DirectionCoefficientType, class DirectionExpression, class FlatCoefficientType, class FlatExpression> \
	constexpr decltype(auto) translate(clifford_expression<DirectionCoefficientType, DirectionExpression> const &direction, clifford_expression<FlatCoefficientType, FlatExpression> const &flat) { \
		return translate(direction, flat, SPACE); \
	}

#endif // __GA_UTILS_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
