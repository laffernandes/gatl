/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_DEGREES_
#define _BTRIG_DEGREES_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * btrig::degrees<real_type> class definition.
 *******************************************************************************************************/

// An angle in degrees.
template<typename real_type>
class degrees
{
private:

	// The angle value.
	real_type m_value;

public:
	
	// Converts from degrees to radians.
	inline
	static real_type to_radians(const real_type &degrees)
	{
		static const real_type scalar = pi<real_type>().value() / 180;
		return degrees * scalar;
	}

	// Converts from degrees to radians.
	inline
	real_type to_radians() const
	{
		return to_radians( m_value );
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

	_btrig_declare_constructors(degrees)

	_btrig_declare_casting_operators(radians)

	_btrig_declare_assignment_operator(degrees,=)
	_btrig_declare_assignment_operator(degrees,+=)
	_btrig_declare_assignment_operator(degrees,-=)
	_btrig_declare_assignment_operator(degrees,*=)
	_btrig_declare_assignment_operator(degrees,/=)

public:

	template<typename some_type>
	friend void std::swap(some_type&, some_type&);

	template<typename some_type>
	friend std::istream& operator >> (std::istream &is, degrees<some_type> &angle);

	template<typename some_type>
	friend std::istream& operator >> (std::istream &is, radians<some_type> &angle);

};

}

#endif // !_BTRIG_DEGREES_
