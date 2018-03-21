#ifndef __GA5E_HPP__
#define __GA5E_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga5e, 5, 0)

namespace ga5e {

	constexpr auto e1 = e(c<1>);
	constexpr auto e2 = e(c<2>);
	constexpr auto e3 = e(c<3>);
	constexpr auto e4 = e(c<4>);
	constexpr auto e5 = e(c<5>);

	constexpr auto I = pseudoscalar();

}

#endif // __GA5E_HPP__
