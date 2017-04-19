/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_PRODUCT_
#define _GA_PRIVATE_PRODUCT_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::get_scale<basis_blade,scaled_store> struct definition.
 *******************************************************************************************************/

// Returns the scale factor assigned to the given stored basis blade.
template<bitmap_t basis_blade, typename scaled_store>
struct get_scale
{
	// Specifies the stored scale factor.
	static const int_t result = (basis_blade == scaled_store::item_bitmap) ? scaled_store::item_scale : get_scale<basis_blade,typename scaled_store::next>::result;
};

// Specialization of get_scale<basis_blade,scaled_store> for scaled_store equal to store_none.
template<bitmap_t basis_blade>
struct get_scale<basis_blade,store_none>
{
	// Specifies the end of the loop.
	static const int_t result = 0;
};

/*******************************************************************************************************
 * ga::_private::scaled_take_grade<grade,scaled_store> struct definition.
 *******************************************************************************************************/

// The base struct for create the operation that returns the k-grade part of a specialized multivector.
template<int grade, typename scaled_store>
struct scaled_take_grade
{
private:

	// This struct is specialized for the case where the given grade is equal than the grade of the current basis blade.
	template<bool same_grade, int dummy>
	struct loop
	{
		// Stores the current basis blade and call the next state of this recursive template.
		typedef ga::_private::black_magic::scaled_store<scaled_store::item_bitmap,scaled_store::item_scale,typename scaled_take_grade<grade,typename scaled_store::next>::result> result;
	};

	// This struct is specialized for the case where the given grade is different than the grade of the current basis blade.
	template<int dummy>
	struct loop<false,dummy>
	{
		// Calls the next state of this recursive template.
		typedef typename scaled_take_grade<grade,typename scaled_store::next>::result result;
	};

public:

	// This recursive template call creates a list with all the basis blades resulting from the operation.
	typedef typename loop<(grade==bit_count<scaled_store::item_bitmap>::result),0>::result result;
};

// Specialization of scaled_take_grade<grade,scaled_store> for scaled_store equal to store_none.
template<int grade>
struct scaled_take_grade<grade,store_none>
{
	// Specifies an empty list of stored basis blades.
	typedef store_none result;
};

/*******************************************************************************************************
 * ga::_private::scaled_to_store<scaled_store> struct definition.
 *******************************************************************************************************/

// The base struct for casting a given scaled_store to store data type.
template<typename scaled_store>
struct scaled_to_store
{
	// Specifies the resulting store type.
	typedef store<
			scaled_store::item_bitmap,
			typename scaled_to_store<typename scaled_store::next>::result
		> result;
};

// Specialization of scaled_to_store<scaled_store> for scaled_store equal to store_none.
template<>
struct scaled_to_store<store_none>
{
	// Specifies the end of the loop.
	typedef store_none result;
};

/*******************************************************************************************************
 * ga::_private::index_of<basis_blade,store> struct definition.
 *******************************************************************************************************/

// Returns the index of a given basis blade.
template<bitmap_t basis_blade, typename store>
struct index_of
{
	// The query result.
	static const index_t result = (basis_blade == store::bitmap) ? 0 : (index_of<basis_blade,typename store::next>::result + 1);
};

// Specialization of index_of<basis_blade,store> for store equal to store_none.
template<bitmap_t basis_blade>
struct index_of<basis_blade,store_none>
{
	// The end of the list was reached.
	static const index_t result = 0;
};

/*******************************************************************************************************
 * ga::_private::step<_scale,basis_blade1,basis_blade2> struct definition.
 *******************************************************************************************************/

// Specifies a set of steps for computing the coefficient of a resulting basis blade.
template<int_t _scale, bitmap_t basis_blade1, bitmap_t basis_blade2, typename next_step>
struct step
{
	// Scale factor.
	static const int_t scale = _scale;

	// Bitmap representation of the first basis blade.
	static const bitmap_t bitmap1 = basis_blade1;

	// Bitmap representation of the second basis blade.
	static const bitmap_t bitmap2 = basis_blade2;

	// Specifies the next step.
	typedef next_step next; 

	// The main method.
	template<typename store1, typename store2>
	static _GA_ALWAYS_INLINE
	real_t run(const real_t *coefficients1, const real_t *coefficients2)
	{
		return (_scale * coefficients1[index_of<basis_blade1,store1>::result] * coefficients2[index_of<basis_blade2,store2>::result]) +
			next_step::template run<store1,store2>( coefficients1, coefficients2 );
	}
};

// Specialization of step<_scale,basis_blade1,basis_blade2,next_step> for next_step equal to void.
template<int_t _scale, bitmap_t basis_blade1, bitmap_t basis_blade2>
struct step<_scale,basis_blade1,basis_blade2,void>
{
	// Scale factor.
	static const int_t scale = _scale;

	// Index of the first coefficient.
	static const bitmap_t bitmap1 = basis_blade1;

	// Index of the second coefficient.
	static const bitmap_t bitmap2 = basis_blade2;

	// Specifies the next step.
	typedef void next; 

	// The main method.
	template<typename store1, typename store2>
	static _GA_ALWAYS_INLINE
	real_t run(const real_t *coefficients1, const real_t *coefficients2)
	{
		return _scale * coefficients1[index_of<basis_blade1,store1>::result] * coefficients2[index_of<basis_blade2,store2>::result];
	}
};

/*******************************************************************************************************
 * ga::_private::merge_steps<steps1,steps2> struct definition.
 *******************************************************************************************************/

// The result data type defined by this struct returns the step type resulting from the union of the given steps.
template<typename steps1, typename steps2>
struct merge_steps
{
	// Merges the given lists of steps.
	typedef typename merge_steps<
			typename steps1::next,
			step<steps1::scale,steps1::bitmap1,steps1::bitmap2,steps2>
		>::result result;
};

// Specialization of merge_steps<steps1,steps2> for steps1 equal to void.
template<typename steps2>
struct merge_steps<void,steps2>
{
	// Returns the steps at right.
	typedef steps2 result;
};

// Specialization of merge_steps<steps1,steps2> for steps2 equal to void.
template<typename steps1>
struct merge_steps<steps1,void>
{
	// Returns the steps at left.
	typedef steps1 result;
};

// Specialization of merge_steps<steps1,steps2> for steps1 and steps2 equal to void.
template<>
struct merge_steps<void,void>
{
	// Returns an empty set of steps.
	typedef void result;
};

/*******************************************************************************************************
 * ga::_private::_product<scale,basis_blade1,basis_blade2> struct definition.
 *******************************************************************************************************/

// The base struct for test wheter a resulting coefficient is computed using current basis blades.
template<int_t scale, bitmap_t basis_blade1, bitmap_t basis_blade2>
struct _product
{
	// Specifies the resulting step for computing the coefficient of a resulting basis blade.
	typedef step<scale,basis_blade1,basis_blade2,void> steps_result;
};

// Specialization of _product<scale,basis_blade1,basis_blade2> for scale equal to 0.
template<bitmap_t basis_blade1, bitmap_t basis_blade2>
struct _product<0,basis_blade1,basis_blade2>
{
	// Specifies the resulting step for computing the coefficient of a resulting basis blade.
	typedef void steps_result;
};

/*******************************************************************************************************
 * ga::_private::product_[op]<model,store1,store2> struct definition.
 *******************************************************************************************************/

// This macro creates the base struct for solve binary distributive product operations over the sum of basis blades stored by multivectors and retrieve the set of performed algebric operations. The product_[op]<model,store1,store2> struct defines a recursive template call that iterates over the list basis blades stored by the first multivector. The _product_[op]_loop2<model,bitmap1,store2> struct defines a recursive template call that iterates over the list of basis blades stored by the second multivector.
#define _ga_product(op,scaled_store_type) \
	template<typename model, bitmap_t bitmap1, typename store2> \
	struct _product_##op##_loop2 \
	{ \
	private: \
	\
		static const int grade1 = bit_count<bitmap1>::result; \
		\
		static const int grade2 = bit_count<store2::bitmap>::result; \
		\
		typedef typename black_magic::clifford< \
				model, \
				bitmap1, \
				store2::bitmap, \
				(grade1 <= grade2) ? grade1 : grade2 \
			>::scaled_store_result geometric_scaled_store; \
		\
		typedef scaled_store_type scaled_store; \
		\
	public: \
		typedef typename merge_stores< \
				typename scaled_to_store<scaled_store>::result, \
				typename _product_##op##_loop2<model,bitmap1,typename store2::next>::store_result \
			>::result store_result; \
		\
		template<bitmap_t result> \
		struct steps \
		{ \
			typedef typename merge_steps< \
					typename _product<get_scale<result,scaled_store>::result,bitmap1,store2::bitmap>::steps_result, \
					typename _product_##op##_loop2<model,bitmap1,typename store2::next>::template steps<result>::steps_result \
				>::result steps_result; \
		}; \
	}; \
	\
	template<typename model, bitmap_t bitmap1> \
	struct _product_##op##_loop2<model,bitmap1,store_none> \
	{ \
		typedef store_none store_result; \
		\
		template<bitmap_t result> \
		struct steps \
		{ \
			typedef void steps_result; \
		}; \
	}; \
	\
	template<typename model, typename store1, typename store2> \
	struct product_##op \
	{ \
		typedef typename merge_stores< \
				typename _product_##op##_loop2<model,store1::bitmap,store2>::store_result, \
				typename product_##op<model,typename store1::next,store2>::store_result \
			>::result store_result; \
		\
		template<bitmap_t result> \
		struct steps \
		{ \
			typedef typename merge_steps< \
					typename _product_##op##_loop2<model,store1::bitmap,store2>::template steps<result>::steps_result, \
					typename product_##op<model,typename store1::next,store2>::template steps<result>::steps_result \
				>::result steps_result; \
		}; \
	}; \
	\
	template<typename model, typename store2> \
	struct product_##op<model,store_none,store2> \
	{ \
		typedef store_none store_result; \
		\
		template<bitmap_t result> \
		struct steps \
		{ \
			typedef void steps_result; \
		}; \
	}; \

// The base struct for solve the geometric product over the sum of basis blades stored by multivectors and retrieve the set of performed algebric operations.
_ga_product(geometric,geometric_scaled_store)

// The base struct for solve the outer product over the sum of basis blades stored by multivectors and retrieve the set of performed algebric operations.
#define outer_scaled_store \
	typename scaled_take_grade< \
			grade1 + grade2, \
			geometric_scaled_store \
		>::result \

_ga_product(outer,outer_scaled_store)

#undef outer_scaled_store

// The base struct for solve the left contraction over the sum of basis blades stored by multivectors and retrieve the set of performed algebric operations.
#define left_contraction_scaled_store \
	typename scaled_take_grade< \
			grade2 - grade1, \
			geometric_scaled_store \
		>::result \

_ga_product(left_contraction,left_contraction_scaled_store)

#undef left_contraction_scaled_store

// The base struct for solve the right contraction over the sum of basis blades stored by multivectors and retrieve the set of performed algebric operations.
#define right_contraction_scaled_store \
	typename scaled_take_grade< \
			grade1 - grade2, \
			geometric_scaled_store \
		>::result \

_ga_product(right_contraction,right_contraction_scaled_store)

#undef right_contraction_scaled_store

// The base struct for solve the dot product over the sum of basis blades stored by multivectors and retrieve the set of performed algebric operations.
#define dot_scaled_store \
	typename scaled_take_grade< \
			(grade1 <= grade2) ? (grade2 - grade1) : (grade1 - grade2), \
			geometric_scaled_store \
		>::result \

_ga_product(dot,dot_scaled_store)

#undef dot_scaled_store

// The base struct for solve the Hestenes inner product over the sum of basis blades stored by multivectors and retrieve the set of performed algebric operations.
#define hestenes_inner_scaled_store \
	typename scaled_take_grade< \
				((grade1 != 0) && (grade2 != 0)) ? ( \
					(grade1 <= grade2) ? (grade2 - grade1) : (grade1 - grade2) \
				) : ( \
					-1 \
				), \
				geometric_scaled_store \
			>::result \

_ga_product(hestenes_inner,hestenes_inner_scaled_store)

#undef hestenes_inner_scaled_store

/*******************************************************************************************************
 * ga::_private::product_[op]_run<model,store1,store2,store_result> struct definition.
 *******************************************************************************************************/

// This macro creates the base struct for computing the coeficients of the multivector resulting from some binary distributive operation. The struct iterates over the list basis blades stored by the resulting multivector.
#define _ga_product_run(op) \
	template<typename model, typename store1, typename store2, typename store_result> \
	struct product_##op##_run \
	{ \
	private: \
	\
		typedef typename product_##op<model,store1,store2>::template steps<store_result::bitmap>::steps_result steps; \
	\
	public: \
	\
		static _GA_ALWAYS_INLINE \
		void run(real_t *result, const real_t *coefficients1, const real_t *coefficients2) \
		{ \
			(*result) = steps::template run<store1,store2>( coefficients1, coefficients2 ); \
		\
			product_##op##_run<model,store1,store2,typename store_result::next>::run( result + 1, coefficients1, coefficients2 ); \
		} \
	}; \
	\
	template<typename model, typename store1, typename store2> \
	struct product_##op##_run<model,store1,store2,store_none> \
	{ \
		static _GA_ALWAYS_INLINE \
		void run(const real_t *result, const real_t *coefficients1, const real_t *coefficients2) \
		{ \
		} \
	}; \

// The base struct for computing the coeficients of the multivector resulting from the geometric product.
_ga_product_run(geometric)

// The base struct for computing the coeficients of the multivector resulting from the outer product.
_ga_product_run(outer)

// The base struct for computing the coeficients of the multivector resulting from the left contraction.
_ga_product_run(left_contraction)

// The base struct for computing the coeficients of the multivector resulting from the right contraction.
_ga_product_run(right_contraction)

// The base struct for computing the coeficients of the multivector resulting from the dot product.
_ga_product_run(dot)

// The base struct for computing the coeficients of the multivector resulting from the hestenes inner product.
_ga_product_run(hestenes_inner)

}

}

#endif // !_GA_PRIVATE_PRODUCT_
