/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_RADIANS_
#define _BTRIG_RADIANS_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * btrig::radians<real_type> class definition.
 *******************************************************************************************************/

// An angle in radians.
template<typename real_type>
class radians
{
private:

	// The angle value.
	real_type m_value;

public:
	
	// Converts from radians to degrees.
	inline
	static real_type to_degrees(const real_type &radians)
	{
		static const real_type scalar = 180 / pi<real_type>().value();
		return radians * scalar;
	}

	// Converts from radians to degrees.
	inline
	real_type to_degrees() const
	{
		return to_degrees( m_value );
	}

public:

	// Raw data access.
	inline
	real_type& value()
	{
		return m_value;
	}

	// Raw data access.
	inline
	const real_type& value() const
	{
		return m_value;
	}

public:

	_btrig_declare_constructors(radians)

	_btrig_declare_casting_operators(degrees)

	_btrig_declare_assignment_operator(radians,=)
	_btrig_declare_assignment_operator(radians,+=)
	_btrig_declare_assignment_operator(radians,-=)
	_btrig_declare_assignment_operator(radians,*=)
	_btrig_declare_assignment_operator(radians,/=)

public:

	template<typename some_type>
	friend void std::swap(some_type&, some_type&);

	template<typename some_type>
	friend std::istream& operator >> (std::istream &is, degrees<some_type> &angle);

	template<typename some_type>
	friend std::istream& operator >> (std::istream &is, radians<some_type> &angle);

};

}

#endif // !_BTRIG_RADIANS_
