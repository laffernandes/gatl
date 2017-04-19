/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _STOOLS_DIVISION_
#define _STOOLS_DIVISION_

// The namespace of the static tools library.
namespace stools
{

/*******************************************************************************************************
 * Division operation.
 *******************************************************************************************************/

// Division of two static arrays.
template<typename data_type, size_t count>
inline
array<data_type,count>
operator / (const array<data_type,count> &array1, const array<data_type,count> &array2)
{
	array<data_type,count> result;
	for (size_t i=0; i!=count; ++i)
	{
		result[i] = array1[i] / array2[i];
	}
	return result;
}


// Division of a static array by a scalar value.
template<typename data_type, size_t count>
inline
array<data_type,count>
operator / (const array<data_type,count> &array1, const data_type &value)
{
	const data_type scale = static_cast<data_type>( 1 ) / value;

	array<data_type,count> result;
	for (size_t i=0; i!=count; ++i)
	{
		result[i] = array1[i] * scale;
	}
	return result;
}


// Division of a scalar value by a static array.
template<typename data_type, size_t count>
inline
array<data_type,count>
operator / (const data_type &value, const array<data_type,count> &array2)
{
	array<data_type,count> result;
	for (size_t i=0; i!=count; ++i)
	{
		result[i] = value / array2[i];
	}
	return result;
}


}

#endif // !_STOOLS_DIVISION_
