#ifndef __GA_HPP__
#define __GA_HPP__

#ifndef GA_DEFAULT_FLT_TOLERANCE
	#define GA_DEFAULT_FLT_TOLERANCE 1.0e-8f
#else
	static_assert(GA_DEFAULT_FLT_TOLERANCE >= 0, "GA_DEFAULT_FLT_TOLERANCE must be a non-negative value.")
#endif // GA_DEFAULT_FLT_TOLERANCE

#ifndef GA_DEFAULT_DBL_TOLERANCE
	#define GA_DEFAULT_DBL_TOLERANCE 1.0e-8
#else
	static_assert(GA_DEFAULT_DBL_TOLERANCE >= 0, "GA_DEFAULT_DBL_TOLERANCE must be a non-negative value.")
#endif // GA_DEFAULT_DBL_TOLERANCE

#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <type_traits>

namespace ga {

	typedef std::uint64_t default_bitset_t;
	typedef std::int32_t default_integral_t;

	typedef default_integral_t grade_t;

	typedef std::make_unsigned<default_integral_t>::type index_t;
	typedef index_t ndims_t;

	template<class BasisBladeType, class CofficientType>
	using default_map_type = std::map<BasisBladeType, CofficientType>;

}

#include "ga/default_tolerance.hpp"

#include "ga/compile_time_ordering.hpp"

#include "ga/compile_time_value.hpp"
#include "ga/value_neg.hpp"
#include "ga/value_mul.hpp"
#include "ga/value_add.hpp"
#include "ga/value_sub.hpp"

#include "ga/compile_time_basis_blade.hpp"
#include "ga/dynamic_basis_blade.hpp"
#include "ga/basis_blade_grade.hpp"
#include "ga/basis_blade_ordering.hpp"

#include "ga/metric.hpp"
#include "ga/signed_metric.hpp"
#include "ga/euclidean_metric.hpp"

#include "ga/component.hpp"
#include "ga/components.hpp"
#include "ga/element_ordering.hpp"
#include "ga/element_unary_minus.hpp"
#include "ga/element_graded_unary_minus.hpp"
#include "ga/element_binary_plus.hpp"
#include "ga/element_binary_minus.hpp"
#include "ga/element_graded_product.hpp"
#include "ga/element_keep_if_grade.hpp"

#include "ga/expression.hpp"
#include "ga/expression_coefficient_type.hpp"
#include "ga/expression_insert.hpp"
#include "ga/expression_iterator.hpp"
#include "ga/expression_ordered_iterator.hpp"

#include "ga/unary_minus.hpp"
#include "ga/unary_plus.hpp"

#include "ga/graded_unary_minus.hpp"
#include "ga/conjugation.hpp"
#include "ga/involution.hpp"
#include "ga/reversion.hpp"

#include "ga/binary_minus.hpp"
#include "ga/binary_plus.hpp"

#include "ga/graded_product.hpp"
#include "ga/geometric_product.hpp"
#include "ga/left_contraction.hpp"
#include "ga/outer_product.hpp"
#include "ga/right_contraction.hpp"
#include "ga/scalar_product.hpp"

#include "ga/take_grade.hpp"

#include "ga/extra.hpp"

#include "ga/write.hpp"

#include "ga/basis_vector.hpp"
#include "ga/scalar_wrapper.hpp"

//TODO Implement exp(arg)
//TODO Implement sqrt(arg)
//TODO Implement grade(arg, tol)
//TODO Implement equal(lhs, rhs, tol)
//TODO Implement is_zero(arg, tol)
//TODO Implement is_scalar(arg, tol)
//TODO Implement is_blade(arg, tol)
//TODO Implement is_versor(arg, tol)
//TODO Implement is_even_versor(arg, tol)
//TODO Implement is_odd_versor(arg, tol)
//TODO Implement meet_and_join(lhs, rhs, tol)
//TODO Implement inv(arg, tol)
//TODO Implement unit(arg, tol)
//TODO Implement rnorm(arg, tol)
//TODO Implement rnorm_sqr(arg, tol)
//TODO Implement dual(arg, pseudoscalar, metric, tol)
//TODO Implement undual(arg, pseudoscalar, metric, tol)
//TODO Implement native(arg, tol)

#endif // __GA_HPP__
