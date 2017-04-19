/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_MATRIX_
#define _LA_MATRIX_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * la::matrix_type definition.
 *******************************************************************************************************/

// The matrix types. Useful for matrix initialization.
enum matrix_type
{
	null_matrix = 0,
	identity_matrix
};

/*******************************************************************************************************
 * la::dmatrix<value_type,rows,cols> class definition.
 *******************************************************************************************************/

// A MxN matrix with dynamic memory allocation.
template<typename value_type, size_t _rows, size_t _cols>
class dmatrix
{
public:

	// Specifies the number of columns of the matrix.
	static const size_t cols = _cols;

	// Specifies the number of rows of the matrix.
	static const size_t rows = _rows;

	// Specifies the number of cells.
	static const size_t size = rows * cols;
	
private:

	// The matrix cells.
	std::vector<value_type> m_cells;

public:

	// Creates a new matrix with the same values of the current one, but using a different data type.
	template<typename other_type>
	dmatrix<other_type,rows,cols> cast() const
	{
		dmatrix<other_type,rows,cols> result;
		for (size_t i=0; i!=result.size; ++i)
		{
			result[i] = static_cast<other_type>( m_cells[i] );
		}
		return result;
	}
	
#ifdef _MSC_VER

	// Specialization of cast<other_type> for other_type equal to value_type.
	template<>
	dmatrix<value_type,rows,cols> cast<value_type>() const
	{
		return (*this);
	}

#endif // _MSC_VER

	// Default constructor.
	dmatrix() :
		m_cells( size )
	{
	}

	// Copy constructor.
	dmatrix(const dmatrix<value_type,rows,cols> &other) :
		m_cells( other.m_cells.begin(), other.m_cells.end() )
	{
	}

	// Initialization constructor.
	dmatrix(const matrix_type type) :
		m_cells( size )
	{
		switch (type)
		{
			// Set a null matrix.
			case null_matrix:
				for (size_t i=0; i!=size; ++i)
				{
					m_cells[i] = 0;
				}
				break;

			// Set an identity matrix.
			case identity_matrix:
				for (size_t r=0, i=0; r!=rows; ++r)
				{
					for (size_t c=0; c!=cols; ++c, ++i)
					{
						m_cells[i] = static_cast<value_type>( (r != c) ? 0 : 1 );
					}
				}
				break;

			default:
				throw std::invalid_argument( "Unknown matrix type." );
		}
	}
	
	// Initialization constructor.
	dmatrix(const value_type &value) :
		m_cells( size, value )
	{
	}
	
	// Default assignment operator overload.
	inline
	dmatrix<value_type,rows,cols>& operator = (const dmatrix<value_type,rows,cols> &other)
	{
		m_cells( other.m_cells.begin(), other.m_cells.end() );
		return (*this);
	}

	// Provides a reference to the cell with a specific index pair.
	inline
	const value_type& operator () (const size_t &r, const size_t &c) const
	{
		assert( (r < rows) && (c < cols) );
		return m_cells[r*cols+c];
	}

	// Provides a reference to the cell with a specific index pair.
	inline
	value_type& operator () (const size_t &r, const size_t &c)
	{
		assert( (r < rows) && (c < cols) );
		return m_cells[r*cols+c];
	}

	// Provides a reference to the cell with a specific index.
	inline
	const value_type& operator [] (const size_t &i) const
	{
		return m_cells[i];
	}
	
	// Provides a reference to the cell with a specific index.
	inline
	value_type& operator [] (const size_t &i)
	{
		return m_cells[i];
	}
};

/*******************************************************************************************************
 * la::smatrix<value_type,rows,cols> class definition.
 *******************************************************************************************************/

// A MxN matrix with static memory allocation.
template<typename value_type, size_t _rows, size_t _cols>
class smatrix
{
public:

	// Specifies the number of columns of the matrix.
	static const size_t cols = _cols;

	// Specifies the number of rows of the matrix.
	static const size_t rows = _rows;

	// Specifies the number of cells.
	static const size_t size = rows * cols;
	
private:

	// The matrix cells.
	value_type m_cells[size];

public:

	// Creates a new matrix with the same values of the current one, but using a different data type.
	template<typename other_type>
	smatrix<other_type,rows,cols> cast() const
	{
		smatrix<other_type,rows,cols> result;
		for (size_t i=0; i!=result.size; ++i)
		{
			result[i] = static_cast<other_type>( m_cells[i] );
		}
		return result;
	}
	
#ifdef _MSC_VER

	// Specialization of cast<other_type> for other_type equal to value_type.
	template<>
	smatrix<value_type,rows,cols> cast<value_type>() const
	{
		return (*this);
	}

#endif // _MSC_VER

	// Default constructor.
	smatrix()
	{
	}

	// Copy constructor.
	smatrix(const smatrix<value_type,rows,cols> &other)
	{
		for (size_t i=0; i!=size; ++i)
		{
			m_cells[i] = other[i];
		}
	}

	// Initialization constructor.
	smatrix(const matrix_type type)
	{
		switch (type)
		{
			// Set a null matrix.
			case null_matrix:
				for (size_t i=0; i!=size; ++i)
				{
					m_cells[i] = 0;
				}
				break;

			// Set an identity matrix.
			case identity_matrix:
				for (size_t r=0, i=0; r!=rows; ++r)
				{
					for (size_t c=0; c!=cols; ++c, ++i)
					{
						m_cells[i] = static_cast<value_type>( (r != c) ? 0 : 1 );
					}
				}
				break;

			default:
				throw std::invalid_argument( "Unknown matrix type." );
		}
	}
	
	// Initialization constructor.
	smatrix(const value_type &value)
	{
		for (size_t i=0; i!=size; ++i)
		{
			m_cells[i] = value;
		}
	}
	
	// Default assignment operator overload.
	inline
	smatrix<value_type,rows,cols>& operator = (const smatrix<value_type,rows,cols> &other)
	{
		for (size_t i=0; i!=size; ++i)
		{
			m_cells[i] = other[i];
		}
		return (*this);
	}

	// Provides a reference to the cell with a specific index pair.
	inline
	const value_type& operator () (const size_t &r, const size_t &c) const
	{
		assert( (r < rows) && (c < cols) );
		return m_cells[r*cols+c];
	}

	// Provides a reference to the cell with a specific index pair.
	inline
	value_type& operator () (const size_t &r, const size_t &c)
	{
		assert( (r < rows) && (c < cols) );
		return m_cells[r*cols+c];
	}

	// Provides a reference to the cell with a specific index.
	inline
	const value_type& operator [] (const size_t &i) const
	{
		assert( i < size );
		return m_cells[i];
	}
	
	// Provides a reference to the cell with a specific index.
	inline
	value_type& operator [] (const size_t &i)
	{
		assert( i < size );
		return m_cells[i];
	}
};

}

#endif // !_LA_MATRIX_
