/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_HOMOGENEOUS_FLAT_UNIT_SUPPORT_POINT_
#define _GA_HOMOGENEOUS_FLAT_UNIT_SUPPORT_POINT_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the homogeneous model.
namespace homogeneous
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for flat_unit_support_point() function.
#define flat_unit_support_point_return_t(flat_type) \
	ga::multivector<flat_type::model_t,ga::flat_unit_support_point_return<flat_type::model_t,flat_type::store_t>::store_t>

// Return type for flat_unit_support_point() function.
template<typename model, typename store>
struct flat_unit_support_point_return
{
	// Store type.
	typedef typename igp_return<model,store,typename flat_direction_return<model,store>::store_t>::store_t store_t;
};

/*******************************************************************************************************
 * Unit support point function implementations.
 *******************************************************************************************************/

// Returns the unit support point parameter of a given k-flat.
template<typename model, typename store>
inline
multivector<model,typename flat_unit_support_point_return<model,store>::store_t>
flat_unit_support_point(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( ga::_private::largest_grade<store>::result > 0 );
	ga_maybe_assert( is_flat( m, tolerance ), "The input multivector is not a flat." );

	return gp( m, inverse( lcont( _private::consts<model>::ie0(), m ), tolerance ) );
}

}

}

#endif // !_GA_HOMOGENEOUS_FLAT_UNIT_SUPPORT_POINT_
