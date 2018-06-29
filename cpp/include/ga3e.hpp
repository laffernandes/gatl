#ifndef __GA3E_HPP__
#define __GA3E_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/euclidean.hpp>

namespace ga3e {

	using namespace ga;

	_GA_UTILS_EUCLIDEAN_ALGEBRA_DEFINITION(space, basis_vectors_names, 3, "e1", "e2", "e3")

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);
	static auto const e3 = e(c<3>);

	_GA_CORE_OVERLOAD(space)
	_GA_EXTRA_OVERLOAD(space, basis_vectors_names)
	_GA_UTILS_EUCLIDEAN_ALGEBRA_OVERLOAD(space)

}

#endif // __GA3E_HPP__
