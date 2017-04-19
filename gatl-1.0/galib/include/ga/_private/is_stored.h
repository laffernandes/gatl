/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_PRIVATE_IS_STORED_
#define _GA_PRIVATE_IS_STORED_

// The namespace of the geometric algebra library.
namespace ga
{

// A namespace for internal use of the geometric algebra library.
namespace _private
{

/*******************************************************************************************************
 * ga::_private::is_stored<basis_blade,store> struct definition.
 *******************************************************************************************************/

// Returns whether a given basis blade is stored by a given store struct.
template<bitmap_t basis_blade, typename store>
struct is_stored
{
	// The query result.
	static const bool result = ((basis_blade == store::bitmap) || (is_stored<basis_blade,typename store::next>::result));
};

// Specialization of is_stored<basis_blade,store> for store equal to store_none.
template<bitmap_t basis_blade>
struct is_stored<basis_blade,store_none>
{
	// The end of the list was reached.
	static const bool result = false;
};

}

}

#endif // !_GA_PRIVATE_IS_STORED_
