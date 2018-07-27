#include <ga3e.hpp>

using namespace ga3e;

int main() {
	std::cout << "-- Scaled basis vetor completly defined in runtime" << std::endl;
	std::cout << std::endl;

	auto c = 6.5 * e(2);

	std::cout << "c = " << c << std::endl;
	std::cout << std::endl;

	std::cout << "sizeof(c) = " << sizeof(c) << " bytes" << std::endl;
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
