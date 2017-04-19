/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_NORM_
#define _LA_NORM_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Squared norm function implementations.
 *******************************************************************************************************/

// Returns the squared norm of a given column matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t size>
inline
value_type
norm2(const matrix<value_type,size,1> &vector)
{
	return dot( vector, vector );
}

// Returns the squared norm of a given row matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t size>
inline
value_type
norm2(const matrix<value_type,1,size> &vector)
{
	return dot( vector, vector );
}

// Returns the squared norm of a given value.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type>
inline
value_type
norm2(const matrix<value_type,1,1> &value)
{
	return value[0] * value[0];
}

/*******************************************************************************************************
 * Norm function implementations.
 *******************************************************************************************************/

// Returns the norm of a given column matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t size>
inline
real_type
norm(const matrix<real_type,size,1> &vector)
{
	return sqrt( dot( vector, vector ) );
}

// Returns the norm of a given row matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t size>
inline
real_type
norm(const matrix<real_type,1,size> &vector)
{
	return sqrt( dot( vector, vector ) );
}

// Returns the norm of a given value.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type>
inline
real_type
norm(const matrix<real_type,1,1> &value)
{
	return abs( value );
}

}

#endif // !_LA_NORM_
