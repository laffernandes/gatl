#ifndef __GA_CLIFFORD_BASIS_VECTOR_HPP__
#define __GA_CLIFFORD_BASIS_VECTOR_HPP__

namespace ga {

	namespace clifford {

		template<index_t Index>
		constexpr decltype(auto) e(constant<Index> const &) {
			static_assert(Index > 0, "Basis vector index out of bounds. It is expected a positive value.");
			return detail::make_expression(detail::make_component(constant<1>(), detail::cbasis_blade<default_bitset_t(default_bitset_t(1) << (Index - 1))>()), detail::empty_expression_tree(), detail::empty_expression_tree());
		}

		constexpr decltype(auto) e(index_t const index) {
			assert(index > 0);
			return detail::make_expression(detail::make_component(constant<1>(), detail::dbasis_blade<default_bitset_t(2)>(default_bitset_t(default_bitset_t(1) << (index - 1)))), detail::empty_expression_tree(), detail::empty_expression_tree());
		}

	}

}

#endif // __GA_CLIFFORD_BASIS_VECTOR_HPP__
