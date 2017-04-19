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
	const mxArray *arg = prhs[0];
	const ga::real_t tol = *mxGetPr( prhs[1] );

	const int nelems = mxGetNumberOfElements( arg );
	const int ndims = mxGetNumberOfDimensions( arg );
	const int *dims = mxGetDimensions( arg );
	plhs[0] = mxCreateLogicalArray( ndims, dims );

	mxLogical *result = mxGetLogicals( plhs[0] );

	// Populate the created array.
	int i;

	#pragma omp parallel for num_threads( std::min( omp_get_num_procs() * 2, nelems ) )
	for (i=0; i<nelems; ++i)
	{
		OMP_LOOP_EXCEPTION_HANDLING_BEGIN
		result[i] = OPERATION( to_multivector( arg, i ), tol );
		OMP_LOOP_EXCEPTION_HANDLING_END
	}

	EXCEPTION_HANDLING_END
}
