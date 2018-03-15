#ifndef __GA_BASIS_VECTOR_HPP__
#define __GA_BASIS_VECTOR_HPP__

namespace ga {

	template<index_t Index>
	constexpr decltype(auto) e(detail::cvalue<Index> const &) {
		return detail::make_expression(detail::make_component(detail::cvalue<1>(), detail::cbasis_blade<(default_bitset_t(1) << Index)>()), detail::empty_expression(), detail::empty_expression());
	}

	constexpr decltype(auto) e(index_t const index) {
		return detail::make_expression(detail::make_component(detail::cvalue<1>(), detail::dbasis_blade<default_bitset_t(2)>(default_bitset_t(1) << index)), detail::empty_expression(), detail::empty_expression());
	}

}

#endif // __GA_BASIS_VECTOR_HPP__
