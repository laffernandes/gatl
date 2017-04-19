/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_DELTA_PRODUCT_
#define _GA_DELTA_PRODUCT_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for delta() function.
#define delta_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::delta_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for delta() function.
template<typename model, typename store1, typename store2>
struct delta_return
{
	// Store type.
	typedef typename gp_return<model,store1,store2>::store_t store_t;
};

// Return type for delta_em() function.
#define delta_em_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::delta_em_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for delta_em() function.
template<typename model, typename store1, typename store2>
struct delta_em_return
{
	// Store type.
	typedef typename gp_em_return<model,store1,store2>::store_t store_t;
};

/*******************************************************************************************************
 * Delta product having two multivectors.
 *******************************************************************************************************/

// Delta product of a specialized multivector with another specialized multivector. The delta product can be interpreted as the symmetric difference operation on subspaces.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename delta_return<model,store1,store2>::store_t>
delta(const multivector<model,store1> &m1, const multivector<model,store2> &m2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return take_largest_grade( gp( m1, m2 ), tolerance );
}

// Delta product (Euclidean metric) of a specialized multivector with another specialized multivector.  The delta product can be interpreted as the symmetric difference operation on subspaces.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename delta_em_return<model,store1,store2>::store_t>
delta_em(const multivector<model,store1> &m1, const multivector<model,store2> &m2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return take_largest_grade( gp_em( m1, m2 ), tolerance );
}

/*******************************************************************************************************
 * Delta product having a scalar value and a multivector.
 *******************************************************************************************************/

// Delta product of a scalar value with a specialized multivector.  The delta product can be interpreted as the symmetric difference operation on subspaces.
template<typename model, typename store2>
inline
multivector<model,typename delta_return<model,store_scalar,store2>::store_t>
delta(const real_t &scalar, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return take_largest_grade( gp( scalar, m ), tolerance );
}

// Delta product (Euclidean metric) of a scalar value with a specialized multivector.  The delta product can be interpreted as the symmetric difference operation on subspaces.
template<typename model, typename store2>
inline
multivector<model,typename delta_em_return<model,store_scalar,store2>::store_t>
delta_em(const real_t &scalar, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return take_largest_grade( gp_em( scalar, m ), tolerance );
}

// Delta product of a specialized multivector with a scalar value.  The delta product can be interpreted as the symmetric difference operation on subspaces.
template<typename model, typename store1>
inline
multivector<model,typename delta_return<model,store1,store_scalar>::store_t>
delta(const multivector<model,store1> &m, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return take_largest_grade( gp( m, scalar ), tolerance );
}

// Delta product (Euclidean metric) of a specialized multivector with a scalar value.  The delta product can be interpreted as the symmetric difference operation on subspaces.
template<typename model, typename store1>
inline
multivector<model,typename delta_em_return<model,store1,store_scalar>::store_t>
delta_em(const multivector<model,store1> &m, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return take_largest_grade( gp_em( m, scalar ), tolerance );
}

/*******************************************************************************************************
 * Delta product having two scalar values.
 *******************************************************************************************************/

// Delta product of a scalar value with another scalar value.  The delta product can be interpreted as the symmetric difference operation on subspaces.
inline
real_t
delta(const real_t &scalar1, const real_t &scalar2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (scalar1 * scalar2);
}

// Delta product (Euclidean metric) of a scalar value with another scalar value.  The delta product can be interpreted as the symmetric difference operation on subspaces.
inline
real_t
delta_em(const real_t &scalar1, const real_t &scalar2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (scalar1 * scalar2);
}

}

#endif // !_GA_DELTA_PRODUCT_
