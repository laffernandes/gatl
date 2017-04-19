/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_LEFT_CONTRACTION_
#define _GA_LEFT_CONTRACTION_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for left contraction.
#define lcont_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::lcont_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for left contraction.
template<typename model, typename store1, typename store2>
struct lcont_return
{
	// Store type.
	typedef typename _private::product_left_contraction<model,store1,store2>::store_result store_t;
};

// Return type for left contraction (Euclidean metric).
#define lcont_em_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::lcont_em_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for left contraction (Euclidean metric).
template<typename model, typename store1, typename store2>
struct lcont_em_return
{
	// Store type.
	typedef typename _private::product_left_contraction<_private::euclidean_model,store1,store2>::store_result store_t;
};

/*******************************************************************************************************
 * Left contraction having two multivectors.
 *******************************************************************************************************/

// Left contraction of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename lcont_return<model,store1,store2>::store_t>
lcont(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename lcont_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_left_contraction_run<model,store1,store2,typename lcont_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

// Left contraction (Euclidean metric) of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename lcont_em_return<model,store1,store2>::store_t>
lcont_em(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename lcont_em_return<model,store1,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_left_contraction_run<_private::euclidean_model,store1,store2,typename lcont_em_return<model,store1,store2>::store_t>::run( result.data(), m1.data(), m2.data() );
	}
	return result;
}

/*******************************************************************************************************
 * Left contraction having a scalar value and a multivector.
 *******************************************************************************************************/

// Left contraction of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename lcont_return<model,store_scalar,store2>::store_t>
lcont(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename lcont_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_left_contraction_run<model,store_scalar,store2,typename lcont_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Left contraction (Euclidean metric) of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename lcont_em_return<model,store_scalar,store2>::store_t>
lcont_em(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename lcont_em_return<model,store_scalar,store2>::store_t> result;
	if (result.size > 0)
	{
		_private::product_left_contraction_run<_private::euclidean_model,store_scalar,store2,typename lcont_em_return<model,store_scalar,store2>::store_t>::run( result.data(), &scalar, m.data() );
	}
	return result;
}

// Left contraction of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename lcont_return<model,store1,store_scalar>::store_t>
lcont(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename lcont_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_left_contraction_run<model,store1,store_scalar,typename lcont_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

// Left contraction (Euclidean metric) of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename lcont_em_return<model,store1,store_scalar>::store_t>
lcont_em(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename lcont_em_return<model,store1,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::product_left_contraction_run<_private::euclidean_model,store1,store_scalar,typename lcont_em_return<model,store1,store_scalar>::store_t>::run( result.data(), m.data(), &scalar );
	}
	return result;
}

/*******************************************************************************************************
 * Left contraction having two scalar values.
 *******************************************************************************************************/

// Left contraction of a scalar value with another scalar value.
inline
real_t
lcont(const real_t &scalar1, const real_t &scalar2)
{
	return scalar1 * scalar2;
}

// Left contraction (Euclidean metric) of a scalar value with another scalar value.
inline
real_t
lcont_em(const real_t &scalar1, const real_t &scalar2)
{
	return scalar1 * scalar2;
}

/*******************************************************************************************************
 * Left shift operator overloads.
 *******************************************************************************************************/

// Left contraction of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename lcont_return<model,store1,store2>::store_t>
operator << (const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	return lcont( m1, m2 );
}

// Left contraction of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename lcont_return<model,store_scalar,store2>::store_t>
operator << (const real_t &scalar, const multivector<model,store2> &m)
{
	return lcont( scalar, m );
}

// Left contraction of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename lcont_return<model,store1,store_scalar>::store_t>
operator << (const multivector<model,store1> &m, const real_t &scalar)
{
	return lcont( m, scalar );
}

/*We cannot redefine the meaning of operators when applied to built-in data types.
// Left contraction of a scalar value with another scalar value.
inline
real_t
operator << (const real_t &scalar1, const real_t &scalar2)
{
	return lcont( scalar1, scalar2 );
}
*/

}

#endif // !_GA_LEFT_CONTRACTION_
