/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_TESTS_
#define _LA_TESTS_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Equality operation implementation.
 *******************************************************************************************************/

// Returns whether two given matrices are equal.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
bool
operator == (const matrix<value_type,rows,cols> &m1, const matrix<value_type,rows,cols> &m2)
{
	for (size_t i=0; i!=m1.size; ++i)
	{
		if (m1[i] != m2[i])
		{
			return false;
		}
	}
	return true;
}

/*******************************************************************************************************
 * Inequality operation implementation.
 *******************************************************************************************************/

// Returns whether two given matrices are different.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
bool
operator != (const matrix<value_type,rows,cols> &m1, const matrix<value_type,rows,cols> &m2)
{
	for (size_t i=0; i!=m1.size; ++i)
	{
		if (m1[i] != m2[i])
		{
			return true;
		}
	}
	return false;
}

}

#endif // !_LA_TESTS_
