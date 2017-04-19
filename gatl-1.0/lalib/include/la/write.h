/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_WRITE_
#define _LA_WRITE_

// The namespace of the basic math library.
namespace la
{

/*******************************************************************************************************
 * Write to the stream operator.
 *******************************************************************************************************/

// Writes the matrix into the output stream.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t rows, size_t cols>
inline
std::ostream&
operator << (std::ostream &os, const matrix<value_type,rows,cols> &m)
{
	for (size_t r=0; r!=rows; ++r)
	{
		os << "[";
		for (size_t c=0; c!=cols; ++c)
		{
			os << ((c > 0) ? ", " : " ") << m(r,c);
		}
		os << " ] ";
	}
	return os;
}

}

#endif // !_LA_WRITE_
