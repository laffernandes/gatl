/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTRIG_READ_
#define _BTRIG_READ_

// The namespace of the basic trigonometry library.
namespace btrig
{

/*******************************************************************************************************
 * Read from the stream operator.
 *******************************************************************************************************/

// Reads the angle (in degrees) from the iutput stream.
template<typename real_type>
std::istream&
operator >> (std::istream &is, degrees<real_type> &angle)
{
	is >> angle.m_value;
	return is;
}

// Reads the angle (in radians) from the iutput stream.
template<typename real_type>
std::istream&
operator >> (std::istream &is, radians<real_type> &angle)
{
	is >> angle.m_value;
	return is;
}

}

#endif // !_BTRIG_READ_
