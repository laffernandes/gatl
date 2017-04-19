/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_INVERSE_MULTIVECTOR_
#define _GA_INVERSE_MULTIVECTOR_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Inverse function implementations for general multivectors.
 *******************************************************************************************************/

// Computes the inverse of a multivector. Use inverse() if you are working with blades or versors.
template<typename model, typename store>
inline
multivector<model,typename store_all<model>::store_type>
inverse_mv(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( !_private::is_empty_store<store>::result );

	try
	{
		// Compute the inverse geometric product matrix.
		const la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count> &matrix = la::inverse( gp_matrix<right_multiplication>( m ), tolerance );
		
		// Extract the resulting multivector as the first column of the inversed geometric product matrix.
		multivector<model,typename store_all<model>::store_type> result;
		
		for (index_t i=0; i!=result.size; ++i)
		{
			result[i] = matrix(i,0);
		}

		return result;
	}
	catch (la::singular_matrix_error &error)
	{
		ga_always_assert( false, "The input multivector is not invertible." );
	}
	catch (...)
	{
		throw; // Pass exception to some other handler.
	}

	// Never reaches here.
	multivector<model,typename store_all<model>::store_type> dummy;
	dummy = multivector<model,store_none>();
	return dummy;
}

// Computes the inverse of a multivector (Euclidean metric). Use inverse_em() if you are working with blades or versors.
template<typename model, typename store>
inline
multivector<model,typename store_all<model>::store_type>
inverse_mv_em(const multivector<model,store> &m, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_static_assert( !_private::is_empty_store<store>::result );

	try
	{
		// Compute the inverse geometric product matrix.
		const la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count> &matrix = la::inverse( gp_matrix_em<right_multiplication>( m ), tolerance );
		
		// Extract the resulting multivector as the first column of the inversed geometric product matrix.
		multivector<model,typename store_all<model>::store_type> result;
		
		for (index_t i=0; i!=result.size; ++i)
		{
			result[i] = matrix(i,0);
		}

		return result;
	}
	catch (la::singular_matrix_error &error)
	{
		ga_always_assert( false, "The input multivector is not invertible." );
	}
	catch (...)
	{
		throw; // Pass exception to some other handler.
	}

	// Never reaches here.
	multivector<model,typename store_all<model>::store_type> dummy;
	dummy = multivector<model,store_none>();
	return dummy;
}

// Computes the inverse of a scalar value.
inline
real_t
inverse_mv(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( !is_zero( scalar, tolerance ), "The input multivector is not invertible." );

	return 1 / scalar;
}

// Computes the inverse (Euclidean metric) of a scalar value.
inline
real_t
inverse_mv_em(const real_t &scalar, const real_t &tolerance _GA_DEFAULT_TOLERANCE)
{
	ga_maybe_assert( !is_zero( scalar, tolerance ), "The input multivector is not invertible." );

	return 1 / scalar;
}

}

#endif // !_GA_INVERSE_MULTIVECTOR_
