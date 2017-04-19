/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_TYPES_
#define _GA_TYPES_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * ga::bitmap_t type definition.
 *******************************************************************************************************/

// Defines the data type for bitmap representation. Bitmaps are used to identify basis vectors and speed up some operations.
typedef unsigned int bitmap_t;

/*******************************************************************************************************
 * ga::index_t type definition.
 *******************************************************************************************************/

// Defines the data type for index representation.
typedef unsigned int index_t;

/*******************************************************************************************************
 * ga::int_t type definition.
 *******************************************************************************************************/

// Defines the data type which represents integer numbers.
typedef int int_t;

/*******************************************************************************************************
 * ga::name_t type definition.
 *******************************************************************************************************/

// Defines the data type for labeling representation.
typedef std::string name_t;

/*******************************************************************************************************
 * ga::real_t type definition.
 *******************************************************************************************************/

#ifndef ASSUMED_GA_REAL_TYPE

	// Defines the data type which represents real numbers. Notice that it also defines the precision of your computation.
	typedef double real_t;

#else // !ASSUMED_GA_REAL_TYPE

	// Defines the data type which represents real numbers. Notice that it also defines the precision of your computation.
	typedef ASSUMED_GA_REAL_TYPE real_t;

#endif // !ASSUMED_GA_REAL_TYPE

}

#endif // !_GA_TYPES_
