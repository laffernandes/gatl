#ifndef __GA_CLIFFORD_PSEUDOSCALAR_HPP__
#define __GA_CLIFFORD_PSEUDOSCALAR_HPP__

namespace ga {

	namespace clifford {

		template<class SpaceType>
		constexpr decltype(auto) pseudoscalar(space<SpaceType> const &spc) {
			return detail::make_expression(detail::make_component(constant<1>(), spc.basis_vectors()), detail::empty_expression_tree(), detail::empty_expression_tree());
		}

	}

}

#endif // __GA_CLIFFORD_PSEUDOSCALAR_HPP__
