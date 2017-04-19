/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_PIVOT_
#define _LA_PIVOT_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Pivot function implementations.
 *******************************************************************************************************/

// Pivot on matrix elements and returns the column index of the pivot element given a row index.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t size>
inline
int pivot(matrix<value_type,size,size> &m, const size_t &row, const value_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	size_t k = row;
	value_type temp, bigger = abs( m(row,row) );

	for (size_t r=(row+1); r!=size; ++r)
	{
		if (bigger < (temp = abs( m(r,row) )))
		{
			k = r;
			bigger = temp;
		}
	}

	if (bigger < tolerance)
	{
		return -1;
	}

	if (k != row)
	{
		for (size_t c=0; c!=size; ++c)
		{
			std::swap( m(k,c), m(row,c) );
		}

		return k;
	}

	return 0;
}

}

#endif // !_LA_PIVOT_
