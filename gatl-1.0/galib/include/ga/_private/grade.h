/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_GRADE_
#define _GA_PRIVATE_GRADE_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::grade<store> struct definition.
 *******************************************************************************************************/

// The base struct for create the grade function.
template<typename store>
struct grade
{
	// The main method.
	static _GA_ALWAYS_INLINE
	int run(const real_t *coefficient, const real_t &tolerance)
	{
		const int next = grade<typename store::next>::run( coefficient + 1, tolerance );

		if (is_zero( *coefficient, tolerance ))
		{
			return next;
		}
		else
		{
			const int current = bit_count<store::bitmap>::result;
			return ((next == 0) || (next == current)) ? current : -1;
		}
	}
};

// Specialization of grade<store> for store equal to store_none.
template<>
struct grade<store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	int run(const real_t *coefficient, const real_t &tolerance)
	{
		return 0;
	}
};

}

}

#endif // !_GA_PRIVATE_GRADE_
