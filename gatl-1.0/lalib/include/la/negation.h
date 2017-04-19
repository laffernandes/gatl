/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_NEGATION_
#define _LA_NEGATION_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Negation operation.
 *******************************************************************************************************/

// Negation of a matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
matrix<value_type,rows,cols>
operator - (const matrix<value_type,rows,cols> &m)
{
	matrix<value_type,rows,cols> result;
	for (size_t i=0; i!=result.size; ++i)
	{
		result[i] = -m[i];
	}
	return result;
}

}

#endif // !_LA_NEGATION_
