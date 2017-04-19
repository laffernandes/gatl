/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_HESTENES_INNER_PRODUCT_MATRIX_
#define _GA_HESTENES_INNER_PRODUCT_MATRIX_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Hestenes' inner product matrix.
 *******************************************************************************************************/

// Computes the Hestenes' inner product matrix for the given specialized multivector.
template<multiplication_type multiplication, typename model, typename store>
inline
la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count>
hip_matrix(const multivector<model,store> &m)
{
	return _private::product_matrix_hip<model,store,multiplication>( m.data() );
}

// Computes the Hestenes' inner product matrix for the given specialized multivector (Euclidean metric).
template<multiplication_type multiplication, typename model, typename store>
inline
la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count>
hip_matrix_em(const multivector<model,store> &m)
{
	return _private::product_matrix_hip_em<model,store,multiplication>( m.data() );
}

// Computes the Hestenes' inner product matrix for the given scalar value.
template<multiplication_type multiplication, typename model>
inline
la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count>
hip_matrix(const real_t &scalar)
{
	return _private::product_matrix_hip<model,store_scalar,multiplication>( &scalar );
}

// Computes the Hestenes' inner product matrix for the given scalar value (Euclidean metric).
template<multiplication_type multiplication, typename model>
inline
la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count>
hip_matrix_em(const real_t &scalar)
{
	return _private::product_matrix_hip_em<model,store_scalar,multiplication>( &scalar );
}

}

#endif // !_GA_HESTENES_INNER_PRODUCT_MATRIX_
