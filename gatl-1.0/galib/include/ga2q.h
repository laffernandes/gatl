/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA2Q_MAIN_
#define _GA2Q_MAIN_

#include "ga.h"

/*******************************************************************************************************
 * Model definition.
 *******************************************************************************************************/

/* Model for 2D quadratic curves (conic sections). We define ga2q_model as a new class rather than a typedef from ga::quadratic::model<base_space_dims> because we want to avoid operations between multivector from different models. Also, we declare the ga2q_model outside the ga2q namespace in order to be able to initialize the basis vectors.
   The basis blades are ordered as follow:

      basis blade: scalar        e1            e2            e1^e2         f0            e1^f0         e2^f0         e1^e2^f0      f1            e1^f1         e2^f1         e1^e2^f1      f0^f1         e1^f0^f1      e2^f0^f1      e1^e2^f0^f1   f2            e1^f2         e2^f2         e1^e2^f2      f0^f2         e1^f0^f2      e2^f0^f2      e1^e2^f0^f2   f1^f2         e1^f1^f2      e2^f1^f2      e1^e2^f1^f2   f0^f1^f2      e1^f0^f1^f2   e2^f0^f1^f2   e1^e2^f0^f1^f2    f3            e1^f3         e2^f3         e1^e2^f3      f0^f3         e1^f0^f3      e2^f0^f3      e1^e2^f0^f3   f1^f3         e1^f1^f3      e2^f1^f3      e1^e2^f1^f3   f0^f1^f3      e1^f0^f1^f3   e2^f0^f1^f3   e1^e2^f0^f1^f3    f2^f3         e1^f2^f3      e2^f2^f3      e1^e2^f2^f3   f0^f2^f3      e1^f0^f2^f3   e2^f0^f2^f3   e1^e2^f0^f2^f3    f1^f2^f3      e1^f1^f2^f3   e2^f1^f2^f3   e1^e2^f1^f2^f3    f0^f1^f2^f3   e1^f0^f1^f2^f3    e2^f0^f1^f2^f3    e1^e2^f0^f1^f2^f3
            index: 0             1             2             3             4             5             6             7             8             9             10            11            12            13            14            15            16            17            18            19            20            21            22            23            24            25            26            27            28            29            30            31                32            33            34            35            36            37            38            39            40            41            42            43            44            45            46            47                48            49            50            51            52            53            54            55                56            57            58            59                60            61                62                63
           bitmap: 000000        000001        000010        000011        000100        000101        000110        000111        001000        001001        001010        001011        001100        001101        001110        001111        010000        010001        010010        010011        010100        010101        010110        010111        011000        011001        011010        011011        011100        011101        011110        011111            100000        100001        100010        100011        100100        100101        100110        100111        101000        101001        101010        101011        101100        101101        101110        101111            110000        110001        110010        110011        110100        110101        110110        110111            111000        111001        111010        111011            111100        111101            111110            111111

		   e1^e2^f0^f1^f2^f3

   The metric matrix is:

         | e1 e2 f0 f1 f2 f3
      ---+------------------
      e1 |  1  0  0  0  0  0
      e2 |  0  1  0  0  0  0
      f0 |  0  0  1  0  0  0
	  f1 |  0  0  0  1  0  0
	  f2 |  0  0  0  0  1  0
	  f3 |  0  0  0  0  0  1
 */
class ga2q_model : public ga::quadratic::model<2> {};

// The namespace of the 2D quadratic curves (conic sections) geometric algebra model.
namespace ga2q
{

/*******************************************************************************************************
 * Model (re-)definition.
 *******************************************************************************************************/

// Geometric algebra model definition.
typedef ga2q_model model;

/*******************************************************************************************************
 * Some useful constant values for internal use only.
 *******************************************************************************************************/

// Bitmap representation of the scalar basis blade.
static const ga::bitmap_t _scalar = 0;

// Bitmap representation of e1.
static const ga::bitmap_t _e1 = ga::basis_vector<model,0>::bitmap;

// Bitmap representation of e2.
static const ga::bitmap_t _e2 = ga::basis_vector<model,1>::bitmap;

// Bitmap representation of f0.
static const ga::bitmap_t _f0 = ga::basis_vector<model,2>::bitmap;

// Bitmap representation of f1.
static const ga::bitmap_t _f1 = ga::basis_vector<model,3>::bitmap;

// Bitmap representation of f2.
static const ga::bitmap_t _f2 = ga::basis_vector<model,4>::bitmap;

// Bitmap representation of f3.
static const ga::bitmap_t _f3 = ga::basis_vector<model,5>::bitmap;

/*******************************************************************************************************
 * Set of products/operations to be used within this model.
 *******************************************************************************************************/

#include "ga_operations.h"
#include "ga_quadratic_operations.h"

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

// Multivector representation of a vector f0.
typedef ga::multivector<
		model,
		ga::store<_f0
	> > f0_t;

// Multivector representation of a vector f1.
typedef ga::multivector<
		model,
		ga::store<_f1
	> > f1_t;

// Multivector representation of a vector f2.
typedef ga::multivector<
		model,
		ga::store<_f2
	> > f2_t;

// Multivector representation of a vector f3.
typedef ga::multivector<
		model,
		ga::store<_f3
	> > f3_t;

// Multivector representation of a point.
typedef ga::multivector<
		model,
		ga::store<_e1,
		ga::store<_e2,
		ga::store<_f0,
		ga::store<_f1,
		ga::store<_f2,
		ga::store<_f3
	> > > > > > > point_t;

// Multivector representation of a point pair.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2,
		ga::store<_e1^_f0,
		ga::store<_e2^_f0,
		ga::store<_e1^_f1,
		ga::store<_e2^_f1,
		ga::store<_f0^_f1,
		ga::store<_e1^_f2,
		ga::store<_e2^_f2,
		ga::store<_f0^_f2,
		ga::store<_f1^_f2,
		ga::store<_e1^_f3,
		ga::store<_e2^_f3,
		ga::store<_f0^_f3,
		ga::store<_f1^_f3,
		ga::store<_f2^_f3
	> > > > > > > > > > > > > > > > point_pair_t;

// Multivector representation of a point triplet.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2^_f0,
		ga::store<_e1^_e2^_f1,
		ga::store<_e1^_f0^_f1,
		ga::store<_e2^_f0^_f1,
		ga::store<_e1^_e2^_f2,
		ga::store<_e1^_f0^_f2,
		ga::store<_e2^_f0^_f2,
		ga::store<_e1^_f1^_f2,
		ga::store<_e2^_f1^_f2,
		ga::store<_f0^_f1^_f2,
		ga::store<_e1^_e2^_f3,
		ga::store<_e1^_f0^_f3,
		ga::store<_e2^_f0^_f3,
		ga::store<_e1^_f1^_f3,
		ga::store<_e2^_f1^_f3,
		ga::store<_f0^_f1^_f3,
		ga::store<_e1^_f2^_f3,
		ga::store<_e2^_f2^_f3,
		ga::store<_f0^_f2^_f3,
		ga::store<_f1^_f2^_f3
	> > > > > > > > > > > > > > > > > > > > > point_triplet_t;

// Multivector representation of a point quadruplet.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2^_f0^_f1,
		ga::store<_e1^_e2^_f0^_f2,
		ga::store<_e1^_e2^_f1^_f2,
		ga::store<_e1^_f0^_f1^_f2,
		ga::store<_e2^_f0^_f1^_f2,
		ga::store<_e1^_e2^_f0^_f3,
		ga::store<_e1^_e2^_f1^_f3,
		ga::store<_e1^_f0^_f1^_f3,
		ga::store<_e2^_f0^_f1^_f3,
		ga::store<_e1^_e2^_f2^_f3,
		ga::store<_e1^_f0^_f2^_f3,
		ga::store<_e2^_f0^_f2^_f3,
		ga::store<_e1^_f1^_f2^_f3,
		ga::store<_e2^_f1^_f2^_f3,
		ga::store<_f0^_f1^_f2^_f3
	> > > > > > > > > > > > > > > > point_quadruplet_t;

// Multivector representation of a conic.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2^_f0^_f1^_f2,
		ga::store<_e1^_e2^_f0^_f1^_f3,
		ga::store<_e1^_e2^_f0^_f2^_f3,
		ga::store<_e1^_e2^_f1^_f2^_f3,
		ga::store<_e1^_f0^_f1^_f2^_f3,
		ga::store<_e2^_f0^_f1^_f2^_f3
	> > > > > > > conic_t;

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

// Unit basis vector f0.
extern const f0_t f0;

// Unit basis vector f1.
extern const f1_t f1;

// Unit basis vector f2.
extern const f2_t f2;

// Unit basis vector f3.
extern const f3_t f3;

// Unit pseudoscalar of quadratic curves model.
extern const pseudoscalar_t I;

// Inverse of the unit pseudoscalar of quadratic curves model.
extern const pseudoscalar_t iI;

// Euclidean unit pseudoscalar.
extern const euclidean_pseudoscalar_t Ie;

// Inverse of the Euclidean unit pseudoscalar.
extern const euclidean_pseudoscalar_t iIe;

}

#endif // !_GA2Q_MAIN_
