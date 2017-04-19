/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _SMATH_BINOMIAL_
#define _SMATH_BINOMIAL__

// The namespace of the static math library.
namespace smath
{

/*******************************************************************************************************
 * smath::binomial<n,k> struct definition.
 *******************************************************************************************************/

// The base struct for compile time computation of a binomial (B(n,k) = n!/(k!(n-k)!)).
template<int n, int k>
struct binomial
{
	// Specifies the resulting value.
	static const int result = factorial<n>::result / (factorial<k>::result * factorial<n-k>::result);
};

}

#endif // !_SMATH_BINOMIAL_
