#ifndef __GA_CORE_SCALAR_HPP__
#define __GA_CORE_SCALAR_HPP__

namespace ga {

	// Helper for defining a scalar clifford expression type.
	template<class CoefficientType, class Coefficient>
	using scalar_clifford_expression = clifford_expression<CoefficientType, detail::component<Coefficient, detail::constant_basis_blade<default_bitset_t(0)> > >;

	// Converts the given native value type to scalar clifford expression.
	template<class ValueType, class = std::enable_if_t<!is_clifford_expression_v<ValueType> > >
	constexpr decltype(auto) scalar(ValueType const &arg) {
		return scalar_clifford_expression<ValueType, detail::stored_value>(make_sequential_storage(arg));
	}

	template<class ValueType, class = std::enable_if_t<!is_clifford_expression_v<ValueType> > >
	constexpr decltype(auto) scalar(ValueType &&arg) {
		return scalar_clifford_expression<ValueType, detail::stored_value>(make_sequential_storage(std::move(arg)));
	}

	template<class CoefficientType, class Coefficient>
	constexpr scalar_clifford_expression<CoefficientType, Coefficient> scalar(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		return arg;
	}

	template<class CoefficientType, class Coefficient>
	constexpr decltype(auto) scalar(scalar_clifford_expression<CoefficientType, Coefficient> &&arg) {
		return std::move(arg);
	}

}

#endif // __GA_CORE_SCALAR_HPP__
