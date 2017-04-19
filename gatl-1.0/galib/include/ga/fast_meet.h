/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_FAST_MEET_
#define _GA_FAST_MEET_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for fast_meet() function.
#define fast_meet_return_t(multivector_type1,multivector_type2) \
	ga::multivector<multivector_type1::model_t,ga::fast_meet_return<multivector_type1::model_t,multivector_type1::store_t,multivector_type2::store_t>::store_t>

// Return type for fast_meet() function.
template<typename model, typename store1, typename store2>
struct fast_meet_return
{
	// Store type.
	typedef typename lcont_em_return<model,typename lcont_em_return<model,store2,typename fast_join_return<model,store1,store2>::store_t>::store_t,store1>::store_t store_t;
};

// Return type for fast_meet() function (specialization of fast_meet_return<model,store1,store2> for store1 equal to store_none).
template<typename model, typename store2>
struct fast_meet_return<model,store_none,store2>
{
	// Store type.
	typedef store_none store_t;
};

// Return type for fast_meet() function (specialization of fast_meet_return<model,store1,store2> for store2 equal to store_none).
template<typename model, typename store1>
struct fast_meet_return<model,store1,store_none>
{
	// Store type.
	typedef store_none store_t;
};

// Return type for fast_meet() function (specialization of fast_meet_return<model,store1,store2> for store1 and store2 equal to store_none).
template<typename model>
struct fast_meet_return<model,store_none,store_none>
{
	// Store type.
	typedef store_none store_t;
};

/*******************************************************************************************************
 * Meet having two multivectors.
 *******************************************************************************************************/

// Meet of a specialized multivector with another specialized multivector (they must be blades). The algorithm is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
template<typename model, typename store1, typename store2>
inline
multivector<model,typename fast_meet_return<model,store1,store2>::store_t>
fast_meet(const multivector<model,store1> &m1, const multivector<model,store2> &m2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return lcont_em( lcont_em( m2, inverse_em( fast_join( m1, m2, tolerance ), tolerance ) ), m1 );
}

/*******************************************************************************************************
 * Meet having a scalar.
 *******************************************************************************************************/

// Meet of a scalar value with a specialized multivector (it must be a blade). The algorithm is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
template<typename model, typename store2>
inline
multivector<model,typename fast_meet_return<model,store_scalar,store2>::store_t>
fast_meet(const real_t &scalar, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return lcont_em( lcont_em( m, inverse_em( fast_join( scalar, m, tolerance ), tolerance ) ), scalar );
}

// Meet of a specialized multivector (it must be a blade) with a scalar value. The algorithm is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
template<typename model, typename store1>
inline
multivector<model,typename fast_meet_return<model,store1,store_scalar>::store_t>
fast_meet(const multivector<model,store1> &m, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return lcont_em( lcont_em( scalar, inverse_em( fast_join( m, scalar, tolerance ), tolerance ) ), m );
}

// Meet of a scalar value with another scalar value. The algorithm is described in D. Fontijne (2008), "Efficient algorithms for factorization and join of blades", In Proc. of the AGACSE, Springer.
template<typename model>
inline
multivector<model,typename fast_meet_return<model,store_scalar,store_scalar>::store_t>
fast_meet(const real_t &scalar1, const real_t &scalar2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return lcont_em( lcont_em( scalar2, inverse_em( fast_join<model>( scalar1, scalar2, tolerance ), tolerance ) ), scalar1 );
}

/*******************************************************************************************************
 * Meet having a zero multivector.
 *******************************************************************************************************/

// Meet of a zero multivector with a specialized multivector (it must be a blade).
template<typename model, typename store2>
inline
multivector<model,typename fast_meet_return<model,store_none,store2>::store_t>
fast_meet(const multivector<model,store_none> &zero, const multivector<model,store2> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The second input multivector should be blade." );

	return zero;
}

// Meet of a zero multivector with a scalar value.
template<typename model>
inline
multivector<model,typename fast_meet_return<model,store_none,store_scalar>::store_t>
fast_meet(const multivector<model,store_none> &zero, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return zero;
}

// Meet of a specialized multivector (it must be a blade) with a zero multivector.
template<typename model, typename store1>
inline
multivector<model,typename fast_meet_return<model,store1,store_none>::store_t>
fast_meet(const multivector<model,store1> &m, const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_blade( m, tolerance ), "The first input multivector should be blade." );

	return zero;
}

// Meet of a scalar value with a zero multivector.
template<typename model>
inline
multivector<model,typename fast_meet_return<model,store_scalar,store_none>::store_t>
fast_meet(const real_t &scalar, const multivector<model,store_none> &zero, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return zero;
}

// Meet of a zero multivector with another zero multivector.
template<typename model>
inline
multivector<model,typename fast_meet_return<model,store_none,store_none>::store_t>
fast_meet(const multivector<model,store_none> &zero1, const multivector<model,store_none> &zero2, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	return zero1;
}

}

#endif // !_GA_FAST_MEET_
