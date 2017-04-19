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

	// Get input multivector.
	const mxArray *arg1 = prhs[0];
	const multivector_t &m = to_multivector( arg1, 0 );

	// Get display format for output.
	const mxArray *arg2 = prhs[1];
	char format[256] = {};
	mxGetString( arg2, format, 256 );

	std::string format_str = format;
	std::transform( format_str.begin(), format_str.end(), format_str.begin(), ::tolower );

	// Create resulting buffer.
	std::ostringstream os;

	// Set display format.

	if (std::strcmp( format_str.c_str(), "short" ) == 0)
	{
		os << std::fixed << std::setprecision( 4 );
	}

	if (std::strcmp( format_str.c_str(), "long" ) == 0)
	{
		os << std::fixed << std::setprecision( 15 );
	}

	if (std::strcmp( format_str.c_str(), "shorte" ) == 0)
	{
		os << std::scientific << std::setprecision( 4 );
	}

	if (std::strcmp( format_str.c_str(), "longe" ) == 0)
	{
		os << std::scientific << std::setprecision( 15 );
	}

	// Write data.
	os << m;

	// Create resulting array.
	plhs[0] = mxCreateString( os.str().c_str() );

	EXCEPTION_HANDLING_END
}
