#ifndef __GA_UTILS_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_UTILS_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define _GA_UTILS_HOMOGENEOUS_ALGEBRA_OVERLOAD(SPACE) \
	template <typename... Types> \
	constexpr decltype(auto) euclidean_vector(Types &&... coords) { \
		return euclidean_vector(SPACE, std::move(coords)...); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) flat_direction(clifford_expression<CoefficientType, Expression> const &flat) { \
		return flat_direction(flat, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) flat_support_vector(clifford_expression<CoefficientType, Expression> const &flat) { \
		return flat_support_vector(flat, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) flat_moment(clifford_expression<CoefficientType, Expression> const &flat) { \
		return flat_moment(flat, SPACE); \
	} \
	\
	template<typename CoefficientType, typename Expression> \
	constexpr decltype(auto) flat_unit_support_point(clifford_expression<CoefficientType, Expression> const &flat) { \
		return flat_unit_support_point(flat, SPACE); \
	} \
	\
	template <typename... Types> \
	constexpr decltype(auto) point(Types &&... coords) { \
		return point(SPACE, std::move(coords)...); \
	} \
	template<typename DirectionCoefficientType, typename DirectionExpression, typename CoefficientType, typename Expression> \
	constexpr decltype(auto) translate(clifford_expression<DirectionCoefficientType, DirectionExpression> const &direction, clifford_expression<CoefficientType, Expression> const &flat) { \
		return translate(direction, flat, SPACE); \
	}

#endif // __GA_UTILS_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
