#ifndef __GA1E_HPP__
#define __GA1E_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/euclidean.hpp>

namespace ga1e {

	using namespace ga;

	_GA_UTILS_EUCLIDEAN_ALGEBRA_DEFINITION(space, basis_vectors_names, 1, "e1")

	static auto const e1 = e(c<1>);

	_GA_CORE_OVERLOAD(space)
	_GA_EXTRA_OVERLOAD(space, basis_vectors_names)

}

#endif // __GA1E_HPP__
