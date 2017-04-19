/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_REVERSE_
#define _GA_REVERSE_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Reverse function implementations.
 *******************************************************************************************************/

// Computes the reverse of a specialized multivector.
template<typename model, typename store>
inline
multivector<model,store>
reverse(const multivector<model,store> &m)
{
	if (_private::grade_sign<store>::reverse_changes)
	{
		multivector<model,store> result;
		_private::grade_sign<store>::reverse_run( result.data(), m.data() );
		return result;
	}
	else
	{
		return m;
	}
}

// Computes the reverse of a scalar value.
inline
real_t
reverse(const real_t &scalar)
{
	return scalar;
}

}

#endif // !_GA_REVERSE_
