/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_OUTER_PRODUCT_TENSOR_
#define _GA_OUTER_PRODUCT_TENSOR_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Outer product tensor.
 *******************************************************************************************************/

// Computes the outer product tensor for the given geometric algebra model.
template<typename model>
inline
const la::dtensor3<real_t,model::basis_blades_count>&
op_tensor()
{
	return _private::product_tensor_op<model>::run();
}

}

#endif // !_GA_OUTER_PRODUCT_TENSOR_
