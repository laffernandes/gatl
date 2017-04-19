/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "grid.h"

// Main function.
int
main(int argc, char *argv[])
{
	typedef grid::warped_buffer<double,3,std::vector<float> > linear_buffer;

	linear_buffer buffer;
	linear_buffer::size_array size = { 10, 10, 10 };
	linear_buffer::coord_array lower_bounds = { -1, -2, -3 }, upper_bounds = { 1, 2, 3 };

	buffer.resize( lower_bounds, upper_bounds, size );
	std::fill( buffer.begin(), buffer.end(), 5.0f );

	std::cout << buffer.container_size() << std::endl;
	std::cout << buffer.operator []<grid::policy_trunc>(lower_bounds) << std::endl;
	return EXIT_SUCCESS;
}
