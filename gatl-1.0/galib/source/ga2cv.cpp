/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#include "ga2cv.h"

/*******************************************************************************************************
 * Basis vectors initialization.
 *******************************************************************************************************/

ga_basis_vector(ga2cv_model,0) = "e1";
ga_basis_vector(ga2cv_model,1) = "e2";
ga_basis_vector(ga2cv_model,2) = "ni";
ga_basis_vector(ga2cv_model,3) = "no";

// The namespace of the 2D conformal geometric algebra model (for the Voronoi example of the subspace detector).
namespace ga2cv
{

/*******************************************************************************************************
 * Constant values initialization.
 *******************************************************************************************************/

const e1_t e1 = { { { 1 } } };
const e2_t e2 = { { { 1 } } };
const ni_t ni = { { { 1 } } };
const no_t no = { { { 1 } } };

const ga::multivector<
		model,
		ga::store<_ni^_no
	> > nino = { { { 1 } } };

const ga::multivector<
		model,
		ga::store<_e1^_ni
	> > e1ni = { { { 1 } } };

const ga::multivector<
		model,
		ga::store<_e2^_ni
	> > e2ni = { { { 1 } } };

const pseudoscalar_t I = { { { 1 } } };
const pseudoscalar_t iI = ga::inverse( I, 0 );

const euclidean_pseudoscalar_t Ie = { { { 1 } } };
const euclidean_pseudoscalar_t iIe = ga::inverse( Ie, 0 );

}
