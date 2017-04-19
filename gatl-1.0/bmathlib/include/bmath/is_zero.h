/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_TESTS_
#define _BMATH_TESTS_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Zero value check specializations.
 *******************************************************************************************************/

// Returns whether the given value is zero assimung a tolerance.
template<typename value_type>
inline
bool
is_zero(const value_type &value, const value_type &tolerance)
{
	return (abs( value ) <= tolerance);
}

}

#endif // !_BMATH_IS_ZERO_
