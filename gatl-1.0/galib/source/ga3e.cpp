/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#include "ga3e.h"

/*******************************************************************************************************
 * Basis vectors initialization.
 *******************************************************************************************************/

ga_basis_vector(ga3e_model,0) = "e1";
ga_basis_vector(ga3e_model,1) = "e2";
ga_basis_vector(ga3e_model,2) = "e3";

// The namespace of the 3D Euclidean vector space geometric algebra model.
namespace ga3e
{

/*******************************************************************************************************
 * Constant values initialization.
 *******************************************************************************************************/

const e1_t e1 = { { { 1 } } };
const e2_t e2 = { { { 1 } } };
const e3_t e3 = { { { 1 } } };

const pseudoscalar_t I = { { { 1 } } };
const pseudoscalar_t iI = ga::inverse( I, 0 );

const euclidean_pseudoscalar_t Ie = { { { 1 } } };
const euclidean_pseudoscalar_t iIe = ga::inverse( Ie, 0 );

}
