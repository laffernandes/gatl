/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_EULER_MASCHERONI_
#define _BTRIG_EULER_MASCHERONI_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * btrig::euler_mascheroni_value<real_type> struct definition.
 *******************************************************************************************************/

// Basic Euler-Mascheroni constant template class. By overloading this template one specialize the Euler-Mascheroni constant for a given real type.
template<typename real_type>
struct euler_mascheroni_value;

// Specialization of euler_mascheroni_value<real_type> for real_type equal to float.
template<>
struct euler_mascheroni_value<float>
{
	// Specifies the Euler-Mascheroni constant.
	static inline
	const float value()
	{
		return 0.577215664901532860606512090082402431042f;
	}
};

// Specialization of euler_mascheroni_value<real_type> for real_type equal to double.
template<>
struct euler_mascheroni_value<double>
{
	// Specifies the Euler-Mascheroni constant.
	static inline
	const double value()
	{
		return 0.577215664901532860606512090082402431042;
	}
};

// Specialization of euler_mascheroni_value<real_type> for real_type equal to long double.
template<>
struct euler_mascheroni_value<long double>
{
	// Specifies the Euler-Mascheroni constant.
	static inline
	const long double value()
	{
		return 0.577215664901532860606512090082402431042l;
	}
};

}

#endif // !_BTRIG_EULER_MASCHERONI_
