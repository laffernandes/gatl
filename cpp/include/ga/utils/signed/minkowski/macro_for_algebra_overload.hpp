#ifndef __GA_UTILS_SIGNED_MINKOWSKI_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_UTILS_SIGNED_MINKOWSKI_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define _GA_UTILS_MINKOWSKI_ALGEBRA_OVERLOAD(SPACE) \
	template <class... Types> \
	constexpr decltype(auto) euclidean_vector(Types &&... coords) { \
		return euclidean_vector(SPACE, std::move(coords)...); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) flat_direction(clifford_expression<CoefficientType, Expression> const &flat) { \
		return flat_direction(flat, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) flat_location(clifford_expression<CoefficientType, Expression> const &flat) { \
		return flat_location(flat, SPACE); \
	} \
	\
	template <class... Types> \
	constexpr decltype(auto) point(Types &&... coords) { \
		return point(SPACE, std::move(coords)...); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) round_direction(clifford_expression<CoefficientType, Expression> const &round) { \
		return round_direction(round, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) round_location(clifford_expression<CoefficientType, Expression> const &round) { \
		return round_location(round, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) round_size_sqr(clifford_expression<CoefficientType, Expression> const &round) { \
		return round_size_sqr(round, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) tangent_direction(clifford_expression<CoefficientType, Expression> const &tangent) { \
		return tangent_direction(tangent, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) tangent_location(clifford_expression<CoefficientType, Expression> const &tangent) { \
		return tangent_location(tangent, SPACE); \
	}

#endif // __GA_UTILS_SIGNED_MINKOWSKI_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
