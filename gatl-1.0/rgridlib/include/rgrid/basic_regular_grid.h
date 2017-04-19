/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _RGRID_BASIC_REGULAR_GRID_
#define _RGRID_BASIC_REGULAR_GRID_

// The namespace of the regular grid library.
namespace rgrid
{

/*******************************************************************************************************
 * rgrid::basic_regular_grid<lattice,sequence_container> class definition.
 *******************************************************************************************************/

// An n-dimensional generalized grid. This grid implementation is not restricted to being used with a specific grid connectivity nor with a specific dimensionality. The lattice of the grid is defined in compilation time.
template<typename _lattice, typename _sequence_container>
class basic_regular_grid
{
public:

	// A type that defines the lattice of the regular grid structure.
	typedef _lattice lattice;

	// A type that defines the sequence container used by the regular grid structure.
	typedef _sequence_container sequence_container;

public:

	// A type that represents a vector in the n-dimensional (continuous) cartesian space below the integer lattice.
	typedef typename lattice::cartesian_vector cartesian_vector;

	// A type that represents an integer value.
	typedef typename lattice::integer_type integer_type;

	// A type that represents a vector in the n-dimensional integer lattice (the position of an elements in a regular grid).
	typedef typename lattice::lattice_vector lattice_vector;

	// A type that represents a real value.
	typedef typename lattice::real_type real_type;

public:

	// The number of dimensions of the regular grid.
	static const size_t dims = lattice::dims;

public:

	// A type that provides a random-access iterator that can read a const element in a regular grid.
	typedef typename sequence_container::const_iterator const_iterator;
	
	// A type that provides a reference to a const element stored in a regular grid for reading and performing const operations.
	typedef typename sequence_container::const_reference const_reference;
	
	// A type that provides a random-access iterator that can read or modify any element in a regular grid.
	typedef typename sequence_container::iterator iterator;
	
	// A type that provides a reference to an element stored in a regular grid.
	typedef typename sequence_container::reference reference;
	
	// A type that counts the number of elements in a regular grid.
	typedef typename sequence_container::size_type size_type;

	// A type that represents the data type stored in a regular grid.
	typedef typename sequence_container::value_type value_type;

protected:

	// A type that represents the offset formula.
	typedef rgrid::offset_formula<lattice,size_type> offset_formula;

public:

	// A type that represents a cell in the n-dimensional memory buffer.
	typedef typename offset_formula::buffer_position buffer_position;

	// A type that represents the number of elements in each dimensions of a regular grid.
	typedef typename offset_formula::size_array size_array;

private:

	// Allocated memory for the regular grid.
	sequence_container m_buffer;

	// Computes the index value for a given lattice vector and the coordinates of a lattice vector related to a given index value.
	offset_formula m_offset_formula;
	
protected:

	// Checks whether a given buffer position is valid.
	inline
	void check_buffer_position(const buffer_position &position) const
	{
		if (!m_offset_formula.inside_bounds( position ))
		{
			throw std::out_of_range( "Buffer position out of range." );
		}
	}

	// Checks whether a given lattice vector is valid.
	inline
	void check_lattice_vector(const lattice_vector &vector) const
	{
		if (!m_offset_formula.inside_bounds( vector ))
		{
			throw std::out_of_range( "Lattice vector out of range." );
		}
	}

	// Returns whether a given buffer position is valid.
	inline
	bool test_buffer_position(const buffer_position &position) const
	{
		return m_offset_formula.inside_bounds( position );
	}

	// Returns whether a given lattice vector is valid.
	inline
	bool test_lattice_vector(const lattice_vector &vector) const
	{
		return m_offset_formula.inside_bounds( vector );
	}

protected:

	// Provides a reference to the element at a specified location in the memory buffer. This function checks whether the given buffer index is valid.
	inline
	reference at(const size_type &index)
	{
		return m_buffer.at( index );
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function checks whether the given buffer position is valid.
	inline
	reference at(const buffer_position &position)
	{
		// Check consistency.
		check_buffer_position( position );

		// Compute the index value of the required element and return a reference to it.
		return m_buffer[m_offset_formula( position )];
	}

	// Provides a reference to the element nearest to a specified location in the cartesian space below the regular grid. This function checks whether the given cartesian vector is valid.
	inline
	reference at(const cartesian_vector &vector)
	{
		return at( lattice::cartesian_to_lattice( vector ) );
	}

	// Provides a reference to the element at a specified location in the regular grid. This function checks whether the given lattice vector is valid.
	inline
	reference at(const lattice_vector &vector)
	{
		// Check consistency.
		check_lattice_vector( vector );

		// Compute the index value of the required element and return a reference to it.
		return m_buffer[m_offset_formula( vector )];
	}

	// Returns a random-access iterator to the first element in the container.
	inline
	iterator begin()
	{
		return m_buffer.begin();
	}

	// Erases the elements of the regular grid.
	inline
	void clear()
	{
		m_buffer.clear();
		m_offset_formula.clear();
	}

	// Returns a random-access iterator that points just beyond the end of the container.
	inline
	iterator end()
	{
		return m_buffer.end();
	}

	// Specifies a new size for a regular grid.
	inline
	void resize(const size_array &size)
	{
		// Check consistency.
		for (size_t i=0; i<dims; ++i)
		{
			if (size[i] < 0)
			{
				throw std::invalid_argument( "Invalid grid size." ); 
			}
		}

		// Update the offset formula.
		m_offset_formula.resize( size );
		
		// Resize the memory buffer of the regular grid.
		size_type buffer_size = size[0];
		for (size_t i=1; i<dims; ++i)
		{
			buffer_size *= size[i];
		}

		m_buffer.resize( buffer_size );
	}

	// Specifies a new size for a regular grid.
	inline
	void resize(const size_type &size)
	{
		// Check consistency.
		if (size < 0)
		{
			throw std::invalid_argument( "Invalid grid size." ); 
		}

		// Update the offset formula.
		m_offset_formula.resize( size );
		
		// Resize the memory buffer of the regular grid.
		size_type buffer_size = size;
		for (size_t i=1; i<dims; ++i)
		{
			buffer_size *= size;
		}

		m_buffer.resize( buffer_size );
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function does not check whether the given buffer index is valid.
	inline
	reference operator [] (const size_type &index)
	{
		return m_buffer[index];
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function does not check whether the given buffer position is valid.
	inline
	reference operator [] (const buffer_position &position)
	{
		// Check consistency (debug mode only).
		assert( m_offset_formula.inside_bounds( position ) );

		// Compute the index value of the required element and return a reference to it.
		return m_buffer[m_offset_formula( position )];
	}

	// Provides a reference to the element nearest to a specified location in the cartesian space below the integer lattice. This function does not check whether the given cartesian vector is valid.
	inline
	reference operator [] (const cartesian_vector &vector)
	{
		return (*this)[lattice::cartesian_to_lattice( vector )];
	}

	// Provides a reference to the element at a specified location in the regular grid. This function does not check whether the given lattice vector is valid.
	inline
	reference operator [] (const lattice_vector &vector)
	{
		// Check consistency (debug mode only).
		assert( m_offset_formula.inside_bounds( vector ) );

		// Compute the index value of the required element and return a reference to it.
		return m_buffer[m_offset_formula( vector )];
	}

public:

	// Computed the absolute index value related to a given location in the memory buffer.
	inline
	size_type absolute_index(const buffer_position &position) const
	{
		// Check consistency (debug mode only).
		assert( m_offset_formula.inside_bounds( position ) );

		// Compute the index value of the required element.
		return m_offset_formula( position );
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function checks whether the given buffer index is valid.
	inline
	const_reference at(const size_type &index) const
	{
		return m_buffer.at( index );
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function checks whether the given buffer position is valid.
	inline
	const_reference at(const buffer_position &position) const
	{
		// Check consistency.
		check_buffer_position( position );

		// Compute the offset to required element and return a reference to it.
		return m_buffer[m_offset_formula( position )];
	}

	// Provides a reference to the element nearest to a specified location in the cartesian space below the regular grid. This function checks whether the given cartesian vector is valid.
	inline
	const_reference at(const cartesian_vector &vector) const
	{
		return at( lattice::cartesian_to_lattice( vector ) );
	}

	// Provides a reference to the element at a specified location in the regular grid. This function checks whether the given lattice vector is valid.
	inline
	const_reference at(const lattice_vector &vector) const
	{
		// Check consistency.
		check_lattice_vector( vector );

		// Compute the offset to required element and return a reference to it.
		return m_buffer[m_offset_formula( vector )];
	}

	// Returns a random-access iterator to the first element in the container.
	inline
	const_iterator begin() const
	{
		return m_buffer.begin();
	}
	
	// Computed the location in the memory buffer related to a given absolute index value.
	inline
	buffer_position position(const size_type &index) const
	{
		// Check consistency (debug mode only).
		assert( index < m_buffer.size() );

		// Compute the index value of the required element.
		return m_offset_formula( index );
	}
	
	// Returns the number of elements in the regular grid.
	inline
	size_type elements() const
	{
		return m_buffer.size();
	}
	
	// Tests if the regular grid is empty.
	inline
	const bool empty() const
	{
		return m_buffer.empty();
	}

	// Returns a random-access iterator that points just beyond the end of the container.
	inline
	const_iterator end() const
	{
		return m_buffer.end();
	}

	// Default constructor.
	basic_regular_grid()
	{
	}
	
	// Copy constructor.
	basic_regular_grid(const basic_regular_grid &other) :
		m_buffer( other.m_buffer ),
		m_offset_formula( other.m_offset_formula )
	{
	}
	
	// Resize constructor.
	basic_regular_grid(const size_array &size)
	{
		resize( size );
	}

	// Returns an array with the number of elements in each dimension of the regular grid.
	inline
	const size_array& size() const
	{
		return m_offset_formula.size();
	}

	// Returns the number of dimensions of the regular grid at a given dimension.
	inline
	const size_type& size(const size_t &dim) const
	{
		return m_offset_formula.size()[dim];
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function does not check whether the given buffer index is valid.
	inline
	const_reference operator [] (const size_type &index) const
	{
		return m_buffer[index];
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function does not check whether the given buffer position is valid.
	inline
	const_reference operator [] (const buffer_position &position) const
	{
		// Check consistency (debug mode only).
		assert( m_offset_formula.inside_bounds( position ) );

		// Compute the index value of the required element and return a reference to it.
		return m_buffer[m_offset_formula( position )];
	}

	// Provides a reference to the element nearest to a specified location in the cartesian space below the integer lattice. This function does not check whether the given cartesian vector is valid.
	inline
	const_reference operator [] (const cartesian_vector &vector) const
	{
		return (*this)[lattice::cartesian_to_lattice( vector )];
	}

	// Provides a reference to the element at a specified location in the regular grid. This function does not check whether the given lattice vector is valid.
	inline
	const_reference operator [] (const lattice_vector &vector) const
	{
		// Check consistency (debug mode only).
		assert( m_offset_formula.inside_bounds( vector ) );

		// Compute the index value of the required element and return a reference to it.
		return m_buffer[m_offset_formula( vector )];
	}
};

}

#endif // !_RGRID_BASIC_REGULAR_GRID_
