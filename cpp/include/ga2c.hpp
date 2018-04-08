#ifndef __GA2C_HPP__
#define __GA2C_HPP__

#include <ga.hpp>
#include <ga/clifford/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga2c, 2 + 1, 1)

namespace ga2c {

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);

	static auto const ep = e(c<3>);
	static auto const em = e(c<4>);

	static auto const no = (em - ep) / c<2>;
	static auto const ni = ep + em;

	static auto const Ie = e1 ^ e2;
	static auto const I = pseudoscalar();

}

#endif // __GA2C_HPP__
