/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_IS_EMPTY_STORE_
#define _GA_PRIVATE_IS_EMPTY_STORE_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::is_empty_store<store> struct definition.
 *******************************************************************************************************/

// Specifies whether the given store does not store any basis blade.
template<typename store>
struct is_empty_store
{
	static const bool result = false;
};

// Specialization of is_empty_store<store> for store equal to store_none.
template<>
struct is_empty_store<store_none>
{
	static const bool result = true;
};

}

}

#endif // !_GA_PRIVATE_IS_EMPTY_STORE_
