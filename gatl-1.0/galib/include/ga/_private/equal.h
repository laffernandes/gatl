/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_EQUAL_
#define _GA_PRIVATE_EQUAL_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::equal<store1,store2> struct definition.
 *******************************************************************************************************/

// The base struct for create binary tests over the basis blades stored by two multivectors.
template<typename store1, typename store2>
struct equal
{
private:

	// This struct is specialized for the case where the basis blade at left comes before the basis blade at right.
	template<bitmap_t bitmap1, bitmap_t bitmap2, int cmp>
	struct loop
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(const real_t *coefficient1, const real_t *coefficient2, const real_t &tolerance)
		{
			return ((bmath::is_zero( *coefficient1, tolerance )) && (equal<typename store1::next,store2>::run( coefficient1 + 1, coefficient2, tolerance )));
		}
	};

	// Specialization of loop for the case where the basis blade at left is equal to the basis blade at right.
	template<bitmap_t bitmap1, bitmap_t bitmap2>
	struct loop<bitmap1,bitmap2,0>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(const real_t *coefficient1, const real_t *coefficient2, const real_t &tolerance)
		{
			return ((bmath::equal( (*coefficient1), (*coefficient2), tolerance )) && (equal<typename store1::next,typename store2::next>::run( coefficient1 + 1, coefficient2 + 1, tolerance )));
		}
	};

	// Specialization of loop for the case where the basis blade at left comes after the basis blade at right.
	template<bitmap_t bitmap1, bitmap_t bitmap2>
	struct loop<bitmap1,bitmap2,1>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(const real_t *coefficient1, const real_t *coefficient2, const real_t &tolerance)
		{
			return ((bmath::is_zero( *coefficient2, tolerance )) && (equal<store1,typename store2::next>::run( coefficient1, coefficient2 + 1, tolerance )));
		}
	};

public:
	
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *coefficient1, const real_t *coefficient2, const real_t &tolerance)
	{
		return loop<
				store1::bitmap,
				store2::bitmap,
				((store1::bitmap < store2::bitmap) ? -1 : ((store1::bitmap > store2::bitmap) ? 1 : 0))
			>::run( coefficient1, coefficient2, tolerance );
	}
};

// Specialization of equal<store1,store2> for store1 equal to store_none.
template<typename store2>
struct equal<store_none,store2>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *coefficient1, const real_t *coefficient2, const real_t &tolerance)
	{
		return ((bmath::is_zero( *coefficient2, tolerance )) && (equal<store_none,typename store2::next>::run( NULL, coefficient2 + 1, tolerance )));
	}
};

// Specialization of equal<store1,store2> for store2 equal to store_none.
template<typename store1>
struct equal<store1,store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *coefficient1, const real_t *coefficient2, const real_t &tolerance)
	{
		return ((bmath::is_zero( *coefficient1, tolerance )) && (equal<typename store1::next,store_none>::run( coefficient1 + 1, NULL, tolerance )));
	}
};

// Specialization of equal<store1,store2> for store1 and store2 equal to store_none.
template<>
struct equal<store_none,store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *coefficient1, const real_t *coefficient2, const real_t &tolerance)
	{
		return true;
	}
};

}

}

#endif // !_GA_PRIVATE_EQUAL_
