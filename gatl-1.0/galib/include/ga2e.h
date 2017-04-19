/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA2E_MAIN_
#define _GA2E_MAIN_

#include "ga.h"

/*******************************************************************************************************
 * Model definition.
 *******************************************************************************************************/

/* Euclidean vector space model of 2D space. We define ga2e_model as a new class rather than a typedef from ga::model<space_dims> because we want to avoid operations between multivector from different models. Also, we declare the ga2e_model outside the ga2e namespace in order to be able to initialize the basis vectors.
   The basis blades are ordered as follow:

      basis blade: scalar  e1      e2      e1^e2
            index: 0       1       2       3
           bitmap: 00      01      10      11

   The metric matrix is:

         | e1 e2
      ---+--------
      e1 |  1  0
      e2 |  0  1
 */
class ga2e_model : public ga::euclidean::model<2> {};

// The namespace of the 2D Euclidean vector space geometric algebra model.
namespace ga2e
{

/*******************************************************************************************************
 * Model (re-)definition.
 *******************************************************************************************************/

// Geometric algebra model definition.
typedef ga2e_model model;

/*******************************************************************************************************
 * Some useful constant values for internal use only.
 *******************************************************************************************************/

// Bitmap representation of the scalar basis blade.
static const ga::bitmap_t _scalar = 0;

// Bitmap representation of e1.
static const ga::bitmap_t _e1 = ga::basis_vector<model,0>::bitmap;

// Bitmap representation of e2.
static const ga::bitmap_t _e2 = ga::basis_vector<model,1>::bitmap;

/*******************************************************************************************************
 * Set of products/operations to be used within this model.
 *******************************************************************************************************/

#include "ga_operations.h"
#include "ga_euclidean_operations.h"

/*******************************************************************************************************
 * Specialized multivectors definition.
 *******************************************************************************************************/

// A scalar value.
typedef ga::real_t real_t;

// A multivector having all the coefficients.
typedef ga::multivector<
		model,
		ga::store_all<model>::store_type
	> multivector_t;

// A null multivector.
typedef ga::multivector<
		model,
		ga::store_none
	> zero_t;

// Multivector representation of a scalar value.
typedef ga::multivector<
		model,
		ga::store<_scalar
	> > scalar_t;

// A multivector representation of a pseudoscalar.
typedef ga::multivector<
		model,
		ga::store_pseudoscalar<model>::store_type
	> pseudoscalar_t;

// A multivector representation of an Euclidean pseudoscalar.
typedef pseudoscalar_t euclidean_pseudoscalar_t;

// Multivector representation of a vector e1.
typedef ga::multivector<
		model,
		ga::store<_e1
	> > e1_t;

// Multivector representation of a vector e2.
typedef ga::multivector<
		model,
		ga::store<_e2
	> > e2_t;

// Multivector representation of a vector.
typedef ga::multivector<
		model,
		ga::store<_e1,
		ga::store<_e2
	> > > vector_t;

// Multivector representation of a bivector.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2
	> > bivector_t;

// Multivector representation of a rotor.
typedef ga::multivector<
		model,
		ga::store<_scalar,
		ga::store<_e1^_e2
	> > > rotor_t;

/*******************************************************************************************************
 * Matrices definition.
 *******************************************************************************************************/

// Matrix representation of a general multivector.
typedef la::dmatrix<real_t,model::basis_blades_count,1> multivector_matrix_t;

// Matrix representation of some linear operation.
typedef la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count> operation_matrix_t;

// 2nd-rank tensor representation some unary operation, for instance.
typedef la::dtensor2<real_t,model::basis_blades_count> rank2_tensor_t;

// 3rd-rank tensor representation some product, for instance.
typedef la::dtensor3<real_t,model::basis_blades_count> rank3_tensor_t;

/*******************************************************************************************************
 * Constant values declaration.
 *******************************************************************************************************/

// Unit Euclidean vector e1.
extern const e1_t e1;

// Unit Euclidean vector e2.
extern const e2_t e2;

// Unit pseudoscalar.
extern const pseudoscalar_t I;

// Inverse of the unit pseudoscalar.
extern const pseudoscalar_t iI;

// Euclidean unit pseudoscalar.
extern const euclidean_pseudoscalar_t Ie;

// Inverse of the Euclidean unit pseudoscalar.
extern const euclidean_pseudoscalar_t iIe;

}

#endif // !_GA2E_MAIN_
