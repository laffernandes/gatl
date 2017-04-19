/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_ROUND_
#define _BMATH_ROUND_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Round function implementation.
 *******************************************************************************************************/

// Round function.
template<typename value_type>
inline
value_type
round(const value_type &value)
{
	return (value < static_cast<value_type>( 0 )) ? ceil( value - static_cast<value_type>( 0.5 ) ) : floor( value + static_cast<value_type>( 0.5 ) );
}

}

#endif // !_BMATH_ROUND_
