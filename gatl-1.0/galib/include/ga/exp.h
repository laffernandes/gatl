/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_EXP_
#define _GA_EXP_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for exp() function.
#define exp_return_t(multivector_type) \
	ga::multivector<multivector_type::model_t,ga::exp_return<multivector_type::model_t,multivector_type::store_t>::store_t>

// Return type for exp() function.
template<typename model, typename store>
struct exp_return
{
	// Store type.
	typedef typename _private::merge_stores<store_scalar,store>::result store_t; 
};

// Return type for exp_em() function.
#define exp_em_return_t(multivector_type) \
	ga::multivector<multivector_type::model_t,ga::exp_em_return<multivector_type::model_t,multivector_type::store_t>::store_t>

// Return type for exp_em() function.
template<typename model, typename store>
struct exp_em_return
{
	// Store type.
	typedef typename _private::merge_stores<store_scalar,store>::result store_t; 
};

/*******************************************************************************************************
 * Exponential function implementations.
 *******************************************************************************************************/

// The exponential of a given multivector.
template<typename model, typename store>
inline
multivector<model,typename exp_return<model,store>::store_t>
exp(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	const multivector<model,typename gp_return<model,store,store>::store_t> &signed_alpha2_mv = gp( m, m );

	// If the square of the given multivector is a scalar value, the exponential can be computed using standard trigonometric of hyperbolic function.
	if (is_scalar( signed_alpha2_mv, tolerance ))
	{
		real_t signed_alpha2;
		assign<false>( signed_alpha2, signed_alpha2_mv, tolerance );

		// A^2 = 0
		if (is_zero( signed_alpha2, tolerance ))
		{
			return (1 + m);
		}

		real_t alpha = sqrt( abs( signed_alpha2 ) );

		// A^2 = +(alpha^2)
		if (signed_alpha2 > 0)
		{
			return (cosh( alpha ) + (m * (sinh( alpha ) / alpha)));
		}

		// A^2 = -(alpha^2)
		return (cos( alpha ) + (m * (sin( alpha ) / alpha)));
	}
	// Otherwise, we use a polynomial expansion.
	else
	{
		ga_always_assert( false, "ga::exp() function is not implemented for general multivectors." );

		multivector<model,typename exp_return<model,store>::store_t> dummy;
		dummy = multivector<model,store_none>();
		return dummy;
	}
}

// The exponential of a given multivector (Euclidean metric).
template<typename model, typename store>
inline
multivector<model,typename exp_em_return<model,store>::store_t>
exp_em(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	const multivector<model,typename gp_em_return<model,store,store>::store_t> &signed_alpha2_mv = gp_em( m, m );

	// If the square of the given multivector is a scalar value, the exponential can be computed using standard trigonometric of hyperbolic function.
	if (is_scalar( signed_alpha2_mv, tolerance ))
	{
		real_t signed_alpha2;
		assign<false>( signed_alpha2, signed_alpha2_mv, tolerance );

		// A^2 = 0
		if (is_zero( signed_alpha2, tolerance ))
		{
			return (1 + m);
		}

		real_t alpha = sqrt( abs( signed_alpha2 ) );

		// A^2 = +(alpha^2)
		if (signed_alpha2 > 0)
		{
			return (cosh( alpha ) + (m * (sinh( alpha ) / alpha)));
		}

		// A^2 = -(alpha^2)
		return (cos( alpha ) + (m * (sin( alpha ) / alpha)));
	}
	// Otherwise, we use a polynomial expansion.
	else
	{
		ga_always_assert( false, "ga::exp_em() function is not implemented for general multivectors." );

		multivector<model,typename exp_return<model,store>::store_t> dummy;
		dummy = multivector<model,store_none>();
		return dummy;
	}
}

// The exponential of a given null multivector.
template<typename model>
inline
multivector<model,typename exp_return<model,store_none>::store_t>
exp(const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	multivector<model,store_scalar> one = { { { 1 } } };
	return one;
}

// The exponential of a given null multivector (Euclidean metric).
template<typename model>
inline
multivector<model,typename exp_em_return<model,store_none>::store_t>
exp_em(const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	multivector<model,store_scalar> one = { { { 1 } } };
	return one;
}

// The exponential of a given scalar value.
template<typename model>
inline
multivector<model,typename exp_return<model,store_scalar>::store_t>
exp(const multivector<model,store_scalar> &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	multivector<model,store_scalar> result = { { { exp( scalar[0] ) } } };
	return result;
}

// The exponential of a given scalar value (Euclidean metric).
template<typename model>
inline
multivector<model,typename exp_em_return<model,store_scalar>::store_t>
exp_em(const multivector<model,store_scalar> &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	multivector<model,store_scalar> result = { { { exp( scalar[0] ) } } };
	return result;
}

}

#endif // !_GA_EXP_
