/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_PRODUCT_TENSOR_
#define _GA_PRIVATE_PRODUCT_TENSOR_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

// The base struct for computing the dot product tensor for a given multivector.
template<typename model>
struct product_tensor_dot
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename dot_return<model,store_all_t,store_all_t>::store_t store_dot_t;
		typedef multivector<model,store_dot_t> multivector_dot_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_DOT)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_dot_t &aux = dot( blade_i, blade_j );

							for (index_t k=0; k!=multivector_dot_t::size; ++k)
							{
								result(multivector_dot_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the dot product tensor for a given multivector (Euclidean metric).
template<typename model>
struct product_tensor_dot_em
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename dot_em_return<model,store_all_t,store_all_t>::store_t store_dot_em_t;
		typedef multivector<model,store_dot_em_t> multivector_dot_em_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_DOT_EM)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_dot_em_t &aux = dot_em( blade_i, blade_j );

							for (index_t k=0; k!=multivector_dot_em_t::size; ++k)
							{
								result(multivector_dot_em_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the geometric product tensor for a given multivector.
template<typename model>
struct product_tensor_gp
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename gp_return<model,store_all_t,store_all_t>::store_t store_gp_t;
		typedef multivector<model,store_gp_t> multivector_gp_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_GP)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_gp_t &aux = gp( blade_i, blade_j );

							for (index_t k=0; k!=multivector_gp_t::size; ++k)
							{
								result(multivector_gp_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the geometric product tensor for a given multivector (Euclidean metric).
template<typename model>
struct product_tensor_gp_em
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename gp_em_return<model,store_all_t,store_all_t>::store_t store_gp_em_t;
		typedef multivector<model,store_gp_em_t> multivector_gp_em_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_GP_EM)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_gp_em_t &aux = gp_em( blade_i, blade_j );

							for (index_t k=0; k!=multivector_gp_em_t::size; ++k)
							{
								result(multivector_gp_em_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the Hestenes' inner product tensor for a given multivector.
template<typename model>
struct product_tensor_hip
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename hip_return<model,store_all_t,store_all_t>::store_t store_hip_t;
		typedef multivector<model,store_hip_t> multivector_hip_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_hip)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_hip_t &aux = hip( blade_i, blade_j );

							for (index_t k=0; k!=multivector_hip_t::size; ++k)
							{
								result(multivector_hip_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the Hestenes' inner product tensor for a given multivector (Euclidean metric).
template<typename model>
struct product_tensor_hip_em
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename hip_em_return<model,store_all_t,store_all_t>::store_t store_hip_em_t;
		typedef multivector<model,store_hip_em_t> multivector_hip_em_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_HIP_EM)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_hip_em_t &aux = hip_em( blade_i, blade_j );

							for (index_t k=0; k!=multivector_hip_em_t::size; ++k)
							{
								result(multivector_hip_em_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the left contraction tensor for a given multivector.
template<typename model>
struct product_tensor_lcont
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename lcont_return<model,store_all_t,store_all_t>::store_t store_lcont_t;
		typedef multivector<model,store_lcont_t> multivector_lcont_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_LCONT)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_lcont_t &aux = lcont( blade_i, blade_j );

							for (index_t k=0; k!=multivector_lcont_t::size; ++k)
							{
								result(multivector_lcont_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the left contraction tensor for a given multivector (Euclidean metric).
template<typename model>
struct product_tensor_lcont_em
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename lcont_em_return<model,store_all_t,store_all_t>::store_t store_lcont_em_t;
		typedef multivector<model,store_lcont_em_t> multivector_lcont_em_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_LCONT_EM)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_lcont_em_t &aux = lcont_em( blade_i, blade_j );

							for (index_t k=0; k!=multivector_lcont_em_t::size; ++k)
							{
								result(multivector_lcont_em_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the outer product tensor for a given multivector.
template<typename model>
struct product_tensor_op
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename op_return<model,store_all_t,store_all_t>::store_t store_op_t;
		typedef multivector<model,store_op_t> multivector_op_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_OP)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_op_t &aux = op( blade_i, blade_j );

							for (index_t k=0; k!=multivector_op_t::size; ++k)
							{
								result(multivector_op_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the right contraction tensor for a given multivector.
template<typename model>
struct product_tensor_rcont
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename rcont_return<model,store_all_t,store_all_t>::store_t store_rcont_t;
		typedef multivector<model,store_rcont_t> multivector_rcont_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_RCONT)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_rcont_t &aux = rcont( blade_i, blade_j );

							for (index_t k=0; k!=multivector_rcont_t::size; ++k)
							{
								result(multivector_rcont_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the right contraction tensor for a given multivector (Euclidean metric).
template<typename model>
struct product_tensor_rcont_em
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename rcont_em_return<model,store_all_t,store_all_t>::store_t store_rcont_em_t;
		typedef multivector<model,store_rcont_em_t> multivector_rcont_em_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_RCONT_EM)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_rcont_em_t &aux = rcont_em( blade_i, blade_j );

							for (index_t k=0; k!=multivector_rcont_em_t::size; ++k)
							{
								result(multivector_rcont_em_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the scalar product tensor for a given multivector.
template<typename model>
struct product_tensor_scp
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename scp_return<model,store_all_t,store_all_t>::store_t store_scp_t;
		typedef multivector<model,store_scp_t> multivector_scp_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_SCP)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_scp_t &aux = scp( blade_i, blade_j );

							for (index_t k=0; k!=multivector_scp_t::size; ++k)
							{
								result(multivector_scp_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}

		return result;
	}
};

// The base struct for computing the scalar product tensor for a given multivector (Euclidean metric).
template<typename model>
struct product_tensor_scp_em
{
	static _GA_ALWAYS_INLINE
	const la::dtensor3<real_t,model::basis_blades_count>& run()
	{
		typedef typename store_all<model>::store_type store_all_t;
		typedef multivector<model,store_all_t> multivector_all_t;

		typedef typename scp_em_return<model,store_all_t,store_all_t>::store_t store_scp_em_t;
		typedef multivector<model,store_scp_em_t> multivector_scp_em_t;

		static la::dtensor3<real_t,model::basis_blades_count> result;

		static bool first_time = true;
		if (first_time)
		{
			#pragma omp critical (GA_PRIVATE_PRODUCT_TENSOR_SCP_EM)
			{
				if (first_time)
				{
					multivector_all_t blade_i, blade_j;

					result = static_cast<real_t>( 0 );

					blade_i = multivector<model,store_none>();
					blade_j = multivector<model,store_none>();
					for (index_t i=0; i!=model::basis_blades_count; ++i)
					{
						blade_i[i] = 1;

						for (index_t j=0; j!=model::basis_blades_count; ++j)
						{
							blade_j[j] = 1;

							const multivector_scp_em_t &aux = scp_em( blade_i, blade_j );

							for (index_t k=0; k!=multivector_scp_em_t::size; ++k)
							{
								result(multivector_scp_em_t::basis_blade(k).bitmap,i,j) += aux[k];
							}

							blade_j[j] = 0;
						}

						blade_i[i] = 0;
					}

					first_time = false;
				}
			}
		}


		return result;
	}
};

}

}

#endif // !_GA_PRIVATE_PRODUCT_TENSOR_
