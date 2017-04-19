/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _STOOLS_ARRAY_
#define _STOOLS_ARRAY_

// The namespace of the static tools library.
namespace stools
{

/*******************************************************************************************************
 * stools::array<data_type,count> struct definition.
 *******************************************************************************************************/

// Fixed size array of elements.
template<typename data_type, size_t count>
struct array
{
public:

#if !defined(_SECURE_SCL) || (_SECURE_SCL == 0)

	// A type that provides a random-access iterator that can read a const element in an array.
	typedef const data_type* const_iterator;
	
	// A type that provides a random-access iterator that can read or modify any element in an array.
	typedef data_type* iterator;

#else // _SECURE_SCL

	// A type that provides a random-access iterator that can read a const element in an array.
	typedef stdext::checked_array_iterator<const data_type*> const_iterator;

	// A type that provides a random-access iterator that can read or modify any element in an array.
	typedef stdext::checked_array_iterator<data_type*> iterator;

#endif // _SECURE_SCL
	
	// A type that provides a reference to a const element stored in an array for reading and performing const operations.
	typedef const data_type& const_reference;

	// A type that provides a bidirectional iterator that can read any const element in an array.
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// A type that represents a signed distance between two elements.
	typedef ptrdiff_t difference_type;

	// A type that provides a reference to an element stored in an array.
	typedef data_type& reference;

	// A type that provides a bidirectional iterator that can read any element in an array.
	typedef std::reverse_iterator<iterator> reverse_iterator;
	
	// A type that counts the number of elements in an array.
	typedef size_t size_type;
	
	// A type that represents the data type stored in an array.
	typedef data_type value_type;
	
public:

	// Compile-time definition of the number of elements in the array.
	static const size_type static_size = count;

private:

	// Checks whether a given index value is valid.
	inline static
	void range_check(const size_type &i)
	{
		if (i >= count)
		{
			throw std::out_of_range( "Index out of range." );
		}
	}

public:

	// Fixed-size array of elements.
	value_type elems[count];

public:

	// Provides a reference to the element at a specified location in the array. This function checks whether the given index is valid.
	inline
	const_reference at(const size_type &i) const
	{
		range_check( i );
		return elems[i];
	}

	// Provides a reference to the element at a specified location in the array. This function checks whether the given index is valid.
	inline
	reference at(const size_type &i)
	{
		range_check( i );
		return elems[i];
	}

	// Provides a reference to the last element in the array.
	inline
	const_reference back() const 
	{ 
		return elems[count-1];
	}

	// Provides a reference to the last element in the array.
	inline
	reference back() 
	{ 
		return elems[count-1];
	}

	// Returns a random-access iterator to the first element in the array.
	inline
	const_iterator begin() const
	{
#if !defined(_SECURE_SCL) || (_SECURE_SCL == 0)
		return elems;
#else // _SECURE_SCL
		return const_iterator( elems, count, 0 );
#endif // _SECURE_SCL
	}

	// Returns a random-access iterator to the first element in the array.
	inline
	iterator begin()
	{
#if !defined(_SECURE_SCL) || (_SECURE_SCL == 0)
		return elems;
#else // _SECURE_SCL
		return iterator( elems, count, 0 );
#endif // _SECURE_SCL
	}
	
	// Provides direct access to data.
	inline
	const value_type* data() const
	{
		return elems;
	}
	
	// Provides direct access to data.
	inline
	value_type* data()
	{
		return elems;
	}

	// Tests if the array is empty.
	inline
	static bool empty()
	{
		return false;
	}

	// Returns a random-access iterator that points just beyond the end of the array.
	inline
	const_iterator end() const
	{
#if !defined(_SECURE_SCL) || (_SECURE_SCL == 0)
		return (elems + count);
#else // _SECURE_SCL
		return const_iterator( elems, count, count );
#endif // _SECURE_SCL
	}

	// Returns a random-access iterator that points just beyond the end of the array.
	inline
	iterator end()
	{
#if !defined(_SECURE_SCL) || (_SECURE_SCL == 0)
		return (elems + count);
#else // _SECURE_SCL
		return iterator( elems, count, count );
#endif // _SECURE_SCL
	}

	// Provides a reference to the first element in the array.
	inline
	const_reference front() const 
	{
		return elems[0];
	}

	// Provides a reference to the first element in the array.
	inline
	reference front() 
	{ 
		return elems[0];
	}

	// Returns the maximum length of the array.
	inline
	static size_type max_size()
	{
		return count;
	}

	// Returns an iterator addressing the first element in a reversed array.
	inline
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator( end() );
	}

	// Returns an iterator addressing the first element in a reversed array.
	inline
	reverse_iterator rbegin()
	{
		return reverse_iterator( end() );
	}

	// Returns a iterator that points just beyond the end of a reversed array.
	inline
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator( begin() );
	}

	// Returns a iterator that points just beyond the end of a reversed array.
	inline
	reverse_iterator rend()
	{
		return reverse_iterator( begin() );
	}

	// Returns the number of elements in the array.
	inline
	static size_type size()
	{
		return count;
	}

public:

	// Assignment operator.
	inline
	array<data_type,count>& operator = (const array<data_type,count> &other)
	{
		std::copy( other.begin(), other.end(), begin() );
		return (*this);
	}

public:
	
	// Provides a reference to the element at a specified location in the array. This function does not check whether the given index is valid.
	inline
	reference operator [] (const size_type &i) 
	{
		assert( i < count );
		return elems[i];
	}

	// Provides a reference to the element at a specified location in the array. This function does not check whether the given index is valid.
	inline
	const_reference operator [] (const size_type &i) const 
	{     
		assert( i < count );
		return elems[i];
	}
};

/*******************************************************************************************************
 * stools::array<data_type,count> struct definition for count equal to zero.
 *******************************************************************************************************/

// Fixed size array of elements. Here, the number of elements is zero.
template<typename data_type>
struct array<data_type,0>
{
public:

#if !defined(_SECURE_SCL) || (_SECURE_SCL == 0)

	// A type that provides a random-access iterator that can read a const element in an array.
	typedef const data_type* const_iterator;
	
	// A type that provides a random-access iterator that can read or modify any element in an array.
	typedef data_type* iterator;

#else // _SECURE_SCL

	// A type that provides a random-access iterator that can read a const element in an array.
	typedef stdext::checked_array_iterator<const data_type*> const_iterator;

	// A type that provides a random-access iterator that can read or modify any element in an array.
	typedef stdext::checked_array_iterator<data_type*> iterator;

#endif // _SECURE_SCL
	
	// A type that provides a reference to a const element stored in an array for reading and performing const operations.
	typedef const data_type& const_reference;

	// A type that provides a bidirectional iterator that can read any const element in an array.
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	// A type that represents a signed distance between two elements.
	typedef ptrdiff_t difference_type;

	// A type that provides a reference to an element stored in an array.
	typedef data_type& reference;

	// A type that provides a bidirectional iterator that can read any element in an array.
	typedef std::reverse_iterator<iterator> reverse_iterator;
	
	// A type that counts the number of elements in an array.
	typedef size_t size_type;
	
	// A type that represents the data type stored in an array.
	typedef data_type value_type;
	
public:

	// Compile-time definition of the number of elements in the array.
	static const size_type static_size = 0;

public:

	// Provides a reference to the element at a specified location in the array. This function checks whether the given index is valid.
	inline
	const_reference at(const size_type &i) const
	{
		throw std::out_of_range( "Index out of range." );
		
		static const data_type dummy;
		return dummy;
	}

	// Provides a reference to the element at a specified location in the array. This function checks whether the given index is valid.
	inline
	reference at(const size_type &i)
	{
		throw std::out_of_range( "Index out of range." );
		
		static data_type dummy;
		return dummy;
	}

	// Provides a reference to the last element in the array.
	inline
	const_reference back() const 
	{ 
		throw std::out_of_range( "Index out of range." );
		
		static const data_type dummy;
		return dummy;
	}

	// Provides a reference to the last element in the array.
	inline
	reference back() 
	{ 
		throw std::out_of_range( "Index out of range." );
		
		static const data_type dummy;
		return dummy;
	}

	// Returns a random-access iterator to the first element in the array.
	inline
	const_iterator begin() const
	{
#if !defined(_SECURE_SCL) || (_SECURE_SCL == 0)
		return NULL;
#else // _SECURE_SCL
		return const_iterator( NULL, 0, 0 );
#endif // _SECURE_SCL
	}

	// Returns a random-access iterator to the first element in the array.
	inline
	iterator begin()
	{
#if !defined(_SECURE_SCL) || (_SECURE_SCL == 0)
		return NULL;
#else // _SECURE_SCL
		return iterator( NULL, 0, 0 );
#endif // _SECURE_SCL
	}
	
	// Provides direct access to data.
	inline
	const value_type* data() const
	{
		return NULL;
	}
	
	// Provides direct access to data.
	inline
	value_type* data()
	{
		return NULL;
	}

	// Tests if the array is empty.
	inline
	static bool empty()
	{
		return false;
	}

	// Returns a random-access iterator that points just beyond the end of the array.
	inline
	const_iterator end() const
	{
#if !defined(_SECURE_SCL) || (_SECURE_SCL == 0)
		return NULL;
#else // _SECURE_SCL
		return const_iterator( NULL, 0, 0 );
#endif // _SECURE_SCL
	}

	// Returns a random-access iterator that points just beyond the end of the array.
	inline
	iterator end()
	{
#if !defined(_SECURE_SCL) || (_SECURE_SCL == 0)
		return NULL;
#else // _SECURE_SCL
		return iterator( NULL, 0, 0 );
#endif // _SECURE_SCL
	}

	// Provides a reference to the first element in the array.
	inline
	const_reference front() const 
	{
		throw std::out_of_range( "Index out of range." );
		
		static const data_type dummy;
		return dummy;
	}

	// Provides a reference to the first element in the array.
	inline
	reference front() 
	{ 
		throw std::out_of_range( "Index out of range." );
		
		static data_type dummy;
		return dummy;
	}

	// Returns the maximum length of the array.
	inline
	static size_type max_size()
	{
		return 0;
	}

	// Returns an iterator addressing the first element in a reversed array.
	inline
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator( end() );
	}

	// Returns an iterator addressing the first element in a reversed array.
	inline
	reverse_iterator rbegin()
	{
		return reverse_iterator( end() );
	}

	// Returns a iterator that points just beyond the end of a reversed array.
	inline
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator( begin() );
	}

	// Returns a iterator that points just beyond the end of a reversed array.
	inline
	reverse_iterator rend()
	{
		return reverse_iterator( begin() );
	}

	// Returns the number of elements in the array.
	inline
	static size_type size()
	{
		return 0;
	}

public:

	// Assignment operator.
	inline
	array<data_type,0>& operator = (const array<data_type,0> &other)
	{
		return (*this);
	}

public:
	
	// Provides a reference to the element at a specified location in the array. This function does not check whether the given index is valid.
	inline
	reference operator [] (const size_type &i) 
	{
		throw std::out_of_range( "Index out of range." );
		
		static data_type dummy;
		return dummy;
	}

	// Provides a reference to the element at a specified location in the array. This function does not check whether the given index is valid.
	inline
	const_reference operator [] (const size_type &i) const 
	{     
		throw std::out_of_range( "Index out of range." );
		
		static const data_type dummy;
		return dummy;
	}
};

}

#endif // !_STOOLS_ARRAY_
