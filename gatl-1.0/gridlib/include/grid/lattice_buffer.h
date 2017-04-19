/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GRID_LATTICE_BUFFER_
#define _GRID_LATTICE_BUFFER_

// The namespace of the multidimensional grid library.
namespace grid
{

/*******************************************************************************************************
 * grid::lattice_buffer<integer_type,dimensions,sequence_container> class definition.
 *******************************************************************************************************/

// An n-dimensional memory buffer index by an integer lattice.
template<typename integer_type, size_t dimensions, typename sequence_container>
class lattice_buffer : private buffer<dimensions,sequence_container>
{
private:

	// Buffer super class.
	typedef grid::buffer<dimensions,sequence_container> buffer;

public:

	// Make some types defined in the buffer super class public.
	typedef typename buffer::const_iterator const_iterator;
	typedef typename buffer::const_reference const_reference;
	typedef typename buffer::iterator iterator;
	typedef typename buffer::reference reference;
	typedef typename buffer::size_array size_array;
	typedef typename buffer::size_type size_type;
	typedef typename buffer::value_type value_type;

	// Make some methods from the buffer super class public.
	using buffer::at;
	using buffer::begin;
	using buffer::buffer_to_container;
	using buffer::container_size;
	using buffer::container_to_buffer;
	using buffer::empty;
	using buffer::end;
	using buffer::size;
	using buffer::operator [];

public:

	// A type that represents the coordinates of a point in the integer lattice.
	typedef integer_type coord_type;

	// A type that represents a set of integer coordinates.
	typedef stools::array<coord_type,dimensions> coord_array;

public:

	// The number of dimensions of the memory buffer.
	static const size_t dims = dimensions;

private:

	// The lower bounds assumed for the integer lattice.
	coord_array m_lower_bounds;
	
	// The upper bounds assumed for the integer lattice.
	coord_array m_upper_bounds;
	
protected:

	// Checks whether the given position is valid and raise an exception when it is not (debug mode only).
	inline
	void assert_lattice_position(const coord_array &lattice_position) const
	{
		assert( is_valid_lattice_position( lattice_position ) );
	}

	// Checks whether the given position is valid and raise an exception when it is not.
	inline
	void check_lattice_position(const coord_array &lattice_position) const
	{
		if (!is_valid_lattice_position( lattice_position ))
		{
			throw std::out_of_range( "Lattice position out of range." );
		}
	}

	// Returns whether the given position is valid.
	inline
	bool is_valid_lattice_position(const coord_array &lattice_position) const
	{
		for (size_t i=0; i<dimensions; ++i)
		{
			if ((lattice_position[i] < m_lower_bounds[i]) || (m_upper_bounds[i] < lattice_position[i]))
			{
				return false;
			}
		}
		return true;
	}

public:

	// Default constructor.
	lattice_buffer() : buffer()
	{
		std::fill( m_lower_bounds.begin(), m_lower_bounds.end(), 0 );
		std::fill( m_upper_bounds.begin(), m_upper_bounds.end(), 0 );
	}
	
	// Copy constructor.
	lattice_buffer(const lattice_buffer<coord_type,dimensions,sequence_container> &other) : buffer( other )
	{
		std::copy( other.m_lower_bounds.begin(), other.m_lower_bounds.end(), m_lower_bounds.begin() );
		std::copy( other.m_upper_bounds.begin(), other.m_upper_bounds.end(), m_upper_bounds.begin() );
	}
	
	// Resize constructor.
	lattice_buffer(const coord_array &lower_bounds, const coord_array &upper_bounds) : buffer()
	{
		resize( lower_bounds, upper_bounds );
	}

public:

	// Provides a reference to the element at a specified location in the memory buffer. This function checks whether the given position is valid.
	inline
	reference at(const coord_array &lattice_position)
	{
		// Check consistency.
		check_lattice_position( lattice_position );

		// Compute the buffer position of the required element and return a reference to it.
		return buffer::operator []( lattice_to_buffer( lattice_position ) );
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function checks whether the given position is valid.
	inline
	const_reference at(const coord_array &lattice_position) const
	{
		// Check consistency.
		check_lattice_position( lattice_position );

		// Compute the offset to required element and return a reference to it.
		return buffer::operator []( lattice_to_buffer( lattice_position ) );
	}

	// Computes the integer lattice position related to a given buffer position.
	inline
	coord_array buffer_to_lattice(const size_array &buffer_position) const
	{
		coord_array result;

		for (size_t i=0; i<dimensions; ++i)
		{
			result[i] = static_cast<coord_type>( buffer_position[i] ) + m_lower_bounds[i];
		}

		return result;
	}

	// Erases the elements of the n-dimensional memory buffer and the bounds of integer lattice.
	inline
	void clear()
	{
		std::fill( m_lower_bounds.begin(), m_lower_bounds.end(), 0 );
		std::fill( m_upper_bounds.begin(), m_upper_bounds.end(), 0 );

		buffer::clear();
	}

	// Computes the buffer position related to a given integer lattice position.
	inline
	size_array lattice_to_buffer(const coord_array &lattice_position) const
	{
		size_array result;

		for (size_t i=0; i<dimensions; ++i)
		{
			result[i] = static_cast<size_type>( lattice_position[i] - m_lower_bounds[i] );
		}

		return result;
	}

	// Return the lower bound assumed for the integer lattice in a given dimension.
	inline
	const coord_type& lower_bound(const size_t &dim) const
	{
		return m_lower_bounds[dim];
	}

	// Return the lower bounds assumed for the integer lattice.
	inline
	const coord_array& lower_bounds() const
	{
		return m_lower_bounds;
	}

	// Specifies a new size for the n-dimensional memory buffer from the new axis aligned bounds in the integer lattice.
	inline
	void resize(const coord_array &lower_bounds, const coord_array &upper_bounds)
	{
		std::copy( lower_bounds.begin(), lower_bounds.end(), m_lower_bounds.begin() );
		std::copy( upper_bounds.begin(), upper_bounds.end(), m_upper_bounds.begin() );

		size_array size;
		for (size_t i=0; i<dimensions; ++i)
		{
			size[i] = upper_bounds[i] - lower_bounds[i];
		}

		buffer::resize( size );
	}

	// Return the upper bound assumed for the integer lattice in a given dimension.
	inline
	const coord_type& upper_bound(const size_t &dim) const
	{
		return m_upper_bounds[dim];
	}

	// Return the upper bounds assumed for the integer lattice.
	inline
	const coord_array& upper_bounds() const
	{
		return m_upper_bounds;
	}

public:

	// Default assignment operator overload.
	inline
	lattice_buffer<coord_type,dimensions,sequence_container>& operator = (const lattice_buffer<coord_type,dimensions,sequence_container> &other)
	{
		buffer::operator =( other );

		std::copy( other.m_lower_bounds.begin(), other.m_lower_bounds.end(), m_lower_bounds.begin() );
		std::copy( other.m_upper_bounds.begin(), other.m_upper_bounds.end(), m_upper_bounds.begin() );

		return (*this);
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function does not check whether the given position is valid.
	inline
	reference operator [] (const coord_array &lattice_position)
	{
		// Check consistency (debug mode only).
		assert_lattice_position( lattice_position );

		// Compute the buffer position of the required element and return a reference to it.
		return buffer::operator []( lattice_to_buffer( lattice_position ) );
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function does not check whether the given position is valid.
	inline
	const_reference operator [] (const coord_array &lattice_position) const
	{
		// Check consistency (debug mode only).
		assert_lattice_position( lattice_position );

		// Compute the buffer position of the required element and return a reference to it.
		return buffer::operator []( lattice_to_buffer( lattice_position ) );
	}
};

}

#endif // !_GRID_LATTICE_BUFFER_
