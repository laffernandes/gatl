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
 * Some internal functions.
 *******************************************************************************************************/

// Retrieves the metric matrix entries.
template<ga::index_t index>
inline
void
set_metric_matrix_entries(double *result)
{
	// Set current entry.
	static const ga::index_t row = index / ga_model::basis_vectors_count;
	static const ga::index_t column = index - (row * ga_model::basis_vectors_count);

	result[index] = ga_model::metric<row,column>::result;

	// Set next entry.
	set_metric_matrix_entries<index+1>( result );
}

// Specialization of set_metric_matrix_entries<index>() for index equal to the number of matrix cells.
template<>
inline
void
set_metric_matrix_entries<ga_model::basis_vectors_count*ga_model::basis_vectors_count>(double *result)
{
	// Loop's end.
}

/*******************************************************************************************************
 * The main function.
 *******************************************************************************************************/

// The MEX-file gateway function.
void
mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	EXCEPTION_HANDLING_BEGIN

	static const int count = ga_model::basis_vectors_count;
	
	// Create resulting matrix.
	plhs[0] = mxCreateDoubleMatrix( count, count, mxREAL );
	mxArray *result = plhs[0];

	// Populate the created matrix with the matrix matrix.
	set_metric_matrix_entries<0>( mxGetPr( result ) );

	EXCEPTION_HANDLING_END
}
