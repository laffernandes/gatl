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

#include "ga2e.h"
using namespace ga2e;

// Main function.
int
main(int argc, char *argv[])
{
	multivector_t m;
	assign<false>( m, e2, 0 );

	const rank2_tensor_t &gamma = reverse_tensor<model>();
	
	const operation_matrix_t &matrix_right = gp_matrix<ga::right_multiplication>( e2 );
	std::cout << matrix_right << std::endl;
	std::cout << std::endl;

	const operation_matrix_t &matrix_left = gp_matrix<ga::left_multiplication>( e2 );
	std::cout << matrix_left << std::endl;
	std::cout << std::endl;
	
	return EXIT_SUCCESS;
}
