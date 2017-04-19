/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_HOMOGENEOUS_TESTS_
#define _GA_HOMOGENEOUS_TESTS_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the homogeneous model.
namespace homogeneous
{

/*******************************************************************************************************
 * Flat check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a flat (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_flat(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((!is_scalar( m, tolerance )) && (is_blade( m, tolerance )));
}

// Returns whether the given scalar value is a flat (up to an assumed numerical error).
inline
bool
is_flat(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

/*******************************************************************************************************
 * Proper flat check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a proper flat (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_proper_flat(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((!is_zero( lcont( _private::consts<model>::ie0(), m ), tolerance )) && (is_blade( m, tolerance )));
}

// Returns whether the given scalar value is a proper flat (up to an assumed numerical error).
inline
bool
is_proper_flat(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

/*******************************************************************************************************
 * Improper flat check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is an improper flat (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_improper_flat(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return ((!is_scalar( m, tolerance )) && (is_zero( lcont( _private::consts<model>::ie0(), m ), tolerance )) && (is_blade( m, tolerance )));
}

// Returns whether the given scalar value is an improper flat (up to an assumed numerical error).
inline
bool
is_improper_flat(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return false;
}

/*******************************************************************************************************
 * Direction check implementations.
 *******************************************************************************************************/

// Returns whether the given specialized multivector is a direction (up to an assumed numerical error).
template<typename model, typename store>
inline
bool
is_direction(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return is_improper_flat( m, tolerance );
}

// Returns whether the given scalar value is a direction (up to an assumed numerical error).
inline
bool
is_direction(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return is_improper_flat( scalar, tolerance );
}

}

}

#endif // !_GA_HOMOGENEOUS_TESTS_
