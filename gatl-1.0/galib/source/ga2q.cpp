/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#include "ga2q.h"

/*******************************************************************************************************
 * Basis vectors initialization.
 *******************************************************************************************************/

ga_basis_vector(ga2q_model,0) = "e1";
ga_basis_vector(ga2q_model,1) = "e2";
ga_basis_vector(ga2q_model,2) = "e0";
ga_basis_vector(ga2q_model,3) = "f1";
ga_basis_vector(ga2q_model,4) = "f2";
ga_basis_vector(ga2q_model,5) = "f3";

// The namespace of the 2D quadratic curves (conic sections) geometric algebra model.
namespace ga2q
{

/*******************************************************************************************************
 * Constant values initialization.
 *******************************************************************************************************/

const e1_t e1 = { { { 1 } } };
const e2_t e2 = { { { 1 } } };
const f0_t f0 = { { { 1 } } };
const f1_t f1 = { { { 1 } } };
const f2_t f2 = { { { 1 } } };
const f3_t f3 = { { { 1 } } };

const pseudoscalar_t I = { { { 1 } } };
const pseudoscalar_t iI = ga::inverse( I, 0 );

const euclidean_pseudoscalar_t Ie = { { { 1 } } };
const euclidean_pseudoscalar_t iIe = ga::inverse( Ie, 0 );

}
