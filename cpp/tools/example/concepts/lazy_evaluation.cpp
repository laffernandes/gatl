#include <ga3h.hpp>

using namespace ga3h;

int main() {
	double x_in, y_in, z_in;

	std::cout << "-- Input" << std::endl;
	std::cout << std::endl;

	std::cout << "x = "; std::cin >> x_in;
	std::cout << "y = "; std::cin >> y_in;
	std::cout << "z = "; std::cin >> z_in;
	std::cout << std::endl;

	std::cout << "-- The motivation for lazy evaluation (result from the conventional approach)" << std::endl;
	std::cout << std::endl;
	{
		auto x = x_in;
		auto y = y_in;
		auto z = z_in;
		
		auto p = x * e1 + y * e2 + z * e3 + ep;
		auto d = x * e1 + y * e2 + z * e3;
		auto l = p ^ d;

		std::cout << "x = " << x << std::endl;
		std::cout << "y = " << y << std::endl;
		std::cout << "z = " << z << std::endl;
		std::cout << std::endl;
		std::cout << "p = " << p << std::endl;
		std::cout << "d = " << d << std::endl;
		std::cout << "l = p ^ d = " << l << std::endl;
		std::cout << std::endl;
		std::cout << "sizeof(x) = " << sizeof(x) << " bytes" << std::endl;
		std::cout << "sizeof(y) = " << sizeof(y) << " bytes" << std::endl;
		std::cout << "sizeof(z) = " << sizeof(z) << " bytes" << std::endl;
		std::cout << "sizeof(p) = " << sizeof(p) << " bytes" << std::endl;
		std::cout << "sizeof(d) = " << sizeof(d) << " bytes" << std::endl;
		std::cout << "sizeof(l) = " << sizeof(l) << " bytes" << std::endl;
	}
	std::cout << std::endl;

	std::cout << "-- The motivation for lazy evaluation (simplification via lazy evaluation)" << std::endl;
	std::cout << std::endl;
	{
		auto lazy = make_lazy_context(scalar(x_in), scalar(y_in), scalar(z_in));
		auto x = lazy.argument<0>();
		auto y = lazy.argument<1>();
		auto z = lazy.argument<2>();

		auto p = x * e1 + y * e2 + z * e3 + ep;
		auto d = x * e1 + y * e2 + z * e3;
		auto l = p ^ d;

		auto eval_l = lazy.eval(l);

		std::cout << "x = " << x << std::endl;
		std::cout << "y = " << y << std::endl;
		std::cout << "z = " << z << std::endl;
		std::cout << std::endl;
		std::cout << "p = " << p << std::endl;
		std::cout << "d = " << d << std::endl;
		std::cout << "l = p ^ d = " << l << std::endl;
		std::cout << "eval(l) = " << eval_l << std::endl;
		std::cout << std::endl;
		std::cout << "sizeof(x) = " << sizeof(x) << " bytes" << std::endl;
		std::cout << "sizeof(y) = " << sizeof(y) << " bytes" << std::endl;
		std::cout << "sizeof(z) = " << sizeof(z) << " bytes" << std::endl;
		std::cout << "sizeof(p) = " << sizeof(p) << " bytes" << std::endl;
		std::cout << "sizeof(d) = " << sizeof(d) << " bytes" << std::endl;
		std::cout << "sizeof(l) = " << sizeof(l) << " bytes" << std::endl;
		std::cout << "sizeof(eval_l) = " << sizeof(eval_l) << " bytes" << std::endl;
		std::cout << std::endl;
	}
	
	return EXIT_SUCCESS;
}
