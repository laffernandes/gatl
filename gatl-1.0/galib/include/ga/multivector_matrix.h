/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_MULTIVECTOR_MATRIX_
#define _GA_MULTIVECTOR_MATRIX_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Multivector matrix.
 *******************************************************************************************************/

// Returns the matrix representation of a given multivector.
template<typename model, typename store>
inline
la::dmatrix<real_t,model::basis_blades_count,1>
multivector_matrix(const multivector<model,store> &m)
{
	la::dmatrix<real_t,model::basis_blades_count,1> result( 0 );

	for (index_t i=0; i!=m.size; ++i)
	{
		result[multivector<model,store>::basis_blade(i).bitmap] = m[i];
	}

	return result;
}

// Returns the matrix representation of a given scalar value.
template<typename model>
inline
la::dmatrix<real_t,model::basis_blades_count,1>
multivector_matrix(const real_t &scalar)
{
	la::dmatrix<real_t,model::basis_blades_count,1> result( 0 );
	
	result[0] = scalar;

	return result;
}

}

#endif // !_GA_MULTIVECTOR_MATRIX_
