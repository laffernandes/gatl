/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_OPERATION_MATRIX_
#define _GA_OPERATION_MATRIX_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * ga::multiplication_type type definition.
 *******************************************************************************************************/

// Matrix multiplication convension types.
enum multiplication_type
{
	right_multiplication = 0, // r = M*a
	left_multiplication       // r = a*M
};

}

#endif // !_GA_OPERATION_MATRIX_
