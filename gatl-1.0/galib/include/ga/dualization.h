/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_DUALIZATION_
#define _GA_DUALIZATION_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for dual() function, relative to the pseudoscalar of the total space.
#define dual_return_t(multivector_type) \
	ga::multivector<multivector_type::model_t,ga::dual_return<multivector_type::model_t,multivector_type::store_t>::store_t>

// Return type for dual() function, relative to the pseudoscalar of the total space.
template<typename model, typename store>
struct dual_return
{
	// Store type.
	typedef typename lcont_return<model,store,typename store_pseudoscalar<model>::store_type>::store_t store_t;
};

// Return type for dual_em() function (Euclidean metric), relative to the pseudoscalar of the total space.
#define dual_em_return_t(multivector_type) \
	ga::multivector<multivector_type::model_t,ga::dual_em_return<multivector_type::model_t,multivector_type::store_t>::store_t>

// Return type for dual_em() function (Euclidean metric), relative to the pseudoscalar of the total space.
template<typename model, typename store>
struct dual_em_return
{
	// Store type.
	typedef typename lcont_em_return<model,store,typename store_pseudoscalar<model>::store_type>::store_t store_t;
};

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for dual() function, relative to a given pseudoscalar.
#define dual2_return_t(multivector_type,pseudoscalar_type) \
	ga::multivector<multivector_type::model_t,ga::dual2_return<multivector_type::model_t,multivector_type::store_t,pseudoscalar_type::store_t>::store_t>

// Return type for dual() function, relative to a given pseudoscalar.
template<typename model, typename store, typename store_pseudoscalar>
struct dual2_return
{
	// Store type.
	typedef typename lcont_return<model,store,store_pseudoscalar>::store_t store_t;
};

// Return type for dual_em() function (Euclidean metric), relative to a given pseudoscalar.
#define dual2_em_return_t(multivector_type,pseudoscalar_type) \
	ga::multivector<multivector_type::model_t,ga::dual2_em_return<multivector_type::model_t,multivector_type::store_t,pseudoscalar_type::store_t>::store_t>

// Return type for dual_em() function (Euclidean metric), relative to a given pseudoscalar.
template<typename model, typename store, typename store_pseudoscalar>
struct dual2_em_return
{
	// Store type.
	typedef typename lcont_em_return<model,store,store_pseudoscalar>::store_t store_t;
};

/*******************************************************************************************************
 * Dualizarion operation, relative to the pseudoscalar of the total space.
 *******************************************************************************************************/

// Returns the dual of a given specialized multivector, relative to the pseudoscalar of the total space.
template<typename model, typename store>
inline
multivector<model,typename dual_return<model,store>::store_t>
dual(const multivector<model,store> &m)
{
	return lcont( m, _private::consts<model>::iI() );
}

// Returns the dual (Euclidean metric) of a given specialized multivector, relative to the pseudoscalar of the total space.
template<typename model, typename store>
inline
multivector<model,typename dual_em_return<model,store>::store_t>
dual_em(const multivector<model,store> &m)
{
	return lcont_em( m, _private::consts_em<model>::iI() );
}

// Returns the dual of a given scalar value, relative to the pseudoscalar of the total space.
template<typename model>
inline
multivector<model,typename dual_return<model,store_scalar>::store_t>
dual(const real_t &scalar)
{
	return lcont( scalar, _private::consts<model>::iI() );
}

// Returns the dual (Euclidean metric) of a given scalar value, relative to the pseudoscalar of the total space.
template<typename model>
inline
multivector<model,typename dual_em_return<model,store_scalar>::store_t>
dual_em(const real_t &scalar)
{
	return lcont_em( scalar, _private::consts_em<model>::iI() );
}

/*******************************************************************************************************
 * Dualizarion operation, relative to a given pseudoscalar.
 *******************************************************************************************************/

// Returns the dual of a given specialized multivector, relative to a given pseudoscalar.
template<typename model, typename store, typename store_pseudoscalar>
inline
multivector<model,typename dual2_return<model,store,store_pseudoscalar>::store_t>
dual(const multivector<model,store> &m, const multivector<model,store_pseudoscalar> &I, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return lcont( m, inverse( I, tolerance ) );
}

// Returns the dual (Euclidean metric) of a given specialized multivector, relative to a given pseudoscalar.
template<typename model, typename store, typename store_pseudoscalar>
inline
multivector<model,typename dual2_em_return<model,store,store_pseudoscalar>::store_t>
dual_em(const multivector<model,store> &m, const multivector<model,store_pseudoscalar> &I, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return lcont_em( m, inverse_em( I, tolerance ) );
}

// Returns the dual of a given scalar value, relative to a given pseudoscalar.
template<typename model, typename store_pseudoscalar>
inline
multivector<model,typename dual2_return<model,store_scalar,store_pseudoscalar>::store_t>
dual(const real_t &scalar, const multivector<model,store_pseudoscalar> &I, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return lcont( scalar, inverse( I, tolerance ) );
}

// Returns the dual (Euclidean metric) of a given scalar value, relative to a given pseudoscalar.
template<typename model, typename store_pseudoscalar>
inline
multivector<model,typename dual2_em_return<model,store_scalar,store_pseudoscalar>::store_t>
dual_em(const real_t &scalar, const multivector<model,store_pseudoscalar> &I, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return lcont_em( scalar, inverse_em( I, tolerance ) );
}

}

#endif // !_GA_DUALIZATION_
