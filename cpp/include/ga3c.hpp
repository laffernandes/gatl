#ifndef __GA3C_HPP__
#define __GA3C_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/conformal.hpp>

namespace ga3c {

	using namespace ga;

	_GA_UTILS_CONFORMAL_ALGEBRA_DEFINITION(space, basis_vectors_names, 3, "e1", "e2", "e3")

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);
	static auto const e3 = e(c<3>);

	_GA_CORE_OVERLOAD(space)
	_GA_EXTRA_OVERLOAD(space, basis_vectors_names)

}

#endif // __GA3C_HPP__
