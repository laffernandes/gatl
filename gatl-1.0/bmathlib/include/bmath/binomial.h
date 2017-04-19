/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_BINOMIAL_
#define _BMATH_BINOMIAL_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Binomial function implementation.
 *******************************************************************************************************/

// Calculates the combination (binomial) of n elements k-by-b.
template<typename integer_type>
inline
integer_type
binomial(const integer_type &n, const integer_type &k)
{
	assert( (n >= 1) && (n >= k) );

	const integer_type r = (k > (n >> 1)) ? (n - k) : k;

	if (r > 1)
	{
		double prod = 1;
		for (integer_type dens=1, nums=(n-r+1); dens<=r; ++dens, ++nums)
		{
			prod *= static_cast<double>( nums ) / dens;
		}
		return static_cast<integer_type>( prod );
	}
	else
	{
		return (r == 1) ? n : 1;
	}
}

}

#endif // !_BMATH_BINOMIAL_
