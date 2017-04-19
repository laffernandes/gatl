/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_FLAT_LOCATION_
#define _GA_CONFORMAL_FLAT_LOCATION_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for flat_location() function.
#define flat_location_return_t(flat_type) \
	ga::multivector<flat_type::model_t,ga::flat_location_return<flat_type::model_t,flat_type::store_t>::store_t>

// Return type for flat_location() function.
template<typename model, typename store>
struct flat_location_return
{
	// Store type.
	typedef typename igp_return<model,typename lcont_return<model,ga::store<model::origin_point_bitmap>,store>::store_t,store>::store_t store_t;
};

/*******************************************************************************************************
 * Location function implementations.
 *******************************************************************************************************/

// Returns the location parameter of a given flat.
template<typename model, typename store>
inline
multivector<model,typename flat_location_return<model,store>::store_t>
flat_location(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( ga::_private::largest_grade<store>::result > 0 );
	ga_maybe_assert( is_flat( m, tolerance ), "The input multivector is not a flat." );

	return gp( lcont( _private::consts<model>::no(), m ), inverse( m, tolerance ) );
}

}

}

#endif // !_GA_CONFORMAL_FLAT_LOCATION_
