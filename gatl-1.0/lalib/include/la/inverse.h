/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_INVERSE_
#define _LA_INVERSE_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * la::singular_matrix_error class definition.
 *******************************************************************************************************/

// Singular matrix error definition.
class singular_matrix_error : public std::runtime_error
{
public:

	// Class constructor.
	singular_matrix_error() : std::runtime_error( "Singular matrix." )
	{
	}
};

/*******************************************************************************************************
 * Inverse function implementations.
 *******************************************************************************************************/

// Creates a new matrix that is the inverse of the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type>
inline
matrix<real_type,1,1>
inverse(const matrix<real_type,1,1> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	if (is_zero( m(0,0), tolerance ))
	{
		throw singular_matrix_error();
	}

	matrix<real_type,1,1> result( static_cast<real_type>( 1 ) / m(0,0) );
	return result;
}

// Creates a new matrix that is the inverse of the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type>
inline
matrix<real_type,2,2>
inverse(const matrix<real_type,2,2> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	const real_type &det = la::determinant( m, tolerance );
	if (is_zero( det, tolerance ))
	{
		throw singular_matrix_error();
	}

	const real_type &reciprocal_det = static_cast<real_type>( 1 ) / det;
	matrix<real_type,2,2> result;

	result(0,0) =  reciprocal_det * m(1,1); result(0,1) = -reciprocal_det * m(0,1);
	result(1,0) = -reciprocal_det * m(1,0); result(1,1) =  reciprocal_det * m(0,0);

	return result;
}

// Creates a new matrix that is the inverse of the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t size>
inline
matrix<real_type,size,size>
inverse(const matrix<real_type,size,size> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	int pivot_col;
	real_type aux;
	matrix<real_type,size,size> result( identity_matrix ), copy( m );

	for (size_t k=0, k_line=0; k!=size; ++k, ++k_line)
	{
		if ((pivot_col = pivot( copy, k, tolerance )) == -1)
		{
			throw singular_matrix_error();
		}

		if (pivot_col != 0)
		{
			for (size_t i=0; i!=size; ++i)
			{
				aux = result(k_line,i);
				result(k_line,i) = result(pivot_col,i);
				result(pivot_col,i) = aux;
			}
		}

		aux = copy(k_line,k);

		for (size_t j=0; j!=size; ++j)
		{
			copy(k_line,j) /= aux;
			result(k_line,j) /= aux;
		}
		
		for (size_t i=0, line=0; i!=size; ++i, ++line)
		{
			if (i != k)
			{
				aux = copy(line,k);

				for (size_t j=0; j!=size; ++j)
				{
					copy(line,j) -= aux * copy(k_line,j);
					result(line,j) -= aux * result(k_line,j);
				}
			}
		}
	}

	return result;
}

}

#endif // !_LA_INVERSE_
