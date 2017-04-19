/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GAMATLAB_COMMON_
#define _GAMATLAB_COMMON_

// MEX-file Library.
#include "mex.h"

// Standard C++ Library.
#include <cstring>
#include <algorithm>

// Geometric Algebra Library.
#include "ga.h"

#ifdef _OPENMP 

	// Open Multi-Processing API.
	#include <omp.h>

#endif // _OPENMP

/*******************************************************************************************************
 * Some useful macros and types for exception handling and OpenMP.
 *******************************************************************************************************/

#ifdef _OPENMP

	// A type that defines an exception raised inside some OpenMP parallel section.
	struct error_msg_t
	{
		// Error message identifier.
		std::string id;

		// Error message text.
		std::string text;

		// Set identifier and text.
		inline
		void set(const std::string &error_id, const std::string &error_text)
		{
			#pragma omp critical (SET_ERROR_MSG)
			{
				id = error_id;
				text = error_text;
			}
		}

	};

	// This macro defines the begin of a exception handling block inside a OpenMP parallel loop.
	#define OMP_LOOP_EXCEPTION_HANDLING_BEGIN \
		try \
		{ \

	// This macro defines the end of a exception handling block inside a OpenMP parallel loop.
	#define OMP_LOOP_EXCEPTION_HANDLING_END \
		} \
		catch (ga::assertion_error &error) \
		{ \
			error_msg.set( "GAToolbox:AssertionError", error.what() ); \
		} \
		catch (std::exception &error) \
		{ \
			error_msg.set( "GAToolbox:UnknownException", error.what() ); \
		} \

	// This macro defines the begin of a exception handling block.
	#define EXCEPTION_HANDLING_BEGIN \
		try \
		{ \
			error_msg_t error_msg; \
		\

	// This macro defines the end of a exception handling block.
	#define EXCEPTION_HANDLING_END \
			if (!error_msg.id.empty()) \
			{ \
				mexErrMsgIdAndTxt( error_msg.id.c_str(), error_msg.text.c_str() ); \
			} \
		} \
		catch (ga::assertion_error &error) \
		{ \
			mexErrMsgIdAndTxt( "GAToolbox:AssertionError", error.what() ); \
		} \
		catch (std::exception &error) \
		{ \
			mexErrMsgIdAndTxt( "GAToolbox:UnknownException", error.what() ); \
		} \

#else // !_OPENMP

	// This macro defines the begin of a exception handling block inside a OpenMP parallel loop.
	#define OMP_LOOP_EXCEPTION_HANDLING_BEGIN \

	// This macro defines the end of a exception handling block inside a OpenMP parallel loop.
	#define OMP_LOOP_EXCEPTION_HANDLING_END \

	// This macro defines the begin of a exception handling block.
	#define EXCEPTION_HANDLING_BEGIN \
		try \
		{ \

	// This macro defines the end of a exception handling block.
	#define EXCEPTION_HANDLING_END \
		} \
		catch (ga::assertion_error &error) \
		{ \
			mexErrMsgIdAndTxt( "GAToolbox:AssertionError", error.what() ); \
		} \
		catch (std::exception &error) \
		{ \
			mexErrMsgIdAndTxt( "GAToolbox:UnknownException", error.what() ); \
		} \

#endif // _OPENMP

/*******************************************************************************************************
 * Some initialization functions.
 *******************************************************************************************************/

// Returns the Matlab specialized model name.
inline
const char*
model_name()
{
#if defined(USING_CLIFFORD_MODEL)

	static char name[32];
	sprintf( name, "ga%dp%dq", P_VECTORS, Q_VECTORS );
	return name;

#elif defined(USING_EUCLIDEAN_MODEL)

	static char name[32];
	sprintf( name, "ga%de", BASE_SPACE_DIMS );
	return name;

#elif defined(USING_HOMOGENEOUS_MODEL)

	static char name[32];
	sprintf( name, "ga%dh", BASE_SPACE_DIMS );
	return name;

#elif defined(USING_CONFORMAL_MODEL)

	static char name[32];
	sprintf( name, "ga%dc", BASE_SPACE_DIMS );
	return name;

#elif defined(USING_CONFORMAL_VORONOI_MODEL)

	static char name[32];
	sprintf( name, "ga%dcv", BASE_SPACE_DIMS );
	return name;

#endif // USING_???_MODEL
}

// Returns the i-th base vector name.
template<ga::index_t index>
inline
const ga::name_t base_vector_name()
{
	static char name[32];
	sprintf( name, "e%d", index );
	return name;
}

/*******************************************************************************************************
 * Some useful constant values for the specialized geometric algebra model (Matlab) specification.
 *******************************************************************************************************/

// Specifies the Matlab specialized model name.
static const char* MODEL_NAME = model_name();

/*******************************************************************************************************
 * Some useful constant values for the (Matlab) multivector class.
 *******************************************************************************************************/

// Specifies the number of fields of the Matlab multivector class.
static const int MULTIVECTOR_FIELDS_COUNT = 2;

// Specifies the index of the model field of the Matlab multivector class.
static const int MULTIVECTOR_MODEL_FIELD_INDEX = 0;

// Specifies the name of the model field of the Matlab multivector class.
static const char* MULTIVECTOR_MODEL_FIELD_NAME = "model";

// Specifies the index of the coefficients field of the Matlab multivector class.
static const int MULTIVECTOR_COEFFICIENTS_FIELD_INDEX = 1;

// Specifies the name of the coefficients field of the Matlab multivector class.
static const char* MULTIVECTOR_COEFFICIENTS_FIELD_NAME = "coefficients";

// Specifies the set of field names of the Matlab multivector class.
static const char *MULTIVECTOR_FIELD_NAMES[MULTIVECTOR_FIELDS_COUNT] = {
		MULTIVECTOR_MODEL_FIELD_NAME,
		MULTIVECTOR_COEFFICIENTS_FIELD_NAME
	};

/*******************************************************************************************************
 * Clifford model class definitions.
 *******************************************************************************************************/

#if defined(USING_CLIFFORD_MODEL)

// Assumed geometric algebra model.
typedef ga::clifford::model<P_VECTORS,Q_VECTORS> ga_model;

// Basis vectors name initialization.
template<typename model, ga::index_t index>
const ga::name_t ga::basis_vector<model,index>::name = base_vector_name<index+1>();


/*******************************************************************************************************
 * Euclidean Vector space model class definitions.
 *******************************************************************************************************/

#elif defined(USING_EUCLIDEAN_MODEL)

// Assumed geometric algebra model.
typedef ga::euclidean::model<BASE_SPACE_DIMS> ga_model;

// Basis vectors name initialization.
template<typename model, ga::index_t index>
const ga::name_t ga::basis_vector<model,index>::name = base_vector_name<index+1>();

/*******************************************************************************************************
 * Homogeneous model class definitions.
 *******************************************************************************************************/

#elif defined(USING_HOMOGENEOUS_MODEL)

// Assumed geometric algebra model.
typedef ga::homogeneous::model<BASE_SPACE_DIMS,0> ga_model;

// Basis vectors name initialization.
template<typename model, ga::index_t index>
const ga::name_t ga::basis_vector<model,index>::name = base_vector_name<index>();

/*******************************************************************************************************
 * Conformal model class definitions.
 *******************************************************************************************************/

#elif defined(USING_CONFORMAL_MODEL)

// Assumed geometric algebra model.
typedef ga::conformal::model<BASE_SPACE_DIMS,0,BASE_SPACE_DIMS+1> ga_model;

// Basis vectors name initialization.
template<typename model, ga::index_t index>
const ga::name_t ga::basis_vector<model,index>::name =
	(index == 0) ? "no"
	: (index < (BASE_SPACE_DIMS + 1)) ? base_vector_name<index>()
	: (index == (BASE_SPACE_DIMS + 1)) ? "ni"
	: "error";

/*******************************************************************************************************
 * Conformal (for Voronoi) model class definitions.
 *******************************************************************************************************/

#elif defined(USING_CONFORMAL_VORONOI_MODEL)

// Assumed geometric algebra model.
typedef ga::conformal::model<BASE_SPACE_DIMS,BASE_SPACE_DIMS+1,BASE_SPACE_DIMS> ga_model;

// Basis vectors name initialization.
template<typename model, ga::index_t index>
const ga::name_t ga::basis_vector<model,index>::name =
	(index < BASE_SPACE_DIMS) ? base_vector_name<index+1>()
	: (index == BASE_SPACE_DIMS) ? "ni"
	: (index == (BASE_SPACE_DIMS + 1)) ? "no"
	: "error";

#endif // USING_???_MODEL

/*******************************************************************************************************
 * Specialized multivector definition.
 *******************************************************************************************************/

// A multivector having all the coefficients.
typedef ga::multivector<
		ga_model,
		ga::store_all<ga_model>::store_type
	> multivector_t;

/*******************************************************************************************************
 * Multivector matrix definition.
 *******************************************************************************************************/

// A multivector matrix.
typedef la::dmatrix<
		ga::real_t,
		ga_model::basis_blades_count,
		1
	> multivector_matrix_t;

/*******************************************************************************************************
 * Operation matrix definition.
 *******************************************************************************************************/

// A product matrix.
typedef la::dmatrix<
		ga::real_t,
		ga_model::basis_blades_count,
		ga_model::basis_blades_count
	> product_matrix_t;

/*******************************************************************************************************
 * Tensor definitions.
 *******************************************************************************************************/

// A 2nd-rank tensor.
typedef la::dtensor2<
		ga::real_t,
		ga_model::basis_blades_count
	> rank2_tensor_t;

// A 3rd-rank tensor.
typedef la::dtensor3<
		ga::real_t,
		ga_model::basis_blades_count
	> rank3_tensor_t;

/*******************************************************************************************************
 * Some useful cast functions.
 *******************************************************************************************************/

// Allocates a multidimensional array of multivector matrices.
inline
mxArray*
alloc_multivector_matrix_array(const int input_ndims, const int *input_dims)
{
	const int ndims = 1 + input_ndims;
	int *dims = static_cast<int*>( mxMalloc( ndims * sizeof( int ) ) );

	dims[0] = ga_model::basis_blades_count;
	for (int i=1; i!=ndims; ++i)
	{
		dims[i] = input_dims[i-1];
	}
	
	return mxCreateNumericArray( ndims, dims, mxDOUBLE_CLASS, mxREAL );
}

// Allocates a multidimensional array of matrices encoding linear operations.
inline
mxArray*
alloc_operation_matrix_array(const int input_ndims, const int *input_dims)
{
	const int ndims = 2 + input_ndims;
	int *dims = static_cast<int*>( mxMalloc( ndims * sizeof( int ) ) );

	dims[0] = dims[1] = ga_model::basis_blades_count;
	for (int i=2; i!=ndims; ++i)
	{
		dims[i] = input_dims[i-2];
	}
	
	return mxCreateNumericArray( ndims, dims, mxDOUBLE_CLASS, mxREAL );
}

// Allocates a multidimensional array of product 2rd-rank tensors.
inline
mxArray*
alloc_rank2_tensor_array()
{
	int dims[2] = { ga_model::basis_blades_count, ga_model::basis_blades_count };
	return mxCreateNumericArray( 2, dims, mxDOUBLE_CLASS, mxREAL );
}

// Allocates a multidimensional array of product 3rd-rank tensors.
inline
mxArray*
alloc_rank3_tensor_array()
{
	int dims[3] = { ga_model::basis_blades_count, ga_model::basis_blades_count, ga_model::basis_blades_count };
	return mxCreateNumericArray( 3, dims, mxDOUBLE_CLASS, mxREAL );
}

// Allocates a multidimensional array of multivectors.
inline
mxArray*
alloc_struct_array(const int ndims, const int *dims, const int nelems)
{
	mxArray* result = mxCreateStructArray( ndims, dims, MULTIVECTOR_FIELDS_COUNT, MULTIVECTOR_FIELD_NAMES );

	for (int i=0; i<nelems; ++i)
	{
		// Set model field.
		mxSetFieldByNumber( result, i, MULTIVECTOR_MODEL_FIELD_INDEX, mxCreateString( MODEL_NAME ) );

		// Set coefficients field.
		mxSetFieldByNumber( result, i, MULTIVECTOR_COEFFICIENTS_FIELD_INDEX, mxCreateDoubleMatrix( 1, multivector_t::size, mxREAL ) );
	}

	return result;
}

// Allocates a matrix of multivectors.
inline
mxArray*
alloc_struct_matrix(const int m, const int n)
{
	const int nelems = m * n;
	mxArray* result = mxCreateStructMatrix( m, n, MULTIVECTOR_FIELDS_COUNT, MULTIVECTOR_FIELD_NAMES );

	for (int i=0; i<nelems; ++i)
	{
		// Set model field.
		mxSetFieldByNumber( result, i, MULTIVECTOR_MODEL_FIELD_INDEX, mxCreateString( MODEL_NAME ) );

		// Set coefficients field.
		mxSetFieldByNumber( result, i, MULTIVECTOR_COEFFICIENTS_FIELD_INDEX, mxCreateDoubleMatrix( 1, multivector_t::size, mxREAL ) );
	}

	return result;
}

// Converts a multivector matrix to a mxArray item.
inline
void
to_matlab(mxArray *result, const int index, const multivector_matrix_t &m)
{
	int subs[2] = { 0, index };
	double *buffer = mxGetPr( result );

	for (subs[0]=0; subs[0]!=(int)multivector_matrix_t::size; ++subs[0])
	{
		buffer[mxCalcSingleSubscript( result, 2, subs )] = m[subs[0]];
	}
}

// Converts a product matrix to a mxArray item.
inline
void
to_matlab(mxArray *result, const int index, const product_matrix_t &m)
{
	int subs[3] = { 0, 0, index };
	double *buffer = mxGetPr( result );

	for (subs[0]=0; subs[0]!=(int)product_matrix_t::rows; ++subs[0])
	{
		for (subs[1]=0; subs[1]!=(int)product_matrix_t::cols; ++subs[1])
		{
			buffer[mxCalcSingleSubscript( result, 3, subs )] = m(subs[0],subs[1]);
		}
	}
}

// Converts a 2nd-rank tensor to a mxArray item.
inline
void
to_matlab(mxArray *result, const rank2_tensor_t &t)
{
	double *buffer = mxGetPr( result );

	int subs[2];
	for (subs[0]=0; subs[0]!=(int)ga_model::basis_blades_count; ++subs[0])
	{
		for (subs[1]=0; subs[1]!=(int)ga_model::basis_blades_count; ++subs[1])
		{
			buffer[mxCalcSingleSubscript( result, 2, subs )] = t( subs[0], subs[1] );
		}
	}
}

// Converts a 3rd-rank tensor to a mxArray item.
inline
void
to_matlab(mxArray *result, const rank3_tensor_t &t)
{
	double *buffer = mxGetPr( result );

	int subs[3];
	for (subs[0]=0; subs[0]!=(int)ga_model::basis_blades_count; ++subs[0])
	{
		for (subs[1]=0; subs[1]!=(int)ga_model::basis_blades_count; ++subs[1])
		{
			for (subs[2]=0; subs[2]!=(int)ga_model::basis_blades_count; ++subs[2])
			{
				buffer[mxCalcSingleSubscript( result, 3, subs )] = t( subs[0], subs[1], subs[2] );
			}
		}
	}
}

// Converts a multivector to a mxArray item.
inline
void
to_matlab(mxArray *result, const int index, const multivector_t &m)
{
	double *buffer = mxGetPr( mxGetFieldByNumber( result, index, MULTIVECTOR_COEFFICIENTS_FIELD_INDEX ) );
	for (ga::index_t i=0; i!=m.size; ++i)
	{
		buffer[i] = m.coefficients[i];
	}
}

// Converts a specialized multivector to a mxArray item.
template<typename store>
inline
void
to_matlab(mxArray *result, const int index, const ga::multivector<ga_model,store> &m)
{
	multivector_t aux;
	aux = m;
	to_matlab( result, index, aux );
}

// Converts a scalar value to a mxArray item.
inline
void
to_matlab(mxArray *result, const int index, const ga::real_t &scalar)
{
	multivector_t aux;
	ga::assign<false>( aux, scalar, 1.0e-5 );
	to_matlab( result, index, aux );
}

// Converts a mxArray item to multivector.
inline
multivector_t
to_multivector(const mxArray *m, const int index)
{
	const double *buffer = mxGetPr( mxGetFieldByNumber( m, index, MULTIVECTOR_COEFFICIENTS_FIELD_INDEX ) );
	
	multivector_t result;
	for (ga::index_t i=0; i!=result.size; ++i)
	{
		result.coefficients[i] = buffer[i];
	}

	return result;
}

#endif // !_GAMATLAB_COMMON_
