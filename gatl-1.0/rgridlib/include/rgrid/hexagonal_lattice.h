/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _RGRID_HEXAGONAL_LATTICE_
#define _RGRID_HEXAGONAL_LATTICE_

// The namespace of the regular grid library.
namespace rgrid
{

/*******************************************************************************************************
 * rgrid::hexagonal_lattice<real_type,integer_type> class definition.
 *******************************************************************************************************/

// Specifies the hexagonal lattice of a 2-dimensional cartesian regular grid.
template<typename real_type, typename integer_type>
struct hexagonal_lattice : public lattice<real_type,integer_type,2>
{
private:

	// A type that represents the super class.
	typedef lattice<real_type,integer_type,2> _super;

public:

	// Returns the transformation matrix that maps vectors represented in the cartesian coordinates system to an n-dimensional integer lattice.
	static inline
	const typename _super::transform& cartesian_to_lattice()
	{
		static const typename _super::transform &matrix = la::inverse( lattice_to_cartesian() );
		return matrix;
	}
		
	// Transforms the given vector represented in cartesian coordinates system to a vector in an n-dimensional integer lattice.
	static inline
	typename _super::lattice_vector cartesian_to_lattice(const typename _super::cartesian_vector &vector)
	{
		static const typename _super::transform &matrix = cartesian_to_lattice();
		return la::round<integer_type>( matrix * vector );
	}

	// Returns the transformation matrix that maps vectors from an n-dimensional integer lattice to vectors represented in cartesian coordinates system.
	static inline
	const typename _super::transform& lattice_to_cartesian()
	{
		static typename _super::transform matrix;

		static bool first_time = true;
		if (first_time)
		{
			matrix(0,0) = 1; matrix(0,1) = static_cast<real_type>( 0.5 );
			matrix(1,0) = 0; matrix(1,1) = sqrt( static_cast<real_type>( 3 ) ) * static_cast<real_type>( 0.5 );
			first_time = false;
		}

		return matrix;
	}
		
	// Transforms the given vector in an n-dimensional integer lattice to a vector represented in cartesian coordinates system.
	static inline
	typename _super::cartesian_vector lattice_to_cartesian(const typename _super::lattice_vector &vector)
	{
		static const typename _super::transform &matrix = lattice_to_cartesian();
		return matrix * vector;
	}
};

}

#endif // !_RGRID_HEXAGONAL_LATTICE_
