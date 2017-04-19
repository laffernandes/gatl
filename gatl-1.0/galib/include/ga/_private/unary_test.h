/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_UNARY_TEST_
#define _GA_PRIVATE_UNARY_TEST_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::unary_test<test,store> struct definition.
 *******************************************************************************************************/

// The base struct for create unary tests over the basis blades stored by a multivector.
template<typename test, typename store>
struct unary_test
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *coefficient, const real_t &tolerance)
	{
		return ((test::template run<store::bitmap>( *coefficient, tolerance )) && (unary_test<test,typename store::next>::run( coefficient + 1, tolerance )));
	}
};

// Specialization of unary_test<test,store> for store equal to store_none.
template<typename test>
struct unary_test<test,store_none>
{
	// The main method.
	static _GA_ALWAYS_INLINE
	bool run(const real_t *coefficient, const real_t &tolerance)
	{
		return true;
	}
};

/*******************************************************************************************************
 * ga::_private::doesnt_have_grade<grade> struct definition.
 *******************************************************************************************************/

// The base struct for create the test function that checks whether a given multivector has at leat one non zero coefficient at a given grade.
template<int grade>
struct doesnt_have_grade
{
	// The main method.
	template<bitmap_t basis_blade>
	static _GA_ALWAYS_INLINE
	bool run(const real_t &coefficient, const real_t &tolerance)
	{
		return ((grade != bit_count<basis_blade>::result) || (is_zero( coefficient, tolerance )));
	}
};

/*******************************************************************************************************
 * ga::_private::has_even_grade_only struct definition.
 *******************************************************************************************************/

// The base struct for create the test function that checks whether a given multivector has non zero coefficient values only at even grade.
struct has_even_grade_only
{
	// The main method.
	template<bitmap_t basis_blade>
	static _GA_ALWAYS_INLINE
	bool run(const real_t &coefficient, const real_t &tolerance)
	{
		return (((bit_count<basis_blade>::result & 1) == 0) || (is_zero( coefficient, tolerance )));
	}
};

/*******************************************************************************************************
 * ga::_private::has_odd_grade_only struct definition.
 *******************************************************************************************************/

// The base struct for create the test function that checks whether a given multivector has non zero coefficient values only at odd grade.
struct has_odd_grade_only
{
	// The main method.
	template<bitmap_t basis_blade>
	static _GA_ALWAYS_INLINE
	bool run(const real_t &coefficient, const real_t &tolerance)
	{
		return (((bit_count<basis_blade>::result & 1) != 0) || (is_zero( coefficient, tolerance )));
	}
};

/*******************************************************************************************************
 * ga::_private::is_grade_homogeneous<grade> struct definition.
 *******************************************************************************************************/

// The base struct for create the test function that checks whether a given multivector has at leat one non zero coefficient only at a given grade.
template<int grade>
struct is_grade_homogeneous
{
	// The main method.
	template<bitmap_t basis_blade>
	static _GA_ALWAYS_INLINE
	bool run(const real_t &coefficient, const real_t &tolerance)
	{
		return ((grade == bit_count<basis_blade>::result) || (is_zero( coefficient, tolerance )));
	}
};

/*******************************************************************************************************
 * ga::_private::is_scalar struct definition.
 *******************************************************************************************************/

// The base struct for create the test function that checks whether a given multivector is a scalar value.
struct is_scalar
{
	// The main method.
	template<bitmap_t basis_blade>
	static _GA_ALWAYS_INLINE
	bool run(const real_t &coefficient, const real_t &tolerance)
	{
		if (basis_blade != 0)
		{
			return is_zero( coefficient, tolerance );
		}
		else
		{
			return true;
		}
	}
};

/*******************************************************************************************************
 * ga::_private::is_pseudoscalar<model> struct definition.
 *******************************************************************************************************/

// The base struct for create the test function that checks whether a given multivector is a pseudoscalar.
template<typename model>
struct is_pseudoscalar
{
	// The main method.
	template<bitmap_t basis_blade>
	static _GA_ALWAYS_INLINE
	bool run(const real_t &coefficient, const real_t &tolerance)
	{
		if (basis_blade != (model::basis_blades_count - 1))
		{
			return is_zero( coefficient, tolerance );
		}
		else
		{
			return true;
		}
	}
};

}

}

#endif // !_GA_PRIVATE_UNARY_TEST_
