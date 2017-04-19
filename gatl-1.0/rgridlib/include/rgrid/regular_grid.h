/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _RGRID_REGULAR_GRID_
#define _RGRID_REGULAR_GRID_

// The namespace of the regular grid library.
namespace rgrid
{

/*******************************************************************************************************
 * rgrid::regular_grid<lattice,sequence_container> class definition.
 *******************************************************************************************************/

// An n-dimensional generalized grid. This grid implementation is not restricted to being used with a specific grid connectivity nor with a specific dimensionality. The lattice of the grid is defined in compilation time.
template<typename lattice, typename sequence_container>
class regular_grid : public basic_regular_grid<lattice,sequence_container>
{
private:

	// A type that represents the super class.
	typedef basic_regular_grid<lattice,sequence_container> _super;

public:

	// Make some methods from the super class public.
	using _super::at;
	using _super::begin;
	using _super::clear;
	using _super::end;
	using _super::resize;
	using _super::operator [];

public:

	// Default constructor.
	regular_grid() : _super()
	{
	}
	
	// Copy constructor.
	regular_grid(const _super &other) : _super( other )
	{
	}
	
	// Resize constructor.
	regular_grid(const typename _super::size_array &size) : _super( size )
	{
	}
};

}

#endif // !_RGRID_REGULAR_GRID_
