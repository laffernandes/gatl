/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_MODEL_
#define _GA_CONFORMAL_MODEL_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * ga::conformal::model<base_space_dims,origin_point,infinity_point> struct definition.
 *******************************************************************************************************/

// Conformal space definition.
template<size_t base_space_dims, index_t origin_point, index_t infinity_point>
struct model : public ga::model<base_space_dims+2>
{
	// Specifies the bitmap of the basis vector interpreted as the point at origin.
	static const bitmap_t origin_point_bitmap = (1 << origin_point);

	// Specifies the bitmap of the basis vector interpreted as the point at infinity.
	static const bitmap_t infinity_point_bitmap = (1 << infinity_point);

	// Specifies the index of the basis vector interpreted as the point at origin.
	static const index_t origin_point_index = origin_point;

	// Specifies the index of the basis vector interpreted as the point at infinity.
	static const index_t infinity_point_index = infinity_point;

	// Assumed metric for a given pair of basis vectors.
	template<index_t basis_vector1, index_t basis_vector2>
	struct metric
	{
		// Specifies the result value for basis_vector1 . basis_vector2.
		static const int_t result =
			((basis_vector1 == basis_vector2) && (basis_vector1 != origin_point) && (basis_vector1 != infinity_point)) ? 1 // ei . ei = 1
			: ((basis_vector1 == origin_point) && (basis_vector2 == infinity_point)) ? -1                                  // no . ni = -1
			: ((basis_vector1 == infinity_point) && (basis_vector2 == origin_point)) ? -1                                  // ni . no = -1
			: 0;                                                                                                           // otherwise 0
	};
};

}

}

#endif // !_GA_CONFORMAL_MODEL_
