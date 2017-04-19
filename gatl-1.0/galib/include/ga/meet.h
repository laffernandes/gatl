/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_MEET_
#define _GA_MEET_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for meet() function.
#define meet_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::meet_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for meet() function.
template<typename model, typename store1, typename store2>
struct meet_return
{
	// Store type.
	typedef typename store_grade_range<
		((_private::smallest_grade<store1>::result+_private::smallest_grade<store2>::result-_private::largest_grade<typename delta_em_return<model,store1,store2>::store_t>::result)>>1),
		((_private::largest_grade<store1>::result+_private::largest_grade<store2>::result-_private::smallest_grade<typename delta_em_return<model,store1,store2>::store_t>::result)>>1),
		model,
		(_private::basis_vectors<store1>::result | _private::basis_vectors<store2>::result)
	>::store_type store_t;
};

// Return type for meet() function (specialization of meet_return<model,store1,store2> for store1 equal to store_none).
template<typename model, typename store2>
struct meet_return<model,store_none,store2>
{
	// Store type.
	typedef store_none store_t;
};

// Return type for meet() function (specialization of meet_return<model,store1,store2> for store2 equal to store_none).
template<typename model, typename store1>
struct meet_return<model,store1,store_none>
{
	// Store type.
	typedef store_none store_t;
};

// Return type for meet() function (specialization of meet_return<model,store1,store2> for store1 and store2 equal to store_none).
template<typename model>
struct meet_return<model,store_none,store_none>
{
	// Store type.
	typedef store_none store_t;
};

/* IMPLEMENTATION ISSUES
 *
 * The grade of meet is (grade(A) + grade(B) - grade(D)) / 2. Therefore, the resulting grade
 * range goes from (smallest_grade(A) + smallest_grade(B) - largest_grade(D)) / 2
 * to (largest_grade(A) + largest_grade(B) - smallest_grade(D)) / 2.
 */

/*******************************************************************************************************
 * Meet having two multivectors.
 *******************************************************************************************************/

// Meet of a specialized multivector with another specialized multivector (they must be blades).
template<typename model, typename store1, typename store2>
inline
multivector<model,typename meet_return<model,store1,store2>::store_t>
meet(const multivector<model,store1> &m1, const multivector<model,store2> &m2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m1, tolerance ), "The first input multivector should be blade." );
	ga_maybe_assert( is_blade( m2, tolerance ), "The second input multivector should be blade." );

	const int gradeM1 = grade( m1, tolerance );
	const int gradeM2 = grade( m2, tolerance );

	multivector<model,typename meet_return<model,store1,store2>::store_t> result;
	if (gradeM1 <= gradeM2)
	{
		assign<false>( result, _private::meet<model,store1,store2>::run( m1, m2, gradeM1, gradeM2, false, tolerance ), tolerance );
	}
	else
	{
		assign<false>( result, _private::meet<model,store2,store1>::run( m2, m1, gradeM2, gradeM1, true, tolerance ), tolerance );
	}
	return result;
}

/*******************************************************************************************************
 * Meet having a scalar.
 *******************************************************************************************************/

// Meet of a scalar value with a specialized multivector (it must be a blade).
template<typename model, typename store2>
inline
multivector<model,typename meet_return<model,store_scalar,store2>::store_t>
meet(const real_t &scalar, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The second input multivector should be blade." );

	const multivector<model,store_scalar> m1 = { { { scalar } } };
	
	multivector<model,typename meet_return<model,store_scalar,store2>::store_t> result;
	assign<false>( result, _private::meet<model,store_scalar,store2>::run( m1, m, 0, grade( m, tolerance ), false, tolerance ), tolerance );
	return result;
}

// Meet of a specialized multivector (it must be a blade) with a scalar value.
template<typename model, typename store1>
inline
multivector<model,typename meet_return<model,store1,store_scalar>::store_t>
meet(const multivector<model,store1> &m, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The first input multivector should be blade." );

	const multivector<model,store_scalar> m2 = { { { scalar } } };

	multivector<model,typename meet_return<model,store1,store_scalar>::store_t> result;
	assign<false>( result, _private::meet<model,store1,store_scalar>::run( m2, m, 0, grade( m, tolerance ), true, tolerance ), tolerance );
	return result;
}

// Meet of a scalar value with another scalar value.
template<typename model>
inline
multivector<model,typename meet_return<model,store_scalar,store_scalar>::store_t>
meet(const real_t &scalar1, const real_t &scalar2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	const multivector<model,store_scalar> m1 = { { { scalar1 } } };
	const multivector<model,store_scalar> m2 = { { { scalar2 } } };

	multivector<model,typename meet_return<model,store_scalar,store_scalar>::store_t> result;
	assign<false>( result, _private::meet<model,store_scalar,store_scalar>::run( m1, m2, 0, 0, false, tolerance ), tolerance );
	return result;
}

/*******************************************************************************************************
 * Meet having a zero multivector.
 *******************************************************************************************************/

// Meet of a zero multivector with a specialized multivector (it must be a blade).
template<typename model, typename store2>
inline
multivector<model,typename meet_return<model,store_none,store2>::store_t>
meet(const multivector<model,store_none> &zero, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The second input multivector should be blade." );

	return zero;
}

// Meet of a zero multivector with a scalar value.
template<typename model>
inline
multivector<model,typename meet_return<model,store_none,store_scalar>::store_t>
meet(const multivector<model,store_none> &zero, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return zero;
}

// Meet of a specialized multivector (it must be a blade) with a zero multivector.
template<typename model, typename store1>
inline
multivector<model,typename meet_return<model,store1,store_none>::store_t>
meet(const multivector<model,store1> &m, const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The first input multivector should be blade." );

	return zero;
}

// Meet of a scalar value with a zero multivector.
template<typename model>
inline
multivector<model,typename meet_return<model,store_scalar,store_none>::store_t>
meet(const real_t &scalar, const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return zero;
}

// Meet of a zero multivector with another zero multivector.
template<typename model>
inline
multivector<model,typename meet_return<model,store_none,store_none>::store_t>
meet(const multivector<model,store_none> &zero1, const multivector<model,store_none> &zero2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return zero1;
}

}

#endif // !_GA_MEET_
