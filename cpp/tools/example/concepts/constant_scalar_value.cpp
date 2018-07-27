#include <ga3e.hpp>

using namespace ga3e;

int main() {
	std::cout << "-- Constant scalar value defined in compilation time" << std::endl;
	std::cout << std::endl;

	auto x = c<5>;

	std::cout << "x = " << x << std::endl;
	std::cout << std::endl;

	std::cout << "sizeof(x) = " << sizeof(x) << " bytes" << std::endl;
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
