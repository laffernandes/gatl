/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_CLAMP_
#define _BMATH_CLAMP_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Clamp function implementations.
 *******************************************************************************************************/

// Clamps a given value to the range [min, max].
template<typename real_type>
inline
real_type
clamp(const real_type &value, const real_type &min, const real_type &max)
{
	return (min < value) ? ((value < max) ? value : max) : min;
}

}

#endif // !_BMATH_ABS_
