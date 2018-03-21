#ifndef __GA1C_HPP__
#define __GA1C_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga1c, 1 + 1, 1)

namespace ga1c {

	constexpr auto e1 = e(c<1>);

	constexpr auto ep = e(c<2>);
	constexpr auto em = e(c<3>);

	constexpr auto no = (em - ep) / c<2>;
	constexpr auto ni = ep + em;

	constexpr auto Ie = e1;
	constexpr auto I = pseudoscalar();

}

#endif // __GA1C_HPP__
