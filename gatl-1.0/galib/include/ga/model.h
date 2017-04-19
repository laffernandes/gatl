/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_MODEL_
#define _GA_MODEL_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * ga::model<space_dims> struct definition.
 *******************************************************************************************************/

// Space definition.
template<size_t space_dims>
struct model
{
	// Specifies the number of vectors on the basis.
	static const size_t basis_vectors_count = space_dims;

	// Specifies the number of basis blades. It is given by 2^{space_dims}.
	static const size_t basis_blades_count = (1 << space_dims);
};

/*******************************************************************************************************
 * ga::basis_vector<model,index> struct definition.
 *******************************************************************************************************/

// Specifies some attributes of a basis vector on the basis.
template<typename model, index_t index>
struct basis_vector
{
	// Specifies the bitmap representation of this basis vector.
	static const bitmap_t bitmap = (1 << index);
	
	// Specifies the name of this basis vector. This property must initialize by the user.
	static const name_t name;
};

// A shortcut macro for basis vector name initialization.
#define ga_basis_vector(model,index) \
	template<> const ga::name_t ga::basis_vector<model,(index)>::name

}

#endif // !_GA_MODEL_
