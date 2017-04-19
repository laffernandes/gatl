/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_ABS_
#define _LA_ABS_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using std::abs;

/*******************************************************************************************************
 * Absolute function implementations.
 *******************************************************************************************************/

// Creates a new matrix with the absolute value of each cell of the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,rows,cols>
abs(const matrix<value_type,rows,cols> &m)
{
	matrix<value_type,rows,cols> result;
	for (size_t i=0; i!=m.size; ++i)
	{
		result[i] = abs( m[i] );
	}
	return result;
}

}

#endif // !_LA_ABS_
