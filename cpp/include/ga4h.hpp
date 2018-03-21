#ifndef __GA4H_HPP__
#define __GA4H_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga4h, 4 + 1, 0)

namespace ga4h {

	constexpr auto e1 = e(c<1>);
	constexpr auto e2 = e(c<2>);
	constexpr auto e3 = e(c<3>);
	constexpr auto e4 = e(c<4>);

	constexpr auto ep = e(c<5>);

	constexpr auto Ie = e1 ^ e2 ^ e3 ^ e4;
	constexpr auto I = pseudoscalar();

}

#endif // __GA4H_HPP__
