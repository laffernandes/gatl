#ifndef __GA1H_HPP__
#define __GA1H_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga1h, 1 + 1, 0)

namespace ga1h {

	static auto const e1 = e(c<1>);

	static auto const ep = e(c<2>);

	static auto const Ie = e1;
	static auto const I = pseudoscalar();

	GA_USE_LAZY_VARK_FUNCTIONS()

}

#endif // __GA1H_HPP__
