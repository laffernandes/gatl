/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CLIFFORD_PRIVATE_VECTOR_
#define _GA_CLIFFORD_PRIVATE_VECTOR_

// The namespace of the geometric algebra library.
namespace ga
{

// The namespace of the Clifford algebras of signatures [p,q].
namespace clifford
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::clifford::_private::vector<store> struct definition.
 *******************************************************************************************************/

// The base struct for create the vector initialization function.
template<typename store>
struct vector
{
private:

	// This struct is specialized for the case where the current stored basis blade is a basis vector.
	template<bool is_basis_vector, int dummy>
	struct loop
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *coefficients, const real_t *input)
		{
			(*coefficients) = (*input);
			vector<typename store::next>::run( coefficients + 1, input + 1 );
		}
	};

	// This struct is specialized for the case where the current stored basis blade is not a basis vector.
	template<int dummy>
	struct loop<false,dummy>
	{
		// The main method.
		static _GA_ALWAYS_INLINE
		void run(real_t *coefficients, const real_t *input)
		{
			(*coefficients) = 0;
			vector<typename store::next>::run( coefficients + 1, input );
		}
	};

public:

	// The main method
	static _GA_ALWAYS_INLINE
	void run(real_t *coefficients, const real_t *input)
	{
		loop<
				(ga::_private::bit_count<store::bitmap>::result == 1),
				0
			>::run( coefficients, input );
	}
};

// Specialization of vector<store> for store equal to store_none.
template<>
struct vector<store_none>
{
	// The main method
	static _GA_ALWAYS_INLINE
	void run(const real_t *coefficients, const real_t *input)
	{
	}
};

}

}

}

#endif // !_GA_CLIFFORD_PRIVATE_VECTOR_
