/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA3C_MAIN_
#define _GA3C_MAIN_

#include "ga.h"

/*******************************************************************************************************
 * Model definition.
 *******************************************************************************************************/

/* Conformal model of 3D space. We define ga3c_model as a new class rather than a typedef from ga::model<base_space_dims,origin_point,infinity_point> because we want to avoid operations between multivector from different models. Also, we declare the ga3c_model outside the ga3c namespace in order to be able to initialize the basis vectors.
   The basis blades are ordered as follow:

      basis blade: scalar       no           e1           no^e1        e2           no^e2        e1^e2        no^e1^e2     e3           no^e3        e1^e3        no^e1^e3     e2^e3        no^e2^e3     e1^e2^e3     no^e1^e2^e3  ni           no^ni        e1^ni        no^e1^ni     e2^ni        no^e2^ni     e1^e2^ni     no^e1^e2^ni  e3^ni        no^e3^ni     e1^e3^ni     no^e1^e3^ni  e2^e3^ni     no^e2^e3^ni  e1^e2^e3^ni  no^e1^e2^e3^ni
            index: 0            1            2            3            4            5            6            7            8            9            10           11           12           13           14           15           16           17           18           19           20           21           22           23           24           25           26           27           28           29           30           31
           bitmap: 00000        00001        00010        00011        00100        00101        00110        00111        01000        01001        01010        01011        01100        01101        01110        01111        10000        10001        10010        10011        10100        10101        10110        10111        11000        11001        11010        11011        11100        11101        11110        11111
 
   The metric matrix is:

         | no e1 e2 e3 ni
      ---+-----------------
	  no |  0  0  0  0 -1
      e1 |  0  1  0  0  0
      e2 |  0  0  1  0  0
      e3 |  0  0  0  1  0
	  ni | -1  0  0  0  0
 */
class ga3c_model : public ga::conformal::model<3,0,4> {};

// The namespace of the 3D conformal geometric algebra model.
namespace ga3c
{

/*******************************************************************************************************
 * Model (re-)definition.
 *******************************************************************************************************/

// Geometric algebra model definition.
typedef ga3c_model model;

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

// Bitmap representation of e3.
static const ga::bitmap_t _e3 = ga::basis_vector<model,3>::bitmap;

// Bitmap representation of ni.
static const ga::bitmap_t _ni = ga::basis_vector<model,4>::bitmap;

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
		ga::store<_e1^_e2^_e3
	> > euclidean_pseudoscalar_t;

// Multivector representation of a null vector no.
typedef ga::multivector<
		model,
		ga::store<_no
	> > no_t;

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

// Multivector representation of a vector e3.
typedef ga::multivector<
		model,
		ga::store<_e3
	> > e3_t;

// Multivector representation of a null vector ni.
typedef ga::multivector<
		model,
		ga::store<_ni
	> > ni_t;

// Multivector representation of a vector.
typedef ga::multivector<
		model,
		ga::store<_e1,
		ga::store<_e2,
		ga::store<_e3
	> > > > vector_t;

// Multivector representation of a bivector.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2,
		ga::store<_e1^_e3,
		ga::store<_e2^_e3
	> > > > bivector_t;

// Multivector representation of a trivector.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2^_e3
	> > trivector_t;

// Multivector representation of a point.
typedef ga::multivector<
		model,
		ga::store<_no,
		ga::store<_e1,
		ga::store<_e2,
		ga::store<_e3,
		ga::store<_ni
	> > > > > > point_t;

// Multivector representation of a flat point.
typedef ga::multivector<
		model,
		ga::store<_no^_ni,
		ga::store<_e1^_ni,
		ga::store<_e2^_ni,
		ga::store<_e3^_ni
	> > > > > flat_point_t;

// Multivector representation of a free vector.
typedef ga::multivector<
		model,
		ga::store<_e1^_ni,
		ga::store<_e2^_ni,
		ga::store<_e3^_ni
	> > > > free_vector_t;

// Multivector representation of a line.
typedef ga::multivector<
		model,
		ga::store<_no^_e1^_ni,
		ga::store<_no^_e2^_ni,
		ga::store<_e1^_e2^_ni,
		ga::store<_no^_e3^_ni,
		ga::store<_e1^_e3^_ni,
		ga::store<_e2^_e3^_ni
	> > > > > > > line_t;

// Multivector representation of a free bivector.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2^_ni,
		ga::store<_e1^_e3^_ni,
		ga::store<_e2^_e3^_ni
	> > > > free_bivector_t;

// Multivector representation of a plane.
typedef ga::multivector<
		model,
		ga::store<_no^_e1^_e2^_ni,
		ga::store<_no^_e1^_e3^_ni,
		ga::store<_no^_e2^_e3^_ni,
		ga::store<_e1^_e2^_e3^_ni
	> > > > > plane_t;

// Multivector representation of a hyperplane.
typedef plane_t hyperplane_t;

// Multivector representation of a free trivector.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2^_e3^_ni
	> > free_trivector_t;

// Multivector representation of a point pair.
typedef ga::multivector<
		model,
		ga::store<_no^_e1,
		ga::store<_no^_e2,
		ga::store<_e1^_e2,
		ga::store<_no^_e3,
		ga::store<_e1^_e3,
		ga::store<_e2^_e3,
		ga::store<_no^_ni,
		ga::store<_e1^_ni,
		ga::store<_e2^_ni,
		ga::store<_e3^_ni
	> > > > > > > > > > > point_pair_t;

// Multivector representation of a tangent vector.
typedef point_pair_t tangent_vector_t;

// Multivector representation of a circle.
typedef ga::multivector<
		model,
		ga::store<_no^_e1^_e2,
		ga::store<_no^_e1^_e3,
		ga::store<_no^_e2^_e3,
		ga::store<_e1^_e2^_e3,
		ga::store<_no^_e1^_ni,
		ga::store<_no^_e2^_ni,
		ga::store<_e1^_e2^_ni,
		ga::store<_no^_e3^_ni,
		ga::store<_e1^_e3^_ni,
		ga::store<_e2^_e3^_ni
	> > > > > > > > > > > circle_t;

// Multivector representation of a tangent bivector.
typedef circle_t tangent_bivector_t;

// Multivector representation of a tangent pseudovector.
typedef circle_t tangent_pseudovector_t;

// Multivector representation of a sphere.
typedef ga::multivector<
		model,
		ga::store<_no^_e1^_e2^_e3,
		ga::store<_no^_e1^_e2^_ni,
		ga::store<_no^_e1^_e3^_ni,
		ga::store<_no^_e2^_e3^_ni,
		ga::store<_e1^_e2^_e3^_ni
	> > > > > > sphere_t;

// Multivector representation of a tangent trivector.
typedef sphere_t tangent_trivector_t;

// Multivector representation of a rotor.
typedef ga::multivector<
		model,
		ga::store<_scalar,
		ga::store<_e1^_e2,
		ga::store<_e1^_e3,
		ga::store<_e2^_e3
	> > > > > rotor_t;

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
		ga::store<_e2^_ni,
		ga::store<_e3^_ni
	> > > > > translator_t;

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

// Unit Euclidean vector e3.
extern const e3_t e3;

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

// Unit free vector e3^ni.
extern const ga::multivector<
		model,
		ga::store<_e3^_ni
	> > e3ni;

// Unit pseudoscalar of conformal model.
extern const pseudoscalar_t I;

// Inverse of the unit pseudoscalar of conformal model.
extern const pseudoscalar_t iI;

// Euclidean unit pseudoscalar.
extern const euclidean_pseudoscalar_t Ie;

// Inverse of the Euclidean unit pseudoscalar.
extern const euclidean_pseudoscalar_t iIe;

}

#endif // !_GA3C_MAIN_
