/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_PRIVATE_DOT_
#define _LA_PRIVATE_DOT_

// The namespace of the linear algebra library.
namespace la
{

// A namespace for internal use of the linear algebra library.
namespace _private
{

/*******************************************************************************************************
 * Dot (inner) product implementations.
 *******************************************************************************************************/

// Returns the dot product of two given matrices.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows1, size_t cols1, size_t rows2, size_t cols2>
inline
value_type
dot(const matrix<value_type,rows1,cols1> &matrix1, const matrix<value_type,rows2,cols2> &matrix2)
{
	typedef matrix<value_type,rows1,cols1> matrix1_t;
	typedef matrix<value_type,rows2,cols2> matrix2_t;

	static_assert( matrix1_t::size == matrix2_t::size );

	value_type result = matrix1[0] * matrix2[0];
	for (size_t i=1; i!=matrix1.size; ++i)
	{
		result += matrix1[i] * matrix2[i];
	}
	return result;
}

}

}

#endif // !_LA_PRIVATE_DOT_
