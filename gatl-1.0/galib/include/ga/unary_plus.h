/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_UNARY_PLUS_
#define _GA_UNARY_PLUS_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Unary plus operation.
 *******************************************************************************************************/

// Returns the given multivector.
template<typename model, typename store>
inline
multivector<model,store>
uplus(const multivector<model,store> &m)
{
	return m;
}

// Returns the given scalar value.
inline
real_t
uplus(const real_t &scalar)
{
	return scalar;
}

/*******************************************************************************************************
 * Unary plus operator overload.
 *******************************************************************************************************/

// Returns the given multivector.
template<typename model, typename store>
inline
multivector<model,store>
operator + (const multivector<model,store> &m)
{
	return m;
}

}

#endif // !_GA_UNARY_PLUS_
