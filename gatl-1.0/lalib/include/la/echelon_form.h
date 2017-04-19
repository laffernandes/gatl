/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_ECHELON_FORM_
#define _LA_ECHELON_FORM_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Reducion to column echelon form function implementation.
 *******************************************************************************************************/

// Reduce a given matrix to column echelon form.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t rows, size_t cols>
inline
matrix<real_type,rows,cols>
column_reduced_echelon_form(size_t &rank, stools::array<size_t,cols> &independent_cols, const matrix<real_type,rows,cols> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	rank = 0;
	matrix<real_type,rows,cols> result( m );

	for (size_t i=0; i!=cols; ++i)
	{
		independent_cols[i] = i;
	}
	
	size_t c = 0;
	size_t r = 0;
	while ((c != cols) && (r != rows))
	{
		// Find value and index of largest element in the remainder of row r.
		size_t k = c;
		real_type max = abs( result(r,c) );
		for (size_t j=(c+1); j!=cols; ++j)
		{
			const real_type curr = abs( result(r,j) );
			if (max < curr)
			{
				k = j;
				max = curr;
			}
		}

		if (is_zero( max, tolerance ))
		{
			// The row is negligible, zero it out.
			for (size_t j=c; j!=cols; ++j)
			{
				result(r,j) = 0;
			}
			++r;
		}
		else
		{
			real_type pivot;

			// Update rank.
			++rank;

			// Swap c-th and k-th columns.
			for (size_t j=0; j!=rows; ++j)
			{
				std::swap( result(j,c), result(j,k) );
			}

			std::swap( independent_cols[c], independent_cols[k] );

			// Divide the pivot column by the pivot element.
			pivot = static_cast<real_type>( 1 ) / result(r,c);
			for (size_t j=r; j!=rows; ++j)
			{
				result(j,c) *= pivot;
			}

			// Subtract multiples of the pivot column from all the other columns.
			for (size_t j=0; j!=c; ++j)
			{
				pivot = result(r,j);

				for (size_t l=r; l!=rows; ++l)
				{
					result(l,j) -= (pivot * result(l,c));
				}
			}

			for (size_t j=c+1; j!=cols; ++j)
			{
				pivot = result(r,j);

				for (size_t l=r; l!=rows; ++l)
				{
					result(l,j) -= (pivot * result(l,c));
				}
			}

			++c;
			++r;
		}
	}

	return result;
}

// Reduce a given matrix to column echelon form.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t rows, size_t cols>
inline
matrix<real_type,rows,cols>
column_reduced_echelon_form(size_t &rank, const matrix<real_type,rows,cols> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	static stools::array<size_t,cols> dummy_independent_columns;
	return column_reduced_echelon_form( rank, dummy_independent_columns, m, tolerance );
}

// Reduce a given matrix to column echelon form.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t rows, size_t cols>
inline
matrix<real_type,rows,cols>
column_reduced_echelon_form(const matrix<real_type,rows,cols> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	static size_t dummy_rank;
	static stools::array<size_t,cols> dummy_independent_columns;
	return column_reduced_echelon_form( dummy_rank, dummy_independent_columns, m, tolerance );
}

/*******************************************************************************************************
 * Reducion to row echelon form function implementation.
 *******************************************************************************************************/

// Reduce a given matrix to row echelon form.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t rows, size_t cols>
inline
matrix<real_type,rows,cols>
row_reduced_echelon_form(size_t &rank, stools::array<size_t,rows> &independent_rows, const matrix<real_type,rows,cols> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	rank = 0;
	matrix<real_type,rows,cols> result( m );
	
	for (size_t i=0; i!=rows; ++i)
	{
		independent_rows[i] = i;
	}

	size_t r = 0;
	size_t c = 0;
	while ((r != rows) && (c != cols))
	{
		// Find value and index of largest element in the remainder of column c.
		size_t k = r;
		real_type max = abs( result(r,c) );
		for (size_t j=(r+1); j!=rows; ++j)
		{
			const real_type curr = abs( result(j,c) );
			if (max < curr)
			{
				k = j;
				max = curr;
			}
		}

		if (is_zero( max, tolerance ))
		{
			// The column is negligible, zero it out.
			for (size_t j=r; j!=rows; ++j)
			{
				result(j,c) = 0;
			}
			++c;
		}
		else
		{
			real_type pivot;

			// Update rank.
			++rank;

			// Swap r-th and k-th rows.
			for (size_t j=0; j!=cols; ++j)
			{
				std::swap( result(r,j), result(k,j) );
			}

			std::swap( independent_rows[r], independent_rows[k] );

			// Divide the pivot row by the pivot element.
			pivot = static_cast<real_type>( 1 ) / result(r,c);
			for (size_t j=c; j!=cols; ++j)
			{
				result(r,j) *= pivot;
			}

			// Subtract multiples of the pivot row from all the other rows.
			for (size_t j=0; j!=r; ++j)
			{
				pivot = result(j,c);

				for (size_t l=c; l!=cols; ++l)
				{
					result(j,l) -= (pivot * result(r,l));
				}
			}

			for (size_t j=r+1; j!=rows; ++j)
			{
				pivot = result(j,c);

				for (size_t l=c; l!=cols; ++l)
				{
					result(j,l) -= (pivot * result(r,l));
				}
			}

			++r;
			++c;
		}
	}

	return result;
}

// Reduce a given matrix to row echelon form.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t rows, size_t cols>
inline
matrix<real_type,rows,cols>
row_reduced_echelon_form(size_t &rank, const matrix<real_type,rows,cols> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	static stools::array<size_t,rows> dummy_independent_rows;
	return row_reduced_echelon_form( rank, dummy_independent_rows, m, tolerance );
}

// Reduce a given matrix to row echelon form.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t rows, size_t cols>
inline
matrix<real_type,rows,cols>
row_reduced_echelon_form(const matrix<real_type,rows,cols> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	static size_t dummy_rank;
	static stools::array<size_t,rows> dummy_independent_rows;
	return row_reduced_echelon_form( dummy_rank, dummy_independent_rows, m, tolerance );
}

}

#endif // !_LA_ECHELON_FORM_
