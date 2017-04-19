/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_RAND_
#define _BMATH_RAND_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using std::rand;
using std::srand;

/*******************************************************************************************************
 * Random number generators implementations.
 *******************************************************************************************************/

// Generates a pseudorandom number in [min,max] range.
template<typename real_type>
inline
real_type
rand_range(const real_type &min, const real_type &max)
{
	assert( min <= max );
	return ((static_cast<real_type>( rand() ) / static_cast<real_type>( RAND_MAX )) * (max - min)) + min;
}

// Generates a pseudorandom number with normal distribution, usign the Box-Muller approach.
template<typename real_type>
inline
real_type
randn()
{
	static const real_type scalar = static_cast<real_type>( 1 ) / RAND_MAX;
	return sqrt( -2 * log( scalar * rand() ) ) * cos( 2 * btrig::pi_value<real_type>::value() * (scalar * rand()) );
}

}

#endif // !_BMATH_RAND_
