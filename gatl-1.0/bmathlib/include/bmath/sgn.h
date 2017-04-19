/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_SGN_
#define _BMATH_SGN_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Sign function implementations.
 *******************************************************************************************************/

// Returns +1, 0, or -1.
template<typename value_type>
inline
int
sgn(const value_type &value)
{
	return (value > static_cast<value_type>( 0 )) ? 1 : ((value == static_cast<value_type>( 0 )) ? 0 : -1);
}

}

#endif // !_BMATH_SIGN_
