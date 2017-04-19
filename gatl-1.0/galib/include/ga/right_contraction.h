/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_RIGHT_CONTRACTION_
#define _GA_RIGHT_CONTRACTION_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for right contraction.
#define rcont_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::rcont_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for right contraction.
template<typename model, typename store1, typename store2>
struct rcont_return
{
	// Store type.
	typedef typename _private::product_right_contraction<model,store1,store2>::store_result store_t;
};

// Return type for right contraction (Euclidean metric).
#define rcont_em_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::rcont_em_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for right contraction (Euclidean metric).
template<typename model, typename store1, typename store2>
struct rcont_em_return
{
	// Store type.
	typedef typename _private::product_right_contraction<_private::euclidean_model,store1,store2>::store_result store_t;
};

/*******************************************************************************************************
 * Right contraction having two multivectors.
 *******************************************************************************************************/

// Right contraction of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename rcont_return<model,store1,store2>::store_t>
rcont(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename rcont_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_right_contraction_run<model,store1,store2,typename rcont_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

// Right contraction (Euclidean metric) of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename rcont_em_return<model,store1,store2>::store_t>
rcont_em(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename rcont_em_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_right_contraction_run<_private::euclidean_model,store1,store2,typename rcont_em_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

/*******************************************************************************************************
 * Right contraction having a scalar value and a multivector.
 *******************************************************************************************************/

// Right contraction of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename rcont_return<model,store_scalar,store2>::store_t>
rcont(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename rcont_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_right_contraction_run<model,store_scalar,store2,typename rcont_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Right contraction (Euclidean metric) of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename rcont_em_return<model,store_scalar,store2>::store_t>
rcont_em(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename rcont_em_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_right_contraction_run<_private::euclidean_model,store_scalar,store2,typename rcont_em_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Right contraction of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename rcont_return<model,store1,store_scalar>::store_t>
rcont(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename rcont_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_right_contraction_run<model,store1,store_scalar,typename rcont_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

// Right contraction (Euclidean metric) of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename rcont_em_return<model,store1,store_scalar>::store_t>
rcont_em(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename rcont_em_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_right_contraction_run<_private::euclidean_model,store1,store_scalar,typename rcont_em_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

/*******************************************************************************************************
 * Right contraction having two scalar values.
 *******************************************************************************************************/

// Right contraction of a scalar values with another scalar value.
inline
real_t
rcont(const real_t &scalar1, const real_t &scalar2)
{
	return scalar1 * scalar2;
}

// Right contraction (Euclidean metric) of a scalar values with another scalar value.
inline
real_t
rcont_em(const real_t &scalar1, const real_t &scalar2)
{
	return scalar1 * scalar2;
}

/*******************************************************************************************************
 * Right shift operator overload.
 *******************************************************************************************************/

// Right contraction of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename rcont_return<model,store1,store2>::store_t>
operator >> (const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	return rcont( m1, m2 );
}

// Right contraction of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename rcont_return<model,store_scalar,store2>::store_t>
operator >> (const real_t &scalar, const multivector<model,store2> &m)
{
	return rcont( scalar, m );
}

// Right contraction of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename rcont_return<model,store1,store_scalar>::store_t>
operator >> (const multivector<model,store1> &m, const real_t &scalar)
{
	return rcont( m, scalar );
}

/*We cannot redefine the meaning of operators when applied to built-in data types.
// Right contraction of a scalar values with another scalar value.
inline
real_t
operator >> (const real_t &scalar1, const real_t &scalar2)
{
	return rcont( scalar1, scalar2 );
}
*/

}

#endif // !_GA_RIGHT_CONTRACTION_
