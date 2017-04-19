/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_GEOMETRIC_PRODUCT_
#define _GA_GEOMETRIC_PRODUCT_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for geometric product.
#define gp_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::gp_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for geometric product.
template<typename model, typename store1, typename store2>
struct gp_return
{
	// Store type.
	typedef typename _private::product_geometric<model,store1,store2>::store_result store_t;
};

// Return type for geometric product (Euclidean metric).
#define gp_em_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::gp_em_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for geometric product (Euclidean metric).
template<typename model, typename store1, typename store2>
struct gp_em_return
{
	// Store type.
	typedef typename _private::product_geometric<_private::euclidean_model,store1,store2>::store_result store_t;
};

/*******************************************************************************************************
 * Geometric product having two multivectors.
 *******************************************************************************************************/

// Geometric product of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename gp_return<model,store1,store2>::store_t>
gp(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename gp_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<model,store1,store2,typename gp_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

// Geometric product (Euclidean metric) of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename gp_em_return<model,store1,store2>::store_t>
gp_em(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename gp_em_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<_private::euclidean_model,store1,store2,typename gp_em_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

/*******************************************************************************************************
 * Geometric product having a scalar value and a multivector.
 *******************************************************************************************************/

// Geometric product of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename gp_return<model,store_scalar,store2>::store_t>
gp(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename gp_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<model,store_scalar,store2,typename gp_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Geometric product (Euclidean metric) of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename gp_em_return<model,store_scalar,store2>::store_t>
gp_em(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename gp_em_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<_private::euclidean_model,store_scalar,store2,typename gp_em_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Geometric product of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename gp_return<model,store1,store_scalar>::store_t>
gp(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename gp_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<model,store1,store_scalar,typename gp_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

// Geometric product (Euclidean metric) of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename gp_em_return<model,store1,store_scalar>::store_t>
gp_em(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename gp_em_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<_private::euclidean_model,store1,store_scalar,typename gp_em_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

/*******************************************************************************************************
 * Geometric product having two scalar values.
 *******************************************************************************************************/

// Geometric product of a scalar value with another scalar value.
inline
real_t
gp(const real_t &scalar1, const real_t &scalar2)
{
	return scalar1 * scalar2;
}

// Geometric product (Euclidean metric) of a scalar value with another scalar value.
inline
real_t
gp_em(const real_t &scalar1, const real_t &scalar2)
{
	return scalar1 * scalar2;
}

/*******************************************************************************************************
 * Multiplication operator overloads.
 *******************************************************************************************************/

// Geometric product of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename gp_return<model,store1,store2>::store_t>
operator * (const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	return gp( m1, m2 );
}

// Geometric product of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename gp_return<model,store_scalar,store2>::store_t>
operator * (const real_t &scalar, const multivector<model,store2> &m)
{
	return gp( scalar, m );
}

// Geometric product of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename gp_return<model,store1,store_scalar>::store_t>
operator * (const multivector<model,store1> &m, const real_t &scalar)
{
	return gp( m, scalar );
}

}

#endif // !_GA_GEOMETRIC_PRODUCT_
