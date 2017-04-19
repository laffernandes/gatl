/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_ASSIGN_
#define _GA_PRIVATE_ASSIGN_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{
	
/*******************************************************************************************************
 * ga::_private::assign<secure_cast,store_target,store_source> struct definition.
 *******************************************************************************************************/

// The base struct for create the assign operation. This implementation assumes secure_cast equal to true.
template<bool secure_cast, typename store_target, typename store_source>
struct assign
{
private:

	// This struct is specialized for the case where the basis blade at left comes before the basis blade at right.
	template<bitmap_t bitmap_target, bitmap_t bitmap_source, int cmp>
	struct loop
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(real_t *target, const real_t *source, const real_t &tolerance)
		{
			(*target) = 0;
			return assign<secure_cast,typename store_target::next,store_source>::run( target + 1, source, tolerance );
		}
	};

	// This struct is specialized for the case where the basis blade at left is equal to the basis blade at right.
	template<bitmap_t bitmap_target, bitmap_t bitmap_source>
	struct loop<bitmap_target,bitmap_source,0>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(real_t *target, const real_t *source, const real_t &tolerance)
		{
			(*target) = (*source);
			return assign<secure_cast,typename store_target::next,typename store_source::next>::run( target + 1, source + 1, tolerance );
		}
	};

	// This struct is specialized for the case where the basis blade at left comes after the basis blade at right.
	template<bitmap_t bitmap_target, bitmap_t bitmap_source>
	struct loop<bitmap_target,bitmap_source,1>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(real_t *target, const real_t *source, const real_t &tolerance)
		{
			ga_debug_assert( bmath::is_zero( *source, tolerance ) );
			return ((bmath::is_zero( *source, tolerance )) && (assign<secure_cast,store_target,typename store_source::next>::run( target, source + 1, tolerance )));
		}
	};

public:

	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(real_t *target, const real_t *source, const real_t &tolerance)
	{
		return loop<
				store_target::bitmap,
				store_source::bitmap,
				((store_target::bitmap < store_source::bitmap) ? -1 : ((store_target::bitmap > store_source::bitmap) ? 1 : 0))
			>::run( target, source, tolerance );
	}
};

// Specialization of assign<secure_cast,store_target,store_source> for store_target equal to store_none. This implementation assumes secure_cast equal to true.
template<bool secure_cast, typename store_source>
struct assign<secure_cast,store_none,store_source>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(real_t *target, const real_t *source, const real_t &tolerance)
	{
		ga_debug_assert( bmath::is_zero( *source, tolerance ) );
		return ((bmath::is_zero( *source, tolerance )) && (assign<secure_cast,store_none,typename store_source::next>::run( NULL, source + 1, tolerance )));
	}
};

// Specialization of assign<secure_cast,store_target,store_source> for store_source equal to store_none. This implementation assumes secure_cast equal to true.
template<bool secure_cast, typename store_target>
struct assign<secure_cast,store_target,store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(real_t *target, const real_t *source, const real_t &tolerance)
	{
		(*target) = 0;
		return assign<secure_cast,typename store_target::next,store_none>::run( target + 1, NULL, tolerance );
	}
};

// Specialization of assign<secure_cast,store_target,store_source> for store_target and store_source equal to store_none. This implementation assumes secure_cast equal to true.
template<bool secure_cast>
struct assign<secure_cast,store_none,store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *target, const real_t *source, const real_t &tolerance)
	{
		return true;
	}
};

#ifndef GA_HIGHEST_ASSERTION_LEVEL

// Specialization of assign<secure_cast,store_target,store_source> for secure_cast equal to false.
template<typename store_target, typename store_source>
struct assign<false,store_target,store_source>
{
private:

	// This struct is specialized for the case where the basis blade at left comes before the basis blade at right.
	template<bitmap_t bitmap_target, bitmap_t bitmap_source, int cmp>
	struct loop
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(real_t *target, const real_t *source, const real_t &tolerance)
		{
			(*target) = 0;
			return assign<false,typename store_target::next,store_source>::run( target + 1, source, tolerance );
		}
	};

	// This struct is specialized for the case where the basis blade at left is equal to the basis blade at right.
	template<bitmap_t bitmap_target, bitmap_t bitmap_source>
	struct loop<bitmap_target,bitmap_source,0>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(real_t *target, const real_t *source, const real_t &tolerance)
		{
			(*target) = (*source);
			return assign<false,typename store_target::next,typename store_source::next>::run( target + 1, source + 1, tolerance );
		}
	};

	// This struct is specialized for the case where the basis blade at left comes after the basis blade at right.
	template<bitmap_t bitmap_target, bitmap_t bitmap_source>
	struct loop<bitmap_target,bitmap_source,1>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		bool run(real_t *target, const real_t *source, const real_t &tolerance)
		{
			return assign<false,store_target,typename store_source::next>::run( target, source + 1, tolerance );
		}
	};

public:

	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(real_t *target, const real_t *source, const real_t &tolerance)
	{
		return loop<
				store_target::bitmap,
				store_source::bitmap,
				((store_target::bitmap < store_source::bitmap) ? -1 : ((store_target::bitmap > store_source::bitmap) ? 1 : 0))
			>::run( target, source, tolerance );
	}
};

// Specialization of assign<secure_cast,store_target,store_source> for secure_cast equal to false and store_target equal to store_none.
template<typename store_source>
struct assign<false,store_none,store_source>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(real_t *target, const real_t *source, const real_t &tolerance)
	{
		return true;
	}
};

// Specialization of assign<secure_cast,store_target,store_source> for secure_cast equal to false and store_source equal to store_none.
template<typename store_target>
struct assign<false,store_target,store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(real_t *target, const real_t *source, const real_t &tolerance)
	{
		(*target) = 0;
		return assign<false,typename store_target::next,store_none>::run( target + 1, NULL, tolerance );
	}
};

// Specialization of assign<secure_cast,store_target,store_source> for secure_cast equal to false and store_target and store_source equal to store_none.
template<>
struct assign<false,store_none,store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *target, const real_t *source, const real_t &tolerance)
	{
		return true;
	}
};

#endif // !GA_HIGHEST_ASSERTION_LEVEL

}

}

#endif // !_GA_PRIVATE_ASSIGN_
