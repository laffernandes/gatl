/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_MULTIPLICATION_
#define _LA_MULTIPLICATION_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Multiplication/assignment operation implementations.
 *******************************************************************************************************/

// Multiply the given value to each cell of the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,rows,cols>& operator *= (matrix<value_type,rows,cols> &m, const value_type &value)
{
	for (size_t i=0; i!=m.size; ++i)
	{
		m[i] *= value;
	}
	return m;
}

/*******************************************************************************************************
 * Multiplication operation implementations.
 *******************************************************************************************************/

// Returns the resulting matrix from the multiplication of a given matrix and a given value.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,rows,cols> operator * (const matrix<value_type,rows,cols> &m, const value_type &value)
{
	matrix<value_type,rows,cols> result;
	for (size_t i=0; i!=result.size; ++i)
	{
		result[i] = m[i] * value;
	}
	return result;
}

// Returns the resulting matrix from the multiplication of a given value and a given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,rows,cols> operator * (const value_type &value, const matrix<value_type,rows,cols> &m)
{
	matrix<value_type,rows,cols> result;
	for (size_t i=0; i!=result.size; ++i)
	{
		result[i] = value * m[i];
	}
	return result;
}

// Returns the resulting matrix from the multiplication of two given matrices.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type1, typename value_type2, size_t rows1, size_t same, size_t cols2>
inline
matrix<value_type1,rows1,cols2> operator * (const matrix<value_type1,rows1,same> &m1, const matrix<value_type2,same,cols2> &m2)
{
	matrix<value_type1,rows1,cols2> result( null_matrix );
	for (size_t r=0; r!=rows1; ++r)
	{
		for (size_t c=0; c!=cols2; ++c)
		{
			for (size_t s=0; s!=same; ++s)
			{
				result(r,c) += m1(r,s) * m2(s,c);
			}
		}
	}
	return result;
}

}

#endif // !_LA_MULTIPLICATION_
