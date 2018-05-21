#ifndef __FUTURE_GA5E_HPP__
#define __FUTURE_GA5E_HPP__

#include "ga.hpp"
#include "ga/macro_for_algebra_overload.hpp"

GA_SIGNED_ALGEBRA_OVERLOAD(ga5e, 5, 0)

namespace ga5e {

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);
	static auto const e3 = e(c<3>);
	static auto const e4 = e(c<4>);
	static auto const e5 = e(c<5>);

	static auto const I = pseudoscalar();

}

#endif // __FUTURE_GA5E_HPP__
