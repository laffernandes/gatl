#ifndef __GA2H_HPP__
#define __GA2H_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga2h, 2 + 1, 0)

namespace ga2h {

	constexpr auto e1 = e(c<1>);
	constexpr auto e2 = e(c<2>);

	constexpr auto ep = e(c<3>);

	constexpr auto Ie = e1 ^ e2;
	constexpr auto I = pseudoscalar();

}

#endif // __GA2H_HPP__
