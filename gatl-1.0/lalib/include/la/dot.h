/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_DOT_
#define _LA_DOT_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Dot (inner) product implementations.
 *******************************************************************************************************/

// Returns the dot product of two given column matrices.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t size>
inline
value_type
dot(const matrix<value_type,size,1> &vector1, const matrix<value_type,size,1> &vector2)
{
	return _private::dot( vector1, vector2 );
}

// Returns the dot product of two given row matrices.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t size>
inline
value_type
dot(const matrix<value_type,1,size> &vector1, const matrix<value_type,1,size> &vector2)
{
	return _private::dot( vector1, vector2 );
}

// Returns the dot product of a given column and a given row matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t size>
inline
value_type
dot(const matrix<value_type,size,1> &vector1, const matrix<value_type,1,size> &vector2)
{
	return _private::dot( vector1, vector2 );
}

// Returns the dot product of a given row and a given column matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t size>
inline
value_type
dot(const matrix<value_type,1,size> &vector1, const matrix<value_type,size,1> &vector2)
{
	return _private::dot( vector1, vector2 );
}

// Returns the dot product of two given value.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type>
inline
value_type
dot(const matrix<value_type,1,1> &value1, const matrix<value_type,1,1> &value2)
{
	return value1[0] * value2[0];
}

}

#endif // !_LA_ABS_
