/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_HAS_GRADE_
#define _GA_PRIVATE_HAS_GRADE_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::has_grade<grade,store> struct definition.
 *******************************************************************************************************/

// Returns whether basis blades of the given grade is stored by a given store struct.
template<int grade, typename store>
struct has_grade
{
	// The query result.
	static const bool result = ((grade == bit_count<store::bitmap>::result) || (has_grade<grade,typename store::next>::result));
};

// Specialization of has_grade<grade,store> for store equal to store_none.
template<int grade>
struct has_grade<grade,store_none>
{
	// The end of the list was reached.
	static const bool result = false;
};

/*******************************************************************************************************
 * ga::_private::has_grade_runtime<store> struct definition.
 *******************************************************************************************************/

// Returns whether basis blades of the given grade is stored by a given store struct.
template<typename store>
struct has_grade_runtime
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const int grade, const real_t *coefficients, const real_t &tolerance)
	{
		return (((grade == bit_count<store::bitmap>::result) && (!bmath::is_zero( *coefficients, tolerance ))) || (has_grade_runtime<typename store::next>::run( grade, coefficients + 1, tolerance )));
	}
};

// Specialization of has_grade_runtime<store> for store equal to store_none.
template<>
struct has_grade_runtime<store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const int grade, const real_t *coefficients, const real_t &tolerance)
	{
		return false;
	}
};

}

}

#endif // !_GA_PRIVATE_HAS_GRADE_
