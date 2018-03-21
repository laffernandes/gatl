#ifndef __GA_PSEUDOSCALAR_HPP__
#define __GA_PSEUDOSCALAR_HPP__

namespace ga {

	template<class SpaceType>
	constexpr decltype(auto) pseudoscalar(space<SpaceType> const &spc) {
		return detail::make_expression(detail::make_component(detail::cvalue<1>(), spc.basis_vectors()), detail::empty_expression(), detail::empty_expression());
	}

}

#endif // __GA_PSEUDOSCALAR_HPP__
