/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_BINARY_ADDITIVE_
#define _GA_PRIVATE_BINARY_ADDITIVE_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::binary_addivite<op,store1,store2> struct definition.
 *******************************************************************************************************/

// The base struct for create the addition and the subtraction operations.
template<typename op, typename store1, typename store2>
struct binary_addivite
{
private:

	// This struct is specialized for the case where the basis blade at left comes before the basis blade at right.
	template<bitmap_t bitmap1, bitmap_t bitmap2, int cmp>
	struct loop
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *result, const real_t *coefficient1, const real_t *coefficient2)
		{
			(*result) = op::run( *coefficient1, 0 );
			binary_addivite<op,typename store1::next,store2>::run( result + 1, coefficient1 + 1, coefficient2 );
		}
	};

	// Specialization of loop for the case where the basis blade at left is equal to the basis blade at right.
	template<bitmap_t bitmap1, bitmap_t bitmap2>
	struct loop<bitmap1,bitmap2,0>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *result, const real_t *coefficient1, const real_t *coefficient2)
		{
			(*result) = op::run( *coefficient1, *coefficient2 );
			binary_addivite<op,typename store1::next,typename store2::next>::run( result + 1, coefficient1 + 1, coefficient2 + 1 );
		}
	};

	// Specialization of loop for the case where the basis blade at left comes after the basis blade at right.
	template<bitmap_t bitmap1, bitmap_t bitmap2>
	struct loop<bitmap1,bitmap2,1>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *result, const real_t *coefficient1, const real_t *coefficient2)
		{
			(*result) = op::run( 0, *coefficient2 );
			binary_addivite<op,store1,typename store2::next>::run( result + 1, coefficient1, coefficient2 + 1 );
		}
	};

public:
	
	// This recursive template call creates a list with all the basis blades resulting from the addition/subtraction of a specialized multivector by another specialized multivector.
	typedef typename merge_stores<store1,store2>::result store_result;

	// The main method.
	static _GA_ALWAYS_INLINE
	void run(real_t *result, const real_t *coefficient1, const real_t *coefficient2)
	{
		loop<
				store1::bitmap,
				store2::bitmap,
				((store1::bitmap < store2::bitmap) ? -1 : ((store1::bitmap > store2::bitmap) ? 1 : 0))
			>::run( result, coefficient1, coefficient2 );
	}
};

// Specialization of binary_addivite<op,store1,store2> for store1 equal to store_none.
template<typename op, typename store2>
struct binary_addivite<op,store_none,store2>
{
	// Specifies the list with all the basis blades resulting from the operation.
	typedef store2 store_result;

	// The main method.
	static _GA_ALWAYS_INLINE
	void run(real_t *result, const real_t *coefficient1, const real_t *coefficient2)
	{
		(*result) = op::run( 0, *coefficient2 );
		binary_addivite<op,store_none,typename store2::next>::run( result + 1, NULL, coefficient2 + 1 );
	}
};

// Specialization of binary_addivite<op,store1,store2> for store2 equal to store_none.
template<typename op, typename store1>
struct binary_addivite<op,store1,store_none>
{
	// Specifies the list with all the basis blades resulting from the operation.
	typedef store1 store_result;

	// The main method.
	static _GA_ALWAYS_INLINE
	void run(real_t *result, const real_t *coefficient1, const real_t *coefficient2)
	{
		(*result) = op::run( *coefficient1, 0 );
		binary_addivite<op,typename store1::next,store_none>::run( result + 1, coefficient1 + 1, NULL );
	}
};

// Specialization of binary_addivite<op,store1,store2> for store1 and store2 equal to store_none.
template<typename op>
struct binary_addivite<op,store_none,store_none>
{
	// Specifies an empty list of stored basis blades.
	typedef store_none store_result;

	// The main method.
	static _GA_ALWAYS_INLINE
	void run(const real_t *result, const real_t *coefficient1, const real_t *coefficient2)
	{
	}
};

/*******************************************************************************************************
 * ga::_private::addition struct definition.
 *******************************************************************************************************/

// The base struct for create the addition operation.
struct addition
{
	// Main method.
	static _GA_ALWAYS_INLINE
	real_t run(const real_t &coefficient1, const real_t &coefficient2)
	{
		return (coefficient1 + coefficient2);
	}
};

/*******************************************************************************************************
 * ga::_private::subtraction struct definition.
 *******************************************************************************************************/

// The base struct for create the subtraction operation.
struct subtraction
{
	// Main method.
	static _GA_ALWAYS_INLINE
	real_t run(const real_t &coefficient1, const real_t &coefficient2)
	{
		return (coefficient1 - coefficient2);
	}
};

}

}

#endif // !_GA_PRIVATE_BINARY_ADDITIVE_
