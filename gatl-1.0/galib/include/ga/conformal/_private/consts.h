/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CONFORMAL_PRIVATE_CONSTS_
#define _GA_CONFORMAL_PRIVATE_CONSTS_

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
 * ga::conformal::_private::consts<model> struct definition.
 *******************************************************************************************************/

// This struct specifies some useful constant values for a given conformal model.
template<typename model>
struct consts
{
	// Specifies the point at origin.
	static _GA_ALWAYS_INLINE
	const multivector<model,store<model::origin_point_bitmap> >& no()
	{
		static multivector<model,store<model::origin_point_bitmap> > result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_CONFORMAL_PRIVATE_CONSTS_NO)
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

	// Specifies the point at infinity.
	static _GA_ALWAYS_INLINE
	const multivector<model,store<model::infinity_point_bitmap> >& ni()
	{
		static multivector<model,store<model::infinity_point_bitmap> > result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_CONFORMAL_PRIVATE_CONSTS_NI)
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
};

}

}

}

#endif // !_GA_CONFORMAL_PRIVATE_CONSTS_
