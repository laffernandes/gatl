/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_CONSTS_
#define _GA_PRIVATE_CONSTS_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::consts<model> struct definition.
 *******************************************************************************************************/

// This struct specifies some useful constant values for a given geometric algebra model
template<typename model>
struct consts
{
	// Specifies the unit pseudoscalar of the whole space.
	static _GA_ALWAYS_INLINE
	const multivector<model,typename store_pseudoscalar<model>::store_type>& I()
	{
		static multivector<model,typename store_pseudoscalar<model>::store_type> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_CONSTS_PSEUDOSCALAR)
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

	// Specifies the inverse unit pseudoscalar of the whole space.
	static _GA_ALWAYS_INLINE
	const multivector<model,typename store_pseudoscalar<model>::store_type>& iI()
	{
		static multivector<model,typename store_pseudoscalar<model>::store_type> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_CONSTS_INVERSE_PSEUDOSCALAR)
			{
				if (first_time)
				{
					result = inverse( I(), 0 );
					first_time = false;
				}
			}
		}

		return result;
	}
};

/*******************************************************************************************************
 * ga::_private::consts_em<model> struct definition.
 *******************************************************************************************************/

// This struct specifies some useful constant values for a given geometric algebra model (forcing Euclidean metric).
template<typename model>
struct consts_em
{
	// Specifies the unit pseudoscalar of the whole space.
	static _GA_ALWAYS_INLINE
	const multivector<model,typename store_pseudoscalar<model>::store_type>& I()
	{
		static multivector<model,typename store_pseudoscalar<model>::store_type> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_CONSTS_EM_PSEUDOSCALAR)
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

	// Specifies the inverse unit pseudoscalar of the whole space.
	static _GA_ALWAYS_INLINE
	const multivector<model,typename store_pseudoscalar<model>::store_type>& iI()
	{
		static multivector<model,typename store_pseudoscalar<model>::store_type> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_CONSTS_EM_INVERSE_PSEUDOSCALAR)
			{
				if (first_time)
				{
					result = inverse_em( I(), 0 );
					first_time = false;
				}
			}
		}

		return result;
	}
};

}

}

#endif // !_GA_PRIVATE_CONSTS_
