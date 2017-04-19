/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_ROUND_
#define _LA_ROUND_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using bmath::round;

/*******************************************************************************************************
 * Round function implementations.
 *******************************************************************************************************/

// Integer round function.
template<typename integer_type, template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t rows, size_t cols>
inline
matrix<integer_type,rows,cols>
round(const matrix<real_type,rows,cols> &m)
{
	matrix<integer_type,rows,cols> result;
	for (size_t i=0; i!=result.size; ++i)
	{
		result[i] = static_cast<integer_type>( round( m[i] ) );
	}
	return result;
}

}

#endif // !_LA_ROUND_
