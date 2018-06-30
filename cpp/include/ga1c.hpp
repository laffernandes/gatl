#ifndef __GA1C_HPP__
#define __GA1C_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/conformal.hpp>

namespace ga1c {

	using namespace ga;

	_GA_UTILS_CONFORMAL_ALGEBRA_DEFINITION(space, basis_vectors_names, 1, "e1")

	static auto const e1 = e(c<1>);

	_GA_CORE_OVERLOAD(space)
	_GA_EXTRA_OVERLOAD(space, basis_vectors_names)
	_GA_UTILS_CONFORMAL_ALGEBRA_OVERLOAD(space)

}

#endif // __GA1C_HPP__
