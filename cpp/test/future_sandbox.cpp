#include <future/ga.hpp>

using namespace future::ga;

int main() {
	auto alpha = c<5>; std::cout << "sizeof(c<5>) = " << sizeof(alpha) << std::endl;
	auto e1 = e(c<1>); std::cout << "sizeof(e1) = " << sizeof(e1) << std::endl;
	auto ei = e(2); std::cout << "sizeof(ei) = " << sizeof(ei) << std::endl;

	auto x = 3.0 + e1; std::cout << "sizeof(x) = " << sizeof(x) << std::endl;
	auto y = e1 + alpha; std::cout << "sizeof(y) = " << sizeof(y) << std::endl;

	return EXIT_SUCCESS;
}
