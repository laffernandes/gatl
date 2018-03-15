#include "ga.hpp"

using namespace ga;

/**
void test_make_cvalue() {
	std::cout << "--- test_make_cvalue()" << std::endl;
	constexpr auto x = c<5>;
	static_assert(x > 3, "x <= 3");
	static_assert(c<5> > 3, "x <= 3");
	std::cout << "5 = " << x << std::endl;
	std::cout << std::endl;
}

void test_make_scalarc() {
	std::cout << "--- test_make_scalarc()" << std::endl;
	std::cout << "5 = " << c<5> << std::endl;
	auto nine = c<9>; std::cout << "9 = " << nine << std::endl;
	std::cout << std::endl;
}

decltype(auto) test_make_ek_func(index_t k) {
	return e(k);
}

void test_make_e() {
	std::cout << "--- test_make_e()" << std::endl;
	std::cout << "e1 = " << e(1) << std::endl;
	std::cout << "e3 = " << e(3) << std::endl;
	std::cout << "e1 = " << test_make_ek_func(1) << std::endl;
	std::cout << "e3 = " << test_make_ek_func(3) << std::endl;
	auto e1 = e(1); std::cout << "e1 = " << e1 << std::endl;
	volatile index_t i = 9; std::cout << "e9 = " << e(i) << std::endl;
	std::cout << std::endl;
}

void test_make_ec() {
	std::cout << "--- test_make_ec()" << std::endl;
	std::cout << "e1 = " << e(c<1>) << std::endl;
	std::cout << "e3 = " << e(c<3>) << std::endl;
	auto e1 = e(c<1>); std::cout << "e1 = " << e1 << std::endl;
	std::cout << std::endl;
}

decltype(auto) test_uplus_func(double x) {
	return uplus(x);
}

void test_uplus() {
	std::cout << "--- test_uplus()" << std::endl;
	std::cout << "5 = " << +(uplus(5.0)) << std::endl;
	std::cout << "5 = " << test_uplus_func(5.0) << std::endl;
	auto five = uplus(5.0); std::cout << "5 = " << five << std::endl;
	auto e1 = +(e(1)); std::cout << "e1 = " << e1 << std::endl;
	auto e2 = uplus(e(c<2>)); std::cout << "e2 = " << e2 << std::endl;
	std::cout << std::endl;
}

void test_uminus() {
	std::cout << "--- test_uminus()" << std::endl;
	auto five = uminus(5.0); std::cout << "-5 = " << five << std::endl;
	auto e1 = uminus(e(1)); std::cout << "-e1 = " << e1 << std::endl;
	auto e2 = uminus(e(c<2>)); std::cout << "-e2 = " << e2 << std::endl;
	std::cout << std::endl;
}

void test_plus() {
	std::cout << "--- test_plus()" << std::endl;
	std::cout << "e1 + e2 = " << (e(c<1>) + e(c<2>)) << std::endl;
	std::cout << "5 + 2 * e1 + e2 = " << (c<5> + e(c<1>) + e(c<2>) + e(c<1>)) << std::endl;
	std::cout << "5 + e1 + e2 = " << (5.0 + e(c<1>) + e(c<2>)) << std::endl;
	std::cout << "5 + 3 * e1 + e2 = " << (e(c<1>) + 5.0 + e(c<1>) + e(c<2>) + e(c<1>)) << std::endl;
	std::cout << std::endl;
}

void test_minus() {
	std::cout << "--- test_minus()" << std::endl;
	std::cout << "e1 - e2 = " << (e(c<1>) - e(c<2>)) << std::endl;
	std::cout << "e2 - e1 = " << (e(c<2>) - e(c<1>)) << std::endl;
	std::cout << "5 + e2 = " << (c<5> - e(c<1>) + e(c<2>) + e(c<1>)) << std::endl;
	std::cout << "5 + e1 + e2 = " << (5.0 + e(c<1>) + e(c<2>)) << std::endl;
	std::cout << "-5 + e1 - 2 * e2 - e3 = " << (e(c<1>) - 5.0 - e(c<2>) - e(c<2>) - e(c<3>)) << std::endl;
	std::cout << std::endl;
}

void test_op() {
	std::cout << "--- test_op()" << std::endl;
	std::cout << "e1^e2 = " << (e(c<1>) ^ e(c<2>)) << std::endl;
	std::cout << "e2^e1 = " << (e(c<2>) ^ e(c<1>)) << std::endl;
	std::cout << "e3^e3 = " << (e(c<3>) ^ e(c<3>)) << std::endl;

	auto e1 = e(c<1>); auto e2 = e(c<2>); auto e3 = e(c<3>); auto e4 = e(c<4>); auto e5 = e(c<5>); auto e6 = e(c<6>); auto e7 = e(c<7>);
	std::cout << "1 + e5 ^ (1 + e6 ^ (1 + e7)) = " << (1 + e5 ^ (1 + e6 ^ (1 + e7))) << std::endl;

	std::cout << std::endl;
}

void test_take_grade() {
	std::cout << "--- test_take_grade()" << std::endl;
	auto e1 = e(c<1>);
	std::cout << "take_grade<0>(" << e1 << ") = " << take_grade(e1, c<0>) << std::endl;
	std::cout << "take_grade<1>(" << e1 << ") = " << take_grade(e1, c<1>) << std::endl;
	std::cout << "take_grade<2>(" << e1 << ") = " << take_grade(e1, c<2>) << std::endl;
	std::cout << "take_grade<1>(5 + 3 * e1 + e2) = " << take_grade(e(c<1>) + 5.0 + e(c<1>) + e(c<2>) + e(c<1>), c<1>) << std::endl;
	std::cout << std::endl;
}

void test_sign_change_operations() {
	auto e1 = e(c<1>); auto e2 = e(c<2>); auto e3 = e(c<3>); auto e4 = e(c<4>); auto e5 = e(c<5>); auto e6 = e(c<6>); auto e7 = e(c<7>);

	std::cout << "--- test_sign_change_operations()" << std::endl;
	std::cout << "+ - - + + - - + = " << conjugation(1 + (e1 ^ (1 + (e2 ^ (1 + (e3 ^ (1 + (e4 ^ (1 + (e5 ^ (1 + (e6 ^ (1 + e7))))))))))))) << std::endl;
	std::cout << "+ - + - + - + - = " << involution(1 + (e1 ^ (1 + (e2 ^ (1 + (e3 ^ (1 + (e4 ^ (1 + (e5 ^ (1 + (e6 ^ (1 + e7))))))))))))) << std::endl;
	std::cout << "+ + - - + + - - = " << reversion(1 + (e1 ^ (1 + (e2 ^ (1 + (e3 ^ (1 + (e4 ^ (1 + (e5 ^ (1 + (e6 ^ (1 + e7))))))))))))) << std::endl;
	std::cout << std::endl;
}

template<class MetricType>
void test_metric(metric<MetricType> const &mtr) {
	std::cout << "--- test_metric()" << std::endl;
	std::cout << mtr.entry(5, 5) << std::endl;
	std::cout << mtr.entry(6, 5) << std::endl;
	std::cout << metric<MetricType>::centry<5, 5>::value << std::endl;
	std::cout << metric<MetricType>::centry<6, 5>::value << std::endl;
	std::cout << std::endl;
}

int main() {
	test_make_cvalue();

	test_make_scalarc();

	test_make_e();
	test_make_ec();

	test_uplus();
	test_plus();

	test_uminus();
	test_minus();

	test_op();

	test_take_grade();

	test_sign_change_operations();

	test_metric(euclidean_metric_t());

	return EXIT_SUCCESS;
}
/*/
int main() {
	auto e0 = e(c<0>);
	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto e4 = e(c<4>);
	auto e5 = e(c<5>);
	auto e6 = e(c<6>);
	auto e7 = e(c<7>);
	auto e8 = e(c<8>);

	double x, y, z, w;
	std::cout << "x = "; std::cin >> x;
	std::cout << "y = "; std::cin >> y;
	std::cout << "z = "; std::cin >> z;
	std::cout << "w = "; std::cin >> w;
	std::cout << std::endl;

	auto p = e0 + x * e1 + y * e2 + z * e3 + w * e4 + e5 + e6;
	std::cout << "p = " << p << std::endl;
	std::cout << std::endl;

	std::cout << "sizeof(empty) = " << sizeof(detail::empty_expression) << std::endl;
	std::cout << "sizeof(x) = " << sizeof(decltype(x)) << std::endl;
	std::cout << "sizeof(e1) = " << sizeof(decltype(e1)) << std::endl;
	std::cout << "sizeof(p) = " << sizeof(decltype(p)) << std::endl;

	auto itr = detail::begin(p);
	auto oitr = detail::obegin(p);

	std::cout << "sizeof(itr) = " << sizeof(decltype(itr)) << std::endl;
	std::cout << "sizeof(oitr) = " << sizeof(decltype(oitr)) << std::endl;

	return EXIT_SUCCESS;
}
/**/
