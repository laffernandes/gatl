/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_FAST_FACTORIZATION_
#define _GA_FAST_FACTORIZATION_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Fast factorization function implementations.
 *******************************************************************************************************/

// Performs the blade factorization by the outer product. For a given blade 'B' of grade 'k', this method returns a set of 'k' vectors 'b_{i}' such that 'B = b_{1} ^ b_{2} ^ ... b_{k}'. This implementation uses the Eucliden metric for convenience, because we are only concerned with the outer product of the factors. The output may not be a set of orthonormal factors in the previously assumed Euclidean metric. Notice that may not be the metric of the space of interest, resulting in non-orthonormal factors in such metric. The algorithm is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
template<typename model, typename store_factor, typename store>
inline
void
fast_factorize_em(real_t &scalar, std::vector<multivector<model,store_factor> > &factors, const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The input multivector should be blade." );

	// Find the basis blade F in the representation of B with the largest coordinate.
	index_t largest_i = 0;
	real_t current, largest = abs( m[0] );
	for (index_t i=1; i<m.size; ++i)
	{
		current = abs( m[i] );
		if (largest < current)
		{
			largest = current;
			largest_i = i;
		}
	}

	multivector<model,store> F;
	F = multivector<model,store_none>();

	F[largest_i] = 1;
	bitmap_t F_bitmap = m.basis_blade( largest_i ).bitmap;

	// Determine the scalar value.
	scalar = m[largest_i];

	// Determine the factors.
	if ((F_bitmap != 0) && (!is_zero( largest, tolerance )))
	{
		typedef multivector<model,typename store_grade_range<1,1,model,_private::basis_vectors<store>::result>::store_type> vector_t;

		// Compute the grade of F.
		int k = 0;

		for (bitmap_t bitmap=F_bitmap; bitmap!=0; bitmap>>=1)
		{
			if (bitmap & 1)
			{
				++k;
			}
		}

		factors.resize( k );

		// Let the scaled input blade be Bs <- B / s and iterate over the basis vectors that span F.
		const multivector<model,store> &Bs = gp_em( inverse_em( scalar, tolerance ), m );
		const multivector<model,store> &iF = inverse_em( F, tolerance );

		// For all basis vectors fi of F...
		vector_t fi;
		typename std::vector<multivector<model,store_factor> >::iterator factor = factors.begin();
		
		fi = multivector<model,store_none>();
		for (index_t i=0; F_bitmap!=0; ++i)
		{
			// Check whether the blade is factorizable by the current basis vector.
			if ((F_bitmap & vector_t::basis_blade( i ).bitmap) != 0)
			{
				fi[i] = 1;

				// Compute the factor.
				assign<true>( *factor, lcont_em( lcont_em( fi, iF ), Bs ), tolerance );

				// Go to the next basis vector (and next factor).
				F_bitmap ^= vector_t::basis_blade( i ).bitmap;
				++factor;

				fi[i] = 0;
			}
		}
	}
	else
	{
		factors.clear();
	}
}

// Performs the blade factorization by the outer product. This function is specializaed for zero blades.
template<typename model, typename store_factor>
inline
void
fast_factorize_em(real_t &scalar, std::vector<multivector<model,store_factor> > &factors, const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	scalar = 0;
	factors.clear();
}

// Performs the blade factorization by the outer product. This function is specializaed for scalar values.
template<typename model, typename store_factor>
inline
void
fast_factorize_em(real_t &scalar, std::vector<multivector<model,store_factor> > &factors, const multivector<model,store_scalar> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	scalar = m[0];
	factors.clear();
}

// Performs the blade factorization by the outer product. This function is specializaed for scalar values.
template<typename model, typename store_factor>
inline
void
fast_factorize_em(real_t &scalar, std::vector<multivector<model,store_factor> > &factors, const real_t &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	scalar = m;
	factors.clear();
}

}

#endif // !_GA_FAST_FACTORIZATION_
