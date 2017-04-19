/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_TANGENT_DIRECTION_
#define _GA_CONFORMAL_TANGENT_DIRECTION_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for tangent_direction() function.
#define tangent_direction_return_t(tangent_type) \
	ga::multivector<tangent_type::model_t,ga::tangent_direction_return<tangent_type::model_t,tangent_type::store_t>::store_t>

// Return type for tangent_direction() function.
template<typename model, typename store>
struct tangent_direction_return
{
	// Store type.
	typedef typename op_return<model,typename lcont_return<model,ga::store<model::infinity_point_bitmap>,store>::store_t,ga::store<model::infinity_point_bitmap> >::store_t store_t;
};

/*******************************************************************************************************
 * Direction function implementations.
 *******************************************************************************************************/

// Returns the direction parameter of a given tangent.
template<typename model, typename store>
inline
multivector<model,typename tangent_direction_return<model,store>::store_t>
tangent_direction(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( ga::_private::largest_grade<store>::result > 0 );
	ga_maybe_assert( is_tangent( m, tolerance ), "The input multivector is not a tangent." );

	return op( lcont( -_private::consts<model>::ni(), m ), _private::consts<model>::ni() );
}

}

}

#endif // !_GA_CONFORMAL_TANGENT_DIRECTION_
