/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_WRITE_
#define _GA_WRITE_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Write to the stream operator overload.
 *******************************************************************************************************/

// Writes the multivector into the output stream.
template<typename model, typename store>
std::ostream&
operator << (std::ostream &os, const multivector<model,store> &m)
{
	_private::write<model,store>::run( os, m.data(), true );
	return os;
}

}

#endif // !_GA_WRITE_
