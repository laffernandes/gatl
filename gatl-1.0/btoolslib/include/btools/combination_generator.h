/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTOOLS_COMBINATION_GENERATOR_
#define _BTOOLS_COMBINATION_GENERATOR_

// The namespace of the basic tools library.
namespace btools
{

/*******************************************************************************************************
 * bmath::combination_generator struct definition.
 *******************************************************************************************************/

// Computes all possible combinations of the n elements taken k at a time.
class combination_generator
{
public:

	// A type that represents a possible combination of n elements taken k at a time.
	typedef std::vector<size_t> combination;

private:

	// The number of combinations that were not generated yet.
	size_t m_combinations_left;

	// The number of items in the combination.
	size_t m_k;
	
	// The number of items to be combined.
	size_t m_n;
	
	// The next combination to be returned.
	combination m_next;

public:

	// Default class constructor.
	combination_generator(const size_t n, const size_t k) :
		m_combinations_left( bmath::binomial( n, k ) ),
		m_k( k ),
		m_n( n ),
		m_next( k )
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
			size_t i = m_k - 1;
			while (m_next[i] == (m_n - m_k + i))
			{
				--i;
			}

			m_next[i] = m_next[i] + 1;
			for (size_t j=i+1; j<m_k; ++j)
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
		m_combinations_left = bmath::binomial( m_n, m_k );

		for (size_t i=0; i!=m_k; ++i)
		{
			m_next[i] = i;
		}
	}
};

}

#endif // !_BTOOLS_COMBINATION_GENERATOR_
