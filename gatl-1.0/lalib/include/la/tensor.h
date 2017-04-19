/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_TENSOR_
#define _LA_TENSOR_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * la::dtensor3<value_type,dimensions> class definition.
 *******************************************************************************************************/

// A 3-rank tensor in m-dimensional space.
template<typename _value_type, size_t _dimensions>
class dtensor3
{
public:

	// A type that defines the sequence container used by the tensor structure.
	typedef std::vector<_value_type> container;

	// A type that provides a reference to a const element stored in the tensor for reading and performing const operations.
	typedef typename container::const_reference const_reference;

	// A type that provides a reference to an element stored in the tensor.
	typedef typename container::reference reference;

	// A type that counts the number of elements in the tensor.
	typedef typename container::size_type size_type;

	// A type that represents the data type stored in the tensor.
	typedef typename container::value_type value_type;

public:

	// Specifies the rank (the number of indices) of the tensor.
	static const size_type rank = 3;

	// Specifies the number of dimensions of the tensor.
	static const size_type dims = _dimensions;

	// Specifies the number of components.
	static const size_type size = _dimensions * _dimensions * _dimensions;

private:

	// The tensor components.
	container m_components;

public:

	// Default class constructor.
	dtensor3() :
		m_components( size )
	{
	}

	// Default copy constructor.
	dtensor3(const dtensor3<_value_type,_dimensions> &other) :
		m_components( other.m_components.begin(), m_components.end() )
	{
	}

	// Default initialization constructor.
	dtensor3(const value_type &value) :
		m_components( size, value )
	{
	}

public:

	// Provides a reference to element at a given location.
	inline
	const_reference operator () (const size_type &i1, const size_type &i2, const size_type &i3) const
	{
		assert( i1 < _dimensions );
		assert( i2 < _dimensions );
		assert( i3 < _dimensions );
		return m_components[(i1 * (dims * dims)) + (i2 * dims) + i3];
	}

	// Provides a reference to element at a given location.
	inline
	reference operator () (const size_type &i1, const size_type &i2, const size_type &i3)
	{
		assert( i1 < _dimensions );
		assert( i2 < _dimensions );
		assert( i3 < _dimensions );
		return m_components[(i1 * (dims * dims)) + (i2 * dims) + i3];
	}

public:

	// Default assignment operator overload.
	inline
	dtensor3<_value_type,_dimensions>& operator = (const dtensor3<_value_type,_dimensions> &other)
	{
		std::copy( other.m_components.begin(), other.m_components.end(), m_components.begin() );
		return (*this);
	}
};

/*******************************************************************************************************
 * la::dtensor2<value_type,dimensions> class definition.
 *******************************************************************************************************/

// A 2-rank tensor in m-dimensional space.
template<typename _value_type, size_t _dimensions>
class dtensor2
{
public:

	// A type that defines the sequence container used by the tensor structure.
	typedef std::vector<_value_type> container;

	// A type that provides a reference to a const element stored in the tensor for reading and performing const operations.
	typedef typename container::const_reference const_reference;

	// A type that provides a reference to an element stored in the tensor.
	typedef typename container::reference reference;

	// A type that counts the number of elements in the tensor.
	typedef typename container::size_type size_type;

	// A type that represents the data type stored in the tensor.
	typedef typename container::value_type value_type;

public:

	// Specifies the rank (the number of indices) of the tensor.
	static const size_type rank = 2;

	// Specifies the number of dimensions of the tensor.
	static const size_type dims = _dimensions;

	// Specifies the number of components.
	static const size_type size = _dimensions * _dimensions;

private:

	// The tensor components.
	container m_components;

public:

	// Default class constructor.
	dtensor2() :
		m_components( size )
	{
	}

	// Default copy constructor.
	dtensor2(const dtensor2<_value_type,_dimensions> &other) :
		m_components( other.m_components.begin(), m_components.end() )
	{
	}

	// Default initialization constructor.
	dtensor2(const value_type &value) :
		m_components( size, value )
	{
	}

public:

	// Provides a reference to element at a given location.
	inline
	const_reference operator () (const size_type &i1, const size_type &i2) const
	{
		assert( i1 < _dimensions );
		assert( i2 < _dimensions );
		return m_components[(i1 * dims) + i2];
	}

	// Provides a reference to element at a given location.
	inline
	reference operator () (const size_type &i1, const size_type &i2)
	{
		assert( i1 < _dimensions );
		assert( i2 < _dimensions );
		return m_components[(i1 * dims) + i2];
	}

public:

	// Default assignment operator overload.
	inline
	dtensor2<_value_type,_dimensions>& operator = (const dtensor2<_value_type,_dimensions> &other)
	{
		std::copy( other.m_components.begin(), other.m_components.end(), m_components.begin() );
		return (*this);
	}
};

}

#endif // !_LA_TENSOR_
