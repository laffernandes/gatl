/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

/*******************************************************************************************************
 * Set of products/operations to be used within any geometric algebra model.
 * The using directive allows an individual name from a specific namespace (e.g., ga namespace) to be
 * used without explicit qualification inside the current namespace.
 *******************************************************************************************************/

using ga::operator %;					// Scalar product.
using ga::operator *;					// Geometric product.
using ga::operator +;					// Binary addition of unary plus.
using ga::operator -;					// Binary subtraction or unary minus (negation).
using ga::operator <<;					// Left contraction or write into a output stream.
using ga::operator >>;					// Right contraction.
using ga::operator ^;					// Outer product.

using ga::abs;							// Absolute value (only for scalar values).
using ga::apply_even_versor;			// Apply even versor.
using ga::apply_even_versor_em;			// Apply even versor (Euclidean metric).
using ga::apply_odd_versor;				// Apply odd versor.
using ga::apply_odd_versor_em;			// Apply odd versor (Euclidean metric).
using ga::assign;						// Assign operation.
using ga::cleanup;						// Cleanup round-off errors at the "zero" coefficients.
using ga::clifford_conjugation;			// Clifford conjugation.
using ga::clifford_conjugation_matrix;	// Clifford conjugation matrix.
using ga::clifford_conjugation_tensor;	// Clifford conjugation tensor.
using ga::cmp;							// Commutator product.
using ga::cmp_em;						// Commutator product (Euclidean metric).
using ga::delta;						// Delta product.
using ga::delta_em;						// Delta product (Euclidean metric).
using ga::dot;							// Dot product.
using ga::dot_em;						// Dot product (Euclidean metric).
using ga::dot_matrix;					// Dot product matrix.
using ga::dot_matrix_em;				// Dot product matrix (Euclidean metric).
using ga::dot_tensor;					// Dot product tensor.
using ga::dot_tensor_em;				// Dot product tensor (Euclidean metric).
using ga::dual;							// Dualization.
using ga::dual_em;						// Dualization (Euclidean metric).
using ga::equal;						// Equality test.
using ga::exp;							// Exponential function.
using ga::exp_em;						// Exponential function (Euclidean metric).
using ga::factorize_em;					// Factorization (Euclidean metric).
using ga::fast_factorize_em;			// Factorization (Euclidean metric).
using ga::gp;							// Geometric product.
using ga::gp_em;						// Geometric product (Euclidean metric).
using ga::gp_matrix;					// Geometric product matrix.
using ga::gp_matrix_em;					// Geometric product matrix (Euclidean metric).
using ga::gp_tensor;					// Geometric product tensor.
using ga::gp_tensor_em;					// Geometric product tensor (Euclidean metric).
using ga::grade;						// Multivector's grade.
using ga::grade_involution;				// Grade involution.
using ga::grade_involution_matrix;		// Grade involution matrix.
using ga::grade_involution_tensor;		// Grade involution tensor.
using ga::has_even_grade_only;			// Even grades test.
using ga::has_grade;					// Grade test.
using ga::has_odd_grade_only;			// Odd grades test.
using ga::hip;							// Hestenes' inner product.
using ga::hip_em;						// Hestenes' inner product (Euclidean metric).
using ga::hip_matrix;					// Hestenes' inner product matrix.
using ga::hip_matrix_em;				// Hestenes' inner product matrix (Euclidean metric).
using ga::hip_tensor;					// Hestenes' inner product tensor.
using ga::hip_tensor_em;				// Hestenes' inner product tensor (Euclidean metric).
using ga::igp;							// Inverse geometric product (only for blades and versors).
using ga::igp_em;						// Inverse geometric product (Euclidean metric, only for blades and versors).
using ga::inverse;						// Inverse (only for blades and versors).
using ga::inverse_em;					// Inverse (Euclidean metric, only for blades and versors).
using ga::inverse_mv;					// Inverse (for general multivectors).
using ga::inverse_mv_em;				// Inverse (Euclidean metric, for general multivectors).
using ga::is_blade;						// Blade test.
using ga::is_grade_homogeneous;			// Grade homogeneous test.
using ga::is_invertible;				// Inversibility test (only for blades and versors).
using ga::is_invertible_em;				// Inversibility test (Euclidean metric, only for blades and versors).
using ga::is_invertible_mv;				// Inversibility test (for general multivectors).
using ga::is_invertible_mv_em;			// Inversibility test (Euclidean metric, for general multivectors).
using ga::is_null;						// Null multivector test.
using ga::is_rotor;						// Rotor test.
using ga::is_rotor_em;					// Rotor test (Euclidean metric).
using ga::is_scalar;					// Scalar value test.
using ga::is_pseudoscalar;				// Pseudoscalar test.
using ga::is_unit;						// Unit multivector test.
using ga::is_unit_em;					// Unit multivector test (Euclidean metric).
using ga::is_versor;					// Versor test.
using ga::is_versor_em;					// Versor test (Euclidean metric).
using ga::is_zero;						// Zero multivector test.
using ga::join;							// Join of blades.
using ga::fast_join;					// Join of blades.
using ga::lcont;						// Left contraction.
using ga::lcont_em;						// Left contraction (Euclidean metric).
using ga::lcont_matrix;					// Left contraction matrix.
using ga::lcont_matrix_em;				// Left contraction matrix (Euclidean metric).
using ga::lcont_tensor;					// Left contraction tensor.
using ga::lcont_tensor_em;				// Left contraction tensor (Euclidean metric).
using ga::meet;							// Meet of blades.
using ga::fast_meet;					// Meet of blades.
using ga::minus;						// Binary subtraction.
using ga::multivector_matrix;			// Matrix representation of a general multivector.
using ga::norm;							// Reverse norm.
using ga::norm_em;						// Euclidean norm.
using ga::norm2;						// Squared reverse norm.
using ga::norm2_em;						// Squared Euclidean norm.
using ga::op;							// Outer product.
using ga::op_matrix;					// Outer product matrix.
using ga::op_tensor;					// Outer product tensor.
using ga::plus;							// Binary addition.
using ga::rand_multivector;				// Random multivector generator.
using ga::rcont;						// Right contraction.
using ga::rcont_em;						// Right contraction (Euclidean metric).
using ga::rcont_matrix;					// Right contraction matrix.
using ga::rcont_matrix_em;				// Right contraction matrix (Euclidean metric).
using ga::rcont_tensor;					// Right contraction tensor.
using ga::rcont_tensor_em;				// Right contraction tensor (Euclidean metric).
using ga::reverse;						// Reverse.
using ga::reverse_matrix;				// Reverse matrix.
using ga::reverse_tensor;				// Reverse tensor.
using ga::scp;							// Scalar product.
using ga::scp_em;						// Scalar product (Euclidean metric).
using ga::scp_matrix;					// Scalar product matrix.
using ga::scp_matrix_em;				// Scalar product matrix (Euclidean metric).
using ga::scp_tensor;					// Scalar product tensor.
using ga::scp_tensor_em;				// Scalar product tensor (Euclidean metric).
using ga::sgn;							// Sign (only for scalar values).
using ga::sqrt;							// Square root (only for scalar values).
using ga::take_grade;					// Take k-grade part.
using ga::take_largest_grade;			// Take largest grade part.
using ga::uminus;						// Unary minus (negation).
using ga::undual;						// Undualization.
using ga::undual_em;					// Undualization (Euclidean metric).
using ga::unit;							// Unit under reverse norm.
using ga::unit_em;						// Unit under Euclidean norm.
using ga::uplus;						// Unary plus.
