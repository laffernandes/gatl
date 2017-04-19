/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_SCALAR_PRODUCT_TENSOR_
#define _GA_SCALAR_PRODUCT_TENSOR_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Scalar product tensor.
 *******************************************************************************************************/

// Computes the scalar product tensor for the given geometric algebra model.
template<typename model>
inline
const la::dtensor3<real_t,model::basis_blades_count>&
scp_tensor()
{
	return _private::product_tensor_scp<model>::run();
}

// Computes the scalar product tensor for the given geometric algebra model (Euclidean metric).
template<typename model>
inline
const la::dtensor3<real_t,model::basis_blades_count>&
scp_tensor_em()
{
	return _private::product_tensor_scp_em<model>::run();
}

}

#endif // !_GA_SCALAR_PRODUCT_TENSOR_
