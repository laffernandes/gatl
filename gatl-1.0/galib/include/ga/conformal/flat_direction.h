/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_FLAT_DIRECTION_
#define _GA_CONFORMAL_FLAT_DIRECTION_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for flat_direction() function.
#define flat_direction_return_t(flat_type) \
	ga::multivector<flat_type::model_t,ga::flat_direction_return<flat_type::model_t,flat_type::store_t>::store_t>

// Return type for flat_direction() function.
template<typename model, typename store>
struct flat_direction_return
{
	// Store type.
	typedef typename lcont_return<model,ga::store<model::infinity_point_bitmap>,store>::store_t store_t;
};

/*******************************************************************************************************
 * Direction function implementations.
 *******************************************************************************************************/

// Returns the direction parameter of a given flat.
template<typename model, typename store>
inline
multivector<model,typename flat_direction_return<model,store>::store_t>
flat_direction(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( ga::_private::largest_grade<store>::result > 0 );
	ga_maybe_assert( is_flat( m, tolerance ), "The input multivector is not a flat." );

	return lcont( -_private::consts<model>::ni(), m );
}

}

}

#endif // !_GA_CONFORMAL_FLAT_DIRECTION_
