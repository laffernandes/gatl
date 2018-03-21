#ifndef __GA1H_HPP__
#define __GA1H_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga1h, 1 + 1, 0)

namespace ga1h {

	constexpr auto e1 = e(c<1>);

	constexpr auto ep = e(c<2>);

	constexpr auto Ie = e1;
	constexpr auto I = pseudoscalar();

}

#endif // __GA1H_HPP__
