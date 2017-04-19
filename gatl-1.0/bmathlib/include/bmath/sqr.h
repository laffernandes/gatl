/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_SQR_
#define _BMATH_SQR_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Square function specializations.
 *******************************************************************************************************/

// Computer the square of a given value.
template<typename value_type>
inline
value_type
sqr(const value_type &value)
{
	return (value * value);
}

}

#endif // !_BMATH_SQR_
