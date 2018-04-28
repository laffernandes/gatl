#ifndef __GA3E_HPP__
#define __GA3E_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga3e, 3, 0)

namespace ga3e {

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);
	static auto const e3 = e(c<3>);

	static auto const I = pseudoscalar();

	GA_USE_LAZY_VARK_FUNCTIONS()

}

#endif // __GA3E_HPP__
