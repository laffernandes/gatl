/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_VECTOR_
#define _GA_CONFORMAL_VECTOR_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * Vector function implementations.
 *******************************************************************************************************/

// Initializes a multivector representation of a vector using the given coordinates expressed in the base space.
template<typename multivector_type>
inline
multivector_type
vector(const real_t *coordinates)
{
	multivector_type result;
	_private::vector<typename multivector_type::store_t,multivector_type::model_t::origin_point_bitmap,multivector_type::model_t::infinity_point_bitmap>::run( result.data(), coordinates );
	return result;
}

// Initializes a multivector representation of a vector using the given coordinates expressed in the base space.
template<typename multivector_type>
inline
multivector_type
vector(const real_t &coordinate1, ...)
{
	typedef typename multivector_type::model_t model_t;
	typedef typename ga::_private::take_grade<1,typename multivector_type::store_t>::result store_t;
	
	static const size_t size = store_t::size - ((ga::_private::is_stored<model_t::origin_point_bitmap,store_t>::result) ? 1 : 0) - ((ga::_private::is_stored<model_t::infinity_point_bitmap,store_t>::result) ? 1 : 0);

	// Read input coordinates.
	va_list marker;
	va_start( marker, coordinate1 );

	real_t coordinates[size];
	
	coordinates[0] = coordinate1;
	for (index_t i=1; i<size; ++i)
	{
		coordinates[i] = va_arg( marker, real_t );
	}

	va_end( marker );

	// Load input coordinates into resulting multivector.
	return vector<multivector_type>( coordinates );
}

}

}

#endif // !_GA_CONFORMAL_VECTOR_
