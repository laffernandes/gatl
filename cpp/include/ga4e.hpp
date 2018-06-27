#ifndef __GA4E_HPP__
#define __GA4E_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/euclidean.hpp>

namespace ga4e {

	using namespace ga;

	_GA_UTILS_EUCLIDEAN_ALGEBRA_DEFINITION(space, basis_vectors_names, 4, "e1", "e2", "e3", "e4")
		
	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);
	static auto const e3 = e(c<3>);
	static auto const e4 = e(c<4>);

	_GA_CORE_OVERLOAD(space)
	_GA_EXTRA_OVERLOAD(space, basis_vectors_names)

}

#endif // __GA4E_HPP__
