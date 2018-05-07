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

#include "ga/compile_time_ordering.hpp"
#include "ga/expression_traits.hpp"
#include "ga/default_tolerance.hpp"

namespace ga {

	static_assert(std::is_integral<decltype((GA_MAX_BASIS_VECTOR_INDEX))>::value && 1 <= (GA_MAX_BASIS_VECTOR_INDEX) && (GA_MAX_BASIS_VECTOR_INDEX) <= 63, "GA_MAX_BASIS_VECTOR_INDEX must be an integer value between 1 and 63, inclusive.");

	typedef std::int32_t default_integral_t;
	typedef std::double_t default_floating_point_t;

	typedef std::uint8_t id_t;

	typedef std::conditional<(GA_MAX_BASIS_VECTOR_INDEX) < 8, std::uint8_t, std::conditional<(GA_MAX_BASIS_VECTOR_INDEX) < 16, std::uint16_t, std::conditional<(GA_MAX_BASIS_VECTOR_INDEX) < 32, std::uint32_t, std::uint64_t>::type>::type>::type default_bitset_t;

	typedef std::int32_t grade_t;

	typedef std::uint32_t index_t;
	typedef std::uint32_t ndims_t;

	namespace lazy {

		using namespace ga::common;

		namespace detail {

			using namespace ga::common::detail;

		}

	}

	namespace clifford {

		using namespace ga::common;

		namespace detail {

			using namespace ga::common::detail;

		}

	}

}

#include "ga/lazy/lazy_expression.hpp"

#include "ga/lazy/constant.hpp"
#include "ga/lazy/value.hpp"
#include "ga/lazy/variable.hpp"

#include "ga/lazy/arguments_storage.hpp"
#include "ga/lazy/add.hpp"
#include "ga/lazy/mul.hpp"
#include "ga/lazy/power.hpp"

#include "ga/lazy/expression_ordering.hpp"

#include "ga/lazy/exponentiation.hpp"
#include "ga/lazy/multiplication.hpp"
#include "ga/lazy/addition.hpp"

#include "ga/lazy/math.hpp"
#include "ga/lazy/arithmetic_operators.hpp"
#include "ga/lazy/insertion_operator.hpp"

#include "ga/lazy/eval.hpp"

#include "ga/lazy/macro_for_variable_definition.hpp"

namespace ga {

	namespace clifford {

		using lazy::lazy_expression;
		using lazy::constant;

	}

}

#include "ga/clifford/compile_time_basis_blade.hpp"
#include "ga/clifford/dynamic_basis_blade.hpp"
#include "ga/clifford/basis_blade_grade.hpp"
#include "ga/clifford/basis_blade_ordering.hpp"

#include "ga/clifford/space.hpp"
#include "ga/clifford/metric_space.hpp"
#include "ga/clifford/general_metric_space.hpp"
#include "ga/clifford/orthogonal_metric_space.hpp"
#include "ga/clifford/signed_metric_space.hpp"
#include "ga/clifford/euclidean_metric_space.hpp"
#include "ga/clifford/conformal_metric_space.hpp"

#include "ga/clifford/clifford_expression.hpp"
#include "ga/clifford/clifford_expression_insert.hpp"
#include "ga/clifford/clifford_expression_iterators.hpp"
#include "ga/clifford/clifford_expression_native.hpp"

#include "ga/clifford/copy.hpp"

#include "ga/clifford/expression_list.hpp"
#include "ga/clifford/expression_list_insert.hpp"
#include "ga/clifford/expression_list_iterators.hpp"

#include "ga/clifford/component.hpp"
#include "ga/clifford/components.hpp"
#include "ga/clifford/element_ordering.hpp"
#include "ga/clifford/element_unary_minus.hpp"
#include "ga/clifford/element_graded_unary_minus.hpp"
#include "ga/clifford/element_binary_plus.hpp"
#include "ga/clifford/element_binary_minus.hpp"
#include "ga/clifford/element_graded_product_general_metric.hpp"
#include "ga/clifford/element_graded_product_orthogonal_metric.hpp"
#include "ga/clifford/element_keep_if_grade.hpp"
#include "ga/clifford/element_deduce_grade.hpp"

#include "ga/clifford/cast_to_variable.hpp"
#include "ga/clifford/expression_list_native.hpp"

#include "ga/clifford/unary_minus.hpp"
#include "ga/clifford/unary_plus.hpp"

#include "ga/clifford/graded_unary_minus.hpp"
#include "ga/clifford/conjugation.hpp"
#include "ga/clifford/involution.hpp"
#include "ga/clifford/reversion.hpp"

#include "ga/clifford/binary_minus.hpp"
#include "ga/clifford/binary_plus.hpp"

#include "ga/clifford/graded_product.hpp"
#include "ga/clifford/geometric_product.hpp"
#include "ga/clifford/left_contraction.hpp"
#include "ga/clifford/outer_product.hpp"
#include "ga/clifford/right_contraction.hpp"
#include "ga/clifford/scalar_product.hpp"

#include "ga/clifford/inverse_geometric_product.hpp"

#include "ga/clifford/scalar_expression_math.hpp"
#include "ga/clifford/blade_exponential.hpp"

#include "ga/clifford/reverse_norm.hpp"
#include "ga/clifford/versor_inverse.hpp"
#include "ga/clifford/dualization.hpp"
#include "ga/clifford/take_grade.hpp"

#include "ga/clifford/insertion_operator.hpp"

#include "ga/clifford/eval.hpp"
#include "ga/clifford/grade.hpp"

#include "ga/clifford/pseudoscalar.hpp"
#include "ga/clifford/basis_vector.hpp"

namespace ga {

	using namespace lazy;
	using namespace clifford;

}

//TODO Implement equal(lhs, rhs, tol)
//TODO Implement is_zero(arg, tol)
//TODO Implement is_scalar(arg, tol)
//TODO Implement is_blade(arg, tol)
//TODO Implement is_versor(arg, tol)
//TODO Implement is_even_versor(arg, tol)
//TODO Implement is_odd_versor(arg, tol)
//TODO Implement meet_and_join(lhs, rhs, tol)

#endif // __GA_HPP__
