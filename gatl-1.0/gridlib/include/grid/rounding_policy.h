/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GRID_ROUNDING_POLICY_
#define _GRID_ROUNDING_POLICY_

// The namespace of the multidimensional grid library.
namespace grid
{

/*******************************************************************************************************
 * grid::policy_ceil class definition.
 *******************************************************************************************************/

// A rounding policy defined as the standard ceil operation.
struct policy_ceil
{
	// Main function.
	template<typename return_type, typename argument_type>
	static inline
	return_type func(const argument_type &arg)
	{
		return static_cast<return_type>( ceil( arg ) );
	}
};

/*******************************************************************************************************
 * grid::policy_floor class definition.
 *******************************************************************************************************/

// A rounding policy defined as the standard floor operation.
struct policy_floor
{
	// Main function.
	template<typename return_type, typename argument_type>
	static inline
	return_type func(const argument_type &arg)
	{
		return static_cast<return_type>( floor( arg ) );
	}
};

/*******************************************************************************************************
 * grid::policy_round class definition.
 *******************************************************************************************************/

// A rounding policy defined as the standard round operation.
struct policy_round
{
	// Main function.
	template<typename return_type, typename argument_type>
	static inline
	return_type func(const argument_type &arg)
	{
		return static_cast<return_type>( bmath::round( arg ) );
	}
};

/*******************************************************************************************************
 * grid::policy_trunc class definition.
 *******************************************************************************************************/

// A rounding policy defined as the standard truncation operation.
struct policy_trunc
{
	// Main function.
	template<typename return_type, typename argument_type>
	static inline
	return_type func(const argument_type &arg)
	{
		return static_cast<return_type>( arg );
	}
};

}

#endif // !_GRID_ROUNDING_POLICY_
