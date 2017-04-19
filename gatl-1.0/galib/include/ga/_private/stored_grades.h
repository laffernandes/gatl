/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_STORED_GRADES_
#define _GA_PRIVATE_STORED_GRADES_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{
	
/*******************************************************************************************************
 * ga::_private::stored_grades<store> struct definition.
 *******************************************************************************************************/

// The base struct for retrieve the grade bitmap from the given store.
template<typename store>
struct stored_grades
{
	// Specifies the grade bitmap.
	static const bitmap_t result = ((1 << bit_count<store::bitmap>::result) | stored_grades<typename store::next>::result);
};

// Specialization of stored_grades<store> fro store equal to store_none.
template<>
struct stored_grades<store_none>
{
	// Specifies the end of the loop.
	static const bitmap_t result = 0;
};


}

}

#endif // !_GA_PRIVATE_STORED_GRADES_
