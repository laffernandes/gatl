#ifndef __GA1C_HPP__
#define __GA1C_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_CONFORMAL_ALGEBRA_OVERLOAD(ga1c, 1)

namespace ga1c {

	static auto const e1 = e(c<1>);

	static auto const no = e(c<2>);
	static auto const ni = e(c<3>);

	static auto const ep = (ni / c<2>) - no;
	static auto const em = (ni / c<2>) + no;

	static auto const Ie = e1;
	static auto const I = pseudoscalar();

}

#endif // __GA1C_HPP__
