/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_TANGENT_LOCATION_
#define _GA_CONFORMAL_TANGENT_LOCATION_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for tangent_location() function.
#define tangent_location_return_t(tangent_type) \
	ga::multivector<tangent_type::model_t,ga::tangent_location_return<tangent_type::model_t,tangent_type::store_t>::store_t>

// Return type for tangent_location() function.
template<typename model, typename store>
struct tangent_location_return
{
	// Store type.
	typedef typename igp_return<model,store,typename lcont_return<model,ga::store<model::infinity_point_bitmap>,store>::store_t>::store_t store_t;
};

/*******************************************************************************************************
 * Location function implementations.
 *******************************************************************************************************/

// Returns the location parameter of a given tangent.
template<typename model, typename store>
inline
multivector<model,typename tangent_location_return<model,store>::store_t>
tangent_location(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( ga::_private::largest_grade<store>::result > 0 );
	ga_maybe_assert( is_tangent( m, tolerance ), "The input multivector is not a tangent." );

	return gp( m, inverse( lcont( -_private::consts<model>::ni(), m ), tolerance ) );
}

}

}

#endif // !_GA_CONFORMAL_TANGENT_LOCATION_
