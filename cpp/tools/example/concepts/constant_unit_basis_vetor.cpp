#include <ga3e.hpp>

using namespace ga3e;

int main() {
	std::cout << "-- Constant unit basis vector defined in compilation time" << std::endl;
	std::cout << std::endl;

	auto a = e(c<1>);
	//auto a = e1; // helper from ga3e

	std::cout << "a = " << a << std::endl;
	std::cout << std::endl;

	std::cout << "sizeof(a) = " << sizeof(a) << " bytes" << std::endl;
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
