#ifndef __GA2E_HPP__
#define __GA2E_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/macro_for_signed_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga2e, 2, 0)

namespace ga2e {

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);

	static auto const I = pseudoscalar();

}

#endif // __GA2E_HPP__
