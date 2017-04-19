/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_FACTORIAL_
#define _BMATH_FACTORIAL_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Factorial function implementation.
 *******************************************************************************************************/

// Calculates the factorial of an integer number.
template<typename integer_type>
inline
integer_type
factorial(const integer_type &n)
{
	assert( n >= 0 );

	integer_type result = std::max( n, static_cast<integer_type>( 1 ) );
	for (integer_type i=(result-1); i>1; --i)
	{
		result *= i;
	}
	return result;
}

}

#endif // !_BMATH_FACTORIAL_
