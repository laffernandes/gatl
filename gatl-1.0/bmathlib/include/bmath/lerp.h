/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_LERP_
#define _BMATH_LERP_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Linear interpolation implementations.
 *******************************************************************************************************/

// Linear interpolation of two values.
template<typename some_type, typename real_type>
inline
some_type
lerp(const some_type &min, const some_type &max, const real_type &position)
{
	return ((max - min) * position) + min;
}

}

#endif // !_BMATH_LERP_
