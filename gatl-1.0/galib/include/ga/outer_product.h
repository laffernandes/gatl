/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_OUTER_PRODUCT_
#define _GA_OUTER_PRODUCT_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for outer product.
#define op_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::op_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for outer product.
template<typename model, typename store1, typename store2>
struct op_return
{
	// Store type.
	typedef typename _private::product_outer<model,store1,store2>::store_result store_t;
};

/*******************************************************************************************************
 * Outer product having two multivectors.
 *******************************************************************************************************/

// Outer product of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename op_return<model,store1,store2>::store_t>
op(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename op_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_outer_run<model,store1,store2,typename op_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

/*******************************************************************************************************
 * Outer product having a scalar value and a multivector.
 *******************************************************************************************************/

// Outer product of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename op_return<model,store_scalar,store2>::store_t>
op(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename op_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_outer_run<model,store_scalar,store2,typename op_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Outer product of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename op_return<model,store1,store_scalar>::store_t>
op(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename op_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_outer_run<model,store1,store_scalar,typename op_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

/*******************************************************************************************************
 * Outer product having two scalar values.
 *******************************************************************************************************/

// Outer product of a scalar value with another scalar value.
inline
real_t
op(const real_t &scalar1, const real_t &scalar2)
{
	return scalar1 * scalar2;
}

/*******************************************************************************************************
 * Bitwise exclusive OR operator overloads.
 *******************************************************************************************************/

// Outer product of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename op_return<model,store1,store2>::store_t>
operator ^ (const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	return op( m1, m2 );
}

// Outer product of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename op_return<model,store_scalar,store2>::store_t>
operator ^ (const real_t &scalar, const multivector<model,store2> &m)
{
	return op( scalar, m );
}

// Outer product of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename op_return<model,store1,store_scalar>::store_t>
operator ^ (const multivector<model,store1> &m, const real_t &scalar)
{
	return op( m, scalar );
}

/* We cannot redefine the meaning of operators when applied to built-in data types.
// Outer product of a scalar value with another scalar value.
inline
real_t
operator ^ (const real_t &scalar1, const real_t &scalar2)
{
	return op( scalar1, scalar2 );
}
*/

}

#endif // !_GA_OUTER_PRODUCT_
