/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_EQUAL_
#define _BMATH_EQUAL_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Equality operation specializations.
 *******************************************************************************************************/

// Compares two values up to a tolerance.
template<typename value_type>
inline
bool
equal(const value_type &value1, const value_type &value2, const value_type &tolerance)
{
	return (abs( value1 - value2 ) <= tolerance);
}

}

#endif // !_BMATH_EQUAL_
