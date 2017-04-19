/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _STOOLS_COMBINATION_GENERATOR_
#define _STOOLS_COMBINATION_GENERATOR_

// The namespace of the static tools library.
namespace stools
{

/*******************************************************************************************************
 * stools::combination_generator struct definition.
 *******************************************************************************************************/

// Computes all possible combinations of the n elements taken k at a time.
template<size_t n, size_t k>
class combination_generator
{
public:

	// A type that represents a possible combination of n elements taken k at a time.
	typedef array<size_t,k> combination;

private:

	// The number of combinations that were not generated yet.
	size_t m_combinations_left;

	// The next combination to be returned.
	combination m_next;

public:

	// Default class constructor.
	combination_generator() :
		m_combinations_left( smath::binomial<n,k>::result )
	{
		// Compute first combination.
		for (size_t i=0; i!=k; ++i)
		{
			m_next[i] = i;
		}
	}

	// Returns true if there are more combinations to be generated.
	inline
	bool has_more_items() const
	{
		return (m_combinations_left > 0);
	}

	// Moves the combination generator on one item.
	inline
	void move_next()
	{
		assert( has_more_items() );

		if (m_combinations_left > 1)
		{
			// Compute next combination.
			size_t i = k - 1;
			while (m_next[i] == (n - k + i))
			{
				--i;
			}

			m_next[i] = m_next[i] + 1;
			for (size_t j=i+1; j<k; ++j)
			{
				m_next[j] = m_next[i] + j - i;
			}
		}

		// Update the number of combination that were not generated yet.
		--m_combinations_left;
	}

	// Returns the next combination, without advancing one more.
	inline
	const combination& peek_next() const
	{
		assert( has_more_items() );
		return m_next;
	}

	// Reset generator.
	inline
	void reset()
	{
		m_combinations_left = smath::binomial<n,k>::result;

		for (size_t i=0; i!=k; ++i)
		{
			m_next[i] = i;
		}
	}
};

}

#endif // !_STOOLS_COMBINATION_GENERATOR_
