/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_HOMOGENEOUS_TRANSLATION_
#define _GA_HOMOGENEOUS_TRANSLATION_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the homogeneous model.
namespace homogeneous
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for translate() function.
#define translate_return_t(vector_type,flat_type) \
	ga::multivector<flat_type::model_t,ga::translate_return<flat_type::model_t,flat_type::store_t,vector_type::store_t>::store_t>

// Return type for translate() function.
template<typename model, typename store_vector, typename store>
struct translate_return
{
	// Store type.
	typedef typename plus_return<model,store,typename op_return<model,store_vector,typename lcont_return<model,ga::store<model::origin_vector_bitmap>,store>::store_t>::store_t>::store_t store_t;
};

/*******************************************************************************************************
 * Translate function implementations.
 *******************************************************************************************************/

// Translate the given k-flat to a given direction.
template<typename model, typename store_vector, typename store>
inline
multivector<model,typename translate_return<model,store_vector,store>::store_t>
translate(const multivector<model,store_vector> &t, const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( ga::_private::largest_grade<store_vector>::result > 0 );
	ga_static_assert( ga::_private::largest_grade<store>::result > 0 );
	ga_maybe_assert( (grade( t, tolerance ) == 1) && (!is_proper_flat( t, tolerance )), "The input translation is not a direction vector." );

	return m + op( t, lcont( _private::consts<model>::ie0(), m ) );
}

}

}

#endif // !_GA_HOMOGENEOUS_TRANSLATION_
