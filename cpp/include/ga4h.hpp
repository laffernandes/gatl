#ifndef __GA4H_HPP__
#define __GA4H_HPP__

#include <ga.hpp>
#include <ga/clifford/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga4h, 4 + 1, 0)

namespace ga4h {

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);
	static auto const e3 = e(c<3>);
	static auto const e4 = e(c<4>);

	static auto const ep = e(c<5>);

	static auto const Ie = e1 ^ e2 ^ e3 ^ e4;
	static auto const I = pseudoscalar();

}

#endif // __GA4H_HPP__
