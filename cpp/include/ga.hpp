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

#include "ga/lazy/binary_lazy_expression.hpp"
#include "ga/lazy/add.hpp"
#include "ga/lazy/mul.hpp"
#include "ga/lazy/pow.hpp"

#include "ga/lazy/expression_ordering.hpp"

#include "ga/lazy/exponentiation.hpp"
#include "ga/lazy/multiplication.hpp"
#include "ga/lazy/addition.hpp"

#include "ga/lazy/math.hpp"
#include "ga/lazy/arithmetic_operators.hpp"
#include "ga/lazy/insertion_operator.hpp"

#include "ga/lazy/macro_for_variable_definition.hpp"

namespace ga {

	namespace clifford {

		using lazy::lazy_expression;
		using lazy::is_lazy_expression;

		using lazy::constant;
		using lazy::value;

	}

}

#include "ga/clifford/compile_time_basis_blade.hpp"
#include "ga/clifford/dynamic_basis_blade.hpp"
#include "ga/clifford/basis_blade_grade.hpp"
#include "ga/clifford/basis_blade_ordering.hpp"

#include "ga/clifford/space.hpp"
#include "ga/clifford/metric_space.hpp"
#include "ga/clifford/orthogonal_metric_space.hpp"
#include "ga/clifford/signed_metric_space.hpp"
#include "ga/clifford/euclidean_metric_space.hpp"

#include "ga/clifford/component.hpp"
#include "ga/clifford/components.hpp"
#include "ga/clifford/element_ordering.hpp"
#include "ga/clifford/element_unary_minus.hpp"
#include "ga/clifford/element_graded_unary_minus.hpp"
#include "ga/clifford/element_binary_plus.hpp"
#include "ga/clifford/element_binary_minus.hpp"
#include "ga/clifford/element_graded_product_orthogonal_metric.hpp"
#include "ga/clifford/element_keep_if_grade.hpp"
#include "ga/clifford/element_deduce_grade.hpp"

#include "ga/clifford/clifford_expression.hpp"

#include "ga/clifford/expression_tree.hpp"
#include "ga/clifford/expression_tree_coefficient_type.hpp"
#include "ga/clifford/expression_tree_insert.hpp"
#include "ga/clifford/expression_tree_iterator.hpp"
#include "ga/clifford/expression_tree_ordered_iterator.hpp"
#include "ga/clifford/expression_tree_reversed_iterator.hpp"
#include "ga/clifford/expression_tree_copy.hpp"

#include "ga/clifford/native.hpp"

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

#include "ga/clifford/write.hpp"

#include "ga/clifford/eval.hpp"
#include "ga/clifford/grade.hpp"

#include "ga/clifford/pseudoscalar.hpp"
#include "ga/clifford/basis_vector.hpp"

#include "ga/clifford/macro_for_operators_overload.hpp"

namespace ga {

	using namespace lazy;
	using namespace clifford;

}

LAZY_DEFINE_VARK_FUNCTION(1)
LAZY_DEFINE_VARK_FUNCTION(2)
LAZY_DEFINE_VARK_FUNCTION(3)
LAZY_DEFINE_VARK_FUNCTION(4)
LAZY_DEFINE_VARK_FUNCTION(5)
LAZY_DEFINE_VARK_FUNCTION(6)
LAZY_DEFINE_VARK_FUNCTION(7)
LAZY_DEFINE_VARK_FUNCTION(8)
LAZY_DEFINE_VARK_FUNCTION(9)
LAZY_DEFINE_VARK_FUNCTION(10)
LAZY_DEFINE_VARK_FUNCTION(11)
LAZY_DEFINE_VARK_FUNCTION(12)
LAZY_DEFINE_VARK_FUNCTION(13)
LAZY_DEFINE_VARK_FUNCTION(14)
LAZY_DEFINE_VARK_FUNCTION(15)
LAZY_DEFINE_VARK_FUNCTION(16)
LAZY_DEFINE_VARK_FUNCTION(17)
LAZY_DEFINE_VARK_FUNCTION(18)
LAZY_DEFINE_VARK_FUNCTION(19)
LAZY_DEFINE_VARK_FUNCTION(20)
LAZY_DEFINE_VARK_FUNCTION(21)
LAZY_DEFINE_VARK_FUNCTION(22)
LAZY_DEFINE_VARK_FUNCTION(23)
LAZY_DEFINE_VARK_FUNCTION(24)
LAZY_DEFINE_VARK_FUNCTION(25)
LAZY_DEFINE_VARK_FUNCTION(26)
LAZY_DEFINE_VARK_FUNCTION(27)
LAZY_DEFINE_VARK_FUNCTION(28)
LAZY_DEFINE_VARK_FUNCTION(29)
LAZY_DEFINE_VARK_FUNCTION(30)
LAZY_DEFINE_VARK_FUNCTION(31)
LAZY_DEFINE_VARK_FUNCTION(32)
LAZY_DEFINE_VARK_FUNCTION(33)
LAZY_DEFINE_VARK_FUNCTION(34)
LAZY_DEFINE_VARK_FUNCTION(35)
LAZY_DEFINE_VARK_FUNCTION(36)
LAZY_DEFINE_VARK_FUNCTION(37)
LAZY_DEFINE_VARK_FUNCTION(38)
LAZY_DEFINE_VARK_FUNCTION(39)
LAZY_DEFINE_VARK_FUNCTION(40)
LAZY_DEFINE_VARK_FUNCTION(41)
LAZY_DEFINE_VARK_FUNCTION(42)
LAZY_DEFINE_VARK_FUNCTION(43)
LAZY_DEFINE_VARK_FUNCTION(44)
LAZY_DEFINE_VARK_FUNCTION(45)
LAZY_DEFINE_VARK_FUNCTION(46)
LAZY_DEFINE_VARK_FUNCTION(47)
LAZY_DEFINE_VARK_FUNCTION(48)
LAZY_DEFINE_VARK_FUNCTION(49)
LAZY_DEFINE_VARK_FUNCTION(50)
LAZY_DEFINE_VARK_FUNCTION(51)
LAZY_DEFINE_VARK_FUNCTION(52)
LAZY_DEFINE_VARK_FUNCTION(53)
LAZY_DEFINE_VARK_FUNCTION(54)
LAZY_DEFINE_VARK_FUNCTION(55)
LAZY_DEFINE_VARK_FUNCTION(56)
LAZY_DEFINE_VARK_FUNCTION(57)
LAZY_DEFINE_VARK_FUNCTION(58)
LAZY_DEFINE_VARK_FUNCTION(59)
LAZY_DEFINE_VARK_FUNCTION(60)
LAZY_DEFINE_VARK_FUNCTION(61)
LAZY_DEFINE_VARK_FUNCTION(62)
LAZY_DEFINE_VARK_FUNCTION(63)

GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(std::int16_t, constexpr)
GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(std::int32_t, constexpr)
GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(std::int64_t, constexpr)

GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(std::float_t, constexpr)
GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(std::double_t, constexpr)

//TODO Refatorar operatores aritméticos
//TODO Refatorar math
//TODO Implementar eval
//TODO verificar onde contant é usado

//TODO Implement equal(lhs, rhs, tol)
//TODO Implement is_zero(arg, tol)
//TODO Implement is_scalar(arg, tol)
//TODO Implement is_blade(arg, tol)
//TODO Implement is_versor(arg, tol)
//TODO Implement is_even_versor(arg, tol)
//TODO Implement is_odd_versor(arg, tol)
//TODO Implement meet_and_join(lhs, rhs, tol)

#endif // __GA_HPP__
