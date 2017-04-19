/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_BASIS_VECTORS_
#define _GA_PRIVATE_BASIS_VECTORS_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::basis_vectors<store> struct definition.
 *******************************************************************************************************/

// The base struct for retrieve the basis vectors that make a given blade.
template<typename store>
struct basis_vectors
{
	// The resulting bitmap identification of the basis vectors found.
	static const bitmap_t result = (store::bitmap | basis_vectors<typename store::next>::result);
};

// Specialization of basis_vectors<store> for store equal to store_none.
template<>
struct basis_vectors<store_none>
{
	// Loop's end.
	static const bitmap_t result = 0;
};

}

}

#endif // !_GA_PRIVATE_BASIS_VECTORS_
