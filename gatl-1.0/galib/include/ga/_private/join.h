/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_JOIN_
#define _GA_PRIVATE_JOIN_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::join<model,store1,store2> struct definition.
 *******************************************************************************************************/

// The base struct for create the join of two blades.
template<typename model, typename store1, typename store2>
struct join
{
private:

	// Specifies the resulting store type for delta product operation.
	typedef typename delta_em_return<model,store1,store2>::store_t delta_store_t;
	
	// Specifies the resulting store type for meet operation.
	typedef typename store_grade_range<
		0,
		((largest_grade<store1>::result + largest_grade<store2>::result - smallest_grade<delta_store_t>::result) >> 1),
		model,
		(basis_vectors<store1>::result | basis_vectors<store2>::result)
	>::store_type meet_store_t;

	// Specifies the resulting store type for join operation.
	typedef typename store_grade_range<
			((smallest_grade<store1>::result + smallest_grade<store2>::result + smallest_grade<delta_store_t>::result) >> 1),
			model::basis_vectors_count,
			model
		>::store_type join_store_t;

public:

	// The main method. Here we know that grade(A) <= grade(B).
	static _GA_ALWAYS_INLINE
	multivector<model,join_store_t> run(const multivector<model,store1> &A, const multivector<model,store2> &B, const int gradeA, const int gradeB, const bool swapped, const real_t &tolerance)
	{
		typedef typename dual_em_return<model,delta_store_t>::store_t dual_delta_store_t;
		typedef typename store_grade_range<1,1,model,basis_vectors<dual_delta_store_t>::result>::store_type vector_store_t;
		
		typedef multivector<model,meet_store_t> meet_t;
		typedef multivector<model,join_store_t> join_t;
		
		typedef multivector<model,delta_store_t> delta_t;
		typedef multivector<model,dual_delta_store_t> dual_delta_t;
		typedef multivector<model,vector_store_t> vector_t;

		meet_t M;
		join_t J;

		// If we have a null blade (a zero multivector forcing Euclidean metric), we're done. We test the input blades here because the implemented algorithm is not proper for them.
		if ((ga::is_zero( A, tolerance )) || (ga::is_zero( B, tolerance )))
		{
			J = multivector<model,store_none>();
		}
		else
		{
			// Initialize the meet M with a scalar and the join J with a unit pseudoscalar of the total space.
			ga::assign<false>( M, 1, tolerance );
			J = consts_em<model>::I();

			// Compute the delta product.
			const delta_t &D = delta_em( A, B, tolerance );

			// Compute the required grade of the meet and join.
			const int gradeD = ga::grade( D, tolerance );
			const int gradeM = (gradeA + gradeB - gradeD) >> 1;
			const int gradeJ = (gradeA + gradeB + gradeD) >> 1;

			// If grade(D) is equal to grade(A) + grade(B), we're done. In such a case A and B are entirely disjoint.
			if (gradeD != (gradeA + gradeB))
			{
				// Compute the dual of the delta product.
				const dual_delta_t &S = dual_em( D );
				const dual_delta_t &iS = inverse_em( S, tolerance );

				// Find the basis blade E in the representation of S with the largest coordinate.
				index_t largest_i = 0;
				real_t current, largest = abs( S[0] );
				for (index_t i=1; i<S.size; ++i)
				{
					current = abs( S[i] );
					if (largest < current)
					{
						largest = current;
						largest_i = i;
					}
				}

				bitmap_t E = dual_delta_t::basis_blade( largest_i ).bitmap;

				/* IMPLEMENTATION ISSUES
				 *
				 * The factorization algorithm described in Section 21.6 makes E be the bitmap
				 * of the largest coefficient of S. However, I believe that we must look for
				 * the largest absolute coefficient.
				 */

				// Iterate over the basis vectors that span E in order to compute the join.
				int MCount = gradeM;
				int JCount = model::basis_vectors_count - gradeJ;
				const multivector<model,store1> &iA = inverse_em( A, tolerance );

				vector_t si, pi, ei;
				ei = multivector<model,store_none>();

				for (index_t i=0; E!=0; ++i)
				{
					// Check whether the blade is factorizable by the current basis vector.
					if ((E & vector_t::basis_blade( i ).bitmap) != 0)
					{
						ei[i] = 1;

						// Project ei onto S.
						ga::assign<false>( si, lcont_em( lcont_em( ei, S ), iS ), tolerance );

						/* IMPLEMENTATION ISSUES
						 *
						 * The algorithm from Section 21.7 using factorization from Section 21.6 does not work.
						 * Therefore, I changed the factorization process. Here I compute the orthogonal projection
						 * of a vector onto a blade using the algorithm described in Section 4.2.
						 */

						// Compute the projection pi of si and A.
						ga::assign<false>( pi, lcont_em( lcont_em( si, A ), iA ), tolerance );

						// If the projection is not zero, then wedge it to the meet (update M). If the new grade of M is the required grade of the meet then compute the join from it.
						if (!ga::is_zero( pi, tolerance ))
						{
							// M was updated.
							ga::assign<false>( M, op( M, pi ), tolerance );
							--MCount;

							// We're done! Compute join from meet.
							if (MCount == 0)
							{
								J = op( A, lcont_em( inverse_em( M, tolerance ), B ) );
								break;
							}
						}

						// Compute the rejection ri of si and A.
						const vector_t &ri = si - pi;

						// If the rejection is not zero, then remove it from the join (update J). If the new grade of J is the required grade of the join then return it.
						if (!ga::is_zero( ri, tolerance ))
						{
							// J was updated.
							ga::assign<false>( J, lcont_em( ri, J ), tolerance );
							--JCount;

							// We're done!
							if (JCount == 0)
							{
								break;
							}
						}

						ga_debug_assert( E != vector_t::basis_blade( i ).bitmap ); // Should never reach here, because the proper meet and join should be computed up to the last factor.
						ga_debug_assert( (!ga::is_zero( pi, tolerance )) || (!ga::is_zero( ri, tolerance )) ); // At least one should be updated.
						
						// Go to the next basis vector (and next factor).
						E ^= vector_t::basis_blade( i ).bitmap;

						ei[i] = 0;
					}
				}
			}
			else
			{
				// Compute join from meet.
				J = op( A, lcont_em( inverse_em( M, tolerance ), B ) );
			}

			// Apply sign fix (from Section 5.7).
			if ((swapped) && (((gradeJ - gradeA) * (gradeJ - gradeB)) & 1))
			{
				for (index_t i=0; i<J.size; ++i)
				{
					J[i] = -J[i];
				}
			}
		}

		return J;
	}
};

}

}

#endif // !_GA_PRIVATE_JOIN_
