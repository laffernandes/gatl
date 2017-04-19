/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_QUADRATIC_PRIVATE_BASE_SPACE_VECTORS_COUNT_
#define _GA_QUADRATIC_PRIVATE_BASE_SPACE_VECTORS_COUNT_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the model for quadratic curves (conic sections).
namespace quadratic
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::quadratic::_private::base_space_vectors_count<store,e0> struct definition.
 *******************************************************************************************************/

// The base struct for count the number of vectors from the base space stored in the list.
template<typename store, bitmap_t e0>
struct base_space_vectors_count
{
	static const int result = (((ga::_private::bit_count<store::bitmap>::result == 1) && (store::bitmap < e0)) ? 1 : 0) + base_space_vectors_count<typename store::next,e0>::result;
};

// Specialization of base_space_vectors_count<store,e0> for store equal to store_none.
template<bitmap_t e0>
struct base_space_vectors_count<store_none,e0>
{
	static const int result = 0;
};

}

}

}

#endif // !_GA_QUADRATIC_PRIVATE_BASE_SPACE_VECTORS_COUNT_
