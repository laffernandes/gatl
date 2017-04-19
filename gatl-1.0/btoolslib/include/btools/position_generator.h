/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTOOLS_POSITION_GENERATOR_
#define _BTOOLS_POSITION_GENERATOR_

// The namespace of the basic tools library.
namespace btools
{

/*******************************************************************************************************
 * bmath::position_generator struct definition.
 *******************************************************************************************************/

// Computes all possible integer positions in some hypercube.
template<typename _integer_type>
class position_generator
{
public:

	// A type that represents an integer value.
	typedef _integer_type integer_type;
	
	// A type that represents a possible position.
	typedef std::vector<integer_type> position;

private:

	// The number of dimensions of the hypercube.
	size_t m_dims;

	// Lower bound.
	const position m_lower_bound;
	
	// The next position to be returned.
	position m_next;

	// The number of positions that were not generated yet.
	integer_type m_positions_left;

	// Upper bound.
	const position m_upper_bound;

private:

	// Computes the number of integer positions in the bounding hypercube.
	static inline
	integer_type positions(const size_t &dims, const position &lower_bound, const position &upper_bound)
	{
		integer_type result = 1;
		for (size_t i=0; i!=dims; ++i)
		{
			if (lower_bound[i] <= upper_bound[i])
			{
				result *= (upper_bound[i] - lower_bound[i]) + 1;
			}
			else
			{
				return 0;
			}
		}
		return result;
	}

public:

	// Default class constructor.
	position_generator(const position &lower_bound, const position &upper_bound) :
		m_dims( lower_bound.size() ),
		m_lower_bound( lower_bound ),
		m_next( lower_bound ),
		m_positions_left( lower_bound.size(), positions( lower_bound, upper_bound ) ),
		m_upper_bound( upper_bound )
	{
		assert( lower_bound.size() == upper_bound.size() );
	}

	// Returns true if there are more positions to be generated.
	inline
	bool has_more_items() const
	{
		return (m_positions_left > 0);
	}

	// Moves the position generator on one item.
	inline
	void move_next()
	{
		assert( has_more_items() );

		if (m_positions_left > 1)
		{
			// Compute next position.
			size_t dim = m_dims - 1;
			
			do
			{
				++m_next[dim];
				if (m_next[dim] <= m_upper_bound[dim])
				{
					for (++dim; dim!=m_dims; ++dim)
					{
						m_next[dim] = m_lower_bound[dim];
					}
				}
				else
				{
					--dim;
				}
			}
			while (dim != m_dims);

			// Update the number of positions that were not generated yet.
			--m_positions_left;
		}
		else if (m_positions_left == 1)
		{
			// Update the number of positions that were not generated yet.
			--m_positions_left;
		}
	}

	// Returns the next position, without advancing one more.
	inline
	const position& peek_next() const
	{
		assert( has_more_items() );
		return m_next;
	}

	// Returns the number of positions that were not generated yet.
	inline
	integer_type positions_left() const
	{
		return m_positions_left;
	}

	// Reset generator.
	inline
	void reset()
	{
		m_next = m_lower_bound;
		m_positions_left = positions( m_dims, m_lower_bound, m_upper_bound );
	}
};

}

#endif // !_BTOOLS_POSITION_GENERATOR_
