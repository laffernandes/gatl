/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#include <cstdlib>
#include <iostream>

#include "ga3c.h"
using namespace ga3c;

#define ga_flat_point(x, y, z) ((((x)*e1 + (y)*e2 + (z)*e3)^ni) + noni)

// Main function.
int
main(int argc, char *argv[])
{
	std::cout << ga_flat_point(.1,.2,.3) << std::endl;

	return EXIT_SUCCESS;
}
