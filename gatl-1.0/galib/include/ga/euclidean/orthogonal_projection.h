/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_EUCLIDEAN_ORTHOGONAL_PROJECTION_
#define _GA_EUCLIDEAN_ORTHOGONAL_PROJECTION_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the Euclidean vector space model.
namespace euclidean
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for project() function.
#define project_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::project_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for project() function.
template<typename model, typename store1, typename store2>
struct project_return
{
	// Store type.
	typedef typename lcont_return<model,typename lcont_return<model,store1,store2>::store_t,store2>::store_t store_t;
};

/*******************************************************************************************************
 * Orthogonal projection operation having two multivectors.
 *******************************************************************************************************/

// Orthogonal projection of a subspace ontho another subspace.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename project_return<model,store1,store2>::store_t>
project(const multivector<model,store1> &m1, const multivector<model,store2> &m2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	/* IMPLEMENTATION ISSUES
	 *
	 * Here, we compute the projection of a blade A ontho another blade B by using two left
	 * contractions, as pointed out in Section 3.6.
	 * 
	 *           P = lcont( lcont( A, inverse( B ) ), B )
	 *
	 * However, we can do so usign a left contraction and a geometric product (Section 6.4):
	 *
	 *           P = gp( lcont( A, B ), inverse( B ) )
	 *
	 * The geometric product is invertible, and this ofen helps to simplify expressions. On
	 * the other hand, the contraction helps remind us about subspaces taken out of other
	 * subspaces. Also, the multiverctor resulting from contraction is more compat in terms
	 * of storage.
	 */

	return lcont( lcont( m1, inverse( m2, tolerance ) ), m2 );
}

/*******************************************************************************************************
 * Orthogonal projection operation having a scalar value and a multivector.
 *******************************************************************************************************/

// Orthogonal projection of a subspace ontho another subspace.
template<typename model, typename store2>
inline
multivector<model,typename project_return<model,store_scalar,store2>::store_t>
project(const real_t &scalar, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return lcont( lcont( scalar, inverse( m, tolerance ) ), m );
}

// Orthogonal projection of a subspace ontho another subspace.
template<typename model, typename store1>
inline
multivector<model,typename project_return<model,store1,store_scalar>::store_t>
project(const multivector<model,store1> &m, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return lcont( lcont( m, inverse( scalar, tolerance ) ), scalar );
}

/*******************************************************************************************************
 * Orthogonal projection operation having two scalar values.
 *******************************************************************************************************/

// Orthogonal projection of a scalar value onto another scalar value.
inline
real_t
project(const real_t &scalar1, const real_t &scalar2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return scalar1;
}

}

}

#endif // !_GA_EUCLIDEAN_ORTHOGONAL_PROJECTION_
