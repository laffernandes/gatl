/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_TAKE_LARGEST_GRADE_
#define _GA_PRIVATE_TAKE_LARGEST_GRADE_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::take_largest_grade<store> struct definition.
 *******************************************************************************************************/

// The base struct for create the operation that returns the largest grade part of a specialized multivector.
template<typename store>
struct take_largest_grade
{
	// The main method.
	static _GA_ALWAYS_INLINE
	int run(real_t *result, const real_t *coefficient, const int largestSoFar, const real_t &tolerance)
	{
		static const int current = bit_count<store::bitmap>::result;

		// Call to the next state of this recursive template.
		const bool isZero = is_zero( *coefficient, tolerance );
		const int largest = take_largest_grade<typename store::next>::run( result + 1, coefficient + 1, (((isZero) || (largestSoFar >= current)) ? largestSoFar : current), tolerance );

		// Copy current coefficient when current grade is the largest, otherwise set zero to the resulting coefficient.
		(*result) = (largest == current) ? (*coefficient) : static_cast<real_t>( 0 );

		// Return the largest coefficient.
		return largest;
	}
};

// Specializatin of take_largest_grade<store> for store equal to store_none.
template<>
struct take_largest_grade<store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	int run(const real_t *result, const real_t *coefficient, const int largest, const real_t &tolerance)
	{
		return largest;
	}
};

}

}

#endif // !_GA_PRIVATE_TAKE_LARGEST_GRADE_
