/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _STOOLS_STATIC_ASSERT_
#define _STOOLS_STATIC_ASSERT_

/*******************************************************************************************************
 * Macro definition.
 *******************************************************************************************************/

#ifdef NDEBUG

// Compile time assert macro.
#define static_assert(expr) ((void)0)

#else // NDEBUG

// Compile time assert macro.
#define static_assert(expr) \
	typedef stools::_private::static_assert_test< \
		sizeof( stools::_private::static_assertion_failure<(expr)> ) \
	> _static_assert_join( static_assertion_failure_, __LINE__ )

// An useful macro.
#define _static_assert_join(x,y) _static_assert_do_join(x,y)

// Another useful macro.
#define _static_assert_do_join(x,y) x##y

#endif // NDEBUG

#endif // !_STOOLS_STATIC_ASSERT_
