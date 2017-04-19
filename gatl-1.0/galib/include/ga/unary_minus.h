/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_UNARY_MINUS_
#define _GA_UNARY_MINUS_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Negation operation.
 *******************************************************************************************************/

// Negates a multivector.
template<typename model, typename store>
inline
multivector<model,store>
uminus(const multivector<model,store> &m)
{
	multivector<model,store> result;
	for (size_t i=0; i<m.size; ++i)
	{
		result[i] = -m[i];
	}
	return result;
}

// Negates a zero multivector.
template<typename model>
inline
multivector<model,store_none>
uminus(const multivector<model,store_none> &zero)
{
	return zero;
}

// Negates a scalar value.
inline
real_t
uminus(const real_t &scalar)
{
	return -scalar;
}

/*******************************************************************************************************
 * Unary negation operator overload.
 *******************************************************************************************************/

// Negates a multivector.
template<typename model, typename store>
inline
multivector<model,store>
operator - (const multivector<model,store> &m)
{
	return uminus( m );
}

}

#endif // !_GA_UNARY_MINUS_
