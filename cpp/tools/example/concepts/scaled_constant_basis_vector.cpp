#include <ga3e.hpp>

using namespace ga3e;

int main() {
	std::cout << "-- Scaled basis vector, where only the basis vector is defined in compilation time" << std::endl;
	std::cout << std::endl;

	auto b = 6.5 * e1;

	std::cout << "b = " << b << std::endl;
	std::cout << std::endl;

	std::cout << "sizeof(b) = " << sizeof(b) << " bytes" << std::endl;
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
