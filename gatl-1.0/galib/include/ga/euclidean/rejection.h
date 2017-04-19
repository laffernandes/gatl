/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_EUCLIDEAN_REJECTION_
#define _GA_EUCLIDEAN_REJECTION_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the Euclidean vector space model.
namespace euclidean
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for reject() function.
#define reject_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::reject_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for reject() function.
template<typename model, typename store1, typename store2>
struct reject_return
{
	// Store type.
	typedef typename minus_return<model,store1,typename project_return<model,store1,store2>::store_t>::store_t store_t;
};

/*******************************************************************************************************
 * Rejection operation having two multivectors.
 *******************************************************************************************************/

// Rejection of a subspace by another subspace.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename reject_return<model,store1,store2>::store_t>
reject(const multivector<model,store1> &m1, const multivector<model,store2> &m2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return m1 - project( m1, m2, tolerance );
}

/*******************************************************************************************************
 * Rejection operation having a scalar value and a multivector.
 *******************************************************************************************************/

// Rejection of a subspace by another subspace.
template<typename model, typename store2>
inline
multivector<model,typename reject_return<model,store_scalar,store2>::store_t>
reject(const real_t &scalar, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return scalar - project( scalar, m, tolerance );
}

// Rejection of a subspace by another subspace.
template<typename model, typename store1>
inline
multivector<model,typename reject_return<model,store1,store_scalar>::store_t>
reject(const multivector<model,store1> &m, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return m - project( m, scalar, tolerance );
}

/*******************************************************************************************************
 * Rejection operation having two scalar values.
 *******************************************************************************************************/

// Rejection of a scalar value by another scalar value.
template<typename model>
inline
multivector<model,store_none>
reject(const real_t &scalar1, const real_t &scalar2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return multivector<model,store_none>();
}

}

}

#endif // !_GA_EUCLIDEAN_REJECTION_
