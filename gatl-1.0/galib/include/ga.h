/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_MAIN_
#define _GA_MAIN_

// Standard C++ Library.
#include <vector>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cstdarg>

// Basic Tools Library.
#include "btools.h"

// Linear Algebra Library.
#include "la.h"

// Geometric Algebra Library.
#define USING_GA_LIB

#ifdef ASSUMED_GA_TOLERANCE
	#define _GA_DEFAULT_TOLERANCE = static_cast<real_t>( ASSUMED_GA_TOLERANCE )
#else // ASSUMED_GA_TOLERANCE
	#define _GA_DEFAULT_TOLERANCE
#endif // ASSUMED_GA_TOLERANCE

#ifndef _GA_ATTRIBUTE_UNUSED
	#if defined(__GNUC__)
		#define _GA_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
	#elif defined(_MSC_VER)
		#define _GA_ATTRIBUTE_UNUSED
	#else
		#define _GA_ATTRIBUTE_UNUSED
	#endif
#endif // !_GA_ATTRIBUTE_UNUSED

#if defined(__GNUC__)
	#define _GA_ALWAYS_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
	#define _GA_ALWAYS_INLINE __forceinline
#else
	#define _GA_ALWAYS_INLINE inline
#endif

#include "ga/_private/assert.h"
#include "ga/types.h"

#include "ga/_private/bit_count.h"

#include "ga/store.h"

#include "ga/_private/assign.h"
#include "ga/_private/has_grade.h"
#include "ga/_private/is_stored.h"
#include "ga/_private/is_empty_store.h"
#include "ga/_private/is_substore.h"
#include "ga/_private/largest_grade.h"
#include "ga/_private/merge_stores.h"
#include "ga/_private/smallest_grade.h"
#include "ga/_private/binary_additive.h"

#include "ga/model.h"
#include "ga/multivector.h"

#include "ga/is_zero.h"

#include "ga/_private/equal.h"
#include "ga/equal.h"

#include "ga/cleanup.h"

#include "ga/_private/basis_vectors.h"
#include "ga/_private/consts.h"

#include "ga/abs.h"
#include "ga/sgn.h"
#include "ga/sqrt.h"
#include "ga/rand.h"

#include "ga/_private/grade.h"
#include "ga/_private/stored_grades.h"
#include "ga/_private/take_grade.h"
#include "ga/_private/take_grades.h"
#include "ga/_private/take_largest_grade.h"
#include "ga/_private/write.h"
#include "ga/assign.h"
#include "ga/grade.h"
#include "ga/take_grade.h"
#include "ga/take_largest_grade.h"
#include "ga/write.h"

#include "ga/_private/black_magic/black_magic.h"
#include "ga/_private/product.h"
#include "ga/_private/grade_sign.h"
#include "ga/_private/unary_test.h"
#include "ga/plus.h"
#include "ga/unary_plus.h"
#include "ga/minus.h"
#include "ga/unary_minus.h"
#include "ga/clifford_conjugation.h"
#include "ga/geometric_product.h"
#include "ga/commutator_product.h"
#include "ga/grade_involution.h"
#include "ga/left_contraction.h"
#include "ga/outer_product.h"
#include "ga/reverse.h"
#include "ga/right_contraction.h"
#include "ga/scalar_product.h"
#include "ga/delta_product.h"
#include "ga/dot_product.h"
#include "ga/hestenes_inner_product.h"
#include "ga/inverse_versor.h"
#include "ga/inverse_geometric_product.h"

#include "ga/norm.h"
#include "ga/unit.h"
#include "ga/dualization.h"
#include "ga/undualization.h"
#include "ga/tests.h"
#include "ga/exp.h"
#include "ga/apply_versor.h"

#include "ga/factorization.h"
#include "ga/fast_factorization.h"

#include "ga/_private/join.h"
#include "ga/_private/meet.h"
#include "ga/join.h"
#include "ga/meet.h"

#include "ga/_private/fast_join.h"
#include "ga/fast_join.h"
#include "ga/fast_meet.h"

#include "ga/clifford_conjugation_tensor.h"
#include "ga/grade_involution_tensor.h"
#include "ga/reverse_tensor.h"

#include "ga/_private/product_tensor.h"
#include "ga/dot_product_tensor.h"
#include "ga/geometric_product_tensor.h"
#include "ga/hestenes_inner_product_tensor.h"
#include "ga/left_contraction_tensor.h"
#include "ga/outer_product_tensor.h"
#include "ga/right_contraction_tensor.h"
#include "ga/scalar_product_tensor.h"

#include "ga/multivector_matrix.h"
#include "ga/operation_matrix.h"

#include "ga/clifford_conjugation_matrix.h"
#include "ga/grade_involution_matrix.h"
#include "ga/reverse_matrix.h"

#include "ga/_private/product_matrix.h"
#include "ga/dot_product_matrix.h"
#include "ga/geometric_product_matrix.h"
#include "ga/hestenes_inner_product_matrix.h"
#include "ga/left_contraction_matrix.h"
#include "ga/outer_product_matrix.h"
#include "ga/right_contraction_matrix.h"
#include "ga/scalar_product_matrix.h"

#include "ga/inverse_multivector.h"

// Geometric Algebra Library - Clifford algebras of signatures [p,q].
#include "ga/clifford/model.h"

// Geometric Algebra Library - Euclidean Vector Space model.
#include "ga/euclidean/model.h"

#include "ga/euclidean/orthogonal_projection.h"
#include "ga/euclidean/rejection.h"

#include "ga/euclidean/_private/vector.h"
#include "ga/euclidean/vector.h"

// Geometric Algebra Library - Homogeneous model.
#include "ga/homogeneous/model.h"

#include "ga/homogeneous/_private/consts.h"

#include "ga/homogeneous/tests.h"

#include "ga/homogeneous/flat_direction.h"
#include "ga/homogeneous/flat_moment.h"
#include "ga/homogeneous/flat_support_vector.h"
#include "ga/homogeneous/flat_unit_support_point.h"

#include "ga/homogeneous/translation.h"

#include "ga/homogeneous/_private/point.h"
#include "ga/homogeneous/_private/vector.h"
#include "ga/homogeneous/point.h"
#include "ga/homogeneous/vector.h"

// Geometric Algebra Library - Conformal model.
#include "ga/conformal/model.h"

#include "ga/conformal/_private/consts.h"

#include "ga/conformal/tests.h"

#include "ga/conformal/flat_direction.h"
#include "ga/conformal/flat_location.h"
#include "ga/conformal/round_direction.h"
#include "ga/conformal/round_location.h"
#include "ga/conformal/round_size2.h"
#include "ga/conformal/tangent_direction.h"
#include "ga/conformal/tangent_location.h"
#include "ga/conformal/tangent_size2.h"

#include "ga/conformal/_private/point.h"
#include "ga/conformal/_private/vector.h"
#include "ga/conformal/point.h"
#include "ga/conformal/vector.h"

// Geometric Algebra Library - Quadratic curves (conic sections) model.
#include "ga/quadratic/model.h"

#include "ga/quadratic/_private/base_space_vectors_count.h"
#include "ga/quadratic/_private/point.h"
#include "ga/quadratic/_private/vector.h"
#include "ga/quadratic/point.h"
#include "ga/quadratic/vector.h"

#endif // !_GA_MAIN_
