/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_UNARY_PLUS_
#define _LA_UNARY_PLUS_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Unary plus operation.
 *******************************************************************************************************/

// Returns the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,rows,cols>
operator + (const matrix<value_type,rows,cols> &m)
{
	return m;
}

}

#endif // !_LA_UNARY_PLUS_
