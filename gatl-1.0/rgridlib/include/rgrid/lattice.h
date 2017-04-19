/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _RGRID_LATTICE_
#define _RGRID_LATTICE_

// The namespace of the regular grid library.
namespace rgrid
{

/*******************************************************************************************************
 * rgrid::lattice<real_type,integer_type,dims> class definition.
 *******************************************************************************************************/

// The lattice of some regular grid structure.
template<typename _real_type, typename _integer_type, size_t _dims>
struct lattice
{
public:

	// A type that represents an integer value.
	typedef _integer_type integer_type;

	// A type that represents a real value.
	typedef _real_type real_type;

public:

	// The number of dimensions of the cartesian space.
	static const size_t dims = _dims;

public:

	// A type that represents a vector having its coordinates represented in cartesian coordinates system.
	typedef la::smatrix<real_type,dims,1> cartesian_vector;

	// A type that represents a vector having its coordinates represented in an n-dimensional integer lattice.
	typedef la::smatrix<integer_type,dims,1> lattice_vector;

	// A type that represents an NxN transformation matrix, where N is the number of dimensions of the space.
	typedef la::smatrix<real_type,dims,dims> transform;
};

}

#endif // !_RGRID_LATTICE_
