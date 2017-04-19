/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _STOOLS_PRIVATE_STATIC_ASSERT_
#define _STOOLS_PRIVATE_STATIC_ASSERT_

// The namespace of the static tools library.
namespace stools
{

// A namespace for internal use of the static tools library.
namespace _private
{

/*******************************************************************************************************
 * stools::_private::static_assert<expr> struct definition.
 *******************************************************************************************************/

// The base struct for create the compile-time assertion failure. stools::_private::static_assertion_failure<expr> takes a single boolean template parameter, and works by only providing a specialization for true. Attempting to call stools::_static::static_assertion_failure<false> causes a compile-time error.
template<bool>
struct static_assertion_failure;

// Specialization of stools::_private::static_assertion_failure<expr> for expr equal to true.
template<>
struct static_assertion_failure<true>
{
};

// The base struct for create the compile-time assetion test.
template<int size>
struct static_assert_test
{
};

}

}

#endif // !_STOOLS_PRIVATE_STATIC_ASSERT_
