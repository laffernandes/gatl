/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _STOOLS_NEGATION_
#define _STOOLS_NEGATION_

// The namespace of the static tools library.
namespace stools
{

/*******************************************************************************************************
 * Negation operation.
 *******************************************************************************************************/

// Negation of the given static array.
template<typename data_type, size_t count>
inline
array<data_type,count>
operator - (const array<data_type,count> &array1)
{
	array<data_type,count> result;
	for (size_t i=0; i!=count; ++i)
	{
		result[i] = array1[i];
	}
	return result;
}

}

#endif // !_STOOLS_NEGATION_
