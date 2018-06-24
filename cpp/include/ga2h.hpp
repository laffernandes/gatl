#ifndef __GA2H_HPP__
#define __GA2H_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/macro_for_signed_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga2h, 2 + 1, 0)

namespace ga2h {

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);

	static auto const ep = e(c<3>);

	static auto const Ie = e1 ^ e2;
	static auto const I = pseudoscalar();

}

#endif // __GA2H_HPP__
