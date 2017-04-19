/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BMATH_DIVISION_
#define _BMATH_DIVISION_

// The namespace of the basic math library.
namespace bmath
{

/*******************************************************************************************************
 * Division operation having angles in degrees.
 *******************************************************************************************************/

// Division of two angles (in degrees).
template<typename real_type>
inline
degrees<real_type>
operator / (const degrees<real_type> &angle1, const degrees<real_type> &angle2)
{
	degrees<real_type> result = { angle1.value / angle2.value };
	return result;
}

// Division of an angle (in degrees) with a scalar value.
template<typename real_type>
inline
degrees<real_type>
operator / (const degrees<real_type> &angle, const real_type &scalar)
{
	degrees<real_type> result = { angle.value / scalar };
	return result;
}

// Division of a scalar value with an angle (in degrees).
template<typename real_type>
inline
degrees<real_type>
operator / (const real_type &scalar, const degrees<real_type> &angle)
{
	degrees<real_type> result = { scalar / angle.value };
	return result;
}

/*******************************************************************************************************
 * Division operation having angles in radians.
 *******************************************************************************************************/

// Division of two angles (in radians).
template<typename real_type>
inline
radians<real_type>
operator / (const radians<real_type> &angle1, const radians<real_type> &angle2)
{
	radians<real_type> result = { angle1.value / angle2.value };
	return result;
}

// Division of an angle (in radians) with a scalar value.
template<typename real_type>
inline
radians<real_type>
operator / (const radians<real_type> &angle, const real_type &scalar)
{
	radians<real_type> result = { angle.value / scalar };
	return result;
}

// Division of a scalar value with an angle (in radians).
template<typename real_type>
inline
radians<real_type>
operator / (const real_type &scalar, const radians<real_type> &angle)
{
	radians<real_type> result = { scalar / angle.value };
	return result;
}

}

#endif // !_BMATH_DIVISION_
