/*
 * Copyright (C) 2010 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_SANDWICH_PRODUCT_
#define _LA_SANDWICH_PRODUCT_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Sandwich product implementations.
 *******************************************************************************************************/

// Returns the resulting scalar value from the sandwich product of a given matrix and a given value.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows>
inline
value_type sandwich_product(const matrix<value_type,rows,1> &m, const value_type &value)
{
	value_type result = m[0] * m[0];
	for (size_t i=1; i!=m.size; ++i)
	{
		result += m[i] * m[i];
	}
	return result * value;
}

// Returns the resulting matrix from the sandwich product of a given value and a given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t cols>
inline
matrix<value_type,1,cols> sandwich_product(const value_type &value, const matrix<value_type,1,cols> &m)
{
	matrix<value_type,1,cols> result;
	const value_type sqr_value = value * value;
	for (size_t i=0; i!=result.size; ++i)
	{
		result[i] = sqr_value * m[i];
	}
	return result;
}

// Returns the resulting matrix from the sandwich product of two given matrices.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type1, typename value_type2, size_t size1, size_t size2>
inline
matrix<value_type1,size1,size1> sandwich_product(const matrix<value_type1,size1,size2> &m1, const matrix<value_type2,size2,size2> &m2)
{
	matrix<value_type1,size1,size2> temp( null_matrix );
	for (size_t r=0; r!=size1; ++r)
	{
		for (size_t c=0; c!=size2; ++c)
		{
			for (size_t s=0; s!=size2; ++s)
			{
				temp(r,c) += m1(r,s) * m2(s,c);
			}
		}
	}
	
	matrix<value_type1,size1,size1> result( null_matrix );
	for (size_t r=0; r!=size1; ++r)
	{
		for (size_t c=0; c!=size1; ++c)
		{
			for (size_t s=0; s!=size2; ++s)
			{
				result(r,c) += temp(r,s) * m1(c,s);
			}
		}
	}
	
	return result;
}

}

#endif // !_LA_SANDWICH_PRODUCT_
