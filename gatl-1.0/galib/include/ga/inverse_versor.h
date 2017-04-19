/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_INVERSE_VERSOR_
#define _GA_INVERSE_VERSOR_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Inverse function implementations for versors and blades.
 *******************************************************************************************************/

// Computes the inverse of a scalar value.
inline
real_t
inverse(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( !is_zero( scalar, tolerance ), "The input multivector is not invertible." );
	return 1 / scalar;
}

// Computes the inverse (Euclidean metric) of a scalar value.
inline
real_t
inverse_em(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( !is_zero( scalar, tolerance ), "The input multivector is not invertible." );
	return 1 / scalar;
}

// Computes the inverse of multivector storing only the scalar basis blade. This method was specialized for this kind of multivector in order to avoid infinine recursive calls to the most general inverse() method.
template<typename model>
inline
multivector<model,store_scalar>
inverse(const multivector<model,store_scalar> &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	multivector<model,store_scalar> result = { { { inverse( scalar[0], tolerance ) } } };
	return result;
}

// Computes the inverse (Euclidean metric) of multivector storing only the scalar basis blade. This method was specialized for this kind of multivector in order to avoid infinine recursive calls to the most general inverse() method.
template<typename model>
inline
multivector<model,store_scalar>
inverse_em(const multivector<model,store_scalar> &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	multivector<model,store_scalar> result = { { { inverse_em( scalar[0], tolerance ) } } };
	return result;
}

// Computes the inverse of a blade or a versor. This method is not suitable for any kind of multivector.
template<typename model, typename store>
inline
multivector<model,store>
inverse(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( !_private::is_empty_store<store>::result );
	ga_maybe_assert( is_versor( m, tolerance ), "The input multivector should be an invertible blade or a versor." ); // All invertible blades are also versors (from Section 21.5).

	const multivector<model,store> &r = reverse( m );
	return gp( r, inverse( scp( m, r ), tolerance ) );
}

// Computes the inverse (Euclidean metric) of a blade or a versor. This method is not suitable for any kind of multivector.
template<typename model, typename store>
inline
multivector<model,store>
inverse_em(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( !_private::is_empty_store<store>::result );
	ga_maybe_assert( is_versor_em( m, tolerance ), "The input multivector should be an invertible blade or a versor." ); // All invertible blades are also versors (from Section 21.5).

	const multivector<model,store> &r = reverse( m );
	return gp_em( r, inverse_em( scp_em( m, r ), tolerance ) );
}

}

#endif // !_GA_INVERSE_VERSOR_
