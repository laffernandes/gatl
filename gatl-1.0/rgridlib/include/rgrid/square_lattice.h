/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _RGRID_SQUARE_LATTICE_
#define _RGRID_SQUARE_LATTICE_

// The namespace of the regular grid library.
namespace rgrid
{

/*******************************************************************************************************
 * rgrid::square_lattice<real_type,integer_type> class definition.
 *******************************************************************************************************/

// Specifies the square lattice of some 2-D regular grid structure.
template<typename real_type, typename integer_type>
struct square_lattice : public hypercubic_simple_lattice<real_type,integer_type,2>
{
};

}

#endif // !_RGRID_SQUARE_LATTICE_
