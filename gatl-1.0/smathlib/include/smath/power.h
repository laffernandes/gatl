/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _SMATH_POWER_
#define _SMATH_POWER__

// The namespace of the static math library.
namespace smath
{

/*******************************************************************************************************
 * smath::pow<x,y> struct definition.
 *******************************************************************************************************/

// The base struct for compile time computation of a x raised to the power of y. Here, y must be positive.
template<int x, size_t y>
struct pow
{
	// Specifies the resulting value.
	static const int result = x * pow<x,y-1>::result;
};

// Specialization of pow<x,y> for y equal to zero.
template<int x>
struct pow<x,0>
{
	// Specifies the end of the loop.
	static const int result = 1;
};

// Specialization of pow<x,y> for x equal to two.
template<size_t y>
struct pow<2,y>
{
	// Specifies the resulting value.
	static const int result = 1 << y;
};

// Specialization of pow<x,y> for x equal to two and y equal to zero.
template<>
struct pow<2,0>
{
	// Specifies the resulting value.
	static const int result = 1;
};

}

#endif // !_SMATH_POWER_
