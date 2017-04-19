/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_HOMOGENEOUS_MODEL_
#define _GA_HOMOGENEOUS_MODEL_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the homogeneous model.
namespace homogeneous
{

/*******************************************************************************************************
 * ga::homogeneous::model<base_space_dims,origin_vector> struct definition.
 *******************************************************************************************************/

// Homogeneous space definition.
template<size_t base_space_dims, index_t origin_vector>
struct model : public ga::model<base_space_dims+1>
{
	// Specifies the bitmap of the basis vector interpreted as the origin of the Euclidean plane.
	static const bitmap_t origin_vector_bitmap = (1 << origin_vector);

	// Specifies the index of the basis vector interpreted as the origin of the Euclidean plane.
	static const index_t origin_vector_index = origin_vector;

	// Assumed metric for a given pair of basis vectors.
	template<index_t basis_vector1, index_t basis_vector2>
	struct metric
	{
		// Specifies the result value for basis_vector1 . basis_vector2.
		static const int_t result =
			(basis_vector1 == basis_vector2) ? 1 // ei . ei = 1
			: 0;                                 // otherwise 0
	};
};

}

}

#endif // !_GA_HOMOGENEOUS_MODEL_
