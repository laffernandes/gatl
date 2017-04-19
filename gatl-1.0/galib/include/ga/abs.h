/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_ABS_
#define _GA_ABS_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using std::abs;

/*******************************************************************************************************
 * Absolute function implementations.
 *******************************************************************************************************/

// Calculates the absolute value.
template<typename model>
inline
multivector<model,store_none>
abs(const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return zero;
}

// Calculates the absolute value.
template<typename model>
inline
multivector<model,store_scalar>
abs(const multivector<model,store_scalar> &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	multivector<model,store_scalar> result = { { { abs( scalar[0] ) } } };
	return result;
}

// Calculates the absolute value.
template<typename model, typename store>
inline
multivector<model,store_scalar>
abs(const multivector<model,store> &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_always_assert( is_scalar( scalar, tolerance ), "ga::abs() function is not implemented for general multivectors." );

	multivector<model,store_scalar> result = { { { abs( scalar[0] ) } } };
	return result;
}

}

#endif // !_GA_ABS_
