/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GRID_WARPER_
#define _GRID_WARPER_

// The namespace of the multidimensional grid library.
namespace grid
{

/*******************************************************************************************************
 * grid::linear_warper class definition.
 *******************************************************************************************************/

// This warper implements the linear discretization of n-dimensional cartesian space.
struct linear_warper
{
	// Computes the cartesian position related to a given buffer position.
	template<typename coord_type, typename size_type, size_t dims>
	inline
	static stools::array<coord_type,dims> buffer_to_cartesian(const stools::array<size_type,dims> &buffer_position, const stools::array<coord_type,dims> &lower_bounds, const stools::array<coord_type,dims> &upper_bounds, const stools::array<size_type,dims> &buffer_size)
	{
		stools::array<coord_type,dims> result;

		for (size_t i=0; i<dims; ++i)
		{
			result[i] = ((static_cast<coord_type>( buffer_position[i] ) / (buffer_size[i] - 1)) * (upper_bounds[i] - lower_bounds[i])) + lower_bounds[i];
		}

		return result;
	}

	// Computes the buffer position related to a given cartesian position, regaring the given rounding policy.
	template<typename rounding_policy, typename coord_type, typename size_type, size_t dims>
	inline
	static stools::array<size_type,dims> cartesian_to_buffer(const stools::array<coord_type,dims> &cartesian_position, const stools::array<coord_type,dims> &lower_bounds, const stools::array<coord_type,dims> &upper_bounds, const stools::array<size_type,dims> &buffer_size)
	{
		stools::array<size_type,dims> result;

		for (size_t i=0; i<dims; ++i)
		{
			result[i] = rounding_policy::template func<size_type>( ((cartesian_position[i] - lower_bounds[i]) / (upper_bounds[i] - lower_bounds[i])) * (buffer_size[i] - 1) );
		}

		return result;
	}
};

}

#endif // !_GRID_WARPER_
