/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_SQRT_
#define _BTRIG_SQRT_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using std::sqrt;

/*******************************************************************************************************
 * Square root function implementations.
 *******************************************************************************************************/

_btrig_declare_unary_operation(degrees,sqrt)
_btrig_declare_unary_operation(radians,sqrt)

}

#endif // !_BTRIG_SQRT_
