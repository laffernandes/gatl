/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_SCALAR_PRODUCT_
#define _GA_SCALAR_PRODUCT_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for scalar product.
#define scp_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::scp_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for scalar product.
template<typename model, typename store1, typename store2>
struct scp_return
{
	// Store type.
	typedef typename _private::take_grade<
			0,
			typename _private::product_geometric<model,store1,store2>::store_result
		>::result store_t;
};

// Return type for scalar product (Euclidean metric).
#define scp_em_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::scp_em_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for scalar product (Euclidean metric).
template<typename model, typename store1, typename store2>
struct scp_em_return
{
	// Store type.
	typedef typename _private::take_grade<
			0,
			typename _private::product_geometric<_private::euclidean_model,store1,store2>::store_result
		>::result store_t;
};

/*******************************************************************************************************
 * Scalar product having two multivectors.
 *******************************************************************************************************/

// Scalar product of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename scp_return<model,store1,store2>::store_t>
scp(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename scp_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<model,store1,store2,typename scp_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

// Scalar product (Euclidean metric) of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename scp_em_return<model,store1,store2>::store_t>
scp_em(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename scp_em_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<_private::euclidean_model,store1,store2,typename scp_em_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

/*******************************************************************************************************
 * Scalar product having a scalar value and a multivector.
 *******************************************************************************************************/

// Scalar product of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename scp_return<model,store_scalar,store2>::store_t>
scp(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename scp_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<model,store_scalar,store2,typename scp_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Scalar product (Euclidean metric) of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename scp_em_return<model,store_scalar,store2>::store_t>
scp_em(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename scp_em_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<_private::euclidean_model,store_scalar,store2,typename scp_em_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Scalar product of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename scp_return<model,store1,store_scalar>::store_t>
scp(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename scp_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<model,store1,store_scalar,typename scp_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

// Scalar product (Euclidean metric) of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename scp_em_return<model,store1,store_scalar>::store_t>
scp_em(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename scp_em_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<_private::euclidean_model,store1,store_scalar,typename scp_em_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

/*******************************************************************************************************
 * Scalar product having two scalar values.
 *******************************************************************************************************/

// Scalar product of a scalar value with another scalar value.
inline
real_t
scp(const real_t &scalar1, const real_t &scalar2)
{
	return scalar1 * scalar2;
}

// Scalar product (Euclidean metric) of a scalar value with another scalar value.
inline
real_t
scp_em(const real_t &scalar1, const real_t &scalar2)
{
	return scalar1 * scalar2;
}

/*******************************************************************************************************
 * Modulus operator overload.
 *******************************************************************************************************/

// Scalar product of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename scp_return<model,store1,store2>::store_t>
operator % (const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	return scp( m1, m2 );
}

// Scalar product of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename scp_return<model,store_scalar,store2>::store_t>
operator % (const real_t &scalar, const multivector<model,store2> &m)
{
	return scp( scalar, m );
}

// Scalar product of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename scp_return<model,store1,store_scalar>::store_t>
operator % (const multivector<model,store1> &m, const real_t &scalar)
{
	return scp( m, scalar );
}

/* We cannot redefine the meaning of operators when applied to built-in data types.
// Scalar product of a scalar value with another scalar value.
inline
real_t
operator % (const real_t &scalar1, const real_t &scalar2)
{
	return scp( scalar1, scalar2 );
}
*/

}

#endif // !_GA_SCALAR_PRODUCT_
