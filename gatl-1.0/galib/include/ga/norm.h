/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_NORM_
#define _GA_NORM_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for norm2() and norm() functions.
#define norm_return_t(multivector_type) \
	ga::multivector<multivector_type::model_t,ga::norm_return<multivector_type::model_t,multivector_type::store_t>::store_t>

// Return type for norm2() and norm() functions.
template<typename model, typename store>
struct norm_return
{
	// Store type.
	typedef typename scp_return<model,store,store>::store_t store_t;
};

// Return type for norm2_em() and norm_em() functions.
#define norm_em_return_t(multivector_type) \
	ga::multivector<multivector_type::model_t,ga::norm_em_return<multivector_type::model_t,multivector_type::store_t>::store_t>

// Return type for norm2_em() and norm_em() functions.
template<typename model, typename store>
struct norm_em_return
{
	// Store type.
	typedef typename scp_em_return<model,store,store>::store_t store_t;
};

/*******************************************************************************************************
 * Squared reverse norm function implementations.
 *******************************************************************************************************/

// Computes the squared reverse norm of a specialized multivector.
template<typename model, typename store>
inline
multivector<model,typename norm_return<model,store>::store_t>
norm2(const multivector<model,store> &m)
{
	return scp( m, reverse( m ) );
}

// Computes the squared reverse norm of a scalar value.
inline
real_t
norm2(const real_t &scalar)
{
	return (scalar * scalar);
}

/*******************************************************************************************************
 * Reverse norm function implementations.
 *******************************************************************************************************/

// Computes the reverse norm of a specialized multivector.
template<typename model, typename store>
inline
multivector<model,typename norm_return<model,store>::store_t>
norm(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	const multivector<model,typename norm_return<model,store>::store_t> &n2 = norm2( m );
	return sgn( n2, tolerance ) * sqrt( abs( n2, tolerance ), tolerance );
}

// Computes the reverse norm of a scalar value.
inline
real_t
norm(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return abs( scalar );
}

/*******************************************************************************************************
 * Squared Euclidean norm function implementations.
 *******************************************************************************************************/

// Computes the squared Euclidean norm of a specialized multivector.
template<typename model, typename store>
inline
multivector<model,typename norm_em_return<model,store>::store_t>
norm2_em(const multivector<model,store> &m)
{
	return scp_em( m, reverse( m ) );
}

// Computes the squared Euclidean norm of a scalar value.
inline
real_t
norm2_em(const real_t &scalar)
{
	return (scalar * scalar);
}

/*******************************************************************************************************
 * Euclidean norm function implementations.
 *******************************************************************************************************/

// Computes the Euclidean norm of a specialized multivector.
template<typename model, typename store>
inline
multivector<model,typename norm_em_return<model,store>::store_t>
norm_em(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return sqrt( norm2_em( m ), tolerance );
}

// Computes the Euclidean norm of a scalar value.
inline
real_t
norm_em(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return abs( scalar );
}

}

#endif // !_GA_NORM_
