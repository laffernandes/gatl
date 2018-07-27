#include <ga3e.hpp>

using namespace ga3e;

int main() {
	std::cout << "-- A more interesting example" << std::endl;
	std::cout << std::endl;

	auto u = c<4> * e1 - c<2> * e2 + c<1> * e3;
	auto v = 6.5 * e1 + c<5> * e2 - 2 * e3;
	auto r = u * v;
	//auto r = gp(u, v); The * operator is an alias to ga::gp()

	std::cout << "u = " << u << std::endl;
	std::cout << "v = " << v << std::endl;
	std::cout << "r = gp(u, v) = " << r << std::endl;
	std::cout << std::endl;
	std::cout << "sizeof(u) = " << sizeof(u) << " bytes" << std::endl;
	std::cout << "sizeof(v) = " << sizeof(v) << " bytes" << std::endl;
	std::cout << "sizeof(r) = " << sizeof(r) << " bytes" << std::endl;
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
