/*
 * Copyright (C) 2010 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_ERF_
#define _BMATH_ERF_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Error function implementation.
 *******************************************************************************************************/

// Error function associated with the integral of a normal distribution.
template<typename real_type>
inline
real_type
erf(const real_type &x)
{
	if (_finite( x ))
	{
		return (x < static_cast<real_type>( 0 )) ? -gammp( static_cast<real_type>( 0.5 ), x * x ) : gammp( static_cast<real_type>( 0.5 ), x * x );
	}
	else
	{
		return (x < static_cast<real_type>( 0 )) ? static_cast<real_type>( -1 ) : static_cast<real_type>( 1 );
	}
}

}

#endif // !_BMATH_ERF_
