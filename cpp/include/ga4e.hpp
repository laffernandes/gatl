#ifndef __GA4E_HPP__
#define __GA4E_HPP__

#include <ga.hpp>
#include <ga/clifford/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga4e, 4, 0)

namespace ga4e {

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);
	static auto const e3 = e(c<3>);
	static auto const e4 = e(c<4>);

	static auto const I = pseudoscalar();

}

#endif // __GA4E_HPP__
