#ifndef __GA_CORE_INVOLUTION_HPP__
#define __GA_CORE_INVOLUTION_HPP__

namespace ga {

	template<typename CoefficientType, typename Expression>
	constexpr decltype(auto) involution(clifford_expression<CoefficientType, Expression> const &arg) {
		auto lazy = make_lazy_context(arg);
		return lazy.eval(clifford_expression<default_integral_t, detail::graded_unary_minus_t<decltype(lazy)::argument_expression_t<0>, (default_bitset_t)0xAAAAAAAAAAAAAAAAull> >());
	}

	template<typename Type>
	constexpr decltype(auto) involution(Type const &arg) {
		return involution(scalar(arg));
	}

}

#endif // __GA_CORE_INVOLUTION_HPP__
