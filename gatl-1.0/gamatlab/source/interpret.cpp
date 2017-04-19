/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#undef GA_HIGHEST_ASSERTION_LEVEL
#include "common.h"

/*******************************************************************************************************
 * Specialized multivectors definition.
 *******************************************************************************************************/

#ifdef USING_EUCLIDEAN_MODEL

// Multivector representation of a purely Euclidean direction.
typedef multivector_t direction_t;

// Multivector representation of an Eucliden direction vector.
typedef take_grade_return_t(1,direction_t) factor_t;

#elif USING_HOMOGENEOUS_MODEL

// Multivector representation of a vector e0.
typedef ga::multivector<ga_model,ga::store<ga_model::origin_vector_bitmap> > e0_t;

// Multivector representation of a purely Euclidean direction.
typedef lcont_return_t(e0_t,multivector_t) direction_t;

// Multivector representation of an Eucliden direction vector.
typedef take_grade_return_t(1,direction_t) factor_t;

#elif USING_CONFORMAL_MODEL

// Multivector representation of a null vector no.
typedef ga::multivector<ga_model,ga::store<ga_model::origin_point_bitmap> > no_t;

// Multivector representation of a null vector ni.
typedef ga::multivector<ga_model,ga::store<ga_model::infinity_point_bitmap> > ni_t;

// Useful (and obscure) type definition.
typedef op_return_t(ni_t,multivector_t) ni_OP_m_t;

// Useful (and obscure) type definition.
typedef lcont_return_t(ni_t,multivector_t) ni_LCONT_m_t;

// Multivector representation of a purely Euclidean direction.
typedef lcont_return_t(no_t,ni_LCONT_m_t) direction_t;

// Multivector representation of an Eucliden direction vector.
typedef take_grade_return_t(1,direction_t) factor_t;

#elif USING_CONFORMAL_VORONOI_MODEL

// Multivector representation of a null vector no.
typedef ga::multivector<ga_model,ga::store<ga_model::origin_point_bitmap> > no_t;

// Multivector representation of a null vector ni.
typedef ga::multivector<ga_model,ga::store<ga_model::infinity_point_bitmap> > ni_t;

// Useful (and obscure) type definition.
typedef op_return_t(ni_t,multivector_t) ni_OP_m_t;

// Useful (and obscure) type definition.
typedef lcont_return_t(ni_t,multivector_t) ni_LCONT_m_t;

// Multivector representation of a purely Euclidean direction.
typedef lcont_return_t(no_t,ni_LCONT_m_t) direction_t;

// Multivector representation of an Eucliden direction vector.
typedef take_grade_return_t(1,direction_t) factor_t;

#endif // USING_???_MODEL

/*******************************************************************************************************
 * Some internal functions.
 *******************************************************************************************************/

#if defined(USING_EUCLIDEAN_MODEL) || defined(USING_HOMOGENEOUS_MODEL) || defined(USING_CONFORMAL_MODEL) || defined(USING_CONFORMAL_VORONOI_MODEL)

// Returns a mxArray having the weight and a mxArray having the direction vectors retrieved from the given n-vector (having only n-vectors computed from base space vectors).
void
attitude(mxArray **weight, mxArray **direction, const direction_t &B, const ga::real_t &tolerance)
{
	// Find the basis blade E in the representation of B with the largest coordinate.
	ga::index_t largest_i = 0;
	ga::real_t current, largest = std::abs( B.coefficients[0] );
	for (ga::index_t i=1; i<B.size; ++i)
	{
		current = std::abs( B.coefficients[i] );
		if (largest < current)
		{
			largest = current;
			largest_i = i;
		}
	}

	ga::bitmap_t E = B.basis_blade( largest_i ).bitmap;

	/* IMPLEMENTATION ISSUES
	 *
	 * The factorization algorithm described in Section 21.6 makes E be the bitmap
	 * of the largest coefficient of B. However, I believe that we must look for
	 * the largest absolute coefficient.
	 */

	if ((E != 0) && (!ga::is_zero( largest, tolerance )))
	{
		// Compute the grade of E.
		int k = 0;

		for (ga::bitmap_t bitmap=E; bitmap!=0; bitmap>>=1)
		{
			if (bitmap & 1)
			{
				++k;
			}
		}

		// Determine the norm of the input blade B: s = ||B||.
		const ga::real_t scalar = ga::norm_em( B, tolerance ).coefficients[0];

		// Create resulting mxArrays.
		*weight = mxCreateDoubleScalar( scalar );
		*direction = mxCreateDoubleMatrix( BASE_SPACE_DIMS, k, mxREAL );
		
		double *coords = mxGetPr( *direction );

		// Let the current input blade be Bc <- B / s and iterate over the basis vectors that span E.
		direction_t Bc = ga::gp_em( ga::inverse_em( scalar, tolerance ), B );

		// For all but one of the basis vectors ei of E...
		factor_t gi, ei;
		ei = ga::multivector<ga_model,ga::store_none>();

		for (ga::index_t i=0; E!=factor_t::basis_blade( i ).bitmap; ++i)
		{
			// Check whether the blade is factorizable by the current basis vector.
			if ((E & factor_t::basis_blade( i ).bitmap) != 0)
			{
				ei.coefficients[i] = 1;

				// Project ei onto Bc.
				gi = ga::lcont_em( ga::lcont_em( ei, Bc ), ga::inverse_em( Bc, tolerance ) );

				/* IMPLEMENTATION ISSUES
				 *
				 * The algorithm from Section 21.6 works! However, I believe that by replacing the
				 * geometric product by a left contraction when projection ei onto Bc we will have the
				 * same numerical result but with an improovement at the coefficient storage.
				 * Therefore, I changed the factorization process. Here I compute the orthogonal projection
				 * of a vector onto a blade using the algorithm described in Section 4.2.
				 */

				// Normalize the resulting factor and assign it to the resultin set of factors.
				const factor_t &fi = ga::unit_em( gi, tolerance );

				for (size_t j=0; j<BASE_SPACE_DIMS; ++j)
				{
					coords[j] = fi.coefficients[j];
				}

				// Update Bc and go to the next basis vector (and next factor).
				Bc = ga::lcont_em( ga::inverse_em( fi, tolerance ), Bc );
				E ^= factor_t::basis_blade( i ).bitmap;
				coords += BASE_SPACE_DIMS;

				ei.coefficients[i] = 0;
			}
		}

		// Obtain the last factor.
		gi = ga::unit_em( Bc, tolerance );

		for (size_t j=0; j<BASE_SPACE_DIMS; ++j)
		{
			coords[j] = gi.coefficients[j];
		}
	}
	else
	{
		// Create resulting mxArrays.
		*weight = mxCreateDoubleScalar( B.coefficients[0] );
		*direction = mxCreateDoubleMatrix( BASE_SPACE_DIMS, 0, mxREAL );
	}
}

#endif // USING_???_MODEL

#ifdef USING_HOMOGENEOUS_MODEL

// Returns a mxArray having the location position retrieved from the given multivector.
template<typename store>
mxArray*
location(const ga::multivector<ga_model,store> &p)
{
	mxArray *result = mxCreateDoubleMatrix( BASE_SPACE_DIMS, 1, mxREAL );
	double *coordinates = mxGetPr( result );

	for (size_t i=0, j=0; i<p.size; ++i)
	{
		if ((p.basis_blade( i ).grade == 1) && ((p.basis_blade( i ).bitmap & ga_model::origin_vector_bitmap) == 0))
		{
			coordinates[j] = p.coefficients[i];
			++j;
		}
	}

	return result;
}

#elif USING_CONFORMAL_MODEL

// Returns a mxArray having the location position retrieved from the given multivector.
template<typename store>
mxArray*
location(const ga::multivector<ga_model,store> &p)
{
	mxArray *result = mxCreateDoubleMatrix( BASE_SPACE_DIMS, 1, mxREAL );
	double *coordinates = mxGetPr( result );

	for (size_t i=0, j=0; i<p.size; ++i)
	{
		if ((p.basis_blade( i ).grade == 1) && ((p.basis_blade( i ).bitmap & (ga_model::origin_point_bitmap | ga_model::infinity_point_bitmap)) == 0))
		{
			coordinates[j] = p.coefficients[i];
			++j;
		}
	}

	return result;
}

#elif USING_CONFORMAL_VORONOI_MODEL

// Returns a mxArray having the location position retrieved from the given multivector.
template<typename store>
mxArray*
location(const ga::multivector<ga_model,store> &p)
{
	mxArray *result = mxCreateDoubleMatrix( BASE_SPACE_DIMS, 1, mxREAL );
	double *coordinates = mxGetPr( result );

	for (size_t i=0, j=0; i<p.size; ++i)
	{
		if ((p.basis_blade( i ).grade == 1) && ((p.basis_blade( i ).bitmap & (ga_model::origin_point_bitmap | ga_model::infinity_point_bitmap)) == 0))
		{
			coordinates[j] = p.coefficients[i];
			++j;
		}
	}

	return result;
}

#endif // USING_???_MODEL

// Interprets the given multivector and returns a mxArray struct with its parameters.
mxArray*
interpret(const multivector_t &m, const ga::real_t &tolerance)
{
	static const int type_field_index = 0;

	static const int weight_field_index = 1;
	static const int direction_field_index = 2;

#if defined(USING_HOMOGENEOUS_MODEL) || defined(USING_CONFORMAL_MODEL) || defined(USING_CONFORMAL_VORONOI_MODEL)
	static const int location_field_index = 3;
#endif // USING_???_MODEL

#ifdef USING_CONFORMAL_MODEL
	static const int radius_field_index = 4;
#endif // USING_CONFORMAL_MODEL

#ifdef USING_CONFORMAL_VORONOI_MODEL
	static const int radius_field_index = 4;
#endif // USING_CONFORMAL_VORONOI_MODEL

	static const char *field_names[5] = { "type", "weight", "direction", "location", "radius" };

#ifdef USING_CONFORMAL_MODEL
	static const int p1_field_index = 1;
	static const int p2_field_index = 2;
	static const char *point_pair_field_names[3] = { "type", "p1", "p2" };
#endif // USING_CONFORMAL_MODEL

#ifdef USING_CONFORMAL_VORONOI_MODEL
	static const int p1_field_index = 1;
	static const int p2_field_index = 2;
	static const char *point_pair_field_names[3] = { "type", "p1", "p2" };
#endif // USING_CONFORMAL_VORONOI_MODEL

	static const int scalar_field_index = 1;
	static const char *scalar_field_names[2] = { "type", "scalar" };

	// Blade test.
	if (ga::is_blade( m, tolerance ))
	{
		// Scalar test.
		if (ga::is_scalar( m, tolerance ))
		{
			mxArray *result = mxCreateStructMatrix( 1, 1, 2, scalar_field_names );
			mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "scalar" ) );
			mxSetFieldByNumber( result, 0, scalar_field_index, mxCreateDoubleScalar( m.coefficients[0] ) );
			return result;
		}

		// Pseudoscalat test.
		if (ga::is_pseudoscalar( m, tolerance ))
		{
			mxArray *result = mxCreateStructMatrix( 1, 1, 2, scalar_field_names );
			mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "pseudoscalar" ) );
			mxSetFieldByNumber( result, 0, scalar_field_index, mxCreateDoubleScalar( m.coefficients[m.size-1] ) );
			return result;
		}

#ifdef USING_EUCLIDEAN_MODEL

		mxArray *weight = NULL;
		mxArray *direction = NULL;
		attitude( &weight, &direction, m, tolerance );

		mxArray *result = mxCreateStructMatrix( 1, 1, 3, field_names );
		switch (ga::grade( m, tolerance ))
		{
			case 1 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "vector" ) ); break;
			case 2 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "bivector" ) ); break;
			case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "trivector" ) ); break;
			default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "nvector" ) ); break;
		}
		mxSetFieldByNumber( result, 0, weight_field_index, weight );
		mxSetFieldByNumber( result, 0, direction_field_index, direction );
		return result;

#elif USING_HOMOGENEOUS_MODEL

		static const e0_t e0 = { { { 1 } } };
		static const e0_t ie0 = ga::inverse( e0, tolerance );

		const direction_t &ie0_LCONT_m = ga::lcont( ie0, m );

		// Improper test.
		if (ga::is_zero( ie0_LCONT_m, tolerance ))
		{
			direction_t B;
			B = m;
			
			/* IMPLEMENTATION ISSUES
			 *
			 * The cast from multivector_t to direction_t is performed in order to simplify
			 * the compilation process. By implementing attitude() as a template function, one
			 * avoid the cast, but the compiler my fail for higher dimention spaces.
			 */

			mxArray *weight = NULL;
			mxArray *direction = NULL;
			attitude( &weight, &direction, B, tolerance );

			mxArray *result = mxCreateStructMatrix( 1, 1, 3, field_names );
			switch (ga::grade( m, tolerance ))
			{
				case 1 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "vector" ) ); break;
				case 2 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "bivector" ) ); break;
				case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "trivector" ) ); break;
				default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "nvector" ) ); break;
			}
			mxSetFieldByNumber( result, 0, weight_field_index, weight );
			mxSetFieldByNumber( result, 0, direction_field_index, direction );
			return result;
		}
		// Proper test.
		else
		{
			mxArray *weight = NULL;
			mxArray *direction = NULL;
			attitude( &weight, &direction, ie0_LCONT_m, tolerance );

			mxArray *result = mxCreateStructMatrix( 1, 1, 4, field_names );
			switch (ga::grade( m, tolerance ))
			{
				case 1 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "point" ) ); break;
				case 2 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "line" ) ); break;
				case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "plane" ) ); break;
				default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "nplane" ) ); break;
			}
			mxSetFieldByNumber( result, 0, weight_field_index, weight );
			mxSetFieldByNumber( result, 0, direction_field_index, direction );
			mxSetFieldByNumber( result, 0, location_field_index, location( ga::gp( ga::lcont( ie0, ga::op( e0, m ) ), ga::inverse( ie0_LCONT_m, tolerance ) ) ) );
			return result;
		}

#elif USING_CONFORMAL_MODEL

		static const no_t no = { { { 1 } } };
		static const ni_t ni = { { { 1 } } };

		const ni_OP_m_t &ni_OP_m = ga::op( ni, m );
		const ni_LCONT_m_t &ni_LCONT_m = ga::lcont( ni, m );

		if (ga::is_zero( ni_OP_m, tolerance ))
		{
			// Free (direction) test.
			if (ga::is_zero( ni_LCONT_m, tolerance ))
			{
				direction_t B;
				B = ga::lcont( no, ga::grade_involution( m ) );

				/* IMPLEMENTATION ISSUES
				 *
				 * The cast from no_LCONT_m_t to direction_t is performed in order to simplify
				 * the compilation process. By implementing attitude() as a template function, one
				 * avoid the cast, but the compiler my fail for higher dimention spaces.
				 */

				mxArray *weight = NULL;
				mxArray *direction = NULL;
				attitude( &weight, &direction, B, tolerance );

				mxArray *result = mxCreateStructMatrix( 1, 1, 3, field_names );
				switch (ga::grade( m, tolerance ))
				{
					case 2 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "free_vector" ) ); break;
					case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "free_bivector" ) ); break;
					case 4 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "free_trivector" ) ); break;
					default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "free_nvector" ) ); break;
				}
				mxSetFieldByNumber( result, 0, weight_field_index, weight );
				mxSetFieldByNumber( result, 0, direction_field_index, direction );
				return result;
			}
			// Flat test.
			else
			{
				mxArray *weight = NULL;
				mxArray *direction = NULL;
				attitude( &weight, &direction, ga::lcont( no, ga::grade_involution( -ni_LCONT_m ) ), tolerance );

				mxArray *result = mxCreateStructMatrix( 1, 1, 4, field_names );
				switch (ga::grade( m, tolerance ))
				{
					case 2 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "flat_point" ) ); break;
					case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "line" ) ); break;
					case 4 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "plane" ) ); break;
					default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "nplane" ) ); break;
				}
				mxSetFieldByNumber( result, 0, weight_field_index, weight );
				mxSetFieldByNumber( result, 0, direction_field_index, direction );
				mxSetFieldByNumber( result, 0, location_field_index, location( ga::gp( ga::lcont( no, m ), ga::inverse( m, tolerance ) ) ) );
				return result;
			}
		}
		else
		{
			// n-vector test.
			if (ga::is_zero( ni_LCONT_m, tolerance ))
			{
				direction_t B;
				B = m;

				/* IMPLEMENTATION ISSUES
				 *
				 * The cast from multivector_t to direction_t is performed in order to simplify
				 * the compilation process. By implementing attitude() as a template function, one
				 * avoid the cast, but the compiler my fail for higher dimention spaces.
				 */

				mxArray *weight = NULL;
				mxArray *direction = NULL;
				attitude( &weight, &direction, B, tolerance );

				mxArray *result = mxCreateStructMatrix( 1, 1, 3, field_names );
				switch (ga::grade( m, tolerance ))
				{
					case 1 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "vector" ) ); break;
					case 2 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "bivector" ) ); break;
					case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "trivector" ) ); break;
					default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "nvector" ) ); break;
				}
				mxSetFieldByNumber( result, 0, weight_field_index, weight );
				mxSetFieldByNumber( result, 0, direction_field_index, direction );
				return result;
			}
			else
			{
				const ga::real_t m2 = ga::scp( m, m ).coefficients[0];
				const ni_LCONT_m_t &minus_ni_LCONT_m = -ni_LCONT_m;
				const ni_LCONT_m_t &inverse_minus_ni_LCONT_m = ga::inverse( minus_ni_LCONT_m, tolerance );

				const multivector_t &p = ga::gp( m, inverse_minus_ni_LCONT_m ); // Location.
				
				// Tangent test.
				if (ga::is_zero( m2, tolerance ))
				{
					mxArray *weight = NULL;
					mxArray *direction = NULL;
					attitude( &weight, &direction, ga::lcont( no, ga::grade_involution( ga::op( minus_ni_LCONT_m, ni ) ) ), tolerance );

					mxArray *result = mxCreateStructMatrix( 1, 1, 4, field_names );
					switch (ga::grade( m, tolerance ))
					{
						case 1 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "point" ) ); break;
						case 2 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "tangent_vector" ) ); break;
						case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "tangent_bivector" ) ); break;
						case 4 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "tangent_trivector" ) ); break;
						default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "tangent_nvector" ) ); break;
					}
					mxSetFieldByNumber( result, 0, weight_field_index, weight );
					mxSetFieldByNumber( result, 0, direction_field_index, direction );
					mxSetFieldByNumber( result, 0, location_field_index, location( p ) );
					return result;
				}
				// Round test.
				else
				{
					const int grade = ga::grade( m, tolerance );

					if (grade == 2)
					{
						const ni_LCONT_m_t &igp_sqrt_m2_minus_ni_LCONT_m = ga::gp( sqrt( m2 ), inverse_minus_ni_LCONT_m );
						
						mxArray *result = mxCreateStructMatrix( 1, 1, 3, point_pair_field_names );

						mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "point_pair" ) );
						mxSetFieldByNumber( result, 0, p1_field_index, location( p - igp_sqrt_m2_minus_ni_LCONT_m ) );
						mxSetFieldByNumber( result, 0, p2_field_index, location( p + igp_sqrt_m2_minus_ni_LCONT_m ) );
						return result;
					}
					else
					{
						mxArray *weight = NULL;
						mxArray *direction = NULL;
						attitude( &weight, &direction, ga::lcont( no, ga::grade_involution( ga::op( minus_ni_LCONT_m, ni ) ) ), tolerance );

						const ga::real_t radius2 = ga::scp( m, ga::grade_involution( m ) ).coefficients[0] / ga::scp( ni_LCONT_m, ni_LCONT_m ).coefficients[0];
						
						mxArray *result = mxCreateStructMatrix( 1, 1, 5, field_names );
						switch (grade)
						{
							case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "circle" ) ); break;
							case 4 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "sphere" ) ); break;
							default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "nsphere" ) ); break;
						}
						mxSetFieldByNumber( result, 0, weight_field_index, weight );
						mxSetFieldByNumber( result, 0, direction_field_index, direction );
						mxSetFieldByNumber( result, 0, location_field_index, location( p ) );
						mxSetFieldByNumber( result, 0, radius_field_index, mxCreateDoubleScalar( ga::sgn( radius2 ) * sqrt( std::abs( radius2 ) ) ) );
						return result;
					}
				}
			}
		}

#elif USING_CONFORMAL_VORONOI_MODEL

		static const ni_t ni = { { { 1 } } };
		static const no_t no = { { { 1 } } };

		const ni_OP_m_t &ni_OP_m = ga::op( ni, m );
		const ni_LCONT_m_t &ni_LCONT_m = ga::lcont( ni, m );

		if (ga::is_zero( ni_OP_m, tolerance ))
		{
			// Free (direction) test.
			if (ga::is_zero( ni_LCONT_m, tolerance ))
			{
				direction_t B;
				B = ga::lcont( no, ga::grade_involution( m ) );

				/* IMPLEMENTATION ISSUES
				 *
				 * The cast from no_LCONT_m_t to direction_t is performed in order to simplify
				 * the compilation process. By implementing attitude() as a template function, one
				 * avoid the cast, but the compiler my fail for higher dimention spaces.
				 */

				mxArray *weight = NULL;
				mxArray *direction = NULL;
				attitude( &weight, &direction, B, tolerance );

				mxArray *result = mxCreateStructMatrix( 1, 1, 3, field_names );
				switch (ga::grade( m, tolerance ))
				{
					case 2 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "free_vector" ) ); break;
					case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "free_bivector" ) ); break;
					case 4 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "free_trivector" ) ); break;
					default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "free_nvector" ) ); break;
				}
				mxSetFieldByNumber( result, 0, weight_field_index, weight );
				mxSetFieldByNumber( result, 0, direction_field_index, direction );
				return result;
			}
			// Flat test.
			else
			{
				mxArray *weight = NULL;
				mxArray *direction = NULL;
				attitude( &weight, &direction, ga::lcont( no, ga::grade_involution( -ni_LCONT_m ) ), tolerance );

				mxArray *result = mxCreateStructMatrix( 1, 1, 4, field_names );
				switch (ga::grade( m, tolerance ))
				{
					case 2 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "flat_point" ) ); break;
					case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "line" ) ); break;
					case 4 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "plane" ) ); break;
					default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "nplane" ) ); break;
				}
				mxSetFieldByNumber( result, 0, weight_field_index, weight );
				mxSetFieldByNumber( result, 0, direction_field_index, direction );
				mxSetFieldByNumber( result, 0, location_field_index, location( ga::gp( ga::lcont( no, m ), ga::inverse( m, tolerance ) ) ) );
				return result;
			}
		}
		else
		{
			// n-vector test.
			if (ga::is_zero( ni_LCONT_m, tolerance ))
			{
				direction_t B;
				B = m;

				/* IMPLEMENTATION ISSUES
				 *
				 * The cast from multivector_t to direction_t is performed in order to simplify
				 * the compilation process. By implementing attitude() as a template function, one
				 * avoid the cast, but the compiler my fail for higher dimention spaces.
				 */

				mxArray *weight = NULL;
				mxArray *direction = NULL;
				attitude( &weight, &direction, B, tolerance );

				mxArray *result = mxCreateStructMatrix( 1, 1, 3, field_names );
				switch (ga::grade( m, tolerance ))
				{
					case 1 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "vector" ) ); break;
					case 2 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "bivector" ) ); break;
					case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "trivector" ) ); break;
					default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "nvector" ) ); break;
				}
				mxSetFieldByNumber( result, 0, weight_field_index, weight );
				mxSetFieldByNumber( result, 0, direction_field_index, direction );
				return result;
			}
			else
			{
				const ga::real_t m2 = ga::scp( m, m ).coefficients[0];
				const ni_LCONT_m_t &minus_ni_LCONT_m = -ni_LCONT_m;
				const ni_LCONT_m_t &inverse_minus_ni_LCONT_m = ga::inverse( minus_ni_LCONT_m, tolerance );

				const multivector_t &p = ga::gp( m, inverse_minus_ni_LCONT_m ); // Location.
				
				// Tangent test.
				if (ga::is_zero( m2, tolerance ))
				{
					mxArray *weight = NULL;
					mxArray *direction = NULL;
					attitude( &weight, &direction, ga::lcont( no, ga::grade_involution( ga::op( minus_ni_LCONT_m, ni ) ) ), tolerance );

					mxArray *result = mxCreateStructMatrix( 1, 1, 4, field_names );
					switch (ga::grade( m, tolerance ))
					{
						case 1 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "point" ) ); break;
						case 2 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "tangent_vector" ) ); break;
						case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "tangent_bivector" ) ); break;
						case 4 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "tangent_trivector" ) ); break;
						default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "tangent_nvector" ) ); break;
					}
					mxSetFieldByNumber( result, 0, weight_field_index, weight );
					mxSetFieldByNumber( result, 0, direction_field_index, direction );
					mxSetFieldByNumber( result, 0, location_field_index, location( p ) );
					return result;
				}
				// Round test.
				else
				{
					const int grade = ga::grade( m, tolerance );

					if (grade == 2)
					{
						const ni_LCONT_m_t &igp_sqrt_m2_minus_ni_LCONT_m = ga::gp( sqrt( m2 ), inverse_minus_ni_LCONT_m );
						
						mxArray *result = mxCreateStructMatrix( 1, 1, 3, point_pair_field_names );

						mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "point_pair" ) );
						mxSetFieldByNumber( result, 0, p1_field_index, location( p - igp_sqrt_m2_minus_ni_LCONT_m ) );
						mxSetFieldByNumber( result, 0, p2_field_index, location( p + igp_sqrt_m2_minus_ni_LCONT_m ) );
						return result;
					}
					else
					{
						mxArray *weight = NULL;
						mxArray *direction = NULL;
						attitude( &weight, &direction, ga::lcont( no, ga::grade_involution( ga::op( minus_ni_LCONT_m, ni ) ) ), tolerance );

						const ga::real_t radius2 = ga::scp( m, ga::grade_involution( m ) ).coefficients[0] / ga::scp( ni_LCONT_m, ni_LCONT_m ).coefficients[0];
						
						mxArray *result = mxCreateStructMatrix( 1, 1, 5, field_names );
						switch (grade)
						{
							case 3 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "circle" ) ); break;
							case 4 : mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "sphere" ) ); break;
							default: mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "nsphere" ) ); break;
						}
						mxSetFieldByNumber( result, 0, weight_field_index, weight );
						mxSetFieldByNumber( result, 0, direction_field_index, direction );
						mxSetFieldByNumber( result, 0, location_field_index, location( p ) );
						mxSetFieldByNumber( result, 0, radius_field_index, mxCreateDoubleScalar( ga::sgn( radius2 ) * sqrt( std::abs( radius2 ) ) ) );
						return result;
					}
				}
			}
		}

#else // USING_???_MODEL

		// Unknown blade type.
		mxArray *result = mxCreateStructMatrix( 1, 1, 1, field_names );
		mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "unknown_blade" ) );
		return result;

#endif // USING_???_MODEL
	}

	// Versor test.
	if (ga::is_versor( m, tolerance ))
	{
#ifdef USING_EUCLIDEAN_MODEL
		//TODO Opa!
#elif USING_HOMOGENEOUS_MODEL
		//TODO Opa!
#elif USING_CONFORMAL_MODEL
		//TODO Opa!
#elif USING_CONFORMAL_VORONOI_MODEL
		//TODO Opa!
#endif // USING_???_MODEL

		// Unknown versor type.
		mxArray *result = mxCreateStructMatrix( 1, 1, 1, field_names );
		mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "unknown_versor" ) );
		return result;
	}

	// Unknown multivector type.
	mxArray *result = mxCreateStructMatrix( 1, 1, 1, field_names );
	mxSetFieldByNumber( result, 0, type_field_index, mxCreateString( "unknown" ) );
	return result;
}

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

	plhs[0] = mxCreateCellArray( ndims, dims );

	// Populate the created array.
	int i;

	//#pragma omp parallel for num_threads( std::min( omp_get_num_procs() * 2, nelems ) )
	for (i=0; i<nelems; ++i)
	{
		//OMP_LOOP_EXCEPTION_HANDLING_BEGIN
		mxSetCell( plhs[0], i, interpret( to_multivector( arg, i ), tol ) );
		//OMP_LOOP_EXCEPTION_HANDLING_END
	}

	EXCEPTION_HANDLING_END
}
