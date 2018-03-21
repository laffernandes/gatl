#ifndef __GA2C_HPP__
#define __GA2C_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga2c, 2 + 1, 1)

namespace ga2c {

	constexpr auto e1 = e(c<1>);
	constexpr auto e2 = e(c<2>);

	constexpr auto ep = e(c<3>);
	constexpr auto em = e(c<4>);

	constexpr auto no = (em - ep) / c<2>;
	constexpr auto ni = ep + em;

	constexpr auto Ie = e1 ^ e2;
	constexpr auto I = pseudoscalar();

}

#endif // __GA2C_HPP__
