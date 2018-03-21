#ifndef __GA2E_HPP__
#define __GA2E_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga2e, 2, 0)

namespace ga2e {

	constexpr auto e1 = e(c<1>);
	constexpr auto e2 = e(c<2>);

	constexpr auto I = pseudoscalar();

}

#endif // __GA2E_HPP__
