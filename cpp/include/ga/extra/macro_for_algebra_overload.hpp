#ifndef __GA_EXTRA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_EXTRA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define _GA_EXTRA_OVERLOAD(SPACE, BASIS_VECTORS_NAMES) \
	template<class VersorType, class Type> \
	constexpr decltype(auto) apply_even_versor(VersorType const &versor, Type const &arg) { \
		return apply_even_versor(versor, arg, SPACE); \
	} \
	\
	template<class VersorType, class Type> \
	constexpr decltype(auto) apply_odd_versor(VersorType const &versor, Type const &arg) { \
		return apply_odd_versor(versor, arg, SPACE); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) cp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return cp(lhs, rhs, SPACE); \
	} \
	\
	template<class Type, class PseudoscalarCoefficientType, class PseudoscalarExpression> \
	constexpr decltype(auto) dual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar) { \
		return dual(arg, pseudoscalar, SPACE); \
	} \
	\
	template<class Type> \
	constexpr decltype(auto) dual(Type const &arg) { \
		return dual(arg, pseudoscalar(SPACE), SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) exp(clifford_expression<CoefficientType, Expression> const &arg, CoefficientType const &tol) { \
		return exp(arg, tol, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) exp(clifford_expression<CoefficientType, Expression> const &arg) { \
		return exp(arg, SPACE); \
	} \
	\
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression> \
	constexpr decltype(auto) igp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
		return igp(lhs, rhs, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) inv(clifford_expression<CoefficientType, Expression> const &arg) { \
		return inv(arg, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) rnorm(clifford_expression<CoefficientType, Expression> const &arg) { \
		return rnorm(arg, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) rnorm_sqr(clifford_expression<CoefficientType, Expression> const &arg) { \
		return rnorm_sqr(arg, SPACE); \
	} \
	\
	template<class Type, class PseudoscalarCoefficientType, class PseudoscalarExpression> \
	constexpr decltype(auto) undual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar) { \
		return undual(arg, pseudoscalar, SPACE); \
	} \
	\
	template<class Type> \
	constexpr decltype(auto) undual(Type const &arg) { \
		return undual(arg, pseudoscalar(SPACE), SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	constexpr decltype(auto) unit(clifford_expression<CoefficientType, Expression> const &arg) { \
		return unit(arg, SPACE); \
	} \
	\
	template<class CoefficientType, class Expression> \
	std::ostream & operator <<(std::ostream &os, clifford_expression<CoefficientType, Expression> const &arg) { \
		return write(os, arg, BASIS_VECTORS_NAMES); \
	}

#endif // __GA_EXTRA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
