/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_TAKE_GRADE_
#define _GA_TAKE_GRADE_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Some useful macros.
 *******************************************************************************************************/

// Return type for take_grade() function.
#define take_grade_return_t(grade,multivector_type) \
	ga::multivector<multivector_type::model_t,ga::take_grade_return<grade,multivector_type::model_t,multivector_type::store_t>::store_t>

// Return type for take_grade() function.
template<int grade, typename model, typename store>
struct take_grade_return
{
	// Store type.
	typedef typename _private::take_grade<grade,store>::result store_t;
};

/*******************************************************************************************************
 * Take grade operation implementation (compile-time).
 *******************************************************************************************************/

// Returns the k-grade part of a specialized multivector.
template<int grade, typename model, typename store>
inline
multivector<model,typename take_grade_return<grade,model,store>::store_t>
take_grade(const multivector<model,store> &m)
{
	multivector<model,typename take_grade_return<grade,model,store>::store_t> result;
	if (result.size > 0)
	{
		_private::take_grade<grade,store>::run( result.data(), m.data() );
	}
	return result;
}

// Returns the k-grade part of a scalar value.
template<int grade, typename model>
inline
multivector<model,typename take_grade_return<grade,model,store_scalar>::store_t>
take_grade(const real_t &scalar)
{
	multivector<model,typename take_grade_return<grade,model,store_scalar>::store_t> result;
	if (result.size > 0)
	{
		_private::take_grade<grade,store_scalar>::run( result.data(), &scalar );
	}
	return result;
}

/*******************************************************************************************************
 * Take grade operation implementation (run-time).
 *******************************************************************************************************/

// Returns the k-grade part of a specialized multivector.
template<typename model, typename store>
inline
multivector<model,store>
take_grade(const int grade, const multivector<model,store> &m)
{
	multivector<model,store> result;
	if (result.size > 0)
	{
		_private::take_grade_runtime<store>::run( grade, result.data(), m.data() );
	}
	return result;
}

// Returns the k-grade part of a scalar value.
inline
real_t
take_grade(const int grade, const real_t &scalar)
{
	real_t result;
	_private::take_grade_runtime<store_scalar>::run( grade, &result, &scalar );
	return result;
}

}

#endif // !_GA_TAKE_GRADE_
