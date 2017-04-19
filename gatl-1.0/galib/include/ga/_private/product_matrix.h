/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_PRODUCT_MATRIX_
#define _GA_PRIVATE_PRODUCT_MATRIX_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::product_matrix_[op]<model,store,multiplication>() function definition.
 *******************************************************************************************************/

// This macro creates the base function for computing the product matrix of some product.
#define _ga_product_matrix(op) \
	template<typename model, typename store, multiplication_type multiplication> \
	_GA_ALWAYS_INLINE \
	la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count> product_matrix_##op(const real_t *coefficients) \
	{ \
		typedef multivector<model,store> multivector_t; \
	\
		const la::dtensor3<real_t,model::basis_blades_count> &tensor = product_tensor_##op<model>::run(); \
	\
		la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count> result( static_cast<real_t>( 0 ) ); \
	\
		for (index_t k=0; k!=model::basis_blades_count; ++k) \
		{ \
			if (multiplication == right_multiplication) \
			{ \
				for (index_t i=0; i!=multivector_t::size; ++i) \
				{ \
					for (index_t j=0; j!=model::basis_blades_count; ++j) \
					{ \
						result(k,j) += tensor(k,multivector_t::basis_blade(i).bitmap,j) * coefficients[i]; \
					} \
				} \
			} \
			else \
			{ \
				for (index_t i=0; i!=model::basis_blades_count; ++i) \
				{ \
					for (index_t j=0; j!=multivector_t::size; ++j) \
					{ \
						result(k,i) += tensor(k,i,multivector_t::basis_blade(j).bitmap) * coefficients[j]; \
					} \
				} \
			} \
		} \
	\
		return result; \
	} \

// The base function for computing the dot product matrix for a given multivector.
_ga_product_matrix(dot)

// The base function for computing the dot product matrix for a given multivector (Euclidean metric).
_ga_product_matrix(dot_em)

// The base function for computing the geometric product matrix for a given multivector.
_ga_product_matrix(gp)

// The base function for computing the geometric product matrix for a given multivector (Euclidean metric).
_ga_product_matrix(gp_em)

// The base function for computing the Hestenes' inner product matrix for a given multivector.
_ga_product_matrix(hip)

// The base function for computing the Hestenes' inner product matrix for a given multivector (Euclidean metric).
_ga_product_matrix(hip_em)

// The base function for computing the left contraction matrix for a given multivector.
_ga_product_matrix(lcont)

// The base function for computing the left contraction matrix for a given multivector (Euclidean metric).
_ga_product_matrix(lcont_em)

// The base function for computing the outer product matrix for a given multivector.
_ga_product_matrix(op)

// The base function for computing the right contraction matrix for a given multivector.
_ga_product_matrix(rcont)

// The base function for computing the right contraction matrix for a given multivector (Euclidean metric).
_ga_product_matrix(rcont_em)

// The base function for computing the scalar product matrix for a given multivector.
_ga_product_matrix(scp)

// The base function for computing the scalar product matrix for a given multivector (Euclidean metric).
_ga_product_matrix(scp_em)

}

}

#endif // !_GA_PRIVATE_PRODUCT_MATRIX_
