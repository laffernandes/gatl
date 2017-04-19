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

	typedef std::vector<ga::multivector<ga_model,ga::store_grade<1,ga_model>::store_type> > factors_t;

	// Take input multivector and perform factorization.
	const mxArray *arg = prhs[0];
	const ga::real_t tol = *mxGetPr( prhs[1] );

	ga::real_t scalar;
	factors_t factors;
	ga::factorize_em( scalar, factors, to_multivector( arg, 0 ), tol );

	// Create resulting array for the scalar value, and populate it.
	plhs[0] = mxCreateDoubleMatrix( 1, 1, mxREAL );
	*mxGetPr( plhs[0] ) = scalar;

	// Create resulting array for the factors, and populate it.
	plhs[1] = alloc_struct_matrix( 1, factors.size() );

	int i = 0;
	for (factors_t::iterator factor=factors.begin(); factor!=factors.end(); ++factor, ++i)
	{
		to_matlab( plhs[1], i, *factor );
	}

	EXCEPTION_HANDLING_END
}
