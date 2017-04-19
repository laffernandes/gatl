/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#include "ga3h.h"

/*******************************************************************************************************
 * Basis vectors initialization.
 *******************************************************************************************************/

ga_basis_vector(ga3h_model,0) = "e0";
ga_basis_vector(ga3h_model,1) = "e1";
ga_basis_vector(ga3h_model,2) = "e2";
ga_basis_vector(ga3h_model,3) = "e3";

// The namespace of the 3D homogeneous geometric algebra model.
namespace ga3h
{

/*******************************************************************************************************
 * Constant values initialization.
 *******************************************************************************************************/

const e0_t e0 = { { { 1 } } };
const e1_t e1 = { { { 1 } } };
const e2_t e2 = { { { 1 } } };
const e3_t e3 = { { { 1 } } };

const e0_t ie0 = ga::inverse( e0, 0 );

const pseudoscalar_t I = { { { 1 } } };
const pseudoscalar_t iI = ga::inverse( I, 0 );

const euclidean_pseudoscalar_t Ie = { { { 1 } } };
const euclidean_pseudoscalar_t iIe = ga::inverse( Ie, 0 );

}
