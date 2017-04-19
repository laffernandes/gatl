/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _RGRID_HYPERCUBIC_SIMPLE_LATTICE_
#define _RGRID_HYPERCUBIC_SIMPLE_LATTICE_

// The namespace of the regular grid library.
namespace rgrid
{

/*******************************************************************************************************
 * rgrid::hypercubic_simple_lattice<real_type,integer_type,dims> class definition.
 *******************************************************************************************************/

// Specifies the hypercubic simple lattice (i.e., square lattice in 2-D, cubic simple lattice in 3-D, etc.) of some regular grid structure.
template<typename real_type, typename integer_type, size_t dims>
struct hypercubic_simple_lattice : public lattice<real_type,integer_type,dims>
{
private:

	// A type that represents the super class.
	typedef lattice<real_type,integer_type,dims> _super;

public:

	// Returns the transformation matrix that maps vectors represented in the cartesian coordinates system to an n-dimensional integer lattice.
	static inline
	const typename _super::transform& cartesian_to_lattice()
	{
		static const typename _super::transform identity( la::identity_matrix );
		return identity;
	}
		
	// Transforms the given vector represented in cartesian coordinates system to a vector in an n-dimensional integer lattice.
	static inline
	typename _super::lattice_vector cartesian_to_lattice(const typename _super::cartesian_vector &vector)
	{
		return la::round<integer_type>( vector ); // The resulting vector is the input vector transformed by the identity matrix.
	}

	// Returns the transformation matrix that maps vectors from an n-dimensional integer lattice to vectors represented in cartesian coordinates system.
	static inline
	const typename _super::transform& lattice_to_cartesian()
	{
		static const typename _super::transform identity( la::identity_matrix );
		return identity;
	}
		
	// Transforms the given vector in an n-dimensional integer lattice to a vector represented in cartesian coordinates system.
	static inline
	typename _super::cartesian_vector lattice_to_cartesian(const typename _super::lattice_vector &vector)
	{
		return vector.template cast<typename _super::real_type>(); // The resulting vector is the input vector transformed by the identity matrix.
	}
};

}

#endif // !_RGRID_HYPERCUBIC_SIMPLE_LATTICE_
