/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_STD_SWAP_
#define _BTRIG_STD_SWAP_

// The namespace of the standard C++ template library.
namespace std
{

/*******************************************************************************************************
 * Some useful macro for std::swap<type>() function specialization (internal use only).
 *******************************************************************************************************/

// Macro for declaring a specialized std::swap<type> function.
#define _btrig_declare_swap(angle_class) \
	template<typename real_type> \
	inline \
	void \
	swap(btrig::angle_class<real_type> &value1, btrig::angle_class<real_type> &value2) \
	{ \
		swap( value1.m_value, value2.m_value ); \
	} \

/*******************************************************************************************************
 * Swap function specializations.
 *******************************************************************************************************/

_btrig_declare_swap(degrees)
_btrig_declare_swap(radians)

/*******************************************************************************************************
 * Cleanup.
 *******************************************************************************************************/

#undef _btrig_declare_swap

}

#endif // !_BTRIG_STD_SWAP_
