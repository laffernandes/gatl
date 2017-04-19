/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GRID_BUFFER_
#define _GRID_BUFFER_

// The namespace of the multidimensional grid library.
namespace grid
{

/*******************************************************************************************************
 * grid::buffer<dimensions,sequence_container> class definition.
 *******************************************************************************************************/

// An n-dimensional memory buffer.
template<size_t dimensions, typename sequence_container>
class buffer : private sequence_container
{
public:

	// Make some types defined in the super class public.
	typedef typename sequence_container::const_iterator const_iterator;
	typedef typename sequence_container::const_reference const_reference;
	typedef typename sequence_container::iterator iterator;
	typedef typename sequence_container::reference reference;
	typedef typename sequence_container::size_type size_type;
	typedef typename sequence_container::value_type value_type;

	// Make some methods from the super class public.
	using sequence_container::at;
	using sequence_container::begin;
	using sequence_container::empty;
	using sequence_container::end;
	using sequence_container::operator [];

public:

	// A type that represents the number of elements (or a buffer position) in each dimensions of the memory buffer.
	typedef stools::array<size_type,dimensions> size_array;

	// The number of dimensions of the memory buffer.
	static const size_t dims = dimensions;

private:

	// Pre-computed products for offset formula of the n-dimensional memory buffer. It specifies the offset for the next element in each dimension.
	size_array m_increment;

	// The number of elements in each dimension of the memory buffer.
	size_array m_size;

protected:

	// Checks whether the given buffer position is valid and raise an exception when it is not (debug mode only).
	inline
	void assert_buffer_position(const size_array &buffer_position) const
	{
		assert( is_valid_buffer_position( buffer_position ) );
	}

	// Checks whether the given buffer position is valid and raise an exception when it is not.
	inline
	void check_buffer_position(const size_array &buffer_position) const
	{
		if (!is_valid_buffer_position( buffer_position ))
		{
			throw std::out_of_range( "Buffer position out of range." );
		}
	}

	// Returns whether the given buffer position is valid.
	inline
	bool is_valid_buffer_position(const size_array &buffer_position) const
	{
		for (size_t i=0; i<dimensions; ++i)
		{
			if (buffer_position[i] >= m_size[i])
			{
				return false;
			}
		}
		return true;
	}

public:

	// Default constructor.
	buffer() : sequence_container()
	{
		std::fill( m_increment.begin(), m_increment.end(), 0 );
		std::fill( m_size.begin(), m_size.end(), 0 );
	}
	
	// Copy constructor.
	buffer(const buffer<dimensions,sequence_container> &other) : sequence_container( other )
	{
		std::copy( other.m_increment.begin(), other.m_increment.end(), m_increment.begin() );
		std::copy( other.m_size.begin(), other.m_size.end(), m_size.begin() );
	}
	
	// Resize constructor.
	buffer(const size_type &size) : sequence_container()
	{
		resize( size );
	}

	// Resize constructor.
	buffer(const size_array &size) : sequence_container()
	{
		resize( size );
	}

public:

	// Provides a reference to the element at a specified location in the memory buffer. This function checks whether the given buffer position is valid.
	inline
	reference at(const size_array &buffer_position)
	{
		// Check consistency.
		check_buffer_position( buffer_position );

		// Compute the index value of the required element and return a reference to it.
		return sequence_container::operator []( buffer_to_container( buffer_position ) );
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function checks whether the given buffer position is valid.
	inline
	const_reference at(const size_array &buffer_position) const
	{
		// Check consistency.
		check_buffer_position( buffer_position );

		// Compute the offset to required element and return a reference to it.
		return sequence_container::operator []( buffer_to_container( buffer_position ) );
	}

	// Computes the index value of a given buffer position.
	inline
	size_type buffer_to_container(const size_array &buffer_position) const
	{
		size_type result = buffer_position[0];
		for (size_t i=1; i<dimensions; ++i)
		{
			result += (buffer_position[i] * m_increment[i]);
		}
		return result;
	}

	// Erases the elements of the n-dimensional memory buffer.
	inline
	void clear()
	{
		std::fill( m_increment.begin(), m_increment.end(), 0 );
		std::fill( m_size.begin(), m_size.end(), 0 );

		sequence_container::clear();
	}

	// Returns the number of elements in the n-dimensional memory buffer.
	inline
	size_type container_size() const
	{
		return sequence_container::size();
	}

	// Computes buffer position related to a given index value.
	inline
	size_array container_to_buffer(size_type index) const
	{
		size_array result;

		for (size_t i=(dimensions-1); i>0; --i)
		{
			result[i] = index / m_increment[i];
			index -= (result[i] * m_increment[i]);
		}
		result[0] = index;

		return result;
	}

	// Specifies a new size for the n-dimensional memory buffer. The same size is set to all dimensions.
	inline
	void resize(const size_type &size)
	{
		// Set the size of each dimension of the memory buffer.
		std::fill( m_size.begin(), m_size.end(), size );

		// Compute the offset for the next element in each dimension and the size of the container.
		m_increment[0] = 1;
		size_type container_size = size;
		for (size_t i=1; i<dimensions; ++i)
		{
			m_increment[i] = m_increment[i-1] * size;
			container_size *= size;
		}

		// Allocate memory.
		sequence_container::resize( container_size );
	}

	// Specifies a new size for the n-dimensional memory buffer.
	inline
	void resize(const size_array &size)
	{
		// Set the size of each dimension of the memory buffer.
		m_size = size;

		// Compute the offset for the next element in each dimension and the size of the container.
		m_increment[0] = 1;
		size_type container_size = size[0];
		for (size_t i=1; i<dimensions; ++i)
		{
			m_increment[i] = m_increment[i-1] * size[i-1];
			container_size *= size[i];
		}

		// Allocate memory.
		sequence_container::resize( container_size );
	}

	// Returns an array with the number of elements in each dimension of the memory buffer.
	inline
	const size_array& size() const
	{
		return m_size;
	}

	// Returns the number of elements at a given dimension of the memory buffer.
	inline
	const size_type& size(const size_t &dim) const
	{
		return m_size[dim];
	}

public:

	// Default assignment operator overload.
	inline
	buffer<dimensions,sequence_container>& operator = (const buffer<dimensions,sequence_container> &other)
	{
		std::copy( other.m_increment.begin(), other.m_increment.end(), m_increment.begin() );
		std::copy( other.m_size.begin(), other.m_size.end(), m_size.begin() );

		sequence_container::operator =( other );

		return (*this);
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function does not check whether the given buffer position is valid.
	inline
	reference operator [] (const size_array &buffer_position)
	{
		// Check consistency (debug mode only).
		assert_buffer_position( buffer_position );

		// Compute the index value of the required element and return a reference to it.
		return sequence_container::operator []( buffer_to_container( buffer_position ) );
	}

	// Provides a reference to the element at a specified location in the memory buffer. This function does not check whether the given buffer position is valid.
	inline
	const_reference operator [] (const size_array &buffer_position) const
	{
		// Check consistency (debug mode only).
		assert_buffer_position( buffer_position );

		// Compute the index value of the required element and return a reference to it.
		return sequence_container::operator []( buffer_to_container( buffer_position ) );
	}
};

}

#endif // !_GRID_BUFFER_
