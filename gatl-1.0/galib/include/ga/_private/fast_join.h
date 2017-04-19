/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_FAST_JOIN_
#define _GA_PRIVATE_FAST_JOIN_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * Some useful functions.
 *******************************************************************************************************/

// Unit function wrapper.
template<typename model, typename store>
static _GA_ALWAYS_INLINE
const multivector<model,store> fast_join_unit_em(const multivector<model,store> &m, const real_t &tolerance)
{
	return ga::unit_em( m, tolerance );
}

template<typename model>
static _GA_ALWAYS_INLINE
const multivector<model,store_none> fast_join_unit_em(const multivector<model,store_none> &m, const real_t &tolerance)
{
	return multivector<model,store_none>();
}


/*******************************************************************************************************
 * ga::_private::fast_join<model,store1,store2> struct definition.
 *******************************************************************************************************/

// The base struct for create the join of two blades.
template<typename model, typename store1, typename store2>
struct fast_join
{
private:

	// Specifies the resulting store type for join operation.
	typedef typename join_return<model,store1,store2>::store_t join_store_t;

public:

	// The main method. Here we know that grade(A) >= grade(B).
	static _GA_ALWAYS_INLINE
	multivector<model,join_store_t> run(const multivector<model,store1> &A, const multivector<model,store2> &B, const int gradeA, const int gradeB, const bool swapped, const real_t &tolerance)
	{
		typedef typename store_grade_range<1,1,model,basis_vectors<store2>::result>::store_type vector_store_t;
		typedef multivector<model,vector_store_t> vector_t;
		typedef multivector<model,join_store_t> join_t;
		typedef multivector<model,store_none> zero_t;
		typedef multivector<model,store2> bladeB_t;
		typedef multivector<model,typename op_return<model,join_store_t,typename lcont_em_return<model,typename lcont_em_return<model,vector_store_t,store2>::store_t,store2>::store_t>::store_t> bladeH_t;

		static const int n = static_cast<int>( model::basis_vectors_count );
		join_t J;

		// If we have a pseudoscalar, we're done.
		if ((gradeA == n) || (gradeB == n))
		{
			ga::assign<false>( J, consts_em<model>::I(), tolerance );
		}
		// If we have a null blade (a zero multivector forcing Euclidean metric), we're done.
		else if ((ga::is_zero( A, tolerance )) || (ga::is_zero( B, tolerance )))
		{
			J = zero_t();
		}
		// If we have a scalar value, we're done.
		else if (gradeA == 0)
		{
			ga::assign<false>( J, fast_join_unit_em( B, tolerance ), tolerance );
		}
		else if (gradeB == 0)
		{
			ga::assign<false>( J, fast_join_unit_em( A, tolerance ), tolerance );
		}
		// Otherwise...
		else
		{
			// Initialize the join J with the unit A.
			ga::assign<false>( J, fast_join_unit_em( A, tolerance ), tolerance );
			int gradeJ = gradeA;

			// Find the basis blade F in the representation of B with the largest coordinate.
			index_t largest_i = 0;
			real_t current, largest = abs( B[0] );
			for (index_t i=1; i<B.size; ++i)
			{
				current = abs( B[i] );
				if (largest < current)
				{
					largest = current;
					largest_i = i;
				}
			}

			bladeB_t F;
			F = zero_t();

			F[largest_i] = 1;
			bitmap_t F_bitmap = B.basis_blade( largest_i ).bitmap;

			const bladeB_t &iF = inverse_em( F, tolerance );

			// While grade(J) != n and not all basis vectors fi in F have been tried...
			vector_t fi;
			fi = zero_t();
			for (index_t i=0; (gradeJ != n) && (F_bitmap != 0); ++i)
			{
				// Check whether the blade is factorizable by the current basis vector.
				if ((F_bitmap & vector_t::basis_blade( i ).bitmap) != 0)
				{
					fi[i] = 1;

					const bladeH_t &H = op( J, fast_join_unit_em( lcont_em( lcont_em( fi, iF ), B ), tolerance ) );

					if (!ga::is_zero( H, tolerance ))
					{
						ga::assign<false>( J, fast_join_unit_em( H, tolerance ), tolerance );
						++gradeJ;
					}

					F_bitmap ^= vector_t::basis_blade( i ).bitmap;
					fi[i] = 0;
				}
			}
			
			// Apply sign fix.
			if ((swapped) && (((gradeA * gradeB) & 1) != 0))
			{
				for (index_t i=0; i<J.size; ++i)
				{
					J[i] = -J[i];
				}
			}
		}

		// Return the resulting blade.
		return J;
	}
};

}

}

#endif // !_GA_PRIVATE_FAST_JOIN_
