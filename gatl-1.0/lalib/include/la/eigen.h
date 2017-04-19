/*
 * Copyright (C) 2010 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_EIGEN_
#define _LA_EIGEN_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * la::max_iterations_error class definition.
 *******************************************************************************************************/

// The maximum numer of iterations was reached.
class max_iterations_error : public std::runtime_error
{
public:

	// Class constructor.
	max_iterations_error() : std::runtime_error( "The maximum number of iterations was reached." )
	{
	}
};

/*******************************************************************************************************
 * Eigen decomposition function implementations.
 *******************************************************************************************************/

// Computes the eigenvectors (column vectors) and eigenvalues (main diagonal, with decrescent sorting order) of a square matrix.
template<bool sort, template<typename value_type, size_t rows, size_t cols> class matrix, typename value_type, size_t size>
inline
void eigen(matrix<value_type,size,size> &vectors, matrix<value_type,size,size> &values, const matrix<value_type,size,size> &m)
{
	values = static_cast<value_type>( 0 );
	vectors = static_cast<value_type>( 0 );
	matrix<value_type,size,1> temp( la::null_matrix );

	_private::tri_diagonalize( values, temp, vectors, m );
	if (_private::calc_eigenstructure<sort>( values, temp, vectors ) != 0)
	{
		throw max_iterations_error();
	}

	for (size_t i=1; i!=size; ++i)
	{
		values(i,i) = values(0,i);
		values(0,i) = static_cast<value_type>( 0 );
	}
}

}

#endif // !_LA_EIGEN_
