#ifndef __FUTURE_GA1E_HPP__
#define __FUTURE_GA1E_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga1e, 1, 0)

namespace ga1e {

	static auto const e1 = e(c<1>);
	
	static auto const I = pseudoscalar();

}

#endif // __FUTURE_GA1E_HPP__
