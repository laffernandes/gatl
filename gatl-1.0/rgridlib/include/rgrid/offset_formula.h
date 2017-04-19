/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _RGRID_OFFSET_FORMULA_
#define _RGRID_OFFSET_FORMULA_

// The namespace of the regular grid library.
namespace rgrid
{

/*******************************************************************************************************
 * rgrid::offset_formula<lattice,size_type> class definition.
 *******************************************************************************************************/

// Implements the offset formula used to compute the index value of a given lattice vector and the lattice vector related to a given index value.
template<typename lattice, typename size_type>
class offset_formula : public basic_offset_formula<lattice,size_type>
{
private:

	// A type that represents the super class.
	typedef basic_offset_formula<lattice,size_type> _super;

public:

	using _super::clear;
	using _super::inside_bounds;
	using _super::resize;
	using _super::size;
	using _super::operator();
};

}

#endif // !_RGRID_OFFSET_FORMULA_
