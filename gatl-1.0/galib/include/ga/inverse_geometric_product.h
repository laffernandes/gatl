/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_IGEOMETRIC_PRODUCT_
#define _GA_IGEOMETRIC_PRODUCT_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for inverse geometric product.
#define igp_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::igp_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for inverse geometric product.
template<typename model, typename store1, typename store2>
struct igp_return
{
	// Store type.
	typedef typename gp_return<model,store1,store2>::store_t store_t;
};

// Return type for inverse geometric product (Euclidean metric).
#define igp_em_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::igp_em_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for inverse geometric product (Euclidean metric).
template<typename model, typename store1, typename store2>
struct igp_em_return
{
	// Store type.
	typedef typename gp_em_return<model,store1,store2>::store_t store_t;
};

/*******************************************************************************************************
 * Inverse geometric product having two multivectors.
 *******************************************************************************************************/

// Inverse geometric product of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename igp_return<model,store1,store2>::store_t>
igp(const multivector<model,store1> &m1, const multivector<model,store2> &m2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return gp( m1, inverse( m2, tolerance ) );
}

// Inverse geometric product (Euclidean metric) of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename igp_em_return<model,store1,store2>::store_t>
igp_em(const multivector<model,store1> &m1, const multivector<model,store2> &m2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return gp_em( m1, inverse_em( m2, tolerance ) );
}

/*******************************************************************************************************
 * Inverse geometric product having a scalar value and a multivector.
 *******************************************************************************************************/

// Inverse geometric product of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename igp_return<model,store_scalar,store2>::store_t>
igp(const real_t &scalar, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return gp( scalar, inverse( m, tolerance ) );
}

// Inverse geometric product (Euclidean metric) of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename igp_em_return<model,store_scalar,store2>::store_t>
igp_em(const real_t &scalar, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return gp_em( scalar, inverse_em( m, tolerance ) );
}

// Inverse geometric product of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename igp_return<model,store1,store_scalar>::store_t>
igp(const multivector<model,store1> &m, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return gp( m, inverse( scalar, tolerance ) );
}

// Inverse geometric product (Euclidean metric) of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename igp_em_return<model,store1,store_scalar>::store_t>
igp_em(const multivector<model,store1> &m, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return gp_em( m, inverse_em( scalar, tolerance ) );
}

/*******************************************************************************************************
 * Inverse geometric product having two scalar values.
 *******************************************************************************************************/

// Inverse geometric product of a scalar value with another scalar value.
inline
real_t
igp(const real_t &scalar1, const real_t &scalar2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( !is_zero( scalar2, tolerance ), "The input multivector is not invertible." );

	return scalar1 / scalar2;
}

// Inverse geometric product (Euclidean metric) of a scalar value with another scalar value.
inline
real_t
igp_em(const real_t &scalar1, const real_t &scalar2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( !is_zero( scalar2, tolerance ), "The input multivector is not invertible." );

	return scalar1 / scalar2;
}

}

#endif // !_GA_IGEOMETRIC_PRODUCT_
