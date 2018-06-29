#ifndef __GA1H_HPP__
#define __GA1H_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/homogeneous.hpp>

namespace ga1h {

	using namespace ga;

	_GA_UTILS_HOMOGENEOUS_ALGEBRA_DEFINITION(space, basis_vectors_names, 1, "e1")

	static auto const e1 = e(c<1>);

	_GA_CORE_OVERLOAD(space)
	_GA_EXTRA_OVERLOAD(space, basis_vectors_names)
	_GA_UTILS_HOMOGENEOUS_ALGEBRA_OVERLOAD(space)

}

#endif // __GA1H_HPP__
