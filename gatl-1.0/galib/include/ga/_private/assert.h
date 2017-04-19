/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_ASSERT_
#define _GA_ASSERT_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * ga::assertion_error class definition.
 *******************************************************************************************************/

// Assertion error definition.
class assertion_error : public std::runtime_error
{
public:

	// Class constructor.
	assertion_error(const char * const &message) : std::runtime_error( message )
	{
	}
};
	
// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * Assertion level definition for debug mode.
 *******************************************************************************************************/

#if !defined(NDEBUG) && !defined(GA_HIGHEST_ASSERTION_LEVEL)

// Specifies the assertion level.
#define GA_HIGHEST_ASSERTION_LEVEL

#endif // !NDEBUG && !GA_HIGHEST_ASSERTION_LEVEL

/*******************************************************************************************************
 * Persistent assert macro definition.
 *******************************************************************************************************/

// Persistent assert macro.
#define ga_always_assert(expr,msg) (void)( (!!(expr)) || (ga::_private::throw_exception( msg, __FILE__, __LINE__ )) )

/*******************************************************************************************************
 * Debug time assert macro definition.
 *******************************************************************************************************/

// Debug time assert macro.
#define ga_debug_assert(expr) assert(expr)

/*******************************************************************************************************
 * Non-persistent assert macro definition.
 *******************************************************************************************************/

#ifdef GA_HIGHEST_ASSERTION_LEVEL

// Non-persistent assert macro.
#define ga_maybe_assert(expr,msg) ((void)((!!(expr)) || (ga::_private::throw_exception( (msg), __FILE__, __LINE__ ))))

#else // GA_HIGHEST_ASSERTION_LEVEL

// Non-persistent assert macro.
#define ga_maybe_assert(expr,msg) ((void)(0))

#endif // GA_HIGHEST_ASSERTION_LEVEL

/*******************************************************************************************************
 * Compile time assert macro definition.
 *******************************************************************************************************/

// Compile time assert macro.
#define ga_static_assert(expr) static_assert(expr)

/*******************************************************************************************************
 * Exception function definition.
 *******************************************************************************************************/

// Throws an exception with the given error message.
_GA_ALWAYS_INLINE
bool
throw_exception(const char *msg, const char *file, unsigned int line)
{
	std::ostringstream os;
	os << msg;

#ifndef NDEBUG
	os << " (file " << file << ", line " << line << ")";
#endif // !NDEBUG

	throw assertion_error( os.str().c_str() );
	return false;
}

}

}

#endif // !_GA_ASSERT_
