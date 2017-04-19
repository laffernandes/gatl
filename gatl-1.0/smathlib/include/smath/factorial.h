/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _SMATH_FACTORIAL_
#define _SMATH_FACTORIAL_

// The namespace of the static math library.
namespace smath
{

/*******************************************************************************************************
 * smath::factorial<n> struct definition.
 *******************************************************************************************************/

// The base struct for compile time computation of a factorial (n! = n * (n - 1) * ... * 1).
template<int n>
struct factorial
{
	// Specifies the resulting value.
	static const int result = n * factorial<n-1>::result;
};

// Specialization of factorial<n> for n equal to zero.
template<>
struct factorial<0>
{
	// Specifies the end of the loop.
	static const int result = 1;
};

}

#endif // !_SMATH_FACTORIAL_
