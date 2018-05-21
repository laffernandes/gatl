#ifndef __FUTURE_GA_REVERSION_HPP__
#define __FUTURE_GA_REVERSION_HPP__

namespace ga {

	template<class CoefficientType, class Expression>
	constexpr decltype(auto) reversion(clifford_expression<CoefficientType, Expression> const &arg) {
		typedef detail::lazy_arguments<Expression> lazy;
		return detail::eval<detail::graded_unary_minus_t<lazy::argument_expression_t<0>, (default_bitset_t)0xCCCCCCCCCCCCCCCCull> >(arg);
	}

	template<class Type>
	constexpr decltype(auto) reversion(Type const &arg) {
		return reversion(scalar(arg));
	}

}

#endif // __FUTURE_GA_REVERSION_HPP__
