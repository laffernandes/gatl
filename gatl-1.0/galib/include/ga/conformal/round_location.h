/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_ROUND_LOCATION_
#define _GA_CONFORMAL_ROUND_LOCATION_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for round_location() function.
#define round_location_return_t(round_type) \
	ga::multivector<round_type::model_t,ga::round_location_return<round_type::model_t,round_type::store_t>::store_t>

// Return type for round_location() function.
template<typename model, typename store>
struct round_location_return
{
	// Store type.
	typedef typename igp_return<model,store,typename lcont_return<model,ga::store<model::infinity_point_bitmap>,store>::store_t>::store_t store_t;
};

/*******************************************************************************************************
 * Location function implementations.
 *******************************************************************************************************/

// Returns the location parameter of a given round.
template<typename model, typename store>
inline
multivector<model,typename round_location_return<model,store>::store_t>
round_location(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( ga::_private::largest_grade<store>::result > 0 );
	ga_maybe_assert( is_round( m, tolerance ), "The input multivector is not a round." );

	return gp( m, inverse( lcont( -_private::consts<model>::ni(), m ), tolerance ) );
}

}

}

#endif // !_GA_CONFORMAL_ROUND_LOCATION_
