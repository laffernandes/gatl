#ifndef __GA_HPP__
#define __GA_HPP__

#include <cassert>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <type_traits>

#ifndef GA_MAX_BASIS_VECTOR_INDEX
	#define GA_MAX_BASIS_VECTOR_INDEX 63
#endif // GA_MAX_BASIS_VECTOR_INDEX

namespace ga {

	static_assert(std::is_integral<decltype((GA_MAX_BASIS_VECTOR_INDEX))>::value && 1 <= (GA_MAX_BASIS_VECTOR_INDEX) && (GA_MAX_BASIS_VECTOR_INDEX) <= 63, "GA_MAX_BASIS_VECTOR_INDEX must be an integer value between 1 and 63, inclusive.");

	typedef std::conditional<
		(GA_MAX_BASIS_VECTOR_INDEX) < 8,
		std::uint8_t,
		std::conditional<
			(GA_MAX_BASIS_VECTOR_INDEX) < 16,
			std::uint16_t,
			std::conditional<
				(GA_MAX_BASIS_VECTOR_INDEX) < 32,
				std::uint32_t,
				std::uint64_t
			>::type
		>::type
	>::type default_bitset_t;

	typedef std::int32_t default_integral_t;
	typedef std::double_t default_floating_point_t;

	typedef std::int32_t grade_t;

	typedef std::uint32_t index_t;
	typedef std::uint32_t ndims_t;

}

#include "ga/default_tolerance.hpp"

#include "ga/compile_time_ordering.hpp"

#include "ga/compile_time_value.hpp"
#include "ga/value_math.hpp"
#include "ga/value_neg.hpp"
#include "ga/value_mul.hpp"
#include "ga/value_div.hpp"
#include "ga/value_add.hpp"
#include "ga/value_sub.hpp"

#include "ga/compile_time_basis_blade.hpp"
#include "ga/dynamic_basis_blade.hpp"
#include "ga/basis_blade_grade.hpp"
#include "ga/basis_blade_ordering.hpp"

#include "ga/space.hpp"
#include "ga/metric_space.hpp"
#include "ga/orthogonal_metric_space.hpp"
#include "ga/signed_metric_space.hpp"
#include "ga/euclidean_metric_space.hpp"

#include "ga/component.hpp"
#include "ga/components.hpp"
#include "ga/element_ordering.hpp"
#include "ga/element_unary_minus.hpp"
#include "ga/element_graded_unary_minus.hpp"
#include "ga/element_binary_plus.hpp"
#include "ga/element_binary_minus.hpp"
#include "ga/element_graded_product_orthogonal_metric.hpp"
#include "ga/element_keep_if_grade.hpp"
#include "ga/element_deduce_grade.hpp"

#include "ga/expression.hpp"
#include "ga/expression_coefficient_type.hpp"
#include "ga/expression_insert.hpp"
#include "ga/expression_iterator.hpp"
#include "ga/expression_ordered_iterator.hpp"
#include "ga/expression_copy.hpp"

#include "ga/native.hpp"

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

#include "ga/inverse_geometric_product.hpp"

#include "ga/scalar_expression_math.hpp"
#include "ga/blade_exponential.hpp"

#include "ga/reverse_norm.hpp"
#include "ga/versor_inverse.hpp"
#include "ga/dualization.hpp"
#include "ga/take_grade.hpp"

#include "ga/write.hpp"

#include "ga/eval.hpp"
#include "ga/grade.hpp"

#include "ga/pseudoscalar.hpp"
#include "ga/basis_vector.hpp"

#include "ga/macro_for_operators_overload.hpp"

GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(std::int16_t, constexpr)
GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(std::int32_t, constexpr)
GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(std::int64_t, constexpr)

GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(std::float_t, constexpr)
GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(std::double_t, constexpr)

//TODO Implement equal(lhs, rhs, tol)
//TODO Implement is_zero(arg, tol)
//TODO Implement is_scalar(arg, tol)
//TODO Implement is_blade(arg, tol)
//TODO Implement is_versor(arg, tol)
//TODO Implement is_even_versor(arg, tol)
//TODO Implement is_odd_versor(arg, tol)
//TODO Implement meet_and_join(lhs, rhs, tol)

#endif // __GA_HPP__
