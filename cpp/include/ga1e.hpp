#ifndef __GA1E_HPP__
#define __GA1E_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga1e, 1, 0)

namespace ga1e {

	constexpr auto e1 = e(c<1>);
	
	constexpr auto I = pseudoscalar();

}

#endif // __GA1E_HPP__
