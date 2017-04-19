/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_WRITE_
#define _BTRIG_WRITE_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * Write to the stream operator.
 *******************************************************************************************************/

// Writes the angle (in degrees) into the output stream.
template<typename real_type>
std::ostream&
operator << (std::ostream &os, const degrees<real_type> &angle)
{
	os << angle.value();
	return os;
}

// Writes the angle (in radians) into the output stream.
template<typename real_type>
std::ostream&
operator << (std::ostream &os, const radians<real_type> &angle)
{
	os << angle.value();
	return os;
}

}

#endif // !_BTRIG_WRITE_
