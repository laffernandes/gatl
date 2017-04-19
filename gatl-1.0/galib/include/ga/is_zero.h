/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_IS_ZERO_
#define _GA_IS_ZERO_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using bmath::is_zero;

/*******************************************************************************************************
 * Zero multivector check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is equal to zero up to an assumed numerical error.
template<typename model, typename store>
inline
bool
is_zero(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	for (size_t i=0; i<m.size; ++i)
	{
		if (!is_zero( m[i], tolerance ))
		{
			return false;
		}
	}
	return true;
}

// Returns whether the given specialized multivector is equal to zero up to an assumed numerical error.
template<typename model>
inline
bool
is_zero(const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return true;
}

}

#endif // !_GA_IS_ZERO_
