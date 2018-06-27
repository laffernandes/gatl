#ifndef __GA1M_HPP__
#define __GA1M_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/minkowski.hpp>

namespace ga1m {

	using namespace ga;

	_GA_UTILS_MINKOWSKI_ALGEBRA_DEFINITION(space, basis_vectors_names, 1, "e1")

	static auto const e1 = e(c<1>);

	_GA_CORE_OVERLOAD(space)
	_GA_EXTRA_OVERLOAD(space, basis_vectors_names)

}

#endif // __GA1M_HPP__
