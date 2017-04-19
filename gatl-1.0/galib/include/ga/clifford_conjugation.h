/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CLIFFORD_CONJUGATION_
#define _GA_CLIFFORD_CONJUGATION_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Clifford conjugation function implementations.
 *******************************************************************************************************/

// Computes the Clifford conjugation of a specialized multivector.
template<typename model, typename store>
inline
multivector<model,store>
clifford_conjugation(const multivector<model,store> &m)
{
	if (_private::grade_sign<store>::clifford_conjugation_changes)
	{
		multivector<model,store> result;
		_private::grade_sign<store>::clifford_conjugation_run( result.data(), m.data() );
		return result;
	}
	else
	{
		return m;
	}
}

// Computes the Clifford conjugation of a scalar value.
inline
real_t
clifford_conjugation(const real_t &scalar)
{
	return scalar;
}

}

#endif // !_GA_CLIFFORD_CONJUGATION_
