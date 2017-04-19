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
	const int *dims = mxGetDimensions( arg );

	if (dims[1] != BASE_SPACE_DIMS)
	{
		mexErrMsgTxt( "Wrong number of coordinates provided." );
		return;
	}

	mxArray *result = plhs[0] = alloc_struct_array( 1, dims, dims[0] );

	// Populate the created array.
	ga::real_t coords[BASE_SPACE_DIMS];
	const double *scalar = mxGetPr( arg );

	for (int i=0; i<dims[0]; ++i)
	{
		for (int j=0; j<BASE_SPACE_DIMS; ++j)
		{
			coords[j] = scalar[(j*dims[0])+i];
		}
		to_matlab( result, i, OPERATION<multivector_t>( coords ) );
	}

	EXCEPTION_HANDLING_END
}
