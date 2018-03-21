#ifndef __GA3C_HPP__
#define __GA3C_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga3c, 3 + 1, 1)

namespace ga3c {

	constexpr auto e1 = e(c<1>);
	constexpr auto e2 = e(c<2>);
	constexpr auto e3 = e(c<3>);

	constexpr auto ep = e(c<4>);
	constexpr auto em = e(c<5>);

	constexpr auto no = (em - ep) / c<2>;
	constexpr auto ni = ep + em;

	constexpr auto Ie = e1 ^ e2 ^ e3;
	constexpr auto I = pseudoscalar();

}

#endif // __GA3C_HPP__
