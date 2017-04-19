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
 * Some useful constant values.
 *******************************************************************************************************/

// Specifies the number of fields of the Matlab output struct.
static const int OUTPUT_FIELDS_COUNT = 3;

// Specifies the index of the name field of the Matlab output struct.
static const int OUTPUT_NAME_FIELD_INDEX = 0;

// Specifies the name of the name field of the Matlab output struct.
static const char* OUTPUT_NAME_FIELD_NAME = "name";

// Specifies the index of the value field of the Matlab output struct.
static const int OUTPUT_VALUE_FIELD_INDEX = 1;

// Specifies the name of the value field of the Matlab output struct.
static const char* OUTPUT_VALUE_FIELD_NAME = "value";

// Specifies the index of the basis vector flag of the Matlab output struct.
static const int OUTPUT_BASIS_VECTOR_FIELD_INDEX = 2;

// Specifies the name of the basis vector flag of the Matlab output struct.
static const char* OUTPUT_BASIS_VECTOR_FIELD_NAME = "is_basis_vector";

// Specifies the set of field names of the Matlab output struct.
static const char *OUTPUT_FIELD_NAMES[OUTPUT_FIELDS_COUNT] = {
		OUTPUT_NAME_FIELD_NAME,
		OUTPUT_VALUE_FIELD_NAME,
		OUTPUT_BASIS_VECTOR_FIELD_NAME
	};

/*******************************************************************************************************
 * Some internal functions.
 *******************************************************************************************************/

// Specifies the i-th entry on the set of global constant values.
template<typename store>
inline
void
set_entry(mxArray *result, const int index, const ga::name_t &name, const ga::multivector<ga_model,store> &m, const bool is_basis_vector)
{
	// Create entry field values.
	mxArray *entry_name = mxCreateString( name.c_str() );

	mxArray *entry_value = alloc_struct_matrix( 1, 1 );
	to_matlab( entry_value, 0, m );

	mxArray *entry_basis_vector = mxCreateLogicalScalar( is_basis_vector );

	// Set entry fields.
	mxSetFieldByNumber( result, index, OUTPUT_NAME_FIELD_INDEX, entry_name );
	mxSetFieldByNumber( result, index, OUTPUT_VALUE_FIELD_INDEX, entry_value );
	mxSetFieldByNumber( result, index, OUTPUT_BASIS_VECTOR_FIELD_INDEX, entry_basis_vector );
}

// Specifies the basis vectors entries on the set of global constant values.
template<ga::index_t index>
inline
void
set_basis_vector_entries(mxArray *result)
{
	// Set current entry.
	multivector_t m;
	m = ga::multivector<ga_model,ga::store_none>();
	m.coefficients[ga::basis_vector<ga_model,index>::bitmap] = 1;

	set_entry( result, index, ga::basis_vector<ga_model,index>::name, m, true );

	// Set the next entry.
	set_basis_vector_entries<index+1>( result );
}

// Specialization of set_basis_vector_entries<index>() for index equal to the number of basis vectors.
template<>
inline
void
set_basis_vector_entries<ga_model::basis_vectors_count>(mxArray *result)
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

#if defined(USING_EUCLIDEAN_MODEL) || defined(USING_HOMOGENEOUS_MODEL) || defined(USING_CONFORMAL_MODEL) || defined(USING_CONFORMAL_VORONOI_MODEL)
	static const int count = ga_model::basis_vectors_count + 2;
#else // USING_???_MODEL
	static const int count = ga_model::basis_vectors_count + 1;
#endif // USING_???_MODEL
	
	// Create resulting array.
	mxArray *result = plhs[0] = mxCreateStructMatrix( count, 1, OUTPUT_FIELDS_COUNT, OUTPUT_FIELD_NAMES );

	// Populate the created array with basis vector.
	set_basis_vector_entries<0>( result );
	
	// Populate the created array with the pseudoscalar.
	static const ga::multivector<ga_model,ga::store_pseudoscalar<ga_model>::store_type> I = { { { 1 } } };
	set_entry( result, ga_model::basis_vectors_count, "I", I, false );

#ifdef USING_EUCLIDEAN_MODEL

	// Populate the created array with the Euclidean unit pseudoscalar.
	static const ga::multivector<ga_model,ga::store<(ga_model::basis_blades_count-1)> > Ie = { { { 1 } } };
	set_entry( result, ga_model::basis_vectors_count + 1, "Ie", Ie, false );

#elif USING_HOMOGENEOUS_MODEL

	// Populate the created array with the Euclidean unit pseudoscalar.
	static const ga::multivector<ga_model,ga::store<((ga_model::basis_blades_count-1)&(~ga_model::origin_vector_bitmap))> > Ie = { { { 1 } } };
	set_entry( result, ga_model::basis_vectors_count + 1, "Ie", Ie, false );

#elif USING_CONFORMAL_MODEL

	// Populate the created array with the Euclidean unit pseudoscalar.
	static const ga::multivector<ga_model,ga::store<((ga_model::basis_blades_count-1)&(~(ga_model::origin_point_bitmap|ga_model::infinity_point_bitmap)))> > Ie = { { { 1 } } };
	set_entry( result, ga_model::basis_vectors_count + 1, "Ie", Ie, false );

#elif USING_CONFORMAL_VORONOI_MODEL

	// Populate the created array with the Euclidean unit pseudoscalar.
	static const ga::multivector<ga_model,ga::store<((ga_model::basis_blades_count-1)&(~(ga_model::origin_point_bitmap|ga_model::infinity_point_bitmap)))> > Ie = { { { 1 } } };
	set_entry( result, ga_model::basis_vectors_count + 1, "Ie", Ie, false );

#endif // USING_???_MODEL

	EXCEPTION_HANDLING_END
}
