/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_TANGENT_SIZE2_
#define _GA_CONFORMAL_TANGENT_SIZE2_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * Squared size function implementations.
 *******************************************************************************************************/

// Returns the squared size parameter of a given tangent (notice that it is always zero).
template<typename model, typename store>
inline
real_t
tangent_size2(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( ga::_private::largest_grade<store>::result > 0 );
	ga_maybe_assert( is_tangent( m, tolerance ), "The input multivector is not a tangent." );

	return 0;
}

}

}

#endif // !_GA_CONFORMAL_TANGENT_SIZE2_
