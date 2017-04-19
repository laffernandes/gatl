/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_SUBTRACTION_
#define _LA_SUBTRACTION_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Subtraction/assignment operation implementations.
 *******************************************************************************************************/

// Subtract the given value from each cell of the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,rows,cols>& operator -= (matrix<value_type,rows,cols> &m, const value_type &value)
{
	for (size_t i=0; i!=m.size; ++i)
	{
		m[i] -= value;
	}
	return m;
}

// Subtract the matrix at right from the matrix at left, cell-by-cell.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,rows,cols>& operator -= (matrix<value_type,rows,cols> &m1, const matrix<value_type,rows,cols> &m2)
{
	for (size_t i=0; i!=m1.size; ++i)
	{
		m1[i] -= m2[i];
	}
	return m1;
}

/*******************************************************************************************************
 * Subtraction operation implementations.
 *******************************************************************************************************/

// Returns the resulting matrix from the subtraction of a given value from a given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,rows,cols> operator - (const matrix<value_type,rows,cols> &m, const value_type &value)
{
	matrix<value_type,rows,cols> result;
	for (size_t i=0; i!=result.size; ++i)
	{
		result[i] = m[i] - value;
	}
	return result;
}

// Returns the resulting matrix from the subtraction of a given matrix and a given value.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,rows,cols> operator - (const value_type &value, const matrix<value_type,rows,cols> &m)
{
	matrix<value_type,rows,cols> result;
	for (size_t i=0; i!=result.size; ++i)
	{
		result[i] = value - m[i];
	}
	return result;
}

// Returns the resulting matrix from the subtraction of two given matrices.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,rows,cols> operator - (const matrix<value_type,rows,cols> &m1, const matrix<value_type,rows,cols> &m2)
{
	matrix<value_type,rows,cols> result;
	for (size_t i=0; i!=result.size; ++i)
	{
		result[i] = m1[i] - m2[i];
	}
	return result;
}

}

#endif // !_LA_SUBTRACTION_
