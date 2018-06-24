#ifndef __GA1E_HPP__
#define __GA1E_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/macro_for_signed_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga1e, 1, 0)

namespace ga1e {

	static auto const e1 = e(c<1>);
	
	static auto const I = pseudoscalar();

}

#endif // __GA1E_HPP__
