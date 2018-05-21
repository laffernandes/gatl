#ifndef __FUTURE_GA_CONJUGATION_HPP__
#define __FUTURE_GA_CONJUGATION_HPP__

namespace ga {

	template<class CoefficientType, class Expression>
	constexpr decltype(auto) conjugation(clifford_expression<CoefficientType, Expression> const &arg) {
		typedef detail::lazy_arguments<Expression> lazy;
		return detail::eval<detail::graded_unary_minus_t<lazy::argument_expression_t<0>, (default_bitset_t)0x6666666666666666ull> >(arg);
	}

	template<class Type>
	constexpr decltype(auto) conjugation(Type const &arg) {
		return conjugation(scalar(arg));
	}
}

#endif // __FUTURE_GA_CONJUGATION_HPP__
