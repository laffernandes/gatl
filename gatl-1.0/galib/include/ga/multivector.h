/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_MULTIVECTOR_
#define _GA_MULTIVECTOR_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some pre-declarations.
 *******************************************************************************************************/

// Multivector definition.
template<typename model, typename stored_basis_blades>
class multivector;

// Copy the source multivector into the target multivector. When secure_cast is true and an invalid convertion is requested, an exception is throw. When secure_cast is false, the consistency check is not performed. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
template<bool secure_cast, typename model, typename store_target, typename store_source>
inline void assign(multivector<model,store_target> &target, const multivector<model,store_source> &source, const real_t &tolerance _GA_DEFAULT_TOLERANCE);

// Copy the source multivector into the target multivector. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
template<bool secure_cast, typename model, typename store>
inline void assign(multivector<model,store> &target, const multivector<model,store> &source, const real_t &tolerance _GA_DEFAULT_TOLERANCE);

// Copy the source multivector into the target multivector. When secure_cast is true and an invalid convertion is requested, an exception is throw. When secure_cast is false, the consistency check is not performed. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
template<bool secure_cast, typename model, typename store_target>
inline void assign(multivector<model,store_target> &target, const real_t &source, const real_t &tolerance _GA_DEFAULT_TOLERANCE);

// Copy the source multivector into the target multivector. When secure_cast is true and an invalid convertion is requested, an exception is throw. When secure_cast is false, the consistency check is not performed. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
template<bool secure_cast, typename model, typename store_source>
inline void assign(real_t &target, const multivector<model,store_source> &source, const real_t &tolerance _GA_DEFAULT_TOLERANCE);

// Copy the source multivector into the target multivector. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
template<bool secure_cast>
inline void assign(real_t &target, const real_t &source, const real_t &tolerance _GA_DEFAULT_TOLERANCE);

/*******************************************************************************************************
 * ga::multivector<model,stored_basis_blades> struct definition.
 *******************************************************************************************************/

// Multivector definition.
template<typename model, typename stored_basis_blades>
class multivector
{
public:

	// Specifies the model type.
	typedef model model_t;

	// Specifies the store type.
	typedef stored_basis_blades store_t;

public:
	
	// Specifies the number of coefficients stored by this multivector.
	static const size_t size = stored_basis_blades::size;

public:

	// The set of coefficients stored by this multivector.
	stools::array<real_t,size> coefficients;

public:

	// Default assignment operator overload.
	inline
	multivector<model,stored_basis_blades>& operator = (const multivector<model,stored_basis_blades> &other)
	{
		for (index_t i=0; i!=size; ++i)
		{
			coefficients[i] = other.coefficients[i];
		}
		return (*this);
	}

	// Specialized assignment operator overload.
	template<typename other_store>
	inline
	multivector<model,stored_basis_blades>& operator = (const multivector<model,other_store> &other)
	{
		static const bool is_substore _GA_ATTRIBUTE_UNUSED = _private::is_substore<stored_basis_blades,other_store>::result;
		ga_static_assert( is_substore );

		_private::assign<false,stored_basis_blades,other_store>::run( coefficients.data(), other.data(), static_cast<real_t>( 0 ) );
		return (*this);
	}

	// Default plus equal operator overload.
	inline
	multivector<model,stored_basis_blades>& operator += (const multivector<model,stored_basis_blades> &other)
	{
		for (index_t i=0; i!=size; ++i)
		{
			coefficients[i] += other.coefficients[i];
		}
		return (*this);
	}

	// Specialized plus equal operator overload.
	template<typename other_store>
	inline
	multivector<model,stored_basis_blades>& operator += (const multivector<model,other_store> &other)
	{
		static const bool is_substore _GA_ATTRIBUTE_UNUSED = _private::is_substore<stored_basis_blades,other_store>::result;
		ga_static_assert( is_substore );

		_private::binary_addivite<_private::addition,stored_basis_blades,other_store>::run( coefficients.data(), coefficients.data(), other.data() );
		return (*this);
	}

	// Default minus equal operator overload.
	inline
	multivector<model,stored_basis_blades>& operator -= (const multivector<model,stored_basis_blades> &other)
	{
		for (index_t i=0; i!=size; ++i)
		{
			coefficients[i] -= other.coefficients[i];
		}
		return (*this);
	}

	// Specialized minus equal operator overload.
	template<typename other_store>
	inline
	multivector<model,stored_basis_blades>& operator -= (const multivector<model,other_store> &other)
	{
		static const bool is_substore _GA_ATTRIBUTE_UNUSED = _private::is_substore<stored_basis_blades,other_store>::result;
		ga_static_assert( is_substore );

		_private::binary_addivite<_private::subtraction,stored_basis_blades,other_store>::run( coefficients.data(), coefficients.data(), other.data() );
		return (*this);
	}

public:

	// Array subscript operator overload.
	inline
	real_t& operator [] (const index_t &index)
	{
		return coefficients[index];
	}

	// Array subscript operator overload.
	inline
	const real_t& operator [] (const index_t &index) const
	{
		return coefficients[index];
	}

public:

	// Copy the source multivector into this multivector. When secure_cast is true and an invalid convertion is requested, an exception is throw. When secure_cast is false, the consistency check is not performed. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
	template<bool secure_cast, typename store_source>
	inline
	void assign(const multivector<model,store_source> &source, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
	{
		ga::assign<secure_cast>( *this, source, tolerance );
	}

	// Copy the source multivector into this multivector. When secure_cast is true and an invalid convertion is requested, an exception is throw. When secure_cast is false, the consistency check is not performed. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
	template<bool secure_cast>
	inline
	void assign(const real_t &source, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
	{
		ga::assign<secure_cast>( *this, source, tolerance );
	}

public:

    // Provides direct access to coefficients (it is for internal use only).
	inline
	real_t* data()
	{
		return coefficients.data();
	}

    // Provides direct access to coefficients (it is for internal use only).
	inline
	const real_t* data() const
	{
		return coefficients.data();
	}

public:

	// Returns the bitmap representation and grade of the i-th stored basis blade.
	static inline
	const basis_blade_t& basis_blade(const index_t &index)
	{
		static basis_blade_t basis_blades[size] = {};

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_MULTIVECTOR_GET_BASIS_BLADES)
			{
				if (first_time)
				{
					stored_basis_blades::get_basis_blades( basis_blades );
					first_time = false;
				}
			}
		}

		return basis_blades[index];
	}
};

// Specialization of multivector<stored_basis_blades> for stored_basis_blades equal to store_none. This specialization defines a null multivector.
template<typename model>
class multivector<model,store_none>
{
public:

	// Specifies the model type.
	typedef model model_t;

	// Specifies the store type.
	typedef store_none store_t;

public:
	
	// Specifies the number of coefficients stored by this multivector. Notice that a null multivector does not store any coefficient, because all of them are equal to zero.
	static const size_t size = 0;

public:

	// Assignment operator overload.
	inline
	multivector<model,store_none>& operator = (const multivector<model,store_none> &other)
	{
		return (*this);
	}

	// Plus equal operator overload.
	inline
	multivector<model,store_none>& operator += (const multivector<model,store_none> &other)
	{
		return (*this);
	}

	// Minus equal operator overload.
	inline
	multivector<model,store_none>& operator -= (const multivector<model,store_none> &other)
	{
		return (*this);
	}

public:

	// Array subscript operator overload.
	inline
	real_t& operator [] (const index_t &index)
	{
		ga_always_assert( false, "Index out of range." );
		
		static real_t dummy = 0;
		return dummy;
	}

	// Array subscript operator overload.
	inline
	const real_t& operator [] (const index_t &index) const
	{
		ga_always_assert( false, "Index out of range." );
		
		static const real_t dummy = 0;
		return dummy;
	}

public:

	// Copy the source multivector into this multivector. When secure_cast is true and an invalid convertion is requested, an exception is throw. When secure_cast is false, the consistency check is not performed. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
	template<bool secure_cast, typename store_source>
	inline
	void assign(const multivector<model,store_source> &source, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
	{
		ga::assign<secure_cast>( *this, source, tolerance );
	}

	// Copy the source multivector into this multivector. When secure_cast is true and an invalid convertion is requested, an exception is throw. When secure_cast is false, the consistency check is not performed. We implement an assignment function rather than implement an assignment operator in order to avoid automatic casting operations. The point was to avoid the performance impact of undesired (accidental) casting.
	template<bool secure_cast>
	inline
	void assign(const real_t &source, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
	{
		ga::assign<secure_cast>( *this, source, tolerance );
	}

public:

    // Provides direct access to coefficients (it is for internal use only).
	inline
	real_t* data()
	{
		return NULL;
	}

    // Provides direct access to coefficients (it is for internal use only).
	inline
	const real_t* data() const
	{
		return NULL;
	}

public:

	// Returns the bitmap representation and grade of the i-th stored basis blade.
	static inline
	const basis_blade_t& basis_blade(const index_t &index)
	{
		ga_always_assert( false, "Index out of range." );

		static const basis_blade_t dummy = {};
		return dummy;
	}
};

}

#endif // !_GA_MULTIVECTOR_
