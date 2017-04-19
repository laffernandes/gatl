/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_DOT_PRODUCT_
#define _GA_DOT_PRODUCT_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for dot product.
#define dot_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::dot_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for dot product.
template<typename model, typename store1, typename store2>
struct dot_return
{
	// Store type.
	typedef typename _private::product_dot<model,store1,store2>::store_result store_t;
};

// Return type for dot product (Euclidean metric).
#define dot_em_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::dot_em_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t:

// Return type for dot product (Euclidean metric).
template<typename model, typename store1, typename store2>
struct dot_em_return
{
	// Store type.
	typedef typename _private::product_dot<_private::euclidean_model,store1,store2>::store_result store_t;
};

/*******************************************************************************************************
 * Dot product having two multivectors.
 *******************************************************************************************************/

// Dot product of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename dot_return<model,store1,store2>::store_t>
dot(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename dot_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_dot_run<model,store1,store2,typename dot_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

// Dot product (Euclidean metric) of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename dot_em_return<model,store1,store2>::store_t>
dot_em(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename dot_em_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_dot_run<_private::euclidean_model,store1,store2,typename dot_em_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

/*******************************************************************************************************
 * Dot product having a scalar value and a multivector.
 *******************************************************************************************************/

// Dot product of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename dot_return<model,store_scalar,store2>::store_t>
dot(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename dot_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_dot_run<model,store_scalar,store2,typename dot_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Dot product (Euclidean metric) of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename dot_em_return<model,store_scalar,store2>::store_t>
dot_em(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename dot_em_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_dot_run<_private::euclidean_model,store_scalar,store2,typename dot_em_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Dot product of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename dot_return<model,store1,store_scalar>::store_t>
dot(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename dot_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_dot_run<model,store1,store_scalar,typename dot_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

// Dot product (Euclidean metric) of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename dot_em_return<model,store1,store_scalar>::store_t>
dot_em(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename dot_em_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_dot_run<_private::euclidean_model,store1,store_scalar,typename dot_em_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

/*******************************************************************************************************
 * Dot product having two scalar values.
 *******************************************************************************************************/

// Dot product of a scalar value with another scalar value.
inline
real_t
dot(const real_t &scalar1, const real_t &scalar2)
{
	return (scalar1 * scalar2);
}

// Dot product (Euclidean metric) of a scalar value with another scalar value.
inline
real_t
dot_em(const real_t &scalar1, const real_t &scalar2)
{
	return (scalar1 * scalar2);
}

}

#endif // !_GA_DOT_PRODUCT_
