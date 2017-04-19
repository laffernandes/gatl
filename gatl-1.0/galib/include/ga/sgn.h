/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_SGN_
#define _GA_SGN_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using bmath::sgn;

/*******************************************************************************************************
 * Sign function implementations.
 *******************************************************************************************************/

// Returns the sign of the given scalar value.
template<typename model>
inline
int
sgn(const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return 0;
}

// Returns the sign of the given scalar value.
template<typename model>
inline
int
sgn(const multivector<model,store_scalar> &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return sgn( scalar[0] );
}

// Returns the sign of the given scalar value.
template<typename model, typename store>
inline
int
sgn(const multivector<model,store> &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_always_assert( is_scalar( scalar, tolerance ), "ga::sgn() function is not implemented for general multivectors." );

	return sgn( scalar[0] );
}

}

#endif // !_GA_SGN_
