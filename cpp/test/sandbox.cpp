#define GA_MAX_BASIS_VECTOR_INDEX 10
#include <ga.hpp>

using namespace ga;

/**/
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
	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	std::cout << "--- test_op()" << std::endl;

	std::cout << "e1^e2 = " << (e1 ^ e2) << std::endl;
	std::cout << "e2^e1 = " << (e2 ^ e1) << std::endl;
	std::cout << "e3^(e3 + e1^e2) = " << (e3 ^ (e3 + (e1 ^ e2))) << std::endl;
	std::cout << std::endl;

	std::cout << "ei^ej = " << (ei ^ ej) << std::endl;
	std::cout << "ej^ei = " << (ej ^ ei) << std::endl;
	auto xyz = (ek ^ (ek + (ei ^ ej))); std::cout << "ek^(ek + ei^ej) = " << xyz << std::endl;
	std::cout << std::endl;

	std::cout << "e1^ej = " << (e1 ^ ej) << std::endl;
	std::cout << "ej^e1 = " << (ej ^ e1) << std::endl;
	std::cout << "e3^(e3 + e1^ej) = " << (e3 ^ (e3 + (e1 ^ ej))) << std::endl;
	std::cout << std::endl;
}

template<class MetricType>
void test_scp(metric<MetricType> const &mtr, std::string const &name) {
	auto e1 =e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	std::cout << "--- test_scp(" << name << ")" << std::endl;

	std::cout << "scp(e1, e1^e2) = " << scp(e1, e1^e2, mtr) << std::endl;
	std::cout << "scp(e1^e2, e1^e2) = " << scp(e1^e2, e1^e2, mtr) << std::endl;
	std::cout << "scp(e1^e3, e1^e2) = " << scp(e1^e3, e1^e2, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "scp(ei, ei^ej) = " << scp(ei, ei^ej, mtr) << std::endl;
	std::cout << "scp(ei^ej, ei^ej) = " << scp(ei^ej, ei^ej, mtr) << std::endl;
	std::cout << "scp(ei^ek, ei^ej) = " << scp(ei^ek, ei^ej, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "scp(e1, e1^ej) = " << scp(e1, e1^ej, mtr) << std::endl;
	std::cout << "scp(e1^ej, e1^ej) = " << scp(e1^ej, e1^ej, mtr) << std::endl;
	std::cout << "scp(e1^e3, e1^ej) = " << scp(e1^e3, e1^ej, mtr) << std::endl;
	std::cout << std::endl;
}

template<class MetricType>
void test_lcont(metric<MetricType> const &mtr, std::string const &name) {
	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	std::cout << "--- test_lcont(" << name << ")" << std::endl;

	std::cout << "lcont(e1, e1^e2) = " << lcont(e1, e1^e2, mtr) << std::endl;
	std::cout << "lcont(e2, e1^e2) = " << lcont(e2, e1^e2, mtr) << std::endl;
	std::cout << "lcont(e1^e2, e2) = " << lcont(e1^e2, e2, mtr) << std::endl;
	std::cout << "lcont(e3, e1^e2) = " << lcont(e3, e1^e2, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "lcont(ei, ei^ej) = " << lcont(ei, ei^ej, mtr) << std::endl;
	std::cout << "lcont(ej, ei^ej) = " << lcont(ej, ei^ej, mtr) << std::endl;
	std::cout << "lcont(ei^ej, ej) = " << lcont(ei^ej, ej, mtr) << std::endl;
	std::cout << "lcont(ek, ei^ej) = " << lcont(ek, ei^ej, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "lcont(e1, e1^ej) = " << lcont(e1, e1^ej, mtr) << std::endl;
	std::cout << "lcont(ej, e1^ej) = " << lcont(ej, e1^ej, mtr) << std::endl;
	std::cout << "lcont(e1^ej, ej) = " << lcont(e1^ej, ej, mtr) << std::endl;
	std::cout << "lcont(e3, e1^ej) = " << lcont(e3, e1^ej, mtr) << std::endl;
	std::cout << std::endl;
}

template<class MetricType>
void test_rcont(metric<MetricType> const &mtr, std::string const &name) {
	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	std::cout << "--- test_rcont(" << name << ")" << std::endl;

	std::cout << "rcont(e1^e2, e1) = " << rcont(e1^e2, e1, mtr) << std::endl;
	std::cout << "rcont(e1^e2, e2) = " << rcont(e1^e2, e2, mtr) << std::endl;
	std::cout << "rcont(e2, e1^e2) = " << rcont(e2, e1^e2, mtr) << std::endl;
	std::cout << "rcont(e1^e2, e3) = " << rcont(e1^e2, e3, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "rcont(ei^ej, ei) = " << rcont(ei^ej, ei, mtr) << std::endl;
	std::cout << "rcont(ei^ej, ej) = " << rcont(ei^ej, ej, mtr) << std::endl;
	std::cout << "rcont(ej, ei^ej) = " << rcont(ej, ei^ej, mtr) << std::endl;
	std::cout << "rcont(ei^ej, ek) = " << rcont(ei^ej, ek, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "rcont(e1^ej, e1) = " << rcont(e1^ej, e1, mtr) << std::endl;
	std::cout << "rcont(e1^ej, ej) = " << rcont(e1^ej, ej, mtr) << std::endl;
	std::cout << "rcont(ej, e1^ej) = " << rcont(ej, e1^ej, mtr) << std::endl;
	std::cout << "rcont(e1^ej, e3) = " << rcont(e1^ej, e3, mtr) << std::endl;
	std::cout << std::endl;
}

template<class MetricType>
void test_gp(metric<MetricType> const &mtr, std::string const &name) {
	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	std::cout << "--- test_gp(" << name << ")" << std::endl;

	std::cout << "gp(e1, e1^e2) = " << gp(e1, e1^e2, mtr) << std::endl;
	std::cout << "gp(e2, e1^e2) = " << gp(e2, e1^e2, mtr) << std::endl;
	std::cout << "gp(e1^e2, e2) = " << gp(e1^e2, e2, mtr) << std::endl;
	std::cout << "gp(e3, e1^e2) = " << gp(e3, e1^e2, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "gp(ei, ei^ej) = " << gp(ei, ei^ej, mtr) << std::endl;
	std::cout << "gp(ej, ei^ej) = " << gp(ej, ei^ej, mtr) << std::endl;
	std::cout << "gp(ei^ej, ej) = " << gp(ei^ej, ej, mtr) << std::endl;
	std::cout << "gp(ek, ei^ej) = " << gp(ek, ei^ej, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "gp(e1, e1^ej) = " << gp(e1, e1^ej, mtr) << std::endl;
	std::cout << "gp(ej, e1^ej) = " << gp(ej, e1^ej, mtr) << std::endl;
	std::cout << "gp(e1^ej, ej) = " << gp(e1^ej, ej, mtr) << std::endl;
	std::cout << "gp(e3, e1^ej) = " << gp(e3, e1^ej, mtr) << std::endl;
	std::cout << std::endl;
}

void test_take_grade() {
	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	std::cout << "--- test_take_grade()" << std::endl;

	std::cout << "take_grade(e1, <0>) = " << take_grade(e1, c<0>) << std::endl;
	std::cout << "take_grade(e1, <1>) = " << take_grade(e1, c<1>) << std::endl;
	std::cout << "take_grade(e1, <2>) = " << take_grade(e1, c<2>) << std::endl;
	std::cout << std::endl;

	std::cout << "take_grade(e1, 0) = " << take_grade(e1, 0) << std::endl;
	std::cout << "take_grade(e1, 1) = " << take_grade(e1, 1) << std::endl;
	std::cout << "take_grade(e1, 2) = " << take_grade(e1, 2) << std::endl;
	std::cout << std::endl;

	std::cout << "take_grade(e1^e2, <0>) = " << take_grade(e1^e2, c<0>) << std::endl;
	std::cout << "take_grade(e1^e2, <1>) = " << take_grade(e1^e2, c<1>) << std::endl;
	std::cout << "take_grade(e1^e2, <2>) = " << take_grade(e1^e2, c<2>) << std::endl;
	std::cout << std::endl;

	std::cout << "take_grade(e1^e2, 0) = " << take_grade(e1^e2, 0) << std::endl;
	std::cout << "take_grade(e1^e2, 1) = " << take_grade(e1^e2, 1) << std::endl;
	std::cout << "take_grade(e1^e2, 2) = " << take_grade(e1^e2, 2) << std::endl;
	std::cout << std::endl;

	std::cout << "take_grade(ei^ej, <0>) = " << take_grade(ei^ej, c<0>) << std::endl;
	std::cout << "take_grade(ei^ej, <1>) = " << take_grade(ei^ej, c<1>) << std::endl;
	std::cout << "take_grade(ei^ej, <2>) = " << take_grade(ei^ej, c<2>) << std::endl;
	std::cout << std::endl;

	std::cout << "take_grade(ei^ej, 0) = " << take_grade(ei^ej, 0) << std::endl;
	std::cout << "take_grade(ei^ej, 1) = " << take_grade(ei^ej, 1) << std::endl;
	std::cout << "take_grade(ei^ej, 2) = " << take_grade(ei^ej, 2) << std::endl;
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
void test_metric(metric<MetricType> const &mtr, std::string const &name) {
	std::cout << "--- test_metric(" << name << ")" << std::endl;
	std::cout << "M(0, 0) = " << mtr.entry(0, 0) << std::endl;
	std::cout << "M(1, 1) = " << mtr.entry(1, 1) << std::endl;
	std::cout << "M(2, 2) = " << mtr.entry(2, 2) << std::endl;
	std::cout << "M(3, 3) = " << mtr.entry(3, 3) << std::endl;
	std::cout << "M(4, 4) = " << mtr.entry(4, 4) << std::endl;
	std::cout << "M(5, 5) = " << mtr.entry(5, 5) << std::endl;
	std::cout << "M(6, 6) = " << mtr.entry(6, 6) << std::endl;
	std::cout << "M(7, 7) = " << mtr.entry(7, 7) << std::endl;
	std::cout << "M(8, 8) = " << mtr.entry(8, 8) << std::endl;
	std::cout << std::endl;

	std::cout << "M(6, 5) = " << mtr.entry(6, 5) << std::endl;
	std::cout << std::endl;

	//std::cout << "M(<0>, <0>)" << metric<MetricType>::centry<0, 0>::value << std::endl; // Must raise a compiler error for signed_metric.
	std::cout << "M(<1>, <1>) = " << metric<MetricType>::centry<1, 1>::value << std::endl;
	std::cout << "M(<2>, <2>) = " << metric<MetricType>::centry<2, 2>::value << std::endl;
	std::cout << "M(<3>, <3>) = " << metric<MetricType>::centry<3, 3>::value << std::endl;
	std::cout << "M(<4>, <4>) = " << metric<MetricType>::centry<4, 4>::value << std::endl;
	std::cout << "M(<5>, <5>) = " << metric<MetricType>::centry<5, 5>::value << std::endl;
	std::cout << "M(<6>, <6>) = " << metric<MetricType>::centry<6, 6>::value << std::endl;
	std::cout << "M(<7>, <7>) = " << metric<MetricType>::centry<7, 7>::value << std::endl;
	std::cout << "M(<8>, <8>) = " << metric<MetricType>::centry<8, 8>::value << std::endl;
	std::cout << std::endl;

	std::cout << "M(<6>, <5>) = " << metric<MetricType>::centry<6, 5>::value << std::endl;
	std::cout << std::endl;

	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto e4 = e(c<4>);
	auto e5 = e(c<5>);
	auto e6 = e(c<6>);
	auto e7 = e(c<7>);
	auto e8 = e(c<8>);

	std::cout << "metric_factor(e1^e2) = " << metric<MetricType>::cmetric_factor<decltype(e1^e2)::element_type::basis_blade_type::value()>::value << std::endl;
	std::cout << "metric_factor(e3^e5) = " << metric<MetricType>::cmetric_factor<decltype(e3^e5)::element_type::basis_blade_type::value()>::value << std::endl;
	std::cout << "metric_factor(e5^e6) = " << metric<MetricType>::cmetric_factor<decltype(e5^e6)::element_type::basis_blade_type::value()>::value << std::endl;
	std::cout << "metric_factor(e5^e6^e7) = " << metric<MetricType>::cmetric_factor<decltype(e5^e6^e7)::element_type::basis_blade_type::value()>::value << std::endl;
	std::cout << "metric_factor(e5^e6^e7^e8) = " << metric<MetricType>::cmetric_factor<decltype(e5^e6^e7^e8)::element_type::basis_blade_type::value()>::value << std::endl;
	std::cout << std::endl;
}

int main() {
	test_make_cvalue();

	test_make_scalarc();

	test_metric(euclidean_metric_t(), "euclidean");
	test_metric(signed_metric_t<3, 4>(), "signed<3, 4>");

	test_make_e();
	test_make_ec();

	test_uplus();
	test_plus();

	test_uminus();
	test_minus();

	test_op();
	test_scp(euclidean_metric_t(), "euclidean");
	test_lcont(euclidean_metric_t(), "euclidean");
	test_rcont(euclidean_metric_t(), "euclidean");
	test_gp(euclidean_metric_t(), "euclidean");

	test_take_grade();

	test_sign_change_operations();

	auto e1 = e(1);
	auto e2 = e(2);
	auto e3 = e(3);

	auto m = 1 + e1 + e2 + e3 + (e1^e2) + (e1^e3) + (e2^e3) + (e1^e2^e3);
	std::cout << m << std::endl;

	auto v1 = c<5> * e(1) + c<5> * e(2);
	auto s1 = scp(v1, v1, euclidean_metric_t());
	std::cout << "v1 = " << v1 << std::endl;
	std::cout << "s1 = " << s1 << std::endl;
	std::cout << std::endl;

	auto v2 = 10.0 * e(1) + 10.0 * e(2);
	auto s2 = scp(v2, v2, euclidean_metric_t());
	std::cout << "v2 = " << v2 << std::endl;
	std::cout << "s2 = " << s2 << std::endl;
	std::cout << std::endl;

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
