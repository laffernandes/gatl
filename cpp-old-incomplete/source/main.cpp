#include "ga.hpp"

#include <functional>
#include <iostream>

// Global variables.
auto zero = ga::make_weighted_scalar_c<0>();

auto alpha = ga::make_weighted_scalar_c<1>();
auto beta = ga::make_weighted_scalar(2);

auto zero_ex = ga::make_weighted_basis_vector_c<0, 12>();

auto e0 = ga::make_basis_vector_c<0>();
auto e1 = ga::make_basis_vector_c<1>();
auto e2 = ga::make_basis_vector_c<2>();

auto e3 = ga::make_weighted_basis_vector_c<1, 3>();
auto e4 = ga::make_weighted_basis_vector_c<1, 4>();
auto e5 = ga::make_weighted_basis_vector_c<1, 5>();

auto e6 = ga::make_weighted_basis_vector<double, 6>(1.0);

auto ei = ga::make_basis_vector(7);
auto ej = ga::make_weighted_basis_vector(1.0, 8);

// Basic print procedures.
template<class T>
void print(const T &m) {
	std::cout << m << std::endl;
}

// Testing functors.
struct minus_test {

	template<class T1, class T2>
	inline
	void operator () (T1 arg1, T2 arg2) const {
		print(ga::minus(arg1, arg2));
		print(arg1 - arg2);
	}
};

struct plus_test {

	template<class T1, class T2>
	inline
	void operator () (T1 arg1, T2 arg2) const {
		print(ga::plus(arg1, arg2));
		print(arg1 + arg2);
	}
};

struct uminus_test {

	template<class T>
	inline
	void operator () (T arg) const {
		print(ga::uminus(arg));
		print(-arg);
	}
};

struct uminus_uminus_test {

	template<class T>
	inline
	void operator () (T arg) const {
		print(ga::uminus(ga::uminus(arg)));
		print(-(-arg));
	}
};

struct uplus_test {

	template<class T>
	inline
	void operator () (T arg) const {
		print(ga::uplus(arg));
		print(+arg);
	}
};

void global_variables_prints() {
	std::cout << std::endl << "Scalar values" << std::endl;
	std::cout << "------------------------------------------------------------------" << std::endl;

	std::cout << zero << std::endl;

	std::cout << alpha << std::endl;
	std::cout << beta << std::endl;

	std::cout << std::endl << "Vectors" << std::endl;
	std::cout << "------------------------------------------------------------------" << std::endl;

	std::cout << zero_ex << std::endl;

	std::cout << e0 << std::endl;
	std::cout << e1 << std::endl;
	std::cout << e2 << std::endl;

	std::cout << e3 << std::endl;
	std::cout << e4 << std::endl;
	std::cout << e5 << std::endl;

	std::cout << e6 << std::endl;

	std::cout << ei << std::endl;
	std::cout << ej << std::endl;
}

// The set of tests.
template<class Functor>
void binary_tests(const std::string &name, const Functor &test) {
	std::cout << std::endl << name << std::endl;
	std::cout << "------------------------------------------------------------------" << std::endl;

	test(zero, zero);
	test(1.0, zero);
	test(alpha, zero);
	test(beta, zero);
	test(e0, zero);
	test(e6, zero);
	test(ei, zero);
	test(ej, zero);

	test(zero, 1.0);
	test(1.0, 1.0);
	test(alpha, 1.0);
	test(beta, 1.0);
	test(e0, 1.0);
	test(e6, 1.0);
	test(ei, 1.0);
	test(ej, 1.0);

	test(zero, alpha);
	test(1.0, alpha);
	test(alpha, alpha);
	test(beta, alpha);
	test(e0, alpha);
	test(e6, alpha);
	test(ei, alpha);
	test(ej, alpha);

	test(zero, beta);
	test(1.0, beta);
	test(alpha, beta);
	test(beta, beta);
	test(e0, beta);
	test(e6, beta);
	test(ei, beta);
	test(ej, beta);

	test(zero, e0);
	test(1.0, e0);
	test(alpha, e0);
	test(beta, e0);
	test(e0, e0);
	test(e6, e0);
	test(ei, e0);
	test(ej, e0);

	test(zero, e6);
	test(1.0, e6);
	test(alpha, e6);
	test(beta, e6);
	test(e0, e6);
	test(e6, e6);
	test(ei, e6);
	test(ej, e6);

	test(zero, ei);
	test(1.0, ei);
	test(alpha, ei);
	test(beta, ei);
	test(e0, ei);
	test(e6, ei);
	test(ei, ei);
	test(ej, ei);

	test(zero, ej);
	test(1.0, ej);
	test(alpha, ej);
	test(beta, ej);
	test(e0, ej);
	test(e6, ej);
	test(ei, ej);
	test(ej, ej);
}

template<class Functor>
void unary_tests(const std::string &name, const Functor &test) {
	std::cout << std::endl << name << std::endl;
	std::cout << "------------------------------------------------------------------" << std::endl;

	test(zero);

	test(1.0);
	test(alpha);
	test(beta);

	test(e0);
	test(e6);
	test(ei);
	test(ej);
}

// The main method.
int main() {

	// Global variables.
	global_variables_prints();

	// Unary operations.
	unary_tests("Unary minus",    uminus_test());
	unary_tests("Unary minus 2X", uminus_uminus_test());
	unary_tests("Unary plus",     uplus_test());

	binary_tests("Minus", minus_test());
	binary_tests("Plus", plus_test());

	// Job done!
	system("pause");
	return EXIT_SUCCESS;
}
