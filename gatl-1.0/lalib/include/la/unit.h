/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_UNIT_
#define _LA_UNIT_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Unit function implementations.
 *******************************************************************************************************/

// Computes an unit vector for a given column matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t size>
inline
matrix<real_type,size,1>
unit(const matrix<real_type,size,1> &vector)
{
	return vector / norm( vector );
}

// Computes an unit vector for a given row matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t size>
inline
matrix<real_type,1,size>
unit(const matrix<real_type,1,size> &vector)
{
	return vector / norm( vector );
}

// Computes an unit vector for a given value.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type>
inline
matrix<real_type,1,1>
unit(const matrix<real_type,1,1> &value)
{
	return value / norm( value );
}

}

#endif // !_LA_UNIT_
