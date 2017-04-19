/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_SMALLEST_GRADE_
#define _GA_PRIVATE_SMALLEST_GRADE_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::smallest_grade<store> struct definition.
 *******************************************************************************************************/

// Returns the smallest grade stored by a given store struct. This struct is for internal use of smallest_grade<store>.
template<typename store>
struct _smallest_grade
{
	// The query result.
	static const int result = (_smallest_grade<typename store::next>::result < bit_count<store::bitmap>::result) ? _smallest_grade<typename store::next>::result : bit_count<store::bitmap>::result;
};

// Specialization of _smallest_grade<store> for store equal to store_none. This struct is for internal use of smallest_grade<store>.
template<>
struct _smallest_grade<store_none>
{
	// The end of the list was reached.
	static const int result = (sizeof( bitmap_t ) * 8) + 1;
};

// Returns the smallest grade stored by a given store struct.
template<typename store>
struct smallest_grade
{
	// The query result.
	static const int result = _smallest_grade<store>::result;
};

// Specialization of smallest_grade<store> for store equal to store_none.
template<>
struct smallest_grade<store_none>
{
	// The query result for null multivectors.
	static const int result = 0;
};

}

}

#endif // !_GA_PRIVATE_SMALLEST_GRADE_
