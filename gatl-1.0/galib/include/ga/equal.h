/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_EQUAL_
#define _GA_EQUAL_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using bmath::equal;

/*******************************************************************************************************
 * Equality operation implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivectors are equal up to an assumed numerical error.
template<typename model, typename store1, typename store2>
inline
bool
equal(const multivector<model,store1> &m1, const multivector<model,store2> &m2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::equal<store1,store2>::run( m1.data(), m2.data(), tolerance );
}

// Returns whether the given specialized multivectors are equal up to an assumed numerical error.
template<typename model, typename store>
inline
bool
equal(const multivector<model,store> &m1, const multivector<model,store> &m2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	for (size_t i=0; i<m1.size; ++i)
	{
		if (!equal( m1[i], m2[i], tolerance ))
		{
			return false;
		}
	}
	return true;
}

// Returns whether the given specialized multivectors are equal up to an assumed numerical error. Notice that this is always true.
template<typename model>
inline
bool
equal(const multivector<model,store_none> &zero1, const multivector<model,store_none> &zero2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return true;
}

// Returns whether a given scalar value and a given specialized multivectors are equal up to an assumed numerical error.
template<typename model, typename store2>
inline
bool
equal(const real_t &scalar, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::equal<store_scalar,store2>::run( &scalar, m.data(), tolerance );
}

// Returns whether a given specialized multivectors and a given scalar value are equal up to an assumed numerical error.
template<typename model, typename store1>
inline
bool
equal(const multivector<model,store1> &m, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::equal<store1,store_scalar>::run( m.data(), &scalar, tolerance );
}

}

#endif // !_GA_EQUAL_
