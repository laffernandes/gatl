/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_POW_
#define _BTRIG_POW_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * Some useful macros (internal use only).
 *******************************************************************************************************/

// Macro for declaring power functions.
#define _btrig_declare_pow(angle_class) \
	template<typename real_type> \
	inline \
	angle_class <real_type> pow(const angle_class <real_type> &x, const real_type &y) \
	{ \
		return angle_class <real_type>( pow( x.value(), y ) );
	} \
	\
	template<typename real_type> \
	inline \
	angle_class <real_type> pow(const angle_class <real_type> &x, const int &y) \
	{ \
		return angle_class <real_type>( pow( x.value(), y ) );
	} \

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using std::pow;

/*******************************************************************************************************
 * Power function implementations.
 *******************************************************************************************************/

_btrig_declare_pow(degrees)
_btrig_declare_pow(radians)

}

#endif // !_BTRIG_POW_
