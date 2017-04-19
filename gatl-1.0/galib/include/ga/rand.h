/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_RAND_
#define _GA_RAND_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Random multivector generator implementations.
 *******************************************************************************************************/

// Generates a pseudorandom multivector with coefficients in [min,max] range.
template<typename multivector_type>
inline
multivector_type
rand_multivector(const real_t &min, const real_t &max)
{
	multivector_type result;
	for (size_t i=0; i<result.size; ++i)
	{
		result[i] = bmath::rand_range( min, max );
	}
	return result;
}

// Generates a pseudorandom scalar value in [min,max] range.
template<>
inline
real_t
rand_multivector<real_t>(const real_t &min, const real_t &max)
{
	return bmath::rand_range( min, max );
}

}

#endif // !_GA_RAND_
