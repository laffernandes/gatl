/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_SQRT_
#define _GA_SQRT_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using std::sqrt;

/*******************************************************************************************************
 * Square root function implementations.
 *******************************************************************************************************/

// Calculates the square root.
template<typename model>
inline
multivector<model,store_none>
sqrt(const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return zero;
}

// Calculates the square root.
template<typename model>
inline
multivector<model,store_scalar>
sqrt(const multivector<model,store_scalar> &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	multivector<model,store_scalar> result = { { { sqrt( scalar[0] ) } } };
	return result;
}

// Calculates the square root.
template<typename model, typename store>
inline
multivector<model,store_scalar>
sqrt(const multivector<model,store> &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_always_assert( is_scalar( scalar, tolerance ), "ga::sqrt() function is not implemented for general multivectors." );

	multivector<model,store_scalar> result = { { { sqrt( scalar[0] ) } } };
	return result;
}

}

#endif // !_GA_SQRT_
