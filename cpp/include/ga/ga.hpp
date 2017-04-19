#pragma once

#ifndef GA_HPP
#define GA_HPP

#include <cassert>
#include <cstdint>
#include <type_traits>

namespace ga {

	#include <ga/declarations.hpp>

	namespace detail {

		#include <ga/detail/time_traits.hpp>
		#include <ga/detail/tree.hpp>
		#include <ga/detail/value.hpp>

		#include <ga/detail/argument_storage_for_expression.hpp>
		#include <ga/detail/sugested_container_class.hpp>

		#include <ga/detail/expression.hpp>
		#include <ga/detail/binary_expression.hpp>
		#include <ga/detail/binary_metric_expression.hpp>
		#include <ga/detail/unary_expression.hpp>

		#include <ga/detail/gp_expression.hpp>
		#include <ga/detail/graded_gp_expression.hpp>
		#include <ga/detail/sign_change_expression.hpp>

		#include <ga/detail/pack.hpp>
		#include <ga/detail/identity_operation.hpp>

	}

	#include <ga/metric.hpp>
	#include <ga/multivector.hpp>

	#include <ga/make_scalar.hpp>
	#include <ga/make_basis_vector.hpp>

	#include <ga/grade.hpp>

	#include <ga/macros.hpp>

	#include <ga/unary_plus.hpp>
	#include <ga/unary_minus.hpp>
	#include <ga/plus.hpp>
	#include <ga/minus.hpp>

	#include <ga/reverse.hpp>
	#include <ga/grade_involution.hpp>
	#include <ga/clifford_conjugation.hpp>

	#include <ga/take_grade.hpp>

	#include <ga/geometric_product.hpp>
	#include <ga/outer_product.hpp>
	#include <ga/scalar_product.hpp>
	#include <ga/left_contraction.hpp>
	#include <ga/right_contraction.hpp>
	#include <ga/delta_product.hpp>

	#include <ga/is_zero.hpp>
	#include <ga/is_blade.hpp>
	#include <ga/is_versor.hpp>
	#include <ga/is_even_versor.hpp>
	#include <ga/is_odd_versor.hpp>

	#include <ga/exp.hpp>
	#include <ga/sqrt.hpp>

	#include <ga/reverse_norm.hpp>
	#include <ga/inverse.hpp>
	#include <ga/inverse_geometric_product.hpp>

	#include <ga/dual.hpp>
	#include <ga/undual.hpp>

	#include <ga/meet_and_join.hpp>

}

#endif
