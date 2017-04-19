/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_POINT_
#define _GA_CONFORMAL_POINT_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * Point function implementations.
 *******************************************************************************************************/

// Initializes a multivector representation of a point using the given coordinates expressed in the base space.
template<typename multivector_type>
inline
multivector_type
point(const real_t *coordinates)
{
	typedef typename multivector_type::model_t model_t;
	typedef typename ga::_private::take_grade<1,typename multivector_type::store_t>::result store_t;

	static const size_t size = store_t::size - ((ga::_private::is_stored<model_t::origin_point_bitmap,store_t>::result) ? 1 : 0) - ((ga::_private::is_stored<model_t::infinity_point_bitmap,store_t>::result) ? 1 : 0);
	
	real_t sqr = 0;
	for (size_t i=0; i<size; ++i)
	{
		sqr += (coordinates[i] * coordinates[i]);
	}

	multivector_type result;
	_private::point<typename multivector_type::store_t,model_t::origin_point_bitmap,model_t::infinity_point_bitmap>::run( result.data(), coordinates, static_cast<real_t>( 0.5 ) * sqr );
	return result;
}

// Initializes a multivector representation of a point using the given coordinates expressed in the base space.
template<typename multivector_type>
inline
multivector_type
point(const real_t &coordinate1, ...)
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
	return point<multivector_type>( coordinates );
}

}

}

#endif // !_GA_CONFORMAL_POINT_
