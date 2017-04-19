/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_WRITE_
#define _GA_PRIVATE_WRITE_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{
	
/*******************************************************************************************************
 * ga::_write::write<model,store> struct definition.
 *******************************************************************************************************/

// The base struct for create the write operation.
template<typename model, typename store>
struct write
{
private:

	// The base struct for iterate over the basis vectors of a given basis blade.
	template<bitmap_t basis_blade, index_t index>
	struct basis_vectors_loop
	{
		// Specifies the bitmap of the basis blade of the next state of this recursive template.
		static const bitmap_t next_basis_blade = (basis_blade & (~basis_vector<model,index>::bitmap));
		
		// Main method.
		static _GA_ALWAYS_INLINE
		void run(std::ostream &os)
		{
			// Write current basis blade.
			if ((basis_blade & basis_vector<model,index>::bitmap) != 0)
			{
				os << basis_vector<model,index>::name;

				if (next_basis_blade != 0)
				{
					os << "^";
				}
			}
			
			// Write next basis vector.
			basis_vectors_loop<next_basis_blade,index+1>::run( os );
		}
	};

	// Specialization of basis_vectors_loop<basis_blade,index> for basis_blade equal to zero.
	template<index_t index>
	struct basis_vectors_loop<0,index>
	{
		// Main method.
		static _GA_ALWAYS_INLINE
		void run(std::ostream &os)
		{
		}
	};

public:

	// The main method.
	static _GA_ALWAYS_INLINE
	void run(std::ostream &os, const real_t *coefficient, bool first)
	{
		if ((*coefficient) != 0)
		{
			// Write current coefficient.
			if (!first)
			{
				os << " + ";
			}
			first = false;

			os << (*coefficient);

			if (store::bitmap != 0)
			{
				os << " * ";
				basis_vectors_loop<store::bitmap,0>::run( os );
			}
		}
	
		// Write next coefficient.
		write<model,typename store::next>::run( os, coefficient + 1, first );
	}
};

// Specialization of write<model,store> for store equal to store_none.
template<typename model>
struct write<model,store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	void run(std::ostream &os, const real_t *coefficient, const bool first)
	{
		if (first)
		{
			os << static_cast<real_t>( 0 );
		}
	}
};

}

}

#endif // !_GA_PRIVATE_WRITE_
