#ifndef __GA2E_HPP__
#define __GA2E_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/euclidean.hpp>

namespace ga2e {

	using namespace ga;

	_GA_UTILS_EUCLIDEAN_ALGEBRA_DEFINITION(space, basis_vectors_names, 2, "e1", "e2")

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);

	_GA_CORE_OVERLOAD(space)
	_GA_EXTRA_OVERLOAD(space, basis_vectors_names)
	_GA_UTILS_EUCLIDEAN_ALGEBRA_OVERLOAD(space)

}

#endif // __GA2E_HPP__
