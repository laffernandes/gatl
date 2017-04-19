/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_HESTENES_INNER_PRODUCT_
#define _GA_HESTENES_INNER_PRODUCT_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for Hestenes' inner product.
#define hip_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::hip_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for Hestenes' inner product.
template<typename model, typename store1, typename store2>
struct hip_return
{
	// Store type.
	typedef typename _private::product_hestenes_inner<model,store1,store2>::store_result store_t;
};

// Return type for Hestenes' inner product (Euclidean metric).
#define hip_em_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::hip_em_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for Hestenes' inner product (Euclidean metric).
template<typename model,typename store1,typename store2>
struct hip_em_return
{
	// Store type.
	typedef typename _private::product_hestenes_inner<_private::euclidean_model,store1,store2>::store_result store_t;
};

/*******************************************************************************************************
 * Hestenes' inner product having two multivectors.
 *******************************************************************************************************/

// Hestenes' inner product of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
ga::multivector<model,typename hip_return<model,store1,store2>::store_t>
hip(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename hip_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_hestenes_inner_run<model,store1,store2,typename hip_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

// Hestenes' inner product (Euclidean metric) of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename hip_em_return<model,store1,store2>::store_t>
hip_em(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename hip_em_return<model,store1,store2>::store_t> result;
	if (result.size > 0 )
	{
		_private::product_hestenes_inner_run<_private::euclidean_model,store1,store2,typename hip_em_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

/*******************************************************************************************************
 * Hestenes' inner product having a scalar value and a multivector.
 *******************************************************************************************************/

// Hestenes' inner product of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename hip_return<model,store_scalar,store2>::store_t>
hip(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename hip_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_hestenes_inner_run<model,store_scalar,store2,typename hip_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Hestenes' inner product (Euclidean metric) of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename hip_em_return<model,store_scalar,store2>::store_t>
hip_em(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename hip_em_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0 )
	{
		_private::product_hestenes_inner_run<_private::euclidean_model,store_scalar,store2,typename hip_em_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Hestenes' inner product of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename hip_return<model,store1,store_scalar>::store_t>
hip(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename hip_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_hestenes_inner_run<model,store1,store_scalar,typename hip_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

// Hestenes' inner product (Euclidean metric) of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename hip_em_return<model,store1,store_scalar>::store_t>
hip_em(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename hip_em_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0 )
	{
		_private::product_hestenes_inner_run<_private::euclidean_model,store1,store_scalar,typename hip_em_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

/*******************************************************************************************************
 * Hestenes' inner product having two scalar values.
 *******************************************************************************************************/

// Hestenes' inner product of a scalar value with another scalar value.
template<typename model>
inline
multivector<model,typename hip_return<model,store_scalar,store_scalar>::store_t>
hip(const real_t &scalar1, const real_t &scalar2)
{
	multivector<model,typename hip_return<model,store_scalar,store_scalar>::store_t> result;
	if (result.size > 0 )
	{
		_private::product_hestenes_inner_run<model,store_scalar,store_scalar,typename hip_return<model,store_scalar,store_scalar>::store_t>::run( result.data(), &scalar1, &scalar2 );
	}
	return result;
}

// Hestenes' inner product (Euclidean metric) of a scalar value with another scalar value.
template<typename model>
inline
multivector<model,typename hip_em_return<model,store_scalar,store_scalar>::store_t>
hip_em(const real_t &scalar1, const real_t &scalar2)
{
	multivector<model,typename hip_em_return<model,store_scalar,store_scalar>::store_t> result;
	if (result.size > 0 )
	{
		_private::product_hestenes_inner_run<_private::euclidean_model,store_scalar,store_scalar,typename hip_em_return<model,store_scalar,store_scalar>::store_t>::run( result.data(), &scalar1, &scalar2 );
	}
	return result;
}

}

#endif // !_GA_HESTENES_INNER_PRODUCT_
