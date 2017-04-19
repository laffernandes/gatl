/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_COMMUTATOR_PRODUCT_
#define _GA_COMMUTATOR_PRODUCT_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for commutator product.
#define cmp_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::cmp_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for commutator product.
template<typename model, typename store1, typename store2>
struct cmp_return
{
	// Store type.
	typedef typename _private::product_geometric<model,store1,store2>::store_result store_t;
};

// Specialization of cmp_return<model,store1,store2> for store1 equal to store_scalar.
template<typename model, typename store2>
struct cmp_return<model,store_scalar,store2>
{
	// Store type.
	typedef store_none store_t;
};

// Specialization of cmp_return<model,store1,store2> for store2 equal to store_scalar.
template<typename model, typename store1>
struct cmp_return<model,store1,store_scalar>
{
	// Store type.
	typedef store_none store_t;
};

// Specialization of cmp_return<model,store1,store2> for store1 and store2 equal to store_scalar.
template<typename model>
struct cmp_return<model,store_scalar,store_scalar>
{
	// Store type.
	typedef store_none store_t;
};

// Return type for commutator product (Euclidean metric).
#define cmp_em_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::cmp_em_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for commutator product (Euclidean metric).
template<typename model, typename store1, typename store2>
struct cmp_em_return
{
	// Store type.
	typedef typename _private::product_geometric<_private::euclidean_model,store1,store2>::store_result store_t;
};

// Specialization of cmp_em_return<model,store1,store2> for store1 equal to store_scalar.
template<typename model, typename store2>
struct cmp_em_return<model,store_scalar,store2>
{
	// Store type.
	typedef store_none store_t;
};

// Specialization of cmp_em_return<model,store1,store2> for store2 equal to store_scalar.
template<typename model, typename store1>
struct cmp_em_return<model,store1,store_scalar>
{
	// Store type.
	typedef store_none store_t;
};

// Specialization of cmp_em_return<model,store1,store2> for store1 and store2 equal to store_scalar.
template<typename model>
struct cmp_em_return<model,store_scalar,store_scalar>
{
	// Store type.
	typedef store_none store_t;
};

/*******************************************************************************************************
 * Commutator product having two multivectors.
 *******************************************************************************************************/

// Commutator product of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename cmp_return<model,store1,store2>::store_t>
cmp(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	return static_cast<real_t>( 0.5 ) * (gp( m1, m2 ) - gp( m2, m1 ));
}

// Commutator product (Euclidean metric) of a specialized multivector with another specialized multivector.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename cmp_em_return<model,store1,store2>::store_t>
cmp_em(const multivector<model,store1> &m1, const multivector<model,store2> &m2)
{
	return static_cast<real_t>( 0.5 ) * (gp_em( m1, m2 ) - gp_em( m2, m1 ));
}

/*******************************************************************************************************
 * Commutator product having a scalar value and a multivector.
 *******************************************************************************************************/

// Commutator product of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,store_none>
cmp(const multivector<model,store_scalar> &scalar, const multivector<model,store2> &m)
{
	return multivector<model,store_none>();
}

// Commutator product of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,store_none>
cmp(const real_t &scalar, const multivector<model,store2> &m)
{
	return multivector<model,store_none>();
}

// Commutator product (Euclidean metric) of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,store_none>
cmp_em(const multivector<model,store_scalar> &scalar, const multivector<model,store2> &m)
{
	return multivector<model,store_none>();
}

// Commutator product (Euclidean metric) of a scalar value with a specialized multivector.
template<typename model, typename store2>
inline
multivector<model,store_none>
cmp_em(const real_t &scalar, const multivector<model,store2> &m)
{
	return multivector<model,store_none>();
}

// Commutator product of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,store_none>
cmp(const multivector<model,store1> &m, const multivector<model,store_scalar> &scalar)
{
	return multivector<model,store_none>();
}

// Commutator product of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,store_none>
cmp(const multivector<model,store1> &m, const real_t &scalar)
{
	return multivector<model,store_none>();
}

// Commutator product (Euclidean metric) of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,store_none>
cmp_em(const multivector<model,store1> &m, const multivector<model,store_scalar> &scalar)
{
	return multivector<model,store_none>();
}

// Commutator product (Euclidean metric) of a specialized multivector with a scalar value.
template<typename model, typename store1>
inline
multivector<model,store_none>
cmp_em(const multivector<model,store1> &m, const real_t &scalar)
{
	return multivector<model,store_none>();
}

/*******************************************************************************************************
 * Commutator product having two scalar values.
 *******************************************************************************************************/

// Commutator product of a scalar value with another scalar value.
template<typename model>
inline
multivector<model,store_none>
cmp(const multivector<model,store_scalar> &scalar1, const multivector<model,store_scalar> &scalar2)
{
	return multivector<model,store_none>();
}

// Commutator product of a scalar value with another scalar value.
template<typename model>
inline
multivector<model,store_none>
cmp(const real_t &scalar1, const real_t &scalar2)
{
	return multivector<model,store_none>();
}

// Commutator product (Euclidean metric) of a scalar value with another scalar value.
template<typename model>
inline
multivector<model,store_none>
cmp_em(const multivector<model,store_scalar> &scalar1, const multivector<model,store_scalar> &scalar2)
{
	return multivector<model,store_none>();
}

// Commutator product (Euclidean metric) of a scalar value with another scalar value.
template<typename model>
inline
multivector<model,store_none>
cmp_em(const real_t &scalar1, const real_t &scalar2)
{
	return multivector<model,store_none>();
}

}

#endif // !_GA_COMMUTATOR_PRODUCT_
