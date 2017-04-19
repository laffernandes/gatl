/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_TESTS_
#define _GA_TESTS_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Grade check implementations (compile-time).
 *******************************************************************************************************/

// Returns whether the given specialized multivector has at least one non zero coefficient (up to an assumed numerical error) at a given grade.
template<int grade, typename model, typename store>
inline
bool
has_grade(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (!_private::unary_test<_private::doesnt_have_grade<grade>,store>::run( m.data(), tolerance ));
}

// Returns whether the given scalar value has at least one non zero coefficient (up to an assumed numerical error) at a given grade.
template<int grade>
inline
bool
has_grade(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (!_private::unary_test<_private::doesnt_have_grade<grade>,store_scalar>::run( &scalar, tolerance ));
}

/*******************************************************************************************************
 * Grade check implementations (run-time).
 *******************************************************************************************************/

// Returns whether the given specialized multivector has at least one non zero coefficient (up to an assumed numerical error) at a given grade.
template<typename model, typename store>
inline
bool
has_grade(const int grade, const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::has_grade_runtime<store>::run( grade, m.data(), tolerance );
}

// Returns whether the given scalar value has at least one non zero coefficient (up to an assumed numerical error) at a given grade.
inline
bool
has_grade(const int grade, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::has_grade_runtime<store_scalar>::run( grade, &scalar, tolerance );
}

/*******************************************************************************************************
 * Even grade check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector has non zero coefficient (up to an assumed numerical error) only at even grades.
template<typename model, typename store>
inline
bool
has_even_grade_only(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::unary_test<_private::has_even_grade_only,store>::run( m.data(), tolerance );
}

// Returns whether the given scalar value has non zero coefficient (up to an assumed numerical error) only at even grades.
inline
bool
has_even_grade_only(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::unary_test<_private::has_even_grade_only,store_scalar>::run( &scalar, tolerance );
}

/*******************************************************************************************************
 * Odd grade check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector has non zero coefficient (up to an assumed numerical error) only at odd grades.
template<typename model, typename store>
inline
bool
has_odd_grade_only(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::unary_test<_private::has_odd_grade_only,store>::run( m.data(), tolerance );
}

// Returns whether the given scalar value has non zero coefficient (up to an assumed numerical error) only at odd grades.
inline
bool
has_odd_grade_only(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::unary_test<_private::has_odd_grade_only,store_scalar>::run( &scalar, tolerance );
}

/*******************************************************************************************************
 * Grade homogeneous check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is grade homogeneous (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_grade_homogeneous(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (grade( m, tolerance ) != -1);
}

// Returns whether the given scalar value is grade homogeneous (up to an assumed numerical error) at a given grade.
inline
bool
is_grade_homogeneous(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return true;
}

// Returns whether the given specialized multivector is grade homogeneous (up to an assumed numerical error).
template<int grade, typename model, typename store>
inline
bool
is_grade_homogeneous(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::unary_test<_private::is_grade_homogeneous<grade>,store>::run( m.data(), tolerance );
}

// Returns whether the given scalar value is grade homogeneous (up to an assumed numerical error) at a given grade.
template<int grade>
inline
bool
is_grade_homogeneous(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::unary_test<_private::is_grade_homogeneous<grade>,store_scalar>::run( &scalar, tolerance );
}

/*******************************************************************************************************
 * Nullity check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a null multivector up to an assumed numerical error.
template<typename model, typename store>
inline
bool
is_null(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	if (norm_return<model,store>::store_t::size > 0)
	{
		const multivector<model,typename norm_return<model,store>::store_t> &n2 = norm2( m );
		return is_zero( n2[0], tolerance );
	}
	else
	{
		return true;
	}
}

// Returns whether the given specialized multivector is a null multivector up to an assumed numerical error.
template<typename model>
inline
bool
is_null(const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return true;
}

// Returns whether the given scalar value is a null multivector up to an assumed numerical error.
inline
bool
is_null(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return is_zero( scalar, tolerance );
}

/*******************************************************************************************************
 * Scalar value check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a scalar value up to an assumed numerical error.
template<typename model, typename store>
inline
bool
is_scalar(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::unary_test<_private::is_scalar,store>::run( m.data(), tolerance );
}

// Returns whether the given specialized multivector is a scalar value up to an assumed numerical error.
template<typename model>
inline
bool
is_scalar(const multivector<model,store_scalar> &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return true;
}

// Returns whether the given specialized multivector is a scalar value up to an assumed numerical error.
inline
bool
is_scalar(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return true;
}

/*******************************************************************************************************
 * Pseudoscalar check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a pseudoscalar up to an assumed numerical error.
template<typename model, typename store>
inline
bool
is_pseudoscalar(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::unary_test<_private::is_pseudoscalar<model>,store>::run( m.data(), tolerance );
}

// Returns whether the given specialized multivector is a pseudoscalar up to an assumed numerical error.
template<typename model>
inline
bool
is_pseudoscalar(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::unary_test<_private::is_pseudoscalar<model>,store_scalar>::run( &scalar, tolerance );
}

/*******************************************************************************************************
 * Inversibility check implementations (only for blades and versors).
 *******************************************************************************************************/

// Returns whether the given specialized multivector is invertible (only for blades and versors).
template<typename model, typename store>
inline
bool
is_invertible(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	if (is_versor( m, tolerance ))
	{
		return true; // All invertible blades are also versors (from Section 21.5); and all versors are invertible.
	}

	ga_maybe_assert( is_blade( m, tolerance ), "The input multivector should be a blade or a versor" );
	return false;
}

// Returns whether the given specialized multivector is invertible (Euclidean metric, only for blades and versors).
template<typename model, typename store>
inline
bool is_invertible_em(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	if (is_versor_em( m, tolerance ))
	{
		return true; // All invertible blades are also versors (from Section 21.5); and all versors are invertible.
	}

	ga_maybe_assert( is_blade( m, tolerance ), "The input multivector should be a blade or a versor" );
	return false;
}

// Returns whether the given scalar value is invertible.
inline
bool
is_invertible(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (!is_zero( scalar, tolerance ));
}

// Returns whether the given scalar value is invertible (Euclidean metric).
inline
bool
is_invertible_em(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (!is_zero( scalar, tolerance ));
}

/*******************************************************************************************************
 * Inversibility check implementations (for general multivectors).
 *******************************************************************************************************/

// Returns whether the given multivector is invertible. Use is_invertible() if you are working with blades or versors.
template<typename model, typename store>
inline
bool
is_invertible_mv(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (!is_zero( la::determinant( gp_matrix<right_multiplication>( m ), tolerance ), tolerance ));
}

// Returns whether the given multivector is invertible (Euclidean metric). Use is_invertible() if you are working with blades or versors.
template<typename model, typename store>
inline
bool is_invertible_mv_em(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (!is_zero( la::determinant( gp_matrix_em<right_multiplication>( m ), tolerance ), tolerance ));
}

// Returns whether the given scalar value is invertible.
inline
bool
is_invertible_mv(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (!is_zero( scalar, tolerance ));
}

// Returns whether the given scalar value is invertible (Euclidean metric).
inline
bool
is_invertible_mv_em(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (!is_zero( scalar, tolerance ));
}

/*******************************************************************************************************
 * Unit multivector check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a unit multivector up to an assumed numerical error.
template<typename model, typename store>
inline
bool
is_unit(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (equal( abs( norm2( m ), tolerance ), static_cast<real_t>( 1 ), tolerance ));
}

// Returns whether the given specialized multivector is a unit multivector (Euclidean metric) up to an assumed numerical error.
template<typename model, typename store>
inline
bool is_unit_em(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (equal( norm2_em( m ), static_cast<real_t>( 1 ), tolerance ));
}

// Returns whether the given scalar value is a unit multivector up to an assumed numerical error.
inline
bool
is_unit(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return is_zero( static_cast<real_t>( 1 ) - abs( scalar ), tolerance );
}

// Returns whether the given scalar value is a unit multivector (Euclidean metric) up to an assumed numerical error.
inline
bool
is_unit_em(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return is_zero( static_cast<real_t>( 1 ) - abs( scalar ), tolerance );
}

/*******************************************************************************************************
 * Multivector classification implementations.
 *******************************************************************************************************/

// Returns whether the given multivector is a blade.
template<typename model, typename store>
inline
bool
is_blade(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	// Test if the blade is of a single grade.
	if (!is_grade_homogeneous( m, tolerance ))
	{
		return false;
	}

	// If we have a null multivector, we're done.
	const multivector<model,store> &rm = reverse( m );
	const multivector<model,typename scp_em_return<model,store,store>::store_t> &norm2 = scp_em( m, rm );

	if (is_zero( norm2, tolerance ))
	{
		return true;
	}
	
	// Test if the blade inverse is truly the inverse of the multivector.
	const multivector<model,store> &gm = grade_involution( m );
	const multivector<model,store> &im = gp_em( rm, inverse_em( norm2, tolerance ) );

	const multivector<model,typename gp_em_return<model,store,store>::store_t> &aux1 = gp_em( gm, im );
	if (grade( aux1, tolerance ) != 0)
	{
		return false;
	}

	const multivector<model,typename gp_em_return<model,store,store>::store_t> &aux2 = gp_em( im, gm );
	if (!equal( aux1, aux2, tolerance ))
	{
		return false;
	}

	// Test the grade preservation properties of the invertible blade.
	multivector<model,typename store_grade<1,model>::store_type> ei;

	ei = multivector<model,store_none>();
	for (size_t i=0; i<model::basis_vectors_count; ++i)
	{
		ei[i] = 1;

		if (grade( gp_em( gp_em( gm, ei ), rm ), tolerance ) != 1)
		{
			return false;
		}

		ei[i] = 0;
	}

	return true;
}

// Returns whether the given specialized multivector is a blade. Notice that this is always true.
template<typename model>
inline
bool
is_blade(const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return true;
}

// Returns whether the given scalar value is a blade. Notice that this is always true.
template<typename model>
inline
bool
is_blade(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return true;
}

// Returns whether the given multivector is a versor.
template<typename model, typename store>
inline
bool
is_versor(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	// If we have a non invertible multivector, we're done.
	const multivector<model,store> &rm = reverse( m );
	const multivector<model,typename scp_return<model,store,store>::store_t> &norm2 = scp( m, rm );

	if (is_zero( norm2, tolerance ))
	{
		return false;
	}
	
	// Test if the versor inverse is truly the inverse of the multivector.
	const multivector<model,store> &gm = grade_involution( m );
	const multivector<model,store> &im = gp( rm, inverse( norm2, tolerance ) );

	const multivector<model,typename gp_return<model,store,store>::store_t> &aux1 = gp( gm, im );
	if (grade( aux1, tolerance ) != 0)
	{
		return false;
	}

	const multivector<model,typename gp_return<model,store,store>::store_t> &aux2 = gp( im, gm );
	if (!equal( aux1, aux2, tolerance ))
	{
		return false;
	}

	// Test the grade preservation properties of the versor.
	multivector<model,typename store_grade<1,model>::store_type> ei;

	ei = multivector<model,store_none>();
	for (size_t i=0; i<model::basis_vectors_count; ++i)
	{
		ei[i] = 1;

		if (grade( gp( gp( gm, ei ), rm ), tolerance ) != 1)
		{
			return false;
		}

		ei[i] = 0;
	}

	return true;
}

// Returns whether the given specialized multivector is a versor. Notice that this is always false.
template<typename model>
inline
bool
is_versor(const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

// Returns whether the given scalar value is a versor. Notice that this is always false.
template<typename model>
inline
bool
is_versor(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

// Returns whether the given multivector is a versor (Euclidean metric).
template<typename model, typename store>
inline
bool
is_versor_em(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	// If we have a non invertible multivector, we're done.
	const multivector<model,store> &rm = reverse( m );
	const multivector<model,typename scp_em_return<model,store,store>::store_t> &norm2 = scp_em( m, rm );

	if (is_zero( norm2, tolerance ))
	{
		return false;
	}
	
	// Test if the versor inverse is truly the inverse of the multivector.
	const multivector<model,store> &gm = grade_involution( m );
	const multivector<model,store> &im = gp_em( rm, inverse_em( norm2, tolerance ) );

	const multivector<model,typename gp_em_return<model,store,store>::store_t> &aux1 = gp_em( gm, im );
	if (grade( aux1, tolerance ) != 0)
	{
		return false;
	}

	const multivector<model,typename gp_em_return<model,store,store>::store_t> &aux2 = gp_em( im, gm );
	if (!equal( aux1, aux2, tolerance ))
	{
		return false;
	}

	// Test the grade preservation properties of the versor.
	multivector<model,typename store_grade<1,model>::store_type> ei;

	ei = multivector<model,store_none>();
	for (size_t i=0; i<model::basis_vectors_count; ++i)
	{
		ei[i] = 1;

		if (grade( gp_em( gp_em( gm, ei ), rm ), tolerance ) != 1)
		{
			return false;
		}

		ei[i] = 0;
	}

	return true;
}

// Returns whether the given specialized multivector is a versor (Euclidean metric). Notice that this is always false.
template<typename model>
inline
bool
is_versor_em(const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

// Returns whether the given scalar value is a versor (Euclidean metric). Notice that this is always false.
template<typename model>
inline
bool
is_versor_em(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

// Returns whether the given multivector is a rotor.
template<typename model, typename store>
inline
bool
is_rotor(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((is_versor( m, tolerance )) && (has_even_grade_only( m, tolerance )) && (equal( scp( m, reverse( m ) ), static_cast<real_t>( 1 ), tolerance )));

	/* IMPLEMENTATION ISSUES
	 *
	 * To be a rotor, a multivector must: (i) be a versor; (ii) have only even grade grades;
	 * and (iii) its reverse must be equal to its inverse. Therefore,
	 *
	 *   reverse(m) = inverse(m)
	 *   reverse(m) = reverse(m) inverse(m * reverse(m))
	 *   reverse(m) [m * reverse(m)] = reverse(m) inverse(m * reverse(m)) [m * reverse(m)]
	 *   reverse(m) [m * reverse(m)] = reverse(m)
	 *
	 * where a white space denotes the geometric product and * the scalar product. Since
	 * the scalar product returns a scalar value, [m * reverse(m)] must be equal to one.
	 * It means that the squared reverse norm of the multivector is equal to one.
	 */
}

// Returns whether the given scalar value is a rotor. Notice that this is always false.
template<typename model>
inline
bool
is_rotor(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

// Returns whether the given multivector is a rotor (Euclidean metric).
template<typename model, typename store>
inline
bool
is_rotor_em(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((is_versor_em( m, tolerance )) && (has_even_grade_only( m, tolerance )) && (equal( scp_em( m, reverse( m ) ), static_cast<real_t>( 1 ), tolerance )));

	/* IMPLEMENTATION ISSUES
	 *
	 * To be a rotor, a multivector must: (i) be a versor; (ii) have only even grade grades;
	 * and (iii) its reverse must be equal to its inverse. Therefore,
	 *
	 *   reverse(m) = inverse(m)
	 *   reverse(m) = reverse(m) inverse(m * reverse(m))
	 *   reverse(m) [m * reverse(m)] = reverse(m) inverse(m * reverse(m)) [m * reverse(m)]
	 *   reverse(m) [m * reverse(m)] = reverse(m)
	 *
	 * where a white space denotes the geometric product and * the scalar product. Since
	 * the scalar product returns a scalar value, [m * reverse(m)] must be equal to one.
	 * It means that the squared reverse norm of the multivector is equal to one.
	 */
}

// Returns whether the given scalar value is a rotor (Euclidean metric). Notice that this is always false.
template<typename model>
inline
bool
is_rotor_em(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

}

#endif // !_GA_TESTS_
