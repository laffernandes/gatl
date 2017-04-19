/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_GRADE_INVOLUTION_MATRIX_
#define _GA_GRADE_INVOLUTION_MATRIX_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Grade involution operation matrix.
 *******************************************************************************************************/

// Returns the matrix representation of the grade involution operation.
template<typename model>
inline
const la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count>&
grade_involution_matrix()
{
	static la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count> result;

	static bool first_time = true;
	if (first_time)
	{
		#pragma omp critical (GA_GRADE_INVOLUTION_MATRIX)
		{
			if (first_time)
			{
				const la::dtensor2<real_t,model::basis_blades_count> &tensor = grade_involution_tensor<model>();

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

#endif // !_GA_GRADE_INVOLUTION_MATRIX_
