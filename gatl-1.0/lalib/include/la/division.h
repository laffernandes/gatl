/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_DIVISION_
#define _LA_DIVISION_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Division/assignment operation implementations.
 *******************************************************************************************************/

// Divide each cell of the given matrix by the given value.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t rows, size_t cols>
inline
matrix<real_type,rows,cols>& operator /= (matrix<real_type,rows,cols> &m, const real_type &value)
{
	return (m *= (static_cast<real_type>( 1 ) / value));
}

/*******************************************************************************************************
 * Division operation implementations.
 *******************************************************************************************************/

// Returns the resulting matrix from the division of a given matrix and a given value.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t rows, size_t cols>
inline
matrix<real_type,rows,cols> operator / (const matrix<real_type,rows,cols> &m, const real_type &value)
{
	return m * (static_cast<real_type>( 1 ) / value);
}

// Returns the resulting matrix from the division of a given value and a given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t rows, size_t cols>
inline
matrix<real_type,rows,cols> operator / (const real_type &value, const matrix<real_type,rows,cols> &m)
{
	return (static_cast<real_type>( 1 ) / value) * m;
}

// Returns the resulting matrix from the division of two given matrices.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t rows1, size_t same, size_t cols2>
inline
matrix<real_type,rows1,cols2> operator / (const matrix<real_type,rows1,same> &m1, const matrix<real_type,same,cols2> &m2)
{
	return m1 * inverse( m2 );
}

}

#endif // !_LA_DIVISION_
