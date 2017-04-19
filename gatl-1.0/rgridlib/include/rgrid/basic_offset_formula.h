/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _RGRID_BASIC_OFFSET_FORMULA_
#define _RGRID_BASIC_OFFSET_FORMULA_

// The namespace of the regular grid library.
namespace rgrid
{

/*******************************************************************************************************
 * rgrid::basic_offset_formula<lattice,size_type> class definition.
 *******************************************************************************************************/

// Implements the offset formula used to compute the index value of a given lattice vector and the lattice vector related to a given index value.
template<typename _lattice, typename _size_type>
class basic_offset_formula
{
public:

	// A type that defines the lattice of the regular grid structure.
	typedef _lattice lattice;

	// A type that counts the number of elements in a regular grid.
	typedef _size_type size_type;

public:

	// The number of dimensions of the regular grid.
	static const size_t dims = lattice::dims;

public:

	// A type that represents an integer value.
	typedef typename lattice::integer_type integer_type;

	// A type that represents a vector in the n-dimensional integer lattice (the position of an elements in a regular grid).
	typedef typename lattice::lattice_vector lattice_vector;

public:

	// A type that represents the number of elements in each dimensions of a regular grid.
	typedef stools::array<size_type,dims> size_array;

	// A type that represents a cell in the n-dimensional memory buffer.
	typedef size_array buffer_position;

protected:

	// Pre-computed products for offset formula of the regular grid. It specifies the offset for the next element in each dimension.
	size_array m_increment;

	// The number of elements in each dimension of the regular grid.
	size_array m_size;

protected:

	// Erases the elements of the regular grid.
	inline
	void clear()
	{
		std::fill( m_increment.begin(), m_increment.end(), 0 );
		std::fill( m_size.begin(), m_size.end(), 0 );
	}

	// Returns whether a given lattice vector is valid.
	inline
	bool inside_bounds(const buffer_position &position) const
	{
		for (size_t i=0; i<dims; ++i)
		{
			if (position[i] >= m_size[i])
			{
				return false;
			}
		}
		return true;
	}


	// Returns whether a given lattice vector is valid.
	inline
	bool inside_bounds(const lattice_vector &vector) const
	{
		for (size_t i=0; i<dims; ++i)
		{
			const integer_type offset = 0; //TODO Definir cálculo genérico do offset.
			const integer_type dim_index = offset + vector[i];
			if ((dim_index < 0) || (static_cast<size_type>( dim_index ) >= m_size[i]))
			{
				return false;
			}
		}
		return true;
	}

	// Default constructor.
	basic_offset_formula()
	{
		clear();
	}
	
	// Copy constructor.
	basic_offset_formula(const basic_offset_formula &other) :
		m_increment(other.m_increment),
		m_size(other.m_size)
	{
	}
	
	// Specifies a new size for a regular grid.
	inline
	void resize(const size_array &size)
	{
		// Set the size of each dimension of the regular grid.
		m_size = size;

		// Compute the offset for the next element in each dimension.
		m_increment[0] = 1;
		for (size_t i=1; i<dims; ++i)
		{
			m_increment[i] = m_increment[i-1] * size[i-1];
		}
	}

	// Specifies a new size for a regular grid.
	inline
	void resize(const size_type &size)
	{
		// Set the size of each dimension of the regular grid.
		std::fill( m_size.begin(), m_size.end(), size );

		// Compute the offset for the next element in each dimension.
		m_increment[0] = 1;
		for (size_t i=1; i<dims; ++i)
		{
			m_increment[i] = m_increment[i-1] * size;
		}
	}

	// Returns an array with the number of elements in each dimension of the regular grid.
	inline
	const size_array& size() const
	{
		return m_size;
	}

	// Function-call operator that computes the index value of a given buffer position.
	inline
	size_type operator () (const buffer_position &position) const
	{
		size_type result = position[0];
		for (size_t i=1; i<dims; ++i)
		{
			result += (position[i] * m_increment[i]);
		}
		return result;
	}

	// Function-call operator that computes the index value of a given lattice vector.
	inline
	size_type operator () (const lattice_vector &vector) const
	{
		const integer_type offset = 0; //TODO Definir cálculo genérico do offset.
		size_type result = static_cast<size_type>( offset + vector[0] );
		for (size_t i=1; i<dims; ++i)
		{
			result += (static_cast<size_type>( offset + vector[i] ) * m_increment[i]);
		}
		return result;
	}

	// Function-call operator that computes buffer position related to a given index value.
	inline
	buffer_position operator () (size_type index) const
	{
		buffer_position result;

		for (size_t i=(dims-1); i>0; --i)
		{
			result[i] = index / m_increment[i];
			index -= (result[i] * m_increment[i]);
		}
		result[0] = index;

		return result;
	}
};

}

#endif // !_RGRID_BASIC_OFFSET_FORMULA_
