/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_APPLY_VERSOR_
#define _GA_APPLY_VERSOR_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for apply_even_versor() and apply_odd_versor() functions.
#define apply_versor_return_t(versor_type,multivector_type) \
	ga::multivector<versor_type::model_t,ga::apply_versor_return<versor_type::model_t,versor_type::store_t,multivector_type::store_t>::store_t>

// Return type for apply_even_versor() and apply_odd_versor() functions.
template<typename model, typename store_versor, typename store>
struct apply_versor_return
{
	// Store type.
	typedef typename _private::take_grades<
			_private::stored_grades<store>::result,
			typename gp_return<model,typename gp_return<model,store_versor,store>::store_t,store_versor>::store_t
		>::result store_t;
};

// Return type for apply_even_versor_em() and apply_odd_versor_em() functions (Euclidean metric).
#define apply_versor_em_return_t(versor_type,multivector_type) \
	ga::multivector<versor_type::model_t,ga::apply_versor_em_return<versor_type::model_t,versor_type::store_t,multivector_type::store_t>::store_t>

// Return type for apply_even_versor_em() and apply_odd_versor_em() functions (Euclidean metric).
template<typename model, typename store_versor, typename store>
struct apply_versor_em_return
{
	// Store type.
	typedef typename _private::take_grades<
			_private::stored_grades<store>::result,
			typename gp_em_return<model,typename gp_em_return<model,store_versor,store>::store_t,store_versor>::store_t
		>::result store_t;
};

/*******************************************************************************************************
 * Versor product implementations having an even versor.
 *******************************************************************************************************/

// Apply an even versor (i.e., an orthogonal transformation) to a specialized multivector.
template<typename model, typename store_versor, typename store>
inline
multivector<model,typename apply_versor_return<model,store_versor,store>::store_t>
apply_even_versor(const multivector<model,store_versor> &versor, const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_even_grade_only( versor, tolerance ), "The input versor is not even." );

	multivector<model,typename apply_versor_return<model,store_versor,store>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<model,typename gp_return<model,store_versor,store>::store_t,store_versor,typename apply_versor_return<model,store_versor,store>::store_t>::run( result.data(), gp( versor, m ).data(), inverse( versor, tolerance ).data() );
	}
	return result;
}

// Apply an even versor (i.e., an orthogonal transformation) to a specialized multivector (Euclidean metric).
template<typename model, typename store_versor, typename store>
inline
multivector<model,typename apply_versor_em_return<model,store_versor,store>::store_t>
apply_even_versor_em(const multivector<model,store_versor> &versor, const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor_em( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_even_grade_only( versor, tolerance ), "The input versor is not even." );

	multivector<model,typename apply_versor_em_return<model,store_versor,store>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<_private::euclidean_model,typename gp_em_return<model,store_versor,store>::store_t,store_versor,typename apply_versor_em_return<model,store_versor,store>::store_t>::run( result.data(), gp_em( versor, m ).data(), inverse_em( versor, tolerance ).data() );
	}
	return result;
}

// Apply an even versor (i.e., an orthogonal transformation) to a scalar value.
template<typename model, typename store_versor>
inline
real_t
apply_even_versor(const multivector<model,store_versor> &versor, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_even_grade_only( versor, tolerance ), "The input versor is not even." );

	return scalar;
}

// Apply an even versor (i.e., an orthogonal transformation) to a scalar value (Euclidean metric).
template<typename model, typename store_versor>
inline
real_t
apply_even_versor_em(const multivector<model,store_versor> &versor, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor_em( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_even_grade_only( versor, tolerance ), "The input versor is not even." );

	return scalar;
}

// Apply an even versor (i.e., an orthogonal transformation) to a specialized multivector. Here, 'iversor' is the inverse of the versor.
template<typename model, typename store_versor, typename store>
inline
multivector<model,typename apply_versor_return<model,store_versor,store>::store_t>
apply_even_versor(const multivector<model,store_versor> &versor, const multivector<model,store> &m, const multivector<model,store_versor> &iversor, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_even_grade_only( versor, tolerance ), "The input versor is not even." );
	ga_debug_assert( equal( inverse( versor, tolerance ), iversor, tolerance ) );

	multivector<model,typename apply_versor_return<model,store_versor,store>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<model,typename gp_return<model,store_versor,store>::store_t,store_versor,typename apply_versor_return<model,store_versor,store>::store_t>::run( result.data(), gp( versor, m ).data(), iversor.data() );
	}
	return result;
}

// Apply an even versor (i.e., an orthogonal transformation) to a specialized multivector (Euclidean metric). Here, 'iversor' is the inverse of the versor under Euclidean metric.
template<typename model, typename store_versor, typename store>
inline
multivector<model,typename apply_versor_em_return<model,store_versor,store>::store_t>
apply_even_versor_em(const multivector<model,store_versor> &versor, const multivector<model,store> &m, const multivector<model,store_versor> &iversor, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor_em( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_even_grade_only( versor, tolerance ), "The input versor is not even." );
	ga_debug_assert( equal( inverse_em( versor, tolerance ), iversor, tolerance ) );

	multivector<model,typename apply_versor_em_return<model,store_versor,store>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<_private::euclidean_model,typename gp_em_return<model,store_versor,store>::store_t,store_versor,typename apply_versor_em_return<model,store_versor,store>::store_t>::run( result.data(), gp_em( versor, m ).data(), iversor.data() );
	}
	return result;
}

// Apply an even versor (i.e., an orthogonal transformation) to a scalar value. Here, 'iversor' is the inverse of the versor.
template<typename model, typename store_versor>
inline
real_t
apply_even_versor(const multivector<model,store_versor> &versor, const real_t &scalar, const multivector<model,store_versor> &iversor, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_even_grade_only( versor, tolerance ), "The input versor is not even." );
	ga_debug_assert( equal( inverse( versor, tolerance ), iversor, tolerance ) );

	return scalar;
}

// Apply an even versor (i.e., an orthogonal transformation) to a scalar value (Euclidean metric). Here, 'iversor' is the inverse of the versor under Euclidean metric.
template<typename model, typename store_versor>
inline
real_t
apply_even_versor_em(const multivector<model,store_versor> &versor, const real_t &scalar, const multivector<model,store_versor> &iversor, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor_em( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_even_grade_only( versor, tolerance ), "The input versor is not even." );
	ga_debug_assert( equal( inverse_em( versor, tolerance ), iversor, tolerance ) );

	return scalar;
}

/*******************************************************************************************************
 * Versor product implementations having an odd versor.
 *******************************************************************************************************/

// Apply an odd versor (i.e., an orthogonal transformation) to a specialized multivector 'm'.
template<typename model, typename store_versor, typename store>
inline
multivector<model,typename apply_versor_return<model,store_versor,store>::store_t>
apply_odd_versor(const multivector<model,store_versor> &versor, const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	/* IMPLEMENTATION ISSUES
	 *
	 * Sections 7.6.1 and 7.6.2 describe some issues about applying odd versors
	 * to a general multivector. I do not understand that. However, I know that
	 * this implementation works for blades.
	 */

	ga_maybe_assert( is_versor( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_odd_grade_only( versor, tolerance ), "The input versor is not odd." );

	multivector<model,typename apply_versor_return<model,store_versor,store>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<model,typename gp_return<model,store_versor,store>::store_t,store_versor,typename apply_versor_return<model,store_versor,store>::store_t>::run( result.data(), gp( versor, grade_involution( m ) ).data(), inverse( versor, tolerance ).data() );
	}
	return result;
}

// Apply an odd versor (i.e., an orthogonal transformation) to a specialized multivector 'm' (Euclidean metric).
template<typename model, typename store_versor, typename store>
inline
multivector<model,typename apply_versor_em_return<model,store_versor,store>::store_t>
apply_odd_versor_em(const multivector<model,store_versor> &versor, const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	/* IMPLEMENTATION ISSUES
	 *
	 * Sections 7.6.1 and 7.6.2 describe some issues about applying odd versors
	 * to a general multivector. I do not understand that. However, I know that
	 * this implementation works for blades.
	 */

	ga_maybe_assert( is_versor_em( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_odd_grade_only( versor, tolerance ), "The input versor is not odd." );

	multivector<model,typename apply_versor_em_return<model,store_versor,store>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<_private::euclidean_model,typename gp_em_return<model,store_versor,store>::store_t,store_versor,typename apply_versor_em_return<model,store_versor,store>::store_t>::run( result.data(), gp_em( versor, grade_involution( m ) ).data(), inverse_em( versor, tolerance ).data() );
	}
	return result;
}

// Apply an odd versor (i.e., an orthogonal transformation) to a scalar value.
template<typename model, typename store_versor>
inline
real_t
apply_odd_versor(const multivector<model,store_versor> &versor, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_odd_grade_only( versor, tolerance ), "The input versor is not odd." );

	return grade_involution( scalar );
}

// Apply an odd versor (i.e., an orthogonal transformation) to a scalar value (Euclidean metric).
template<typename model, typename store_versor>
inline
real_t
apply_odd_versor_em(const multivector<model,store_versor> &versor, const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor_em( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_odd_grade_only( versor, tolerance ), "The input versor is not odd." );

	return grade_involution( scalar );
}

// Apply an odd versor (i.e., an orthogonal transformation) to a specialized multivector 'm'. Here, 'iversor' is the inverse of the versor.
template<typename model, typename store_versor, typename store>
inline
multivector<model,typename apply_versor_return<model,store_versor,store>::store_t>
apply_odd_versor(const multivector<model,store_versor> &versor, const multivector<model,store> &m, const multivector<model,store_versor> &iversor, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	/* IMPLEMENTATION ISSUES
	 *
	 * Sections 7.6.1 and 7.6.2 describe some issues about applying odd versors
	 * to a general multivector. I do not understand that. However, I know that
	 * this implementation works for blades.
	 */

	ga_maybe_assert( is_versor( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_odd_grade_only( versor, tolerance ), "The input versor is not odd." );
	ga_debug_assert( equal( inverse( versor, tolerance ), iversor, tolerance ) );

	multivector<model,typename apply_versor_return<model,store_versor,store>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<model,typename gp_return<model,store_versor,store>::store_t,store_versor,typename apply_versor_return<model,store_versor,store>::store_t>::run( result.data(), gp( versor, grade_involution( m ) ).data(), iversor.data() );
	}
	return result;
}

// Apply an odd versor (i.e., an orthogonal transformation) to a specialized multivector 'm' (Euclidean metric). Here, 'iversor' is the inverse of the versor under Euclidean metric.
template<typename model, typename store_versor, typename store>
inline
multivector<model,typename apply_versor_em_return<model,store_versor,store>::store_t>
apply_odd_versor_em(const multivector<model,store_versor> &versor, const multivector<model,store> &m, const multivector<model,store_versor> &iversor, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	/* IMPLEMENTATION ISSUES
	 *
	 * Sections 7.6.1 and 7.6.2 describe some issues about applying odd versors
	 * to a general multivector. I do not understand that. However, I know that
	 * this implementation works for blades.
	 */

	ga_maybe_assert( is_versor_em( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_odd_grade_only( versor, tolerance ), "The input versor is not odd." );
	ga_debug_assert( equal( inverse_em( versor, tolerance ), iversor, tolerance ) );

	multivector<model,typename apply_versor_em_return<model,store_versor,store>::store_t> result;
	if (result.size > 0)
	{
		_private::product_geometric_run<_private::euclidean_model,typename gp_em_return<model,store_versor,store>::store_t,store_versor,typename apply_versor_em_return<model,store_versor,store>::store_t>::run( result.data(), gp_em( versor, grade_involution( m ) ).data(), iversor.data() );
	}
	return result;
}

// Apply an odd versor (i.e., an orthogonal transformation) to a scalar value. Here, 'iversor' is the inverse of the versor.
template<typename model, typename store_versor>
inline
real_t
apply_odd_versor(const multivector<model,store_versor> &versor, const real_t &scalar, const multivector<model,store_versor> &iversor, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_odd_grade_only( versor, tolerance ), "The input versor is not odd." );
	ga_debug_assert( equal( inverse( versor, tolerance ), iversor, tolerance ) );

	return grade_involution( scalar );
}

// Apply an odd versor (i.e., an orthogonal transformation) to a scalar value (Euclidean metric). Here, 'iversor' is the inverse of the versor under Euclidean metric.
template<typename model, typename store_versor>
inline
real_t
apply_odd_versor_em(const multivector<model,store_versor> &versor, const real_t &scalar, const multivector<model,store_versor> &iversor, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( is_versor_em( versor, tolerance ), "The input versor is invalid." );
	ga_maybe_assert( has_odd_grade_only( versor, tolerance ), "The input versor is not odd." );
	ga_debug_assert( equal( inverse_em( versor, tolerance ), iversor, tolerance ) );

	return grade_involution( scalar );
}

}

#endif // !_GA_APPLY_VERSOR_
