/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CLIFFORD_CONJUGATION_MATRIX_
#define _GA_CLIFFORD_CONJUGATION_MATRIX_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Clifford conjugation operation matrix.
 *******************************************************************************************************/

// Returns the matrix representation of the Clifford conjugation operation.
template<typename model>
inline
const la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count>&
clifford_conjugation_matrix()
{
	static la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count> result;

	static bool first_time = true;
	if (first_time)
	{
		#pragma omp critical (GA_CLIFFORD_CONJUGATION_MATRIX)
		{
			if (first_time)
			{
				const la::dtensor2<real_t,model::basis_blades_count> &tensor = clifford_conjugation_tensor<model>();

				for (index_t k=0; k!=model::basis_blades_count; ++k)
				{
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						result(k,i) = tensor(k,i);
					}
				}

				first_time = false;
			}
		}
	}

	return result;
}

}

#endif // !_GA_CLIFFORD_CONJUGATION_MATRIX_
