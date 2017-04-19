/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_TESTS_
#define _GA_CONFORMAL_TESTS_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

/*******************************************************************************************************
 * Direction check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a direction (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_direction(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((!is_scalar( m, tolerance )) && (is_zero( op( _private::consts<model>::ni(), m ), tolerance )) && (is_zero( lcont( _private::consts<model>::ni(), m ), tolerance )) && (is_blade( m, tolerance )));
}

// Returns whether the given scalar value is a direction (up to an assumed numerical error).
inline
bool
is_direction(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

/*******************************************************************************************************
 * Dual direction check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a dual direction (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_dual_direction(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((!is_scalar( m, tolerance )) && (is_zero( op( _private::consts<model>::ni(), m ), tolerance )) && (is_zero( lcont( _private::consts<model>::ni(), m ), tolerance )) && (is_blade( m, tolerance )));
}

// Returns whether the given scalar value is a dual direction (up to an assumed numerical error).
inline
bool
is_dual_direction(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

/*******************************************************************************************************
 * Flat check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a flat (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_flat(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((is_zero( op( _private::consts<model>::ni(), m ), tolerance )) && (!is_zero( lcont( _private::consts<model>::ni(), m ), tolerance )) && (is_blade( m, tolerance )));
}

// Returns whether the given scalar value is a flat (up to an assumed numerical error).
inline
bool
is_flat(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

/*******************************************************************************************************
 * Dual flat check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a dual flat (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_dual_flat(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((!is_scalar( m, tolerance )) && (!is_zero( op( _private::consts<model>::ni(), m ), tolerance )) && (is_zero( lcont( _private::consts<model>::ni(), m ), tolerance )) && (is_blade( m, tolerance )));
}

// Returns whether the given scalar value is a dual flat (up to an assumed numerical error).
inline
bool
is_dual_flat(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

/*******************************************************************************************************
 * Tangent check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a tangent (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_tangent(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((!is_zero( op( _private::consts<model>::ni(), m ), tolerance )) && (!is_zero( lcont( _private::consts<model>::ni(), m ), tolerance )) && (is_zero( scp( m, m ), tolerance )) && (is_blade( m, tolerance )));

	/* IMPLEMENTATION ISSUES
	 *
	 * The condition from Table 14.1 (see Errata) states that the square of a tangent is
	 * zero. I changed the test because gp(X,X) = scp(X,X) for X being a blade.
	 */
}

// Returns whether the given scalar value is a tangent (up to an assumed numerical error).
inline
bool
is_tangent(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

/*******************************************************************************************************
 * Dual tangent check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a dual tangent (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_dual_tangent(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((!is_zero( op( _private::consts<model>::ni(), m ), tolerance )) && (!is_zero( lcont( _private::consts<model>::ni(), m ), tolerance )) && (is_zero( scp( m, m ), tolerance )) && (is_blade( m, tolerance )));

	/* IMPLEMENTATION ISSUES
	 *
	 * The condition from Table 14.1 (see Errata) states that the square of a dual tangent is
	 * zero. I changed the test because gp(X,X) = scp(X,X) for X being a blade.
	 */
}

// Returns whether the given scalar value is a dual tangent (up to an assumed numerical error).
inline
bool
is_dual_tangent(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

/*******************************************************************************************************
 * Round check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a round (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_round(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((!is_zero( op( _private::consts<model>::ni(), m ), tolerance )) && (!is_zero( lcont( _private::consts<model>::ni(), m ), tolerance )) && (!is_zero( scp( m, m ), tolerance )) && (is_blade( m, tolerance )));

	/* IMPLEMENTATION ISSUES
	 *
	 * The condition from Table 14.1 (see Errata) states that the square of a round is
	 * not zero. I changed the test because gp(X,X) = scp(X,X) for X being a blade.
	 */
}

// Returns whether the given scalar value is a round (up to an assumed numerical error).
inline
bool
is_round(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

/*******************************************************************************************************
 * Dual round check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a dual round (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_dual_round(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((!is_zero( op( _private::consts<model>::ni(), m ), tolerance )) && (!is_zero( lcont( _private::consts<model>::ni(), m ), tolerance )) && (!is_zero( scp( m, m ), tolerance )) && (is_blade( m, tolerance )));

	/* IMPLEMENTATION ISSUES
	 *
	 * The condition from Table 14.1 (see Errata) states that the square of a dual round is
	 * not zero. I changed the test because gp(X,X) = scp(X,X) for X being a blade.
	 */
}

// Returns whether the given scalar value is a dual round (up to an assumed numerical error).
inline
bool
is_dual_round(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

}

}

#endif // !_GA_CONFORMAL_TESTS_
