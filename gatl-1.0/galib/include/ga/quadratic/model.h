/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_QUADRATIC_MODEL_
#define _GA_QUADRATIC_MODEL_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the model for quadratic curves (conic sections).
namespace quadratic
{

/*******************************************************************************************************
 * ga::quadratic::model<base_space_dims> struct definition.
 *******************************************************************************************************/

// Vector space for quadratic curvers (conic sections) definition.
template<size_t base_space_dims>
struct model : public ga::model<(((base_space_dims+1)*(base_space_dims+2))>>1)>
{
	// Specifies the bitmap of the basis vector interpreted as the origin.
	static const bitmap_t origin_vector_bitmap = (1 << (base_space_dims + 1));

	// Specifies the index of the basis vector interpreted as the origin.
	static const index_t origin_vector_index = (base_space_dims + 1);

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

#endif // !_GA_QUADRATIC_MODEL_
