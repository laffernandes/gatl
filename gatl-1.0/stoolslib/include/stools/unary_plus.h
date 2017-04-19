/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _STOOLS_UNARY_PLUS_
#define _STOOLS_UNARY_PLUS_

// The namespace of the static tools library.
namespace stools
{

/*******************************************************************************************************
 * Unary plus operation.
 *******************************************************************************************************/

// Returns the given static array.
template<typename data_type, size_t count>
inline
array<data_type,count>
operator + (const array<data_type,count> &array1)
{
	return array1;
}

}

#endif // !_STOOLS_UNARY_PLUS_
