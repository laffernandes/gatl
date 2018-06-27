#ifndef __GA3M_HPP__
#define __GA3M_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/minkowski.hpp>

namespace ga3m {

	using namespace ga;

	_GA_UTILS_MINKOWSKI_ALGEBRA_DEFINITION(space, basis_vectors_names, 3, "e1", "e2", "e3")

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);
	static auto const e3 = e(c<3>);

	_GA_CORE_OVERLOAD(space)
	_GA_EXTRA_OVERLOAD(space, basis_vectors_names)

}

#endif // __GA3M_HPP__
