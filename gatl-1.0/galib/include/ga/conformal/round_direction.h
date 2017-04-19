/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_ROUND_DIRECTION_
#define _GA_CONFORMAL_ROUND_DIRECTION_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for round_direction() function.
#define round_direction_return_t(round_type) \
	ga::multivector<round_type::model_t,ga::round_direction_return<round_type::model_t,round_type::store_t>::store_t>

// Return type for round_direction() function.
template<typename model, typename store>
struct round_direction_return
{
	// Store type.
	typedef typename op_return<model,typename lcont_return<model,ga::store<model::infinity_point_bitmap>,store>::store_t,ga::store<model::infinity_point_bitmap> >::store_t store_t;
};

/*******************************************************************************************************
 * Direction function implementations.
 *******************************************************************************************************/

// Returns the direction parameter of a given round.
template<typename model, typename store>
inline
multivector<model,typename round_direction_return<model,store>::store_t>
round_direction(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( ga::_private::largest_grade<store>::result > 0 );
	ga_maybe_assert( is_round( m, tolerance ), "The input multivector is not a round." );

	return op( lcont( -_private::consts<model>::ni(), m ), _private::consts<model>::ni() );
}

}

}

#endif // !_GA_CONFORMAL_ROUND_DIRECTION_
