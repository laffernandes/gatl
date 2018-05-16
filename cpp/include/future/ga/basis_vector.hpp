#ifndef __FUTURE_GA_BASIS_VECTOR_HPP__
#define __FUTURE_GA_BASIS_VECTOR_HPP__

namespace ga {

	template<index_t Index>
	constexpr decltype(auto) e(constant<Index> const &) {
		static_assert(Index > 0, "Basis vector index out of bounds. It is expected a positive value.");
		return clifford_expression<default_integral_t, detail::component_t<detail::constant_value<1>, detail::constant_basis_blade<default_bitset_t(default_bitset_t(1) << (Index - 1))> > >();
	}

	constexpr decltype(auto) e(index_t const index) {
		assert(index > 0);
		return clifford_expression<default_integral_t, detail::component_t<detail::constant_value<1>, detail::dynamic_basis_blade<default_bitset_t(2), detail::stored_bitset> > >(make_sequential_storage(default_bitset_t(default_bitset_t(1) << (index - 1))));
	}

}

#endif // __FUTURE_GA_BASIS_VECTOR_HPP__
