/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_TRIG_FUNCTIONS_
#define _BTRIG_TRIG_FUNCTIONS_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * Some pre-definitions.
 *******************************************************************************************************/

using std::sin;
using std::cos;
using std::tan;

using std::asin;
using std::acos;
using std::atan;
using std::atan2;

using std::sinh;
using std::cosh;
using std::tanh;

/*******************************************************************************************************
 * Trigonometric functions that can be derived from standard math functions.
 *******************************************************************************************************/

// The secant of a given angle (angle in radians).
template<typename real_type>
inline
real_type
sec(const real_type &angle)
{
	return 1 / cos( angle );
}

// The cosecant of a given angle (angle in radians).
template<typename real_type>
inline
real_type
csc(const real_type &angle)
{
	return 1 / sin( angle );
}

// The cotangent of a given angle (angle in radians).
template<typename real_type>
inline
real_type
cot(const real_type &angle)
{
	return 1 / tan( angle );
}

// The inverse secant of a given value (result in radians).
template<typename real_type>
inline
real_type
asec(const real_type &value)
{
	return atan( value / sqrt( (value * value) - 1 ) ) + ((sgn( value ) - 1) * 2 * atan( static_cast<real_type>( 1 ) ));
}

// The inverse cosecant of a given value (result in radians).
template<typename real_type>
inline
real_type
acsc(const real_type &value)
{
	return atan( value / sqrt( (value * value) - 1 ) ) + ((sgn( value ) - 1) * 2 * atan( static_cast<real_type>( 1 ) ));
}

// The inverse cotangent of a given value (result in radians).
template<typename real_type>
inline
real_type
acot(const real_type &value)
{
	return atan( value ) + (2 * atan( static_cast<real_type>( 1 ) ));
}

// The hyperbolic secant of a given angle (angle in radians).
template<typename real_type>
inline
real_type
sech(const real_type &angle)
{
	return 2 / (exp( angle ) + exp( -angle ));
}

// The hyperbolic cosecant of a given angle (angle in radians).
template<typename real_type>
inline
real_type
csch(const real_type &angle)
{
	return 2 / (exp( angle ) - exp( -angle ));
}

// The hyperbolic cotangent of a given angle (angle in radians).
template<typename real_type>
inline
real_type
coth(const real_type &angle)
{
	real_type extValue = exp( angle ), expMinusValue = exp( -angle );
	return (extValue + expMinusValue) / (extValue - expMinusValue);
}

// The inverse hyperbolic sine of a given value (result in radians).
template<typename real_type>
inline
real_type
asinh(const real_type &value)
{
	return log( value + sqrt( (value * value) + 1 ) );
}

// The inverse hyperbolic cosine of a given value (result in radians).
template<typename real_type>
inline
real_type
acosh(const real_type &value)
{
	return log( value + sqrt( (value * value) - 1 ) );
}

// The inverse hyperbolic tangent of a given value (result in radians).
template<typename real_type>
inline
real_type
atanh(const real_type &value)
{
	return log( (1 + value) / (1 - value) ) / 2;
}

// The inverse hyperbolic secant of a given value (result in radians).
template<typename real_type>
inline
real_type
asech(const real_type &value)
{
	return log( (sqrt( 1 - (value * value) ) + 1) / value );
}

// The inverse hyperbolic cosecant of a given value (result in radians).
template<typename real_type>
inline
real_type
acsch(const real_type &value)
{
	return log( ((sgn( value ) * sqrt( ( value * value) + 1 )) + 1) / value );
}

// The inverse hyperbolic cotangent of a given value (result in radians).
template<typename real_type>
inline
real_type
acoth(const real_type &value)
{
	return log( (value + 1) / (value - 1) ) / 2;
}

/*******************************************************************************************************
 * Trigonometric functions overload for btrig::degrees<real_type>.
 *******************************************************************************************************/

// The sine of a given angle.
template<typename real_type>
inline
real_type
sin(const degrees<real_type> &angle)
{
	return sin( angle.to_radians() );
}

// The cosine of a given angle.
template<typename real_type>
inline
real_type
cos(const degrees<real_type> &angle)
{
	return cos( angle.to_radians() );
}

// The tangent of a given angle.
template<typename real_type>
inline
real_type
tan(const degrees<real_type> &angle)
{
	return tan( angle.to_radians() );
}

// The secant of a given angle.
template<typename real_type>
inline
real_type
sec(const degrees<real_type> &angle)
{
	return sec( angle.to_radians() );
}

// The cosecant of a given angle
template<typename real_type>
inline
real_type
csc(const degrees<real_type> &angle)
{
	return csc( angle.to_radians() );
}

// The cotangent of a given angle
template<typename real_type>
inline
real_type
cot(const degrees<real_type> &angle)
{
	return cot( angle.to_radians() );
}

// The hyperbolic sine of a given angle.
template<typename real_type>
inline
real_type
sinh(const
	 degrees<real_type> &angle)
{
	return sinh( angle.to_radians() );
}

// The hyperbolic cosine of a given angle.
template<typename real_type>
inline
real_type
cosh(const degrees<real_type> &angle)
{
	return cosh( angle.to_radians() );
}
// The hyperbolic tangent of a given angle.
template<typename real_type>
inline
real_type
tanh(const degrees<real_type> &angle)
{
	return tanh( angle.to_radians() );
}
// The hyperbolic secant of a given angle.
template<typename real_type>
inline
real_type
sech(const degrees<real_type> &angle)
{
	return sech( angle.to_radians() );
}

// The hyperbolic cosecant of a given angle.
template<typename real_type>
inline
real_type
csch(const degrees<real_type> &angle)
{
	return csch( angle.to_radians() );
}

// The hyperbolic cotangent of a given angle.
template<typename real_type>
inline
real_type
coth(const degrees<real_type> &angle)
{
	return coth( angle.to_radians() );
}

/*******************************************************************************************************
 * Trigonometric functions overload for btrig::radians<real_type>.
 *******************************************************************************************************/

// The sine of a given angle.
template<typename real_type>
inline
real_type
sin(const radians<real_type> &angle)
{
	return sin( angle.value() );
}

// The cosine of a given angle.
template<typename real_type>
inline
real_type
cos(const radians<real_type> &angle)
{
	return cos( angle.value() );
}

// The tangent of a given angle.
template<typename real_type>
inline
real_type
tan(const radians<real_type> &angle)
{
	return tan( angle.value() );
}

// The secant of a given angle.
template<typename real_type>
inline
real_type
sec(const radians<real_type> &angle)
{
	return sec( angle.value() );
}

// The cosecant of a given angle
template<typename real_type>
inline
real_type
csc(const radians<real_type> &angle)
{
	return csc( angle.value() );
}

// The cotangent of a given angle
template<typename real_type>
inline
real_type
cot(const radians<real_type> &angle)
{
	return cot( angle.value() );
}

// The hyperbolic sine of a given angle.
template<typename real_type>
inline
real_type
sinh(const radians<real_type> &angle)
{
	return sinh( angle.value() );
}

// The hyperbolic cosine of a given angle.
template<typename real_type>
inline
real_type
cosh(const radians<real_type> &angle)
{
	return cosh( angle.value() );
}

// The hyperbolic tangent of a given angle.
template<typename real_type>
inline
real_type
tanh(const radians<real_type> &angle)
{
	return tanh( angle.value() );
}

// The hyperbolic secant of a given angle.
template<typename real_type>
inline
real_type
sech(const radians<real_type> &angle)
{
	return sech( angle.value() );
}

// The hyperbolic cosecant of a given angle.
template<typename real_type>
inline
real_type
csch(const radians<real_type> &angle)
{
	return csch( angle.value() );
}

// The hyperbolic cotangent of a given angle.
template<typename real_type>
inline
real_type
coth(const radians<real_type> &angle)
{
	return coth( angle.value() );
}

}

#endif // !_BTRIG_TRIG_FUNCTIONS_
