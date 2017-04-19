/*
 * Copyright (C) 2010 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_STDNORMCDF_
#define _BMATH_STDNORMCDF_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Standard normal cumulative distribution function implementation.
 *******************************************************************************************************/

// Univariate standard normal cumulative distribution function.
template<typename real_type>
inline
real_type
stdnormcdf(const real_type &x)
{
	return static_cast<real_type>( 0.5 ) * (static_cast<real_type>( 1 ) + erf( x / sqrt( static_cast<real_type>( 2 ) ) ));
}

}

#endif // !_BMATH_STDNORMCDF_
