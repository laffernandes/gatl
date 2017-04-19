/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_HOMOGENEOUS_PRIVATE_CONSTS_
#define _GA_HOMOGENEOUS_PRIVATE_CONSTS_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the homogeneous model.
namespace homogeneous
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::homogeneous::_private::consts<model> struct definition.
 *******************************************************************************************************/

// This struct specifies some useful constant values for a given homogeneous model.
template<typename model>
struct consts
{
	// Specifies the unit vector e0.
	static _GA_ALWAYS_INLINE
	const multivector<model,store<model::origin_vector_bitmap> >& e0()
	{
		static multivector<model,store<model::origin_vector_bitmap> > result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_HOMOGENEOUS_PRIVATE_CONSTS_E0)
			{
				if (first_time)
				{
					result[0] = 1;
					first_time = false;
				}
			}
		}

		return result;
	}

	// Specifies the inverse of the unit vector e0.
	static _GA_ALWAYS_INLINE
	const multivector<model,store<model::origin_vector_bitmap> >& ie0()
	{
		static multivector<model,store<model::origin_vector_bitmap> > result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_HOMOGENEOUS_PRIVATE_CONSTS_INVERSE_E0)
			{
				if (first_time)
				{
					result = inverse( e0(), 0 );
					first_time = false;
				}
			}
		}

		return result;
	}
};

}

}

}

#endif // !_GA_HOMOGENEOUS_PRIVATE_CONSTS_
