/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _STOOLS_ADDITION_
#define _STOOLS_ADDITION_

// The namespace of the static tools library.
namespace stools
{

/*******************************************************************************************************
 * Addition operation.
 *******************************************************************************************************/

// Addition of two static arrays.
template<typename data_type, size_t count>
inline
array<data_type,count>
operator + (const array<data_type,count> &array1, const array<data_type,count> &array2)
{
	array<data_type,count> result;
	for (size_t i=0; i!=count; ++i)
	{
		result[i] = array1[i] + array2[i];
	}
	return result;
}

// Addition of a static array with a scalar value.
template<typename data_type, size_t count>
inline
array<data_type,count>
operator + (const array<data_type,count> &array1, const data_type &value)
{
	array<data_type,count> result;
	for (size_t i=0; i!=count; ++i)
	{
		result[i] = array1[i] + value;
	}
	return result;
}

// Addition of a scalar value with a static array.
template<typename data_type, size_t count>
inline
array<data_type,count>
operator + (const data_type &value, const array<data_type,count> &array2)
{
	array<data_type,count> result;
	for (size_t i=0; i!=count; ++i)
	{
		result[i] = value + array2[i];
	}
	return result;
}

}

#endif // !_STOOLS_ADDITION_
