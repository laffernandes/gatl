/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_LARGEST_GRADE_
#define _GA_PRIVATE_LARGEST_GRADE_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::largest_grade<store> struct definition.
 *******************************************************************************************************/

// Returns the largest grade stored by a given store struct.
template<typename store>
struct largest_grade
{
	// The query result.
	static const int result = (largest_grade<typename store::next>::result > bit_count<store::bitmap>::result) ? largest_grade<typename store::next>::result : bit_count<store::bitmap>::result;
};

// Specialization of largest_grade<store> for store equal to store_none.
template<>
struct largest_grade<store_none>
{
	// The end of the list was reached.
	static const int result = 0;
};

}

}

#endif // !_GA_PRIVATE_LARGEST_GRADE_
