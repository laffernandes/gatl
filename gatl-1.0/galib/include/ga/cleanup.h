/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CLEANUP_
#define _GA_CLEANUP_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Cleanup function implementation.
 *******************************************************************************************************/

// Cleanup round-off errors at the "zero" coefficients.
template<typename model, typename store>
inline
multivector<model,store>
cleanup(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	multivector<model,store> result;

	for (size_t i=0; i!=m.size; ++i)
	{
		result[i] = (is_zero( m[i], tolerance )) ? static_cast<real_t>( 0 ) : m[i];
	}

	return result;
}

// Cleanup round-off errors at the "zero" coefficients.
inline
real_t
cleanup(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return (is_zero( scalar, tolerance )) ? static_cast<real_t>( 0 ) : scalar;
}

}

#endif // !_GA_CLEANUP_
