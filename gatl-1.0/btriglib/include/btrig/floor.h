/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_FLOOR_
#define _BTRIG_FLOOR_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using std::floor;

/*******************************************************************************************************
 * Floor function implementations.
 *******************************************************************************************************/

_btrig_declare_unary_operation(degrees,floor)
_btrig_declare_unary_operation(radians,floor)

}

#endif // !_BTRIG_FLOOR_
