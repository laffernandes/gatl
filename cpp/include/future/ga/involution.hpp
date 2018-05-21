#ifndef __FUTURE_GA_INVOLUTION_HPP__
#define __FUTURE_GA_INVOLUTION_HPP__

namespace ga {

	template<class CoefficientType, class Expression>
	constexpr decltype(auto) involution(clifford_expression<CoefficientType, Expression> const &arg) {
		typedef detail::lazy_arguments<Expression> lazy;
		return detail::eval<detail::graded_unary_minus_t<lazy::argument_expression_t<0>, (default_bitset_t)0xAAAAAAAAAAAAAAAAull> >(arg);
	}

	template<class Type>
	constexpr decltype(auto) involution(Type const &arg) {
		return involution(scalar(arg));
	}

}

#endif // __FUTURE_GA_INVOLUTION_HPP__
