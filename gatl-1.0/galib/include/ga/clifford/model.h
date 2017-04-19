/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CLIFFORD_MODEL_
#define _GA_CLIFFORD_MODEL_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the Clifford algebras of signatures [p,q].
namespace clifford
{

/*******************************************************************************************************
 * ga::clifford::model<p,q> struct definition.
 *******************************************************************************************************/

// Clifford algebra of real spaces. Here, p+q is the spatial dimensions, of which 'p' basis vectors have a positive square and 'q' basis vectors have a negative square.
template<size_t p, size_t q>
struct model : public ga::model<p+q>
{
	// Assumed metric for a given pair of basis vectors.
	template<index_t basis_vector1, index_t basis_vector2>
	struct metric
	{
		// Specifies the result value for basis_vector1 . basis_vector2.
		static const int_t result =
			((basis_vector1 == basis_vector2) && (basis_vector1 < p)) ? 1          // ei . ei = +1
			: ((basis_vector1 == basis_vector2) && (basis_vector1 < (p + q))) ? -1 // ei . ei = -1
			: 0;                                                                   // otherwise 0
	};
};

}

}

#endif // !_GA_HOMOGENEOUS_MODEL_
