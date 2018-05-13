#include <future/ga.hpp>

using namespace future::ga;

int main() {
	auto alpha = c<5>;
	auto e1 = e(c<1>);
	auto ei = e(2);

	auto x = 3.0 + e1; std::cout << "sizeof(x) = " << sizeof(x) << std::endl;
	auto y = e1 + alpha; std::cout << "sizeof(y) = " << sizeof(y) << std::endl;

	return EXIT_SUCCESS;
}
