/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA2C_MAIN_
#define _GA2C_MAIN_

#include "ga.h"

/*******************************************************************************************************
 * Model definition.
 *******************************************************************************************************/

/* Conformal model of 2D space. We define ga2c_model as a new class rather than a typedef from ga::model<base_space_dims,origin_point,infinity_point> because we want to avoid operations between multivector from different models. Also, we declare the ga2c_model outside the ga2c namespace in order to be able to initialize the basis vectors.
   The basis blades are ordered as follow:

      basis blade: scalar    no       e1        no^e1     e2        no^e2     e1^e2     no^e1^e2  ni        no^ni     e1^ni     no^e1^ni  e2^ni     no^e2^ni  e1^e2^ni  no^e1^e2^ni
            index: 0         1        2         3         4         5         6         7         8         9         10        11        12        13        14        15
           bitmap: 0000      0001     0010      0011      0100      0101      0110      0111      1000      1001      1010      1011      1100      1101      1110      1111

   The metric matrix is:

         | no e1 e2 ni
      ---+--------------
	  no |  0  0  0 -1
      e1 |  0  1  0  0
      e2 |  0  0  1  0
	  ni | -1  0  0  0
 */
class ga2c_model : public ga::conformal::model<2,0,3> {};

// The namespace of the 2D conformal geometric algebra model.
namespace ga2c
{

/*******************************************************************************************************
 * Model (re-)definition.
 *******************************************************************************************************/

// Geometric algebra model definition.
typedef ga2c_model model;

/*******************************************************************************************************
 * Some useful constant values for internal use only.
 *******************************************************************************************************/

// Bitmap representation of the scalar basis blade.
static const ga::bitmap_t _scalar = 0;

// Bitmap representation of no.
static const ga::bitmap_t _no = ga::basis_vector<model,0>::bitmap;

// Bitmap representation of e1.
static const ga::bitmap_t _e1 = ga::basis_vector<model,1>::bitmap;

// Bitmap representation of e2.
static const ga::bitmap_t _e2 = ga::basis_vector<model,2>::bitmap;

// Bitmap representation of ni.
static const ga::bitmap_t _ni = ga::basis_vector<model,3>::bitmap;

/*******************************************************************************************************
 * Set of products/operations to be used within this model.
 *******************************************************************************************************/

#include "ga_operations.h"
#include "ga_conformal_operations.h"

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
typedef ga::multivector<
		model,
		ga::store<_e1^_e2
	> > euclidean_pseudoscalar_t;

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

// Multivector representation of a null vector no.
typedef ga::multivector<
		model,
		ga::store<_no
	> > no_t;

// Multivector representation of a null vector ni.
typedef ga::multivector<
		model,
		ga::store<_ni
	> > ni_t;

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

// Multivector representation of a point.
typedef ga::multivector<
		model,
		ga::store<_no,
		ga::store<_e1,
		ga::store<_e2,
		ga::store<_ni
	> > > > > point_t;

// Multivector representation of a flat point.
typedef ga::multivector<
		model,
		ga::store<_no^_ni,
		ga::store<_e1^_ni,
		ga::store<_e2^_ni
	> > > > flat_point_t;

// Multivector representation of a free vector.
typedef ga::multivector<
		model,
		ga::store<_e1^_ni,
		ga::store<_e2^_ni
	> > > free_vector_t;

// Multivector representation of a line.
typedef ga::multivector<
		model,
		ga::store<_no^_e1^_ni,
		ga::store<_no^_e2^_ni,
		ga::store<_e1^_e2^_ni
	> > > > line_t;

// Multivector representation of a hyperplane.
typedef line_t hyperplane_t;

// Multivector representation of a free bivector.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2^_ni
	> > free_bivector_t;

// Multivector representation of a point pair.
typedef ga::multivector<
		model,
		ga::store<_no^_e1,
		ga::store<_no^_e2,
		ga::store<_e1^_e2,
		ga::store<_no^_ni,
		ga::store<_e1^_ni,
		ga::store<_e2^_ni
	> > > > > > > point_pair_t;

// Multivector representation of a tangent vector.
typedef point_pair_t tangent_vector_t;

// Multivector representation of a tangent pseudovector.
typedef point_pair_t tangent_pseudovector_t;

// Multivector representation of a circle.
typedef ga::multivector<
		model,
		ga::store<_no^_e1^_e2,
		ga::store<_no^_e1^_ni,
		ga::store<_no^_e2^_ni,
		ga::store<_e1^_e2^_ni
	> > > > > circle_t;

// Multivector representation of a tangent bivector.
typedef circle_t tangent_bivector_t;

// Multivector representation of a rotor.
typedef ga::multivector<
		model,
		ga::store<_scalar,
		ga::store<_e1^_e2
	> > > rotor_t;

// Multivector representation of a scalor.
typedef ga::multivector<
		model,
		ga::store<_scalar,
		ga::store<_no^_ni
	> > > scalor_t;

// Multivector representation of a translator.
typedef ga::multivector<
		model,
		ga::store<_scalar,
		ga::store<_e1^_ni,
		ga::store<_e2^_ni
	> > > > translator_t;

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

// Unit point at origin.
extern const no_t no;

// Unit Euclidean vector e1.
extern const e1_t e1;

// Unit Euclidean vector e2.
extern const e2_t e2;

// Unit point at infinity.
extern const ni_t ni;

// Unit flat point at origin.
extern const ga::multivector<
		model,
		ga::store<_no^_ni
	> > noni;

// Unit free vector e1^ni.
extern const ga::multivector<
		model,
		ga::store<_e1^_ni
	> > e1ni;

// Unit free vector e2^ni.
extern const ga::multivector<
		model,
		ga::store<_e2^_ni
	> > e2ni;

// Unit pseudoscalar of conformal model.
extern const pseudoscalar_t I;

// Inverse of the unit pseudoscalar of conformal model.
extern const pseudoscalar_t iI;

// Euclidean unit pseudoscalar.
extern const euclidean_pseudoscalar_t Ie;

// Inverse of the Euclidean unit pseudoscalar.
extern const euclidean_pseudoscalar_t iIe;

}

#endif // !_GA2C_MAIN_
