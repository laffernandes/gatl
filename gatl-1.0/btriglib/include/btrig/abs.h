/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_ABS_
#define _BTRIG_ABS_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using std::abs;

/*******************************************************************************************************
 * Absolute function implementations.
 *******************************************************************************************************/

_btrig_declare_unary_operation(degrees,abs)
_btrig_declare_unary_operation(radians,abs)

}

#endif // !_BTRIG_ABS_
