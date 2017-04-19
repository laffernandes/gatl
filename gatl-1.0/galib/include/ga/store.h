/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_STORE_
#define _GA_STORE_

// The namespace of the geometric algebra library.
namespace ga
{

// Bitmap representation and grade of the stored basis blades.
struct basis_blade_t
{
	// The bitmap representation of the basis blade.
	bitmap_t bitmap;

	// The grade of the basis blade.
	int grade;
};

/*******************************************************************************************************
 * ga::store_none type definition.
 *******************************************************************************************************/

// This store type makes the specialized ga::multivector<model,store_none> do not store any coefficient (the multivector will be a null multivector). Also, store_none defines the end of the lists of stored basis blades (see store<basis_blade,next> struct).
typedef void store_none;

/*******************************************************************************************************
 * ga::store<basis_blade,next_store> struct definition.
 *******************************************************************************************************/

// This struct defines the list of basis blades which are stored by a specialized ga::multivector<model,stored_basis_blades> struct. The set of stored basis blades must be ordered by the numerical representation of the bitmap.
template<bitmap_t basis_blade, typename next_store = store_none>
struct store
{
private:

	// Declare friend classes.
	template<bitmap_t basis_blade, typename next_store> friend struct store;
	template<typename model, typename stored_basis_blades> friend class multivector;
	
	// Returns the bitmap representation and grade of the stored basis blades.
	static _GA_ALWAYS_INLINE
	void get_basis_blades(basis_blade_t *basis_blades)
	{
		(*basis_blades).bitmap = basis_blade;
		(*basis_blades).grade = _private::bit_count<basis_blade>::result;

		next_store::get_basis_blades( basis_blades + 1 );
	}

public:

	// Specifies the bitmap of the basis blade stored here.
	static const bitmap_t bitmap = basis_blade;

	// Specifies the next stored item.
	typedef next_store next;

	// Specifies the size of this list.
	static const size_t size = next_store::size + 1;
};

// Specialization of ga::store<basis_blade,next_store> for next_store equal to store_none.
template<bitmap_t basis_blade>
struct store<basis_blade,store_none>
{
private:

	// Declare friend classes.
	template<bitmap_t basis_blade, typename next_store> friend struct store;
	template<typename model, typename stored_basis_blades> friend class multivector;

	// Returns the bitmap representation and grade of the stored basis blades.
	static _GA_ALWAYS_INLINE
	void get_basis_blades(basis_blade_t *basis_blades)
	{
		(*basis_blades).bitmap = basis_blade;
		(*basis_blades).grade = _private::bit_count<basis_blade>::result;
	}

public:

	// Specifies the bitmap of the basis blade stored here.
	static const bitmap_t bitmap = basis_blade;

	// Specifies the next stored item.
	typedef store_none next;

	// Specifies the size of this list.
	static const size_t size = 1;
};

/*******************************************************************************************************
 * ga::store_scalar type definition.
 *******************************************************************************************************/

// This store type makes the specialized ga::multivector<model,store_scalar> struct stores a coefficient only for the scalar basis blade.
typedef store<0> store_scalar;

/*******************************************************************************************************
 * ga::store_pseudoscalar<model> struct definition.
 *******************************************************************************************************/

// The store_type data type defined by this struct makes a specialized ga::multivector<model,store_pseudoscalar<model>::store_type> stores a coefficient only for the pseudoscalar basis blade.
template<typename model>
struct store_pseudoscalar
{
	typedef store<model::basis_blades_count-1> store_type;
};

/*******************************************************************************************************
 * ga::store_all<model> struct definition.
 *******************************************************************************************************/

// The store_type data type defined by this struct makes a specialized ga::multivector<model,store_all::store_type> store coefficients for all the basis blades.
template<typename model>
struct store_all
{
private:

	// Base struct used to create the list with all the basis blades.
	template<bitmap_t bitmap, bool end>
	struct basis_blades_loop
	{
		typedef store<
				bitmap,
				typename basis_blades_loop<
						bitmap + 1,
						((bitmap + 1) == model::basis_blades_count)
					>::result
			> result;
	};

	// Specialization of basis_blades_loop<bitmap,end> for end equal to true.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,true>
	{
		typedef store_none result;
	};

public:

	// This recursive template call creates a list with all the basis blades bitmaps.
	typedef typename basis_blades_loop<0,false>::result store_type;
};

/*******************************************************************************************************
 * ga::store_grade<k,model> struct definition.
 *******************************************************************************************************/

// The store_type data type defined by this struct makes a specialized ga::multivector<model,store_grade<k,model>::store_type> store coefficients for the basis blades with grade k.
template<int k, typename model>
struct store_grade
{
private:

	// Base struct used to create the list with the desired basis blades. This struct is specialized for same_grade equal to true and end equal to false.
	template<bitmap_t bitmap, bool same_grade, bool end>
	struct basis_blades_loop
	{
		typedef store<
				bitmap,
				typename basis_blades_loop<
						bitmap + 1,
						(k == _private::bit_count<bitmap+1>::result),
						((bitmap + 1) >= model::basis_blades_count)
					>::result
			> result;
	};

	// Specialization of basis_blades_loop<bitmap,same_grade,end> for same_grade equal to false and end equal to false.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,false,false>
	{
		typedef typename basis_blades_loop<
				bitmap + 1,
				(k == _private::bit_count<bitmap+1>::result),
				((bitmap + 1) >= model::basis_blades_count)
			>::result result;
	};

	// Specialization of basis_blades_loop<bitmap,same_grade,end> for same_grade equal to false and end equal to true.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,false,true>
	{
		typedef store_none result;
	};

	// Specialization of basis_blades_loop<bitmap,same_grade,end> for same_grade equal to true and end equal to true.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,true,true>
	{
		typedef store_none result;
	};

public:

	// This recursive template call creates a list with the desired basis blades bitmaps.
	typedef typename basis_blades_loop<
			0,
			(k == 0),
			false
		>::result store_type;
};

/*******************************************************************************************************
 * ga::store_grade_range<first,last,model,basis_vectors> struct definition.
 *******************************************************************************************************/

// The store_type data type defined by this struct makes a specialized ga::multivector<model,store_grade_range<first,last,model>::store_type> store coefficients for the basis blades with grade in [first,last] and the basis vectors in basis_vectors.
template<int first, int last, typename model, bitmap_t basis_vectors = (model::basis_blades_count - 1)>
struct store_grade_range
{
private:

	// Base struct used to create the list with the desired basis blades. This struct is specialized for found equal to true and end equal to false.
	template<bitmap_t bitmap, bool found, bool end>
	struct basis_blades_loop
	{
		typedef store<
				bitmap,
				typename basis_blades_loop<
						bitmap + 1,
						(((bitmap + 1) & basis_vectors) && (first <= _private::bit_count<bitmap+1>::result) && (_private::bit_count<bitmap+1>::result <= last)),
						((bitmap + 1) >= model::basis_blades_count)
					>::result
			> result;
	};

	// Specialization of basis_blades_loop<bitmap,found,end> for found equal to false and end equal to false.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,false,false>
	{
		typedef typename basis_blades_loop<
				bitmap + 1,
				(((bitmap + 1) & basis_vectors) && (first <= _private::bit_count<bitmap+1>::result) && (_private::bit_count<bitmap+1>::result <= last)),
				((bitmap + 1) >= model::basis_blades_count)
			>::result result;
	};

	// Specialization of basis_blades_loop<bitmap,found,end> for found equal to false and end equal to true.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,false,true>
	{
		typedef store_none result;
	};

	// Specialization of basis_blades_loop<bitmap,found,end> for found equal to true and end equal to true.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,true,true>
	{
		typedef store_none result;
	};

public:

	// This recursive template call creates a list with the desired basis blades bitmaps.
	typedef typename basis_blades_loop<
			0,
			((first <= 0) && (0 <= last)),
			false
		>::result store_type;
};

/*******************************************************************************************************
 * ga::store_even_grades<model> struct definition.
 *******************************************************************************************************/

// The store_type data type defined by this struct makes a specialized ga::multivector<model,store_even_grades<model>::store_type> store coefficients for the basis blades with even grades.
template<typename model>
struct store_even_grades
{
private:

	// Base struct used to create the list with the desired basis blades.
	template<bitmap_t bitmap, bool is_even, bool end>
	struct basis_blades_loop;

	// Specialization of basis_blades_loop<bitmap,is_even,end> for is_even equal to true and end equal to false.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,true,false>
	{
		typedef store<
				bitmap,
				typename basis_blades_loop<
						bitmap + 1,
						(_private::bit_count<bitmap+1>::result & 1) == 0,
						((bitmap + 1) >= model::basis_blades_count)
					>::result
			> result;
	};

	// Specialization of basis_blades_loop<bitmap,is_even,end> for is_even equal to false and end equal to false.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,false,false>
	{
		typedef typename basis_blades_loop<
				bitmap + 1,
				(_private::bit_count<bitmap+1>::result & 1) == 0,
				((bitmap + 1) >= model::basis_blades_count)
			>::result result;
	};

	// Specialization of basis_blades_loop<bitmap,is_even,end> for is_even equal to true and end equal to true.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,true,true>
	{
		typedef store_none result;
	};

	// Specialization of basis_blades_loop<bitmap,is_even,end> for is_even equal to false and end equal to true.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,false,true>
	{
		typedef store_none result;
	};

public:

	// This recursive template call creates a list with the desired basis blades bitmaps.
	typedef typename basis_blades_loop<
			0,
			true,
			false
		>::result store_type;
};

/*******************************************************************************************************
 * ga::store_odd_grades<model> struct definition.
 *******************************************************************************************************/

// The store_type data type defined by this struct makes a specialized ga::multivector<model,store_odd_grades<model>::store_type> store coefficients for the basis blades with odd grades.
template<typename model>
struct store_odd_grades
{
private:

	// Base struct used to create the list with the desired basis blades.
	template<bitmap_t bitmap, bool is_odd, bool end>
	struct basis_blades_loop;

	// Specialization of basis_blades_loop<bitmap,is_odd,end> for is_odd equal to true and end equal to false.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,true,false>
	{
		typedef store<
				bitmap,
				typename basis_blades_loop<
						bitmap + 1,
						(_private::bit_count<bitmap+1>::result & 1) != 0,
						((bitmap + 1) >= model::basis_blades_count)
					>::result
			> result;
	};

	// Specialization of basis_blades_loop<bitmap,is_odd,end> for is_odd equal to false and end equal to false.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,false,false>
	{
		typedef typename basis_blades_loop<
				bitmap + 1,
				(_private::bit_count<bitmap+1>::result & 1) != 0,
				((bitmap + 1) >= model::basis_blades_count)
			>::result result;
	};

	// Specialization of basis_blades_loop<bitmap,is_odd,end> for is_odd equal to true and end equal to true.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,true,true>
	{
		typedef store_none result;
	};

	// Specialization of basis_blades_loop<bitmap,is_odd,end> for is_odd equal to false and end equal to true.
	template<bitmap_t bitmap>
	struct basis_blades_loop<bitmap,false,true>
	{
		typedef store_none result;
	};

public:

	// This recursive template call creates a list with the desired basis blades bitmaps.
	typedef typename basis_blades_loop<
			1,
			true,
			false
		>::result store_type;
};

}

#endif // !_GA_STORE_
