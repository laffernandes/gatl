/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_FACTORIZATION_
#define _GA_FACTORIZATION_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Factorization function implementations.
 *******************************************************************************************************/

// Performs the blade factorization by the outer product. For a given blade 'B' of grade 'k', this method returns a set of 'k' vectors 'b_{i}' such that 'B = b_{1} ^ b_{2} ^ ... b_{k}'. This implementation uses the Eucliden metric for convenience, because we are only concerned with the outer product of the factors. As a result, the output is a set of orthonormal factors in the previously assumed Euclidean metric. Notice that may not be the metric of the space of interest, resulting in non-orthonormal factors in such metric.
template<typename model, typename store_factor, typename store>
inline
void
factorize_em(real_t &scalar, std::vector<multivector<model,store_factor> > &factors, const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The input multivector should be blade." );

	// Find the basis blade E in the representation of B with the largest coordinate.
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

	bitmap_t E = m.basis_blade( largest_i ).bitmap;

	/* IMPLEMENTATION ISSUES
	 *
	 * The factorization algorithm described in Section 21.6 makes E be the bitmap
	 * of the largest coefficient of B. However, I believe that we must look for
	 * the largest absolute coefficient.
	 */

	if ((E != 0) && (!is_zero( largest, tolerance )))
	{
		typedef typename store_grade_range<1,_private::largest_grade<store>::result,model,_private::basis_vectors<store>::result>::store_type blade_store_t;
		
		typedef multivector<model,store_factor> factor_t;
		typedef multivector<model,blade_store_t> blade_t;
		typedef multivector<model,typename _private::take_grade<1,blade_store_t>::result> vector_t;

		// Compute the grade of E.
		int k = 0;

		for (bitmap_t bitmap=E; bitmap!=0; bitmap>>=1)
		{
			if (bitmap & 1)
			{
				++k;
			}
		}

		factors.resize( k );

		// Determine the norm of the input blade B: s = ||B||.
		scalar = norm_em( m, tolerance )[0];

		// Let the current input blade be Bc <- B / s and iterate over the basis vectors that span E.
		blade_t Bc;
		Bc = gp_em( inverse_em( scalar, tolerance ), m );

		// For all but one of the basis vectors ei of E...
		vector_t gi, ei;
		typename std::vector<factor_t>::iterator factor = factors.begin();
		
		ei = multivector<model,store_none>();
		for (index_t i=0; E!=vector_t::basis_blade( i ).bitmap; ++i)
		{
			// Check whether the blade is factorizable by the current basis vector.
			if ((E & vector_t::basis_blade( i ).bitmap) != 0)
			{
				ei[i] = 1;

				// Project ei onto Bc.
				assign<false>( gi, lcont_em( lcont_em( ei, Bc ), inverse_em( Bc, tolerance ) ), tolerance );

				/* IMPLEMENTATION ISSUES
				 *
				 * The algorithm from Section 21.6 works! However, I believe that by replacing the
				 * geometric product by a left contraction when projection ei onto Bc we will have the
				 * same numerical result but with an improovement at the coefficient storage.
				 * Therefore, I changed the factorization process. Here I compute the orthogonal projection
				 * of a vector onto a blade using the algorithm described in Section 4.2.
				 */

				// Normalize the resulting factor and assign it to the resultin set of factors.
				const vector_t &fi = unit_em( gi, tolerance );
				assign<true>( *factor, fi, tolerance );

				// Update Bc and go to the next basis vector (and next factor).
				assign<false>( Bc, lcont_em( inverse_em( fi, tolerance ), Bc ), tolerance );
				E ^= vector_t::basis_blade( i ).bitmap;
				++factor;

				ei[i] = 0;
			}
		}

		// Obtain the last factor.
		assign<true>( *factor, unit_em( Bc, tolerance ), tolerance );
	}
	else
	{
		assign<false>( scalar, m, tolerance );
		factors.clear();
	}
}

// Performs the blade factorization by the outer product. This function is specializaed for zero blades.
template<typename model, typename store_factor>
inline
void
factorize_em(real_t &scalar, std::vector<multivector<model,store_factor> > &factors, const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	scalar = 0;
	factors.clear();
}

// Performs the blade factorization by the outer product. This function is specializaed for scalar values.
template<typename model, typename store_factor>
inline
void
factorize_em(real_t &scalar, std::vector<multivector<model,store_factor> > &factors, const multivector<model,store_scalar> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	scalar = m[0];
	factors.clear();
}

// Performs the blade factorization by the outer product. This function is specializaed for scalar values.
template<typename model, typename store_factor>
inline
void
factorize_em(real_t &scalar, std::vector<multivector<model,store_factor> > &factors, const real_t &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	scalar = m;
	factors.clear();
}

}

#endif // !_GA_FACTORIZATION_
