/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_GRADE_INVOLUTION_TENSOR_
#define _GA_GRADE_INVOLUTION_TENSOR_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Grade involution operation tensor.
 *******************************************************************************************************/

// Computes the tensor representation of the grade involution operation.
template<typename model>
inline
const la::dtensor2<real_t,model::basis_blades_count>&
grade_involution_tensor()
{
	typedef multivector<model,typename store_all<model>::store_type> multivector_t;

	static la::dtensor2<real_t,model::basis_blades_count> result;

	static bool first_time = true;
	if (first_time)
	{
		#pragma omp critical (GA_GRADE_INVOLUTION_TENSOR)
		{
			if (first_time)
			{
				multivector_t blade_i;

				result = static_cast<real_t>( 0 );

				blade_i = multivector<model,store_none>();
				for (index_t i=0; i!=model::basis_blades_count; ++i)
				{
					blade_i[i] = 1;

					const multivector_t &aux = grade_involution( blade_i );

					for (index_t k=0; k!=model::basis_blades_count; ++k)
					{
						result(k,i) += aux[k];
					}

					blade_i[i] = 0;
				}

				first_time = false;
			}
		}
	}

	return result;
}

}

#endif // !_GA_GRADE_INVOLUTION_TENSOR_
