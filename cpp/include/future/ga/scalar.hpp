#ifndef __FUTURE_GA_SCALAR_HPP__
#define __FUTURE_GA_SCALAR_HPP__

namespace ga {

	// Converts the given native value type to scalar clifford expression.
	template<class ValueType, class = std::enable_if_t<!is_clifford_expression_v<ValueType> > >
	constexpr decltype(auto) scalar(ValueType const &arg) {
		return clifford_expression<ValueType, detail::component_t<detail::stored_value, detail::constant_basis_blade<default_bitset_t(0)> > >(make_sequential_storage(arg));
	}

	template<class ValueType, class = std::enable_if_t<!is_clifford_expression_v<ValueType> > >
	constexpr decltype(auto) scalar(ValueType &&arg) {
		return clifford_expression<ValueType, detail::component_t<detail::stored_value, detail::constant_basis_blade<default_bitset_t(0)> > >(make_sequential_storage(std::move(arg)));
	}

	template<class CoefficientType, class Expression, class = std::enable_if_t<detail::is_scalar_expression_v<Expression> > >
	constexpr decltype(auto) scalar(clifford_expression<CoefficientType, Expression> const &arg) {
		return arg;
	}

	template<class CoefficientType, class Expression, class = std::enable_if_t<detail::is_scalar_expression_v<Expression> > >
	constexpr decltype(auto) scalar(clifford_expression<CoefficientType, Expression> &&arg) {
		return std::move(arg);
	}

}

#endif // __FUTURE_GA_SCALAR_HPP__
