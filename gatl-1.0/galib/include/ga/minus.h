/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_MINUS_
#define _GA_MINUS_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for subtraction operation.
#define minus_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::minus_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for subtraction operation.
template<typename model, typename store1, typename store2>
struct minus_return
{
	// Store type.
	typedef typename _private::binary_addivite<_private::subtraction,store1,store2>::store_result store_t;
};

/*******************************************************************************************************
 * Subtraction operation having two multivectors.
 *******************************************************************************************************/

// Subtraction of a specialized multivector from another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename minus_return<model,store1,store2>::store_t>
minus(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	multivector<model,typename minus_return<model,store1,store2>::store_t> result;
	_private::binary_addivite<_private::subtraction,store1,store2>::run( result.data(), m1.data(), m2.data() );
	return result;
}

/*******************************************************************************************************
 * Subtraction operation having a scalar value and a multivector.
 *******************************************************************************************************/

// Subtraction of a specialized multivector from a scalar value.
template<typename model, typename store2>
inline
multivector<model,typename minus_return<model,store_scalar,store2>::store_t>
minus(const real_t &scalar, const multivector<model,store2> &m)
{
	multivector<model,typename minus_return<model,store_scalar,store2>::store_t> result;
	_private::binary_addivite<_private::subtraction,store_scalar,store2>::run( result.data(), &scalar, m.data() );
	return result;
}

// Subtraction of a scalar value from a specialized multivector.
template<typename model, typename store1>
inline
multivector<model,typename minus_return<model,store1,store_scalar>::store_t>
minus(const multivector<model,store1> &m, const real_t &scalar)
{
	multivector<model,typename minus_return<model,store1,store_scalar>::store_t> result;
	_private::binary_addivite<_private::subtraction,store1,store_scalar>::run( result.data(), m.data(), &scalar );
	return result;
}

/*******************************************************************************************************
 * Subtraction operation having two scalar values.
 *******************************************************************************************************/

// Subtraction of a scalar value from another scalar value.
inline
real_t
minus(const real_t &scalar1, const real_t &scalar2)
{
	return scalar1 - scalar2;
}

/*******************************************************************************************************
 * Subtraction operation having null multivectors.
 *******************************************************************************************************/

// Subtraction of a null multivector with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,typename minus_return<model,store_none,store2>::store_t>
minus(const multivector<model,store_none> &zero, const multivector<model,store2> &m)
{
	return -m;
}

// Subtraction of a null multivector with a scalar value.
template<typename model>
inline
multivector<model,typename minus_return<model,store_none,store_scalar>::store_t>
minus(const multivector<model,store_none> &zero, const real_t &scalar)
{
	multivector<model,store_scalar> result = { { { -scalar } } };
	return result;
}

// Subtraction of a specialized multivector with a null multivector.
template<typename model, typename store1>
inline
multivector<model,typename minus_return<model,store1,store_none>::store_t>
minus(const multivector<model,store1> &m, const multivector<model,store_none> &zero)
{
	return m;
}

// Subtraction of a scalar value with a null multivector.
template<typename model>
inline
multivector<model,typename minus_return<model,store_scalar,store_none>::store_t>
minus(const real_t &scalar, const multivector<model,store_none> &zero)
{
	multivector<model,store_scalar> result = { { { scalar } } };
	return result;
}

// Subtraction of a null multivector with another null multivector.
template<typename model>
inline
multivector<model,typename minus_return<model,store_none,store_none>::store_t>
minus(const multivector<model,store_none> &zero1, const multivector<model,store_none> &zero2)
{
	return zero1;
}

/*******************************************************************************************************
 * Subtraction operator overloads.
 *******************************************************************************************************/

// Subtraction of a specialized multivector from another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename minus_return<model,store1,store2>::store_t>
operator - (const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	return minus( m1, m2 );
}

// Subtraction of a specialized multivector from a scalar value.
template<typename model, typename store2>
inline
multivector<model,typename minus_return<model,store_scalar,store2>::store_t>
operator - (const real_t &scalar, const multivector<model,store2> &m)
{
	return minus( scalar, m );
}

// Subtraction of a scalar value from a specialized multivector.
template<typename model, typename store1>
inline
multivector<model,typename minus_return<model,store1,store_scalar>::store_t>
operator - (const multivector<model,store1> &m, const real_t &scalar)
{
	return minus( m, scalar );
}

}

#endif // !_GA_MINUS_
