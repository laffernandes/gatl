/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_ROUND_SIZE2_
#define _GA_CONFORMAL_ROUND_SIZE2_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * Squared size function implementations.
 *******************************************************************************************************/

// Returns the squared size parameter of a given round.
template<typename model, typename store>
inline
real_t
round_size2(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( ga::_private::largest_grade<store>::result > 0 );
	ga_maybe_assert( is_round( m, tolerance ), "The input multivector is not a round." );

	real_t result;

	const multivector<model,typename lcont_return<model,ga::store<model::infinity_point_bitmap>,store>::store_t> &aux = lcont( _private::consts<model>::ni(), m );
	assign<false>( result, scp( scp( m, grade_involution( m ) ), inverse( scp( aux, aux ), tolerance ) ), tolerance );
	

	/* IMPLEMENTATION ISSUES
	 *
	 * Table 14.1 (see Errata) states that the squared size of a round is computed as
	 * gp( gp( X, grade_involution( X ) ), inverse( gp( lcont( ni, X ), lcont( ni, X ) ) ) ).
	 * I changed the implementation becouse X and lcont( ni, X ) are blades, so
	 * gp( X, grade_involution( X ) ) = scp( X, grade_involution( X ) ) and
	 * lcont( ni, X )^2 = scp( lcont( ni, X ), lcont( ni, X ) ).
	 */

	return result;
}

}

}

#endif // !_GA_CONFORMAL_ROUND_SIZE2_
