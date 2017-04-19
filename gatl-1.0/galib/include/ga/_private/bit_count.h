/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_BIT_COUNT_
#define _GA_PRIVATE_BIT_COUNT_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::bit_count<bitmap> struct definition.
 *******************************************************************************************************/

// The base struct for count the 1-bits in the bitmap. We use it to compute the grade of a given basis blade bitmap.
template<bitmap_t bitmap>
struct bit_count
{
	static const int result = (bitmap & 1) + bit_count<(bitmap>>1)>::result;
};

// Specialization of bit_count<bitmap> for bitmap equal to zero.
template<>
struct bit_count<0>
{
	static const int result = 0;
};

}

}

#endif // !_GA_PRIVATE_BIT_COUNT_
