/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_TAKE_GRADE_
#define _GA_PRIVATE_TAKE_GRADE_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{
	
/*******************************************************************************************************
 * ga::_private::take_grade<grade,store> struct definition.
 *******************************************************************************************************/

// The base struct for create the operation that returns the k-grade part of a specialized multivector.
template<int grade, typename store>
struct take_grade
{
private:

	// This struct is specialized for the case where the given grade is equal than the grade of the current basis blade.
	template<bitmap_t bitmap, bool same_grade>
	struct loop
	{
		// Stores the current basis blade and call the next state of this recursive template.
		typedef ga::store<bitmap,typename take_grade<grade,typename store::next>::result> result;

		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *result, const real_t *coefficient)
		{
			// Copy current coefficient.
			(*result) = (*coefficient);

			// Call to the next state of this recursive template.
			take_grade<grade,typename store::next>::run( result + 1, coefficient + 1 );
		}
	};

	// This struct is specialized for the case where the given grade is different than the grade of the current basis blade.
	template<bitmap_t bitmap>
	struct loop<bitmap,false>
	{
		// Calls the next state of this recursive template.
		typedef typename take_grade<grade,typename store::next>::result result;

		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *result, const real_t *coefficient)
		{
			take_grade<grade,typename store::next>::run( result, coefficient + 1 );
		}
	};

public:

	// This recursive template call creates a list with all the basis blades resulting from the operation.
	typedef typename loop<store::bitmap,(grade==bit_count<store::bitmap>::result)>::result result;

	// The main method.
	static _GA_ALWAYS_INLINE
	void run(real_t *result, const real_t *coefficient)
	{
		loop<store::bitmap,(grade==bit_count<store::bitmap>::result)>::run( result, coefficient );
	}
};

// Specialization of take_grade<grade,store> for store equal to store_none.
template<int grade>
struct take_grade<grade,store_none>
{
	// Specifies an empty list of stored basis blades.
	typedef store_none result;
	
	// The main method.
	static _GA_ALWAYS_INLINE
	void run(const real_t *result, const real_t *coefficient)
	{
	}
};

/*******************************************************************************************************
 * ga::_private::take_grade_runtime<store> struct definition.
 *******************************************************************************************************/

// The base struct for create the operation that returns the k-grade part of a specialized multivector.
template<typename store>
struct take_grade_runtime
{
	// The main method.
	static _GA_ALWAYS_INLINE
	void run(const int grade, real_t *result, const real_t *coefficient)
	{
		// Set current coefficient.
		(*result) = (grade != bit_count<store::bitmap>::result) ? static_cast<real_t>( 0 ) : (*coefficient);

		// Call to the next state of this recursive template.
		take_grade_runtime<typename store::next>::run( grade, result + 1, coefficient + 1 );
	}
};

// Specialization of take_grade_runtime<store> for store equal to store_none.
template<>
struct take_grade_runtime<store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	void run(const int grade, const real_t *result, const real_t *coefficient)
	{
	}
};

}

}

#endif // !_GA_PRIVATE_TAKE_GRADE_
