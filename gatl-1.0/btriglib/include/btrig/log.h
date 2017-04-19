/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_LOG_
#define _BTRIG_LOG_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using std::log;
using std::log10;

/*******************************************************************************************************
 * Logarithm function implementations.
 *******************************************************************************************************/

_btrig_declare_unary_operation(degrees,log)
_btrig_declare_unary_operation(radians,log)

_btrig_declare_unary_operation(degrees,log10)
_btrig_declare_unary_operation(radians,log10)

}

#endif // !_BTRIG_LOG_
