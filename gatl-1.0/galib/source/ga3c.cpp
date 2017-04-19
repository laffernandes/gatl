/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#include "ga3c.h"

/*******************************************************************************************************
 * Basis vectors initialization.
 *******************************************************************************************************/

ga_basis_vector(ga3c_model,0) = "no";
ga_basis_vector(ga3c_model,1) = "e1";
ga_basis_vector(ga3c_model,2) = "e2";
ga_basis_vector(ga3c_model,3) = "e3";
ga_basis_vector(ga3c_model,4) = "ni";

// The namespace of the 3D conformal geometric algebra model.
namespace ga3c
{

/*******************************************************************************************************
 * Constant values initialization.
 *******************************************************************************************************/

const no_t no = { { { 1 } } };
const e1_t e1 = { { { 1 } } };
const e2_t e2 = { { { 1 } } };
const e3_t e3 = { { { 1 } } };
const ni_t ni = { { { 1 } } };

const ga::multivector<
		model,
		ga::store<_no^_ni
	> > noni = { { { 1 } } };

const ga::multivector<
		model,
		ga::store<_e1^_ni
	> > e1ni = { { { 1 } } };

const ga::multivector<
		model,
		ga::store<_e2^_ni
	> > e2ni = { { { 1 } } };

const ga::multivector<
		model,
		ga::store<_e3^_ni
	> > e3ni = { { { 1 } } };

const pseudoscalar_t I = { { { 1 } } };
const pseudoscalar_t iI = ga::inverse( I, 0 );

const euclidean_pseudoscalar_t Ie = { { { 1 } } };
const euclidean_pseudoscalar_t iIe = ga::inverse( Ie, 0 );

}
