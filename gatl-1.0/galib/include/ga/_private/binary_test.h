/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_BINARY_TEST_
#define _GA_PRIVATE_BINARY_TEST_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::binary_test<test,store1,store2> struct definition.
 *******************************************************************************************************/

// The base struct for create binary tests over the basis blades stored by two multivectors.
template<typename test, typename store1, typename store2>
struct binary_test
{
private:

	// This struct is specialized for the case where the basis blade at left comes before the basis blade at right.
	template<bitmap_t bitmap1, bitmap_t bitmap2, int cmp = ((bitmap1 < bitmap2) ? -1 : ((bitmap1 > bitmap2) ? 1 : 0))>
	struct loop
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(const real_t *coefficient1, const real_t *coefficient2)
		{
			return ((test::run( *coefficient1, static_cast<real_t>( 0 ) )) && (binary_test<test,typename store1::next,store2>::run( coefficient1 + 1, coefficient2 )));
		}
	};

	// Specialization of loop for the case where the basis blade at left is equals to the basis blade at right.
	template<bitmap_t bitmap1, bitmap_t bitmap2>
	struct loop<bitmap1,bitmap2,0>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(const real_t *coefficient1, const real_t *coefficient2)
		{
			return ((test::run( *coefficient1, *coefficient2 )) && (binary_test<test,typename store1::next,typename store2::next>::run( coefficient1 + 1, coefficient2 + 1 )));
		}
	};

	// Specialization of loop for the case where the basis blade at left comes after the basis blade at right.
	template<bitmap_t bitmap1, bitmap_t bitmap2>
	struct loop<bitmap1,bitmap2,1>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(const real_t *coefficient1, const real_t *coefficient2)
		{
			return ((test::run( static_cast<real_t>( 0 ), *coefficient2 )) && (binary_test<test,store1,typename store2::next>::run( coefficient1, coefficient2 + 1 )));
		}
	};

public:
	
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *coefficient1, const real_t *coefficient2)
	{
		return loop<store1::bitmap,store2::bitmap>::run( coefficient1, coefficient2 );
	}
};

// Specialization of binary_test<test,store1,store2> for store1 equals to store_none.
template<typename test, typename store2>
struct binary_test<test,store_none,store2>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *coefficient1, const real_t *coefficient2)
	{
		return ((test::run( static_cast<real_t>( 0 ), *coefficient2 )) && (binary_test<test,store_none,typename store2::next>::run( NULL, coefficient2 + 1 )));
	}
};

// Specialization of binary_test<test,store1,store2> for store2 equals to store_none.
template<typename test, typename store1>
struct binary_test<test,store1,store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *coefficient1, const real_t *coefficient2)
	{
		return ((test::run( *coefficient1, static_cast<real_t>( 0 ) )) && (binary_test<test,typename store1::next,store_none>::run( coefficient1 + 1, NULL )));
	}
};

// Specialization of binary_test<test,store1,store2> for store1 and store2 equals to store_none.
template<typename test>
struct binary_test<test,store_none,store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *coefficient1, const real_t *coefficient2)
	{
		return true;
	}
};

/*******************************************************************************************************
 * ga::_private::are_equal struct definition.
 *******************************************************************************************************/

// The base struct for create the test function that checks whether two multivectors are equal.
struct are_equal
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t &coefficient1, const real_t &coefficient2)
	{
		return bmath::is_zero( coefficient1 - coefficient2 );
	}
};

}

}

#endif // !_GA_PRIVATE_BINARY_TEST_
