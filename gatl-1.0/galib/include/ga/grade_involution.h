/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_GRADE_INVOLUTION_
#define _GA_GRADE_INVOLUTION_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Grade involution function implementations.
 *******************************************************************************************************/

// Computes the grade involution of a specialized multivector.
template<typename model, typename store>
inline
multivector<model,store>
grade_involution(const multivector<model,store> &m)
{
	if (_private::grade_sign<store>::grade_involution_changes)
	{
		multivector<model,store> result;
		_private::grade_sign<store>::grade_involution_run( result.data(), m.data() );
		return result;
	}
	else
	{
		return m;
	}
}

// Computes the grade involution of a scalar value.
inline
real_t
grade_involution(const real_t &scalar)
{
	return scalar;
}

}

#endif // !_GA_GRADE_INVOLUTION_
