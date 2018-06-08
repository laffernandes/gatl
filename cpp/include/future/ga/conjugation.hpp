#ifndef __FUTURE_GA_CONJUGATION_HPP__
#define __FUTURE_GA_CONJUGATION_HPP__

namespace ga {

	template<class CoefficientType, class Expression>
	constexpr decltype(auto) conjugation(clifford_expression<CoefficientType, Expression> const &arg) {
		auto lazy = make_lazy_context(arg);
		return lazy.eval(clifford_expression<default_integral_t, detail::graded_unary_minus_t<decltype(lazy)::argument_expression_t<0>, (default_bitset_t)0x6666666666666666ull> >());
	}

	template<class Type>
	constexpr decltype(auto) conjugation(Type const &arg) {
		return conjugation(scalar(arg));
	}
}

#endif // __FUTURE_GA_CONJUGATION_HPP__
