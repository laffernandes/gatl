/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_DOT_PRODUCT_MATRIX_
#define _GA_DOT_PRODUCT_MATRIX_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Dot product matrix.
 *******************************************************************************************************/

// Computes the dot product matrix for the given specialized multivector.
template<multiplication_type multiplication, typename model, typename store>
inline
la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count>
dot_matrix(const multivector<model,store> &m)
{
	return _private::product_matrix_dot<model,store,multiplication>( m.data() );
}

// Computes the dot product matrix for the given specialized multivector (Euclidean metric).
template<multiplication_type multiplication, typename model, typename store>
inline
la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count>
dot_matrix_em(const multivector<model,store> &m)
{
	return _private::product_matrix_dot_em<model,store,multiplication>( m.data() );
}

// Computes the dot product matrix for the given scalar value.
template<multiplication_type multiplication, typename model>
inline
la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count>
dot_matrix(const real_t &scalar)
{
	return _private::product_matrix_dot<model,store_scalar,multiplication>( &scalar );
}

// Computes the dot product matrix for the given scalar value (Euclidean metric).
template<multiplication_type multiplication, typename model>
inline
la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count>
dot_matrix_em(const real_t &scalar)
{
	return _private::product_matrix_dot_em<model,store_scalar,multiplication>( &scalar );
}

}

#endif // !_GA_DOT_PRODUCT_MATRIX_
