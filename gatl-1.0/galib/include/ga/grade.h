/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_GRADE_
#define _GA_GRADE_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Grade function implementations.
 *******************************************************************************************************/

// Returns the grade of the given grade homogeneous multivector, or -1 whether the multivector is not grade homogeneous.
template<typename model, typename store>
inline
int
grade(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return _private::grade<store>::run( m.data(), tolerance );
}

// Returns the grade of the given scalar value.
inline
int
grade(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return 0;
}

}

#endif // !_GA_GRADE_
