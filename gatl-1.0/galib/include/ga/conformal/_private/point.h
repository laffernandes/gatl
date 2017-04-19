/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_PRIVATE_POINT_
#define _GA_CONFORMAL_PRIVATE_POINT_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the conformal model.
namespace conformal
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::conformal::_private::point<store,no,ni> struct definition.
 *******************************************************************************************************/

// The base struct for create the point initialization function.
template<typename store, bitmap_t no, bitmap_t ni>
struct point
{
private:

	// This struct is specialized for the case where the current stored basis blade is a basis vector of the base space.
	template<int cmp, int dummy>
	struct loop
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *coefficients, const real_t *input, const real_t &half_sqr)
		{
			(*coefficients) = (*input);
			point<typename store::next,no,ni>::run( coefficients + 1, input + 1, half_sqr );
		}
	};

	// This struct is specialized for the case where the current stored basis blade is the basis vector interpreted as the point at origin.
	template<int dummy>
	struct loop<1,dummy>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *coefficients, const real_t *input, const real_t &half_sqr)
		{
			(*coefficients) = 1;
			point<typename store::next,no,ni>::run( coefficients + 1, input, half_sqr );
		}
	};

	// This struct is specialized for the case where the current stored basis blade is the basis vector interpreted as the point at infinity.
	template<int dummy>
	struct loop<2,dummy>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *coefficients, const real_t *input, const real_t &half_sqr)
		{
			(*coefficients) = half_sqr;
			point<typename store::next,no,ni>::run( coefficients + 1, input, half_sqr );
		}
	};

	// This struct is specialized for the case where the current stored basis blade is not a basis vector.
	template<int dummy>
	struct loop<3,dummy>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *coefficients, const real_t *input, const real_t &half_sqr)
		{
			(*coefficients) = 0;
			point<typename store::next,no,ni>::run( coefficients + 1, input, half_sqr );
		}
	};

public:

	// The main method
	static _GA_ALWAYS_INLINE
	void run(real_t *coefficients, const real_t *input, const real_t &half_sqr)
	{
		loop<
				((ga::_private::bit_count<store::bitmap>::result == 1) ? (
					(store::bitmap == no) ? 1 :
					(store::bitmap == ni) ? 2 :
					0
				) : (
					3
				)),
				0
			>::run( coefficients, input, half_sqr );
	}
};

// Specialization of point<store,no,ni> for store equal to store_none.
template<bitmap_t no, bitmap_t ni>
struct point<store_none,no,ni>
{
	// The main method
	static _GA_ALWAYS_INLINE
	void run(const real_t *coefficients, const real_t *input, const real_t &half_sqr)
	{
	}
};

}

}

}

#endif // !_GA_CONFORMAL_PRIVATE_POINT_
