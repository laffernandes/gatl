/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_UNDUALIZATION_
#define _GA_UNDUALIZATION_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for undual() function, relative to the pseudoscalar of the total space.
#define undual_return_t(multivector_type) \
	ga::multivector<multivector_type::model_t,ga::undual_return<multivector_type::model_t,multivector_type::store_t>::store_t>

// Return type for undual() function, relative to the pseudoscalar of the total space.
template<typename model, typename store>
struct undual_return
{
	// Store type.
	typedef typename lcont_return<model,store,typename store_pseudoscalar<model>::store_type>::store_t store_t;
};

// Return type for undual_em() function (Euclidean metric), relative to the pseudoscalar of the total space.
#define undual_em_return_t(multivector_type) \
	ga::multivector<multivector_type::model_t,ga::undual_em_return<multivector_type::model_t,multivector_type::store_t>::store_t>

// Return type for undual_em() function (Euclidean metric), relative to the pseudoscalar of the total space.
template<typename model, typename store>
struct undual_em_return
{
	// Store type.
	typedef typename lcont_em_return<model,store,typename store_pseudoscalar<model>::store_type>::store_t store_t;
};

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for undual() function, relative to a given pseudoscalar.
#define undual2_return_t(multivector_type,pseudoscalar_type) \
	ga::multivector<multivector_type::model_t,ga::undual2_return<multivector_type::model_t,multivector_type::store_t,pseudoscalar_type::store_t>::store_t>

// Return type for undual() function, relative to a given pseudoscalar.
template<typename model, typename store, typename store_pseudoscalar>
struct undual2_return
{
	// Store type.
	typedef typename lcont_return<model,store,store_pseudoscalar>::store_t store_t;
};

// Return type for undual_em() function (Euclidean metric), relative to a given pseudoscalar.
#define undual2_em_return_t(multivector_type,pseudoscalar_type) \
	ga::multivector<multivector_type::model_t,ga::undual2_em_return<multivector_type::model_t,multivector_type::store_t,pseudoscalar_type::store_t>::store_t>

// Return type for undual_em() function (Euclidean metric), relative to a given pseudoscalar.
template<typename model, typename store, typename store_pseudoscalar>
struct undual2_em_return
{
	// Store type.
	typedef typename lcont_em_return<model,store,store_pseudoscalar>::store_t store_t;
};

/*******************************************************************************************************
 * Undualizarion operation, relative to the pseudoscalar of the total space.
 *******************************************************************************************************/

// Returns a specialized multivector from the given dual representation, relative to the pseudoscalar of the total space.
template<typename model, typename store>
inline
multivector<model,typename undual_return<model,store>::store_t>
undual(const multivector<model,store> &dual)
{
	return lcont( dual, _private::consts<model>::I() );
}

// Returns a specialized multivector from the given dual representation (Euclidean metric), relative to the pseudoscalar of the total space.
template<typename model, typename store>
inline
multivector<model,typename undual_em_return<model,store>::store_t>
undual_em(const multivector<model,store> &dual)
{
	return lcont_em( dual, _private::consts_em<model>::I() );
}

// Returns a specialized multivector from the given dual representation, relative to the pseudoscalar of the total space.
template<typename model>
inline
multivector<model,typename undual_return<model,store_scalar>::store_t>
undual(const real_t &dual)
{
	return lcont( dual, _private::consts<model>::I() );
}

// Returns a specialized multivector from the given dual representation (Euclidean metric), relative to the pseudoscalar of the total space.
template<typename model>
inline
multivector<model,typename undual_em_return<model,store_scalar>::store_t>
undual_em(const real_t &dual)
{
	return lcont_em( dual, _private::consts_em<model>::I() );
}

/*******************************************************************************************************
 * Undualizarion operation, relative to a given pseudoscalar.
 *******************************************************************************************************/

// Returns a specialized multivector from the given dual representation, relative to a given pseudoscalar.
template<typename model, typename store, typename store_pseudoscalar>
inline
multivector<model,typename undual2_return<model,store,store_pseudoscalar>::store_t>
undual(const multivector<model,store> &dual, const multivector<model,store_pseudoscalar> &I)
{
	return lcont( dual, I );
}

// Returns a specialized multivector from the given dual representation (Euclidean metric), relative to a given pseudoscalar.
template<typename model, typename store, typename store_pseudoscalar>
inline
multivector<model,typename undual2_em_return<model,store,store_pseudoscalar>::store_t>
undual_em(const multivector<model,store> &dual, const multivector<model,store_pseudoscalar> &I)
{
	return lcont_em( dual, I );
}

// Returns a specialized multivector from the given dual representation, relative to a given pseudoscalar.
template<typename model, typename store_pseudoscalar>
inline
multivector<model,typename undual2_return<model,store_scalar,store_pseudoscalar>::store_t>
undual(const real_t &dual, const multivector<model,store_pseudoscalar> &I)
{
	return lcont( dual, I );
}

// Returns a specialized multivector from the given dual representation (Euclidean metric), relative to a given pseudoscalar.
template<typename model, typename store_pseudoscalar>
inline
multivector<model,typename undual2_em_return<model,store_scalar,store_pseudoscalar>::store_t>
undual_em(const real_t &dual, const multivector<model,store_pseudoscalar> &I)
{
	return lcont_em( dual, I );
}

}

#endif // !_GA_UNDUALIZATION_
