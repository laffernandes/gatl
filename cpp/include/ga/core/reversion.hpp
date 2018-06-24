#ifndef __GA_CORE_REVERSION_HPP__
#define __GA_CORE_REVERSION_HPP__

namespace ga {

	template<class CoefficientType, class Expression>
	constexpr decltype(auto) reversion(clifford_expression<CoefficientType, Expression> const &arg) {
		auto lazy = make_lazy_context(arg);
		return lazy.eval(clifford_expression<default_integral_t, detail::graded_unary_minus_t<decltype(lazy)::argument_expression_t<0>, (default_bitset_t)0xCCCCCCCCCCCCCCCCull> >());
	}

	template<class Type>
	constexpr decltype(auto) reversion(Type const &arg) {
		return reversion(scalar(arg));
	}

}

#endif // __CORE_GA_REVERSION_HPP__
