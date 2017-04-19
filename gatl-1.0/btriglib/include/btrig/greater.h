/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_GREATER_
#define _BTRIG_GREATER_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * "Greater than" operator implementations.
 *******************************************************************************************************/

_btrig_declare_binary_test_operator(degrees,>)
_btrig_declare_binary_test_operator(radians,>)

}

#endif // !_BTRIG_GREATER_
