/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_HOMOGENEOUS_FLAT_MOMENT_
#define _GA_HOMOGENEOUS_FLAT_MOMENT_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the homogeneous model.
namespace homogeneous
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for flat_moment() function.
#define flat_moment_return_t(flat_type) \
	ga::multivector<flat_type::model_t,ga::flat_moment_return<flat_type::model_t,flat_type::store_t>::store_t>

// Return type for flat_moment() function.
template<typename model, typename store>
struct flat_moment_return
{
	// Store type.
	typedef typename lcont_return<model,ga::store<model::origin_vector_bitmap>,typename op_return<model,ga::store<model::origin_vector_bitmap>,store>::store_t>::store_t store_t; 
};

/*******************************************************************************************************
 * Moment function implementations.
 *******************************************************************************************************/

// Returns the moment parameter of a given k-flat.
template<typename model, typename store>
inline
multivector<model,typename flat_moment_return<model,store>::store_t>
flat_moment(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( ga::_private::largest_grade<store>::result > 0 );
	ga_maybe_assert( is_flat( m, tolerance ), "The input multivector is not a flat." );

	return lcont( _private::consts<model>::ie0(), op( _private::consts<model>::e0(), m ) );
}

}

}

#endif // !_GA_HOMOGENEOUS_FLAT_MOMENT_
