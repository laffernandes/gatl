#ifndef __GA4E_HPP__
#define __GA4E_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga4e, 4, 0)

namespace ga4e {

	constexpr auto e1 = e(c<1>);
	constexpr auto e2 = e(c<2>);
	constexpr auto e3 = e(c<3>);
	constexpr auto e4 = e(c<4>);

	constexpr auto I = pseudoscalar();

}

#endif // __GA4E_HPP__
