/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_PI_
#define _BTRIG_PI_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * btrig::pi_value<real_type> struct definition.
 *******************************************************************************************************/

// Basic pi value template class. By overloading this template one specialize pi for a given real type.
template<typename real_type>
struct pi_value;

// Specialization of pi_value<real_type> for real_type equal to float.
template<>
struct pi_value<float>
{
	// Specifies the pi value (in radians).
	static inline
	const float value()
	{
		return 3.14159265358979323846264338327950288f;
	}
};

// Specialization of pi_value<real_type> for real_type equal to double.
template<>
struct pi_value<double>
{
	// Specifies the pi value (in radians).
	static inline
	const double value()
	{
		return 3.14159265358979323846264338327950288;
	}
};

// Specialization of pi_value<real_type> for real_type equal to long double.
template<>
struct pi_value<long double>
{
	// Specifies the pi value (in radians).
	static inline
	const long double value()
	{
		return 3.14159265358979323846264338327950288l;
	}
};

/*******************************************************************************************************
 * Some pre-declarations.
 *******************************************************************************************************/

template<typename real_type>
class degrees;

template<typename real_type>
class radians;

/*******************************************************************************************************
 * btrig::pi<real_type> class definition.
 *******************************************************************************************************/

// pi = 3.14159265358979323846264338327950288
template<typename real_type>
class pi : public radians<real_type>
{
public:

	// Default class constructor.
	pi() : radians<real_type>( pi_value<real_type>::value() )
	{
	}

};

}

#endif // !_BTRIG_PI_
