/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _SMATH_FACTORIAL2_
#define _SMATH_FACTORIAL2_

// The namespace of the static math library.
namespace smath
{

/*******************************************************************************************************
 * smath::factorial2<n> struct definition.
 *******************************************************************************************************/

// The base struct for compile time computation of a double factorial (n!!).
template<int n>
struct factorial2
{
	// Specifies the resulting value.
	static const int result = n * factorial2<n-2>::result;
};

// Specialization of factorial2<n> for n equal to zero.
template<>
struct factorial2<0>
{
	// Specifies the end of the loop.
	static const int result = 1;
};

// Specialization of factorial2<n> for n equal to -1.
template<>
struct factorial2<-1>
{
	// Specifies the end of the loop.
	static const int result = 1;
};

}

#endif // !_SMATH_FACTORIAL2_
