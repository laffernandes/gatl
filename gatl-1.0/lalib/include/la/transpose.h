/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_TRANSPOSE_
#define _LA_TRANSPOSE_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Matrix transpose function implementations.
 *******************************************************************************************************/

// Creates a new matrix as the transpose of the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,cols,rows>
transpose(const matrix<value_type,rows,cols> &m)
{
	matrix<value_type,cols,rows> result;
	for (size_t c=0; c!=cols; ++c)
	{
		for (size_t r=0; r!=rows; ++r)
		{
			result(c,r) = m(r,c);
		}
	}
	return result;
}

}

#endif // !_LA_TRANSPOSE_
