/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#include "common.h"

/*******************************************************************************************************
 * The main function.
 *******************************************************************************************************/

// The MEX-file gateway function.
void
mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	EXCEPTION_HANDLING_BEGIN

	// Create resulting array.
	const mxArray *arg1 = prhs[0];
	const mxArray *arg2 = prhs[1];
	const ga::real_t tol = *mxGetPr( prhs[2] );

	const int nelems1 = mxGetNumberOfElements( arg1 );
	const int nelems2 = mxGetNumberOfElements( arg2 );

	if ((nelems1 == nelems2) || (nelems2 == 1))
	{
		const int ndims1 = mxGetNumberOfDimensions( arg1 );
		const int *dims1 = mxGetDimensions( arg1 );
		plhs[0] = mxCreateLogicalArray( ndims1, dims1 );
	}
	else
	{
		const int ndims2 = mxGetNumberOfDimensions( arg2 );
		const int *dims2 = mxGetDimensions( arg2 );
		plhs[0] = mxCreateLogicalArray( ndims2, dims2 );
	}
	
	mxLogical *result = mxGetLogicals( plhs[0] );

	// Populate the created array.
	if (nelems1 == nelems2)
	{
		int i;

		#pragma omp parallel for num_threads( std::min( omp_get_num_procs() * 2, nelems1 ) )
		for (i=0; i<nelems1; ++i)
		{
			OMP_LOOP_EXCEPTION_HANDLING_BEGIN
			result[i] = OPERATION( to_multivector( arg1, i ), to_multivector( arg2, i ), tol );
			OMP_LOOP_EXCEPTION_HANDLING_END
		}
	}

	if (nelems2 == 1)
	{
		int i;
		const multivector_t &m2 = to_multivector( arg2, 0 );

		#pragma omp parallel for num_threads( std::min( omp_get_num_procs() * 2, nelems1 ) )
		for (i=0; i<nelems1; ++i)
		{
			OMP_LOOP_EXCEPTION_HANDLING_BEGIN
			result[i] = OPERATION( to_multivector( arg1, i ), m2, tol );
			OMP_LOOP_EXCEPTION_HANDLING_END
		}
	}

	if (nelems1 == 1)
	{
		int i;
		const multivector_t &m1 = to_multivector( arg1, 0 );
		
		#pragma omp parallel for num_threads( std::min( omp_get_num_procs() * 2, nelems2 ) )
		for (i=0; i<nelems2; ++i)
		{
			OMP_LOOP_EXCEPTION_HANDLING_BEGIN
			result[i] = OPERATION( m1, to_multivector( arg2, i ), tol );
			OMP_LOOP_EXCEPTION_HANDLING_END
		}
	}

	EXCEPTION_HANDLING_END
}
