/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_EUCLIDEAN_MODEL_
#define _GA_EUCLIDEAN_MODEL_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the Euclidean vector space model.
namespace euclidean
{

/*******************************************************************************************************
 * ga::euclidean::model<base_space_dims> struct definition.
 *******************************************************************************************************/

// Euclidean vector space space definition.
template<size_t base_space_dims>
struct model : public ga::model<base_space_dims>
{
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

#endif // !_GA_EUCLIDEAN_MODEL_
