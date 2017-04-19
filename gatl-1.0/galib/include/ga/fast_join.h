/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_FAST_JOIN_
#define _GA_FAST_JOIN_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for fast_join() function.
#define fast_join_return_t(multivector_type1,multivector_type2) \
	join_return_t(multivector_type1,multivector_type2)

// Return type for fast_join() function.
template<typename model, typename store1, typename store2>
struct fast_join_return : public join_return<model,store1,store2>
{
};

/*******************************************************************************************************
 * Join having two multivectors.
 *******************************************************************************************************/

// Join of a specialized multivector with another specialized multivector (they must be blades). The algorithm is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename fast_join_return<model,store1,store2>::store_t>
fast_join(const multivector<model,store1> &m1, const multivector<model,store2> &m2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m1, tolerance ), "The first input multivector should be blade." );
	ga_maybe_assert( is_blade( m2, tolerance ), "The second input multivector should be blade." );

	const int gradeM1 = grade( m1, tolerance );
	const int gradeM2 = grade( m2, tolerance );

	if (gradeM1 >= gradeM2)
	{
		return _private::fast_join<model,store1,store2>::run( m1, m2, gradeM1, gradeM2, false, tolerance );
	}
	else
	{
		return _private::fast_join<model,store2,store1>::run( m2, m1, gradeM2, gradeM1, true, tolerance );
	}
}

/*******************************************************************************************************
 * Join having a scalar value.
 *******************************************************************************************************/

// Join of a scalar value with a specialized multivector (it must be a blade). The algorithm is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
template<typename model, typename store2>
inline
multivector<model,typename fast_join_return<model,store_scalar,store2>::store_t>
fast_join(const real_t &scalar, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The second input multivector should be blade." );

	const multivector<model,store_scalar> m1 = { { { scalar } } };
	return _private::fast_join<model,store2,store_scalar>::run( m, m1, grade( m, tolerance ), 0, false, tolerance );
}

// Join of a specialized multivector (it must be a blade) with a scalar value. The algorithm is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
template<typename model, typename store1>
inline
multivector<model,typename fast_join_return<model,store1,store_scalar>::store_t>
fast_join(const multivector<model,store1> &m, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The first input multivector should be blade." );

	const multivector<model,store_scalar> m2 = { { { scalar } } };
	return _private::fast_join<model,store1,store_scalar>::run( m, m2, grade( m, tolerance ), 0, true, tolerance );
}

// Join of a scalar value with another scalar value. The algorithm is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
template<typename model>
inline
multivector<model,typename fast_join_return<model,store_scalar,store_scalar>::store_t>
fast_join(const real_t &scalar1, const real_t &scalar2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	const multivector<model,store_scalar> m1 = { { { scalar1 } } };
	const multivector<model,store_scalar> m2 = { { { scalar2 } } };
	return _private::fast_join<model,store_scalar,store_scalar>::run( m1, m2, 0, 0, false, tolerance );
}

/*******************************************************************************************************
 * Join having a zero multivector.
 *******************************************************************************************************/

// Join of a zero multivector with a specialized multivector (it must be a blade).
template<typename model, typename store2>
inline
multivector<model,typename fast_join_return<model,store_none,store2>::store_t>
fast_join(const multivector<model,store_none> &zero, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The second input multivector should be blade." );

	return zero;
}

// Join of a zero multivector with a scalar value.
template<typename model>
inline
multivector<model,typename fast_join_return<model,store_none,store_scalar>::store_t>
fast_join(const multivector<model,store_none> &zero, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return zero;
}

// Join of a specialized multivector (it must be a blade) with a zero multivector.
template<typename model, typename store1>
inline
multivector<model,typename fast_join_return<model,store1,store_none>::store_t>
fast_join(const multivector<model,store1> &m, const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The first input multivector should be blade." );

	return zero;
}

// Join of a scalar value with a zero multivector.
template<typename model>
inline
multivector<model,typename fast_join_return<model,store_scalar,store_none>::store_t>
fast_join(const real_t &scalar, const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return zero;
}

// Join of a zero multivector with another zero multivector.
template<typename model>
inline
multivector<model,typename fast_join_return<model,store_none,store_none>::store_t>
fast_join(const multivector<model,store_none> &zero1, const multivector<model,store_none> &zero2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return zero1;
}

}

#endif // !_GA_FAST_JOIN_
