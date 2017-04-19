/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_BLACK_MAGIC_
#define _GA_PRIVATE_BLACK_MAGIC_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::euclidean_model type definition.
 *******************************************************************************************************/

// Euclidean model definition. This model is used in order to force the Euclidean metric.
typedef void euclidean_model;
	
// A namespace for internal use of the product<model,store1,store2> struct.
namespace black_magic
{

/*******************************************************************************************************
 * ga::_private::black_magic::scaled_store<basis_blade,scale,next_store> struct definition.
 *******************************************************************************************************/

// This struct defines a list of (scaled) basis blades. The set of stored basis blades must be ordered by the numerical representation of their bitmaps.
template<bitmap_t basis_blade, int_t scale, typename next_store>
struct scaled_store
{
	// Specifies the stored basis blade bitmap.
	static const bitmap_t item_bitmap = basis_blade;

	// Specifies the stored basis blade scale.
	static const int_t item_scale = scale;

	// Specifies the next stored item.
	typedef next_store next;
};

/*******************************************************************************************************
 * ga::_private::black_magic::scale<_scaled_store,value> struct definition.
 *******************************************************************************************************/

// Scales all the stored basis blades by the given scalar value.
template<typename _scaled_store, int_t value>
struct scale
{
	// Specifies the resulting scaled store.
	typedef scaled_store<_scaled_store::item_bitmap,(_scaled_store::item_scale*value),typename scale<typename _scaled_store::next,value>::result> result;
};

// Specialization of scale<_scaled_store,value> for _scaled_store equal to store_none.
template<int_t value>
struct scale<store_none,value>
{
	// Specifies the resulting scaled store.
	typedef store_none result;
};

// Specialization of scale<_scaled_store,value> for value equal to one.
template<typename _scaled_store>
struct scale<_scaled_store,1>
{
	// Specifies the resulting scaled store.
	typedef _scaled_store result;
};

// Specialization of scale<_scaled_store,value> for _scaled_store equal to store_none and value equal to one.
template<>
struct scale<store_none,1>
{
	// Specifies the resulting scaled store.
	typedef store_none result;
};

// Specialization of scale<_scaled_store,value> for value equal to zero.
template<typename _scaled_store>
struct scale<_scaled_store,0>
{
	// Specifies the resulting scaled store.
	typedef store_none result;
};

// Specialization of scale<_scaled_store,value> for _scaled_store equal to store_none and value equal to zero.
template<>
struct scale<store_none,0>
{
	// Specifies the resulting scaled store.
	typedef store_none result;
};

/*******************************************************************************************************
 * ga::_private::black_magic::merge<scaled_store1,scaled_store2> struct definition.
 *******************************************************************************************************/

// The result data type defined by this struct returns the scaled_store type resulting from the addition of the given stores.
template<typename scaled_store1, typename scaled_store2>
struct merge
{
private:

	// Tests the scale of the resulting basis blade.
	template<int_t scale, int dummy>
	struct test_scale
	{
		typedef scaled_store<scaled_store1::item_bitmap,scale,typename merge<typename scaled_store1::next,typename scaled_store2::next>::result> result;
	};

	// Specialization of test_scale<scale,dummy> for scale equal to zero.
	template<int dummy>
	struct test_scale<0,dummy>
	{
		typedef typename merge<typename scaled_store1::next,typename scaled_store2::next>::result result;
	};

	// This struct is specialized for the case where the basis blade at left comes before the basis blade at right.
	template<int cmp, int dummy>
	struct loop
	{
		// This recursive template call merges the given scaled_store structs.
		typedef scaled_store<scaled_store1::item_bitmap,scaled_store1::item_scale,typename merge<typename scaled_store1::next,scaled_store2>::result> result;
	};

	// Specialization of loop for the case where the basis blade at left is equal to the basis blade at right.
	template<int dummy>
	struct loop<0,dummy>
	{
		// This recursive template call merges the given scaled_store structs.
		typedef typename test_scale<(scaled_store1::item_scale+scaled_store2::item_scale),0>::result result;
	};

	// Specialization of loop for the case where the basis blade at left comes after the basis blade at right.
	template<int dummy>
	struct loop<1,dummy>
	{
		// This recursive template call merges the given scaled_store structs.
		typedef scaled_store<scaled_store2::item_bitmap,scaled_store2::item_scale,typename merge<scaled_store1,typename scaled_store2::next>::result> result;
	};

public:

	// Merges the given lists of basis blades.
	typedef typename loop<((scaled_store2::item_bitmap > scaled_store1::item_bitmap) ? -1 : ((scaled_store1::item_bitmap > scaled_store2::item_bitmap) ? 1 : 0 )),0>::result result;
};

// Specialization of merge<scaled_store1,scaled_store2> for scaled_store1 equal to store_none.
template<typename scaled_store2>
struct merge<store_none,scaled_store2>
{
	// Returns the store struct at right.
	typedef scaled_store2 result;
};

// Specialization of merge<scaled_store1,scaled_store2> for scaled_store2 equal to store_none.
template<typename scaled_store1>
struct merge<scaled_store1,store_none>
{
	// Returns the store struct at left.
	typedef scaled_store1 result;
};

// Specialization of merge<scaled_store1,scaled_store2> for both scaled_store1 and scaled_store2 equal to store_none.
template<>
struct merge<store_none,store_none>
{
	// Returns an empty store.
	typedef store_none result;
};

/*******************************************************************************************************
 * ga::_private::black_magic::canonical_reordering_sign<basis_blade1,basis_blade2> struct definition.
 *******************************************************************************************************/

// The base struct for count the number of basis vectors swaps required to get basis_blade1 and basis_blade2 into canonical order. This struct if for internal use of canonical_reordering_sign<basis_blade1,basis_blade2>
template<bitmap_t basis_blade1, bitmap_t basis_blade2>
struct swaps_count
{
	// Recursive template call.
	static const size_t result = bit_count<basis_blade1&basis_blade2>::result + swaps_count<(basis_blade1>>1),basis_blade2>::result;
};

// Specialization of swaps_count<basis_blade1,basis_blade2> for basis_blade1 equal to zero.
template<bitmap_t basis_blade2>
struct swaps_count<0,basis_blade2>
{
	// Specifies the end of the loop.
	static const size_t result = 0;
};

// Computes the sign of a basis blade after get its basis vectors into canonical order.
template<bitmap_t basis_blade1, bitmap_t basis_blade2>
struct canonical_reordering_sign
{
	// Specifies the resulting sign (1 for positive and -1 for negative).
	static const int_t result = (((swaps_count<(basis_blade1>>1),basis_blade2>::result & 1) != 0) ? -1 : 1);
};

/*******************************************************************************************************
 * ga::_private::black_magic::exterior<scaled_store1,basis_blade2> struct definition.
 *******************************************************************************************************/

// Computes the exterior product of two scaled basis blades. This struct is for internal use of exterior<scaled_store1,basis_blade2>.
template<bitmap_t basis_blade1, bitmap_t basis_blade2, bool independent>
struct _exterior_private
{
	// Specifies the resulting basis blade and its scale factor.
	typedef scaled_store<(basis_blade1^basis_blade2),canonical_reordering_sign<basis_blade1,basis_blade2>::result,store_none> result;
};

// Specialization of _exterior_private<basis_blade1,basis_blade2,independent> for independent equal to false.
template<bitmap_t basis_blade1, bitmap_t basis_blade2>
struct _exterior_private<basis_blade1,basis_blade2,false>
{
	// The outer product of dependent basis blades results in a zero multivector.
	typedef store_none result;
};

// The base struct for compile-time computation of the resulting basis blades (and their respective scale factors) from the exterior product (outer product) of a given set of basis blade (at left) with a given single basis blade (at right).
template<typename scaled_store1, bitmap_t basis_blade2>
struct exterior
{
	// Specifies the resulting basis blades and scale factors.
	typedef typename merge<
			typename exterior<typename scaled_store1::next,basis_blade2>::scaled_store_result,
			typename scale<
					typename _exterior_private<scaled_store1::item_bitmap,basis_blade2,((scaled_store1::item_bitmap&basis_blade2)==0)>::result,
					scaled_store1::item_scale
				>::result
		>::result scaled_store_result;
};

// Specialization of exterior<scaled_store1,basis_blade2> for scaled_store1 equal to store_none.
template<bitmap_t basis_blade2>
struct exterior<store_none,basis_blade2>
{
	// Specifies the end of the loop.
	typedef store_none scaled_store_result;
};

/*******************************************************************************************************
 * ga::_private::black_magic::regressive<model,scaled_store1,scaled_store2> struct definition.
 *******************************************************************************************************/

// Computes the rdgressive product of two scaled basis blades. This struct is for internal use of _regressive_loop2<model,basis_blade1,basis_blade2>.
template<bitmap_t basis_blade1, bitmap_t basis_blade2, bool is_valid>
struct _regressive_private
{
	// Specified the bitmap representation of the resulting basis blade.
	static const bitmap_t result_bitmap = (basis_blade1 & basis_blade2);

	// Specifies the bitmap representation of the factor of the first basis blade.
	static const bitmap_t factor1_bitmap = (basis_blade1 ^ result_bitmap);

	// Specifies the resulting scale factor.
	static const int_t result_scale = canonical_reordering_sign<factor1_bitmap,result_bitmap>::result * canonical_reordering_sign<factor1_bitmap,basis_blade2>::result;
	
	// Specifies the resulting basis blade and its scale factor.
	typedef scaled_store<result_bitmap,result_scale,store_none> result;
};

// Specialization of _regressive_private<basis_blade1,basis_blade2,is_valid> for is_valid equal to false.
template<bitmap_t basis_blade1, bitmap_t basis_blade2>
struct _regressive_private<basis_blade1,basis_blade2,false>
{
	// If A and B do not have all the basis vectors of the whole space then the regressive product is necessarily zero.
	typedef store_none result;
};

// The base struct for iterate over the list of basis blades stored by the second set of scaled basis blades. This struct is for internal use of regressive<model,scaled_store1,scaled_store2>.
template<typename model, bitmap_t basis_blade1, typename scaled_store2>
struct _regressive_loop2
{
	// Includes the resulting basis blade in the list of stored blasis blades and call the next state of this recursive template.
	typedef typename merge<
			typename _regressive_loop2<model,basis_blade1,typename scaled_store2::next>::scaled_store_result,
			typename scale<
					typename _regressive_private<
							basis_blade1,
							scaled_store2::item_bitmap,
							((basis_blade1 | scaled_store2::item_bitmap) == (model::basis_blades_count - 1))
						>::result,
					scaled_store2::item_scale
				>::result
		>::result scaled_store_result;
};

// Specialization of _regressive_loop2<model,basis_blade1,scaled_store2> for scaled_store2 equal to store_none.
template<typename model, bitmap_t basis_blade1>
struct _regressive_loop2<model,basis_blade1,store_none>
{
	// Specifies the end of the loop.
	typedef store_none scaled_store_result;
};

// The base struct for compile-time computation of the resulting basis blades (and their respective scale factors) from the regressive product of two given basis blades.
template<typename model, typename scaled_store1, typename scaled_store2>
struct regressive
{
	// This recursive template call creates a list with all the basis blades resulting from the regressive product of two sets of scaled basis blades.
	typedef typename merge<
			typename regressive<model,typename scaled_store1::next,scaled_store2>::scaled_store_result,
			typename scale<
					typename _regressive_loop2<model,scaled_store1::item_bitmap,scaled_store2>::scaled_store_result,
					scaled_store1::item_scale
				>::result
		>::result scaled_store_result;
};

// Specialization of regressive<model,scaled_store1,scaled_store2> for scaled_store1 equal to store_none.
template<typename model, typename scaled_store2>
struct regressive<model,store_none,scaled_store2>
{
	// Specifies the end of the loop.
	typedef store_none scaled_store_result;
};

// Specialization of regressive<model,scaled_store1,scaled_store2> for scaled_store2 equal to store_none.
template<typename model, typename scaled_store1>
struct regressive<model,scaled_store1,store_none>
{
	// Specifies the end of the loop.
	typedef store_none scaled_store_result;
};

// Specialization of regressive<model,scaled_store1,scaled_store2> for both scaled_store1 and scaled_store2 equal to store_none.
template<typename model>
struct regressive<model,store_none,store_none>
{
	// Specifies the end of the loop.
	typedef store_none scaled_store_result;
};

/*******************************************************************************************************
 * ga::_private::black_magic::complement<model,basis_blade> struct definition.
 *******************************************************************************************************/

// Returns the index of the first enabled bit in a bitmap. This struct is for internal use of complement<model,basis_blade>.
template<bitmap_t bitmap, bitmap_t one>
struct _complement_first_bit_on
{
	// Specifies the index of the first enabled bit.
	static const index_t result = _complement_first_bit_on<(bitmap>>1),((bitmap>>1)&1)>::result + 1;
};

// Specialization of _complement_first_bit_on<bitmap,one> for one equal to 1.
template<bitmap_t bitmap>
struct _complement_first_bit_on<bitmap,1>
{
	// Specifies the end of the loop.
	static const index_t result = 0;
};

// Returns the cobasis of a given basis vector. This struct is for internal use of _complement_basis<model,basis_vector1,basis_vector2>.
template<typename model, index_t basis_vector, int_t scale>
struct _complement_cobasis
{
	// Specifies the resulting basis blade and its scale factor.
	typedef scaled_store<
			((model::basis_blades_count - 1) ^ (1 << basis_vector)),
			((basis_vector & 1) ? -scale : scale),
			store_none
		> scaled_store_result;
};

// Specialization of _complement_cobasis<model,basis_vector,scale> for scale equal to zero.
template<typename model, index_t basis_vector>
struct _complement_cobasis<model,basis_vector,0>
{
	// The resulting basis blade is zero.
	typedef store_none scaled_store_result; 
};

// Returns the complement of a given basis vector. This struct is for internal use of complement<model,basis_blade>.
template<typename model, index_t basis_vector1, index_t basis_vector2>
struct _complement_basis
{
	// Specifies the resulting basis blades and scale factors.
	typedef typename merge<
			typename _complement_basis<model,basis_vector1,(basis_vector2-1)>::scaled_store_result,
			typename _complement_cobasis<
					model,
					basis_vector2,
					model::template metric<basis_vector1,basis_vector2>::result
				>::scaled_store_result
		>::result scaled_store_result;
};

// Specialization of _complement_basis<model,basis_vector1,basis_vector2> for basis_vector2 equal to zero.
template<typename model, index_t basis_vector1>
struct _complement_basis<model,basis_vector1,0>
{
	// Specifies the resulting basis blades and scale factors.
	typedef typename _complement_cobasis<
			model,
			0,
			model::template metric<basis_vector1,0>::result
		>::scaled_store_result scaled_store_result;
};

// The base struct for compile-time computation of the resulting basis blades (and their respective scale factors) from the complement of a given basis blade.
template<typename model, bitmap_t basis_blade>
struct complement
{
private:

	// Specifies the index of the first basis vector of the input basis blade.
	static const index_t basis_left_index = _complement_first_bit_on<basis_blade,(basis_blade&1)>::result;
	
	// Specifies the bitmap representation of the remaining basis vectors.
	static const bitmap_t remaining_right = (basis_blade ^ (1 << basis_left_index));

public:
	
	// Specifies the resulting basis blades and scale factors.
	typedef typename regressive<
			model,
			typename _complement_basis<model,basis_left_index,(model::basis_vectors_count-1)>::scaled_store_result,
			typename complement<model,remaining_right>::scaled_store_result
		>::scaled_store_result scaled_store_result;
};

// Specialization of complement<model,basis_blade> for basis_blade equal to zero
template<typename model>
struct complement<model,0>
{
	// The complement of a scalar value is the pseudoscalar.
	typedef scaled_store<(model::basis_blades_count-1),1,store_none> scaled_store_result;
};

/*******************************************************************************************************
 * ga::_private::black_magic::grassmann<model,basis_blade1,basis_blade2,lambda,index> struct definition.
 *******************************************************************************************************/

// The base struct for retrieve the bitmap of the i-th basis blade, of a given grade, which is a factor of the given basis blade. This struct is for internal use of grassmann<model,basis_blade1,basis_blade2,lambda,index> and is specialized for maybe equal to false.
template<bitmap_t basis_blade, int grade, index_t index, bitmap_t current, bool maybe>
struct _get_factor
{
	// Recursive template call.
	static const bitmap_t result = _get_factor<
			basis_blade,
			grade,
			index,
			(current + 1),
			((bit_count<current+1>::result == grade) && (((current + 1) | basis_blade) == basis_blade))
		>::result;
};

// Specialization of _get_factor<basis_blade,grade,index,current,maybe> for maybe equal to true.
template<bitmap_t basis_blade, int grade, index_t index, bitmap_t current>
struct _get_factor<basis_blade,grade,index,current,true>
{
	// Recursive template call.
	static const bitmap_t result = _get_factor<
			basis_blade,
			grade,
			(index - 1),
			(current + 1),
			((bit_count<current+1>::result == grade) && (((current + 1) | basis_blade) == basis_blade))
		>::result;
};

// Specialization of _get_factor<basis_blade,grade,index,current,maybe> for maybe equal to true and index equal to one.
template<bitmap_t basis_blade, int grade, bitmap_t current>
struct _get_factor<basis_blade,grade,1,current,true>
{
	// Specifies the end of the loop.
	static const bitmap_t result = current;
};

// The base struct for compile-time computation of the resulting basis blades (and their respective scale factors) from the Grassmann product (of order lambda) of two given basis blades.
template<typename model, bitmap_t basis_blade1, bitmap_t basis_blade2, int lambda, size_t index>
struct grassmann
{
private:

	// Specifies the "left" factor's bitmap of the second input basis blade.
	static const bitmap_t left_factor = _get_factor<
			basis_blade2,
			lambda,
			index,
			0,
			(lambda == 0)
		>::result;

	// Specifies the "right" factor's bitmap of the second input basis blade.
	static const bitmap_t right_factor = (basis_blade2 ^ left_factor);

	// Specifies the "right" factor's sign change.
	static const int_t sign_change = canonical_reordering_sign<left_factor,right_factor>::result;

public:

	// Specifies the resulting basis blades and scale factors.
	typedef typename merge<
			typename scale<
					typename exterior<
							typename regressive<
									model,
									scaled_store<basis_blade1,1,store_none>,
									typename complement<model,left_factor>::scaled_store_result
								>::scaled_store_result,
							right_factor 
						>::scaled_store_result,
					sign_change
				>::result,
			typename grassmann<model,basis_blade1,basis_blade2,lambda,index-1>::scaled_store_result
		>::result scaled_store_result;
};

// Specialization of grassmann<model,basis_blade1,basis_blade2,lambda,index> for index equal to zero.
template<typename model, bitmap_t basis_blade1, bitmap_t basis_blade2, int lambda>
struct grassmann<model,basis_blade1,basis_blade2,lambda,0>
{
	// Specifies the end of the loop.
	typedef store_none scaled_store_result;
};

/*******************************************************************************************************
 * ga::_private::black_magic::clifford<model,basis_blade1,basis_blade2,lambda> struct definition.
 *******************************************************************************************************/

// The base struct for compile-time computation of the resulting basis blades (and their respective scale factors) from the Clifford product (geometric product) of two given basis blades.
template<typename model, bitmap_t basis_blade1, bitmap_t basis_blade2, int lambda>
struct clifford
{
private:

	// The sign change is given by (-1)^(lambda * (grade1 - lambda) + 1/2 * lambda * (lambda - 1)).
	static const int_t sign_change = ((((lambda * (bit_count<basis_blade1>::result - lambda)) + ((lambda * (lambda - 1)) >> 1)) & 1) != 0) ? -1 : 1;

	// Computes the resulting basis blades from the Grassmann product of order lambda.
	typedef typename grassmann<model,basis_blade1,basis_blade2,lambda,smath::binomial<bit_count<basis_blade2>::result,lambda>::result>::scaled_store_result grassmann_result;

public:
	
	// Specifies the resulting basis blades and scale factors.
	typedef typename merge<
			typename scale<grassmann_result,sign_change>::result,
			typename clifford<model,basis_blade1,basis_blade2,lambda-1>::scaled_store_result
		>::result scaled_store_result;
};

// Specialization of clifford<model,basis_blade1,basis_blade2,lambda> for lambda equal to -1.
template<typename model, bitmap_t basis_blade1, bitmap_t basis_blade2>
struct clifford<model,basis_blade1,basis_blade2,-1>
{
	// Specifies the end of the loop.
	typedef store_none scaled_store_result;
};

// Specialization of clifford<model,basis_blade1,basis_blade2,lambda> for model equal to euclidean_model.
template<bitmap_t basis_blade1, bitmap_t basis_blade2, int lambda>
struct clifford<euclidean_model,basis_blade1,basis_blade2,lambda>
{
	// Specifies the resulting basis blades and scale factors.
	typedef scaled_store<
			(basis_blade1^basis_blade2),
			canonical_reordering_sign<basis_blade1,basis_blade2>::result,
			store_none
		> scaled_store_result;
};

}

}

}

#endif // !_GA_PRIVATE_BLACK_MAGIC_
