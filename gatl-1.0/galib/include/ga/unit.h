/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_UNIT_
#define _GA_UNIT_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Unit multivector under reverse norm implementations.
 *******************************************************************************************************/

// Computes the unit multivector under reverse norm.
template<typename model, typename store>
inline
multivector<model,store>
unit(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return gp( m, inverse( sqrt( abs( scp( m, reverse( m ) ), tolerance ), tolerance ), tolerance ) );
}

// Computes the unit multivector under reverse norm.
inline
real_t
unit(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( !is_zero( scalar, tolerance ), "The input multivector is not invertible." );

	return sgn( scalar );
}

/*******************************************************************************************************
 * Unit multivector under Euclidean norm implementations.
 *******************************************************************************************************/

// Computes the unit multivector in the sense that its Euclidean norm is 1.
template<typename model, typename store>
inline
multivector<model,store>
unit_em(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return gp_em( m, inverse_em( norm_em( m, tolerance ), tolerance ) );
}

// Computes the unit multivector in the sense that its Euclidean norm is 1.
inline
real_t
unit_em(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( !is_zero( scalar, tolerance ), "The input multivector is not invertible." );

	return sgn( scalar );
}

}

#endif // !_GA_UNIT_
