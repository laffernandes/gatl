/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_TAKE_LARGEST_GRADE_
#define _GA_TAKE_LARGEST_GRADE_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Take largest grade operation implementation.
 *******************************************************************************************************/

// Returns the largest grade part of a specialized multivector such that it is not zero.
template<typename model, typename store>
inline
multivector<model,store>
take_largest_grade(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	multivector<model,store> result;
	_private::take_largest_grade<store>::run( result.data(), m.data(), -1, tolerance );
	return result;
}

// Returns the largest grade part of a scalar value.
inline
real_t
take_largest_grade(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return scalar;
}

}

#endif // !_GA_TAKE_LARGEST_GRADE_
