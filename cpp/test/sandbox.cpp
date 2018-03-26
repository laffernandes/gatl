/**/
#include <ga3e.hpp>
#include <ga3c.hpp>

using namespace ga;

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
	using namespace ga3e;

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

template<class MetricSpaceType>
void test_scp(metric_space<MetricSpaceType> const &mtr, std::string const &name) {
	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	auto e1e2 = op(e1, e2, mtr);
	auto e1e3 = op(e1, e3, mtr);
	auto eiej = op(ei, ej, mtr);
	auto eiek = op(ei, ek, mtr);
	auto e1ej = op(e1, ej, mtr);

	std::cout << "--- test_scp(" << name << ")" << std::endl;

	std::cout << "scp(e1, e1^e2) = " << scp(e1, e1e2, mtr) << std::endl;
	std::cout << "scp(e1^e2, e1^e2) = " << scp(e1e2, e1e2, mtr) << std::endl;
	std::cout << "scp(e1^e3, e1^e2) = " << scp(e1e3, e1e2, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "scp(ei, ei^ej) = " << scp(ei, eiej, mtr) << std::endl;
	std::cout << "scp(ei^ej, ei^ej) = " << scp(eiej, eiej, mtr) << std::endl;
	std::cout << "scp(ei^ek, ei^ej) = " << scp(eiek, eiej, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "scp(e1, e1^ej) = " << scp(e1, e1ej, mtr) << std::endl;
	std::cout << "scp(e1^ej, e1^ej) = " << scp(e1ej, e1ej, mtr) << std::endl;
	std::cout << "scp(e1^e3, e1^ej) = " << scp(e1e3, e1ej, mtr) << std::endl;
	std::cout << std::endl;
}

template<class MetricSpaceType>
void test_lcont(metric_space<MetricSpaceType> const &mtr, std::string const &name) {
	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	auto e1e2 = op(e1, e2, mtr);
	auto e1e3 = op(e1, e3, mtr);
	auto eiej = op(ei, ej, mtr);
	auto eiek = op(ei, ek, mtr);
	auto e1ej = op(e1, ej, mtr);

	std::cout << "--- test_lcont(" << name << ")" << std::endl;

	std::cout << "lcont(e1, e1^e2) = " << lcont(e1, e1e2, mtr) << std::endl;
	std::cout << "lcont(e2, e1^e2) = " << lcont(e2, e1e2, mtr) << std::endl;
	std::cout << "lcont(e1^e2, e2) = " << lcont(e1e2, e2, mtr) << std::endl;
	std::cout << "lcont(e3, e1^e2) = " << lcont(e3, e1e2, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "lcont(ei, ei^ej) = " << lcont(ei, eiej, mtr) << std::endl;
	std::cout << "lcont(ej, ei^ej) = " << lcont(ej, eiej, mtr) << std::endl;
	std::cout << "lcont(ei^ej, ej) = " << lcont(eiej, ej, mtr) << std::endl;
	std::cout << "lcont(ek, ei^ej) = " << lcont(ek, eiej, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "lcont(e1, e1^ej) = " << lcont(e1, e1ej, mtr) << std::endl;
	std::cout << "lcont(ej, e1^ej) = " << lcont(ej, e1ej, mtr) << std::endl;
	std::cout << "lcont(e1^ej, ej) = " << lcont(e1ej, ej, mtr) << std::endl;
	std::cout << "lcont(e3, e1^ej) = " << lcont(e3, e1ej, mtr) << std::endl;
	std::cout << std::endl;
}

template<class MetricSpaceType>
void test_rcont(metric_space<MetricSpaceType> const &mtr, std::string const &name) {
	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	auto e1e2 = op(e1, e2, mtr);
	auto e1e3 = op(e1, e3, mtr);
	auto eiej = op(ei, ej, mtr);
	auto eiek = op(ei, ek, mtr);
	auto e1ej = op(e1, ej, mtr);

	std::cout << "--- test_rcont(" << name << ")" << std::endl;

	std::cout << "rcont(e1^e2, e1) = " << rcont(e1e2, e1, mtr) << std::endl;
	std::cout << "rcont(e1^e2, e2) = " << rcont(e1e2, e2, mtr) << std::endl;
	std::cout << "rcont(e2, e1^e2) = " << rcont(e2, e1e2, mtr) << std::endl;
	std::cout << "rcont(e1^e2, e3) = " << rcont(e1e2, e3, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "rcont(ei^ej, ei) = " << rcont(eiej, ei, mtr) << std::endl;
	std::cout << "rcont(ei^ej, ej) = " << rcont(eiej, ej, mtr) << std::endl;
	std::cout << "rcont(ej, ei^ej) = " << rcont(ej, eiej, mtr) << std::endl;
	std::cout << "rcont(ei^ej, ek) = " << rcont(eiej, ek, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "rcont(e1^ej, e1) = " << rcont(e1ej, e1, mtr) << std::endl;
	std::cout << "rcont(e1^ej, ej) = " << rcont(e1ej, ej, mtr) << std::endl;
	std::cout << "rcont(ej, e1^ej) = " << rcont(ej, e1ej, mtr) << std::endl;
	std::cout << "rcont(e1^ej, e3) = " << rcont(e1ej, e3, mtr) << std::endl;
	std::cout << std::endl;
}

template<class MetricSpaceType>
void test_gp(metric_space<MetricSpaceType> const &mtr, std::string const &name) {
	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	auto e1e2 = op(e1, e2, mtr);
	auto e1e3 = op(e1, e3, mtr);
	auto eiej = op(ei, ej, mtr);
	auto eiek = op(ei, ek, mtr);
	auto e1ej = op(e1, ej, mtr);

	std::cout << "--- test_gp(" << name << ")" << std::endl;

	std::cout << "gp(e1, e1^e2) = " << gp(e1, e1e2, mtr) << std::endl;
	std::cout << "gp(e2, e1^e2) = " << gp(e2, e1e2, mtr) << std::endl;
	std::cout << "gp(e1^e2, e2) = " << gp(e1e2, e2, mtr) << std::endl;
	std::cout << "gp(e3, e1^e2) = " << gp(e3, e1e2, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "gp(ei, ei^ej) = " << gp(ei, eiej, mtr) << std::endl;
	std::cout << "gp(ej, ei^ej) = " << gp(ej, eiej, mtr) << std::endl;
	std::cout << "gp(ei^ej, ej) = " << gp(eiej, ej, mtr) << std::endl;
	std::cout << "gp(ek, ei^ej) = " << gp(ek, eiej, mtr) << std::endl;
	std::cout << std::endl;

	std::cout << "gp(e1, e1^ej) = " << gp(e1, e1ej, mtr) << std::endl;
	std::cout << "gp(ej, e1^ej) = " << gp(ej, e1ej, mtr) << std::endl;
	std::cout << "gp(e1^ej, ej) = " << gp(e1ej, ej, mtr) << std::endl;
	std::cout << "gp(e3, e1^ej) = " << gp(e3, e1ej, mtr) << std::endl;
	std::cout << std::endl;
}

void test_take_grade() {
	using namespace ga3e;

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
	auto mtr = signed_metric_space<6, 1>();
	auto e1 = e(c<1>); auto e2 = e(c<2>); auto e3 = e(c<3>); auto e4 = e(c<4>); auto e5 = e(c<5>); auto e6 = e(c<6>); auto e7 = e(c<7>);

	std::cout << "--- test_sign_change_operations()" << std::endl;
	std::cout << "+ - - + + - - + = " << conjugation(1 + op(e1, (1 + op(e2, (1 + op(e3, (1 + op(e4, (1 + op(e5, (1 + op(e6, (1 + e7), mtr)), mtr)), mtr)), mtr)), mtr)), mtr)) << std::endl;
	std::cout << "+ - + - + - + - = " << involution(1 + op(e1, (1 + op(e2, (1 + op(e3, (1 + op(e4, (1 + op(e5, (1 + op(e6, (1 + e7), mtr)), mtr)), mtr)), mtr)), mtr)), mtr)) << std::endl;
	std::cout << "+ + - - + + - - = " << reversion(1 + op(e1, (1 + op(e2, (1 + op(e3, (1 + op(e4, (1 + op(e5, (1 + op(e6, (1 + e7), mtr)), mtr)), mtr)), mtr)), mtr)), mtr)) << std::endl;
	std::cout << std::endl;
}

template<class MetricSpaceType>
void test_metric(metric_space<MetricSpaceType> const &mtr, std::string const &name) {
	std::cout << "--- test_metric(" << name << ")" << std::endl;
	//std::cout << "M(0, 0) = " << mtr.metric_entry(0, 0) << std::endl; // Must raise a runtime error for all metric spaces.
	std::cout << "M(1, 1) = " << mtr.metric_entry(1, 1) << std::endl;
	std::cout << "M(2, 2) = " << mtr.metric_entry(2, 2) << std::endl;
	std::cout << "M(3, 3) = " << mtr.metric_entry(3, 3) << std::endl;
	std::cout << "M(4, 4) = " << mtr.metric_entry(4, 4) << std::endl;
	std::cout << "M(5, 5) = " << mtr.metric_entry(5, 5) << std::endl;
	std::cout << "M(6, 6) = " << mtr.metric_entry(6, 6) << std::endl;
	std::cout << "M(7, 7) = " << mtr.metric_entry(7, 7) << std::endl;
	//std::cout << "M(8, 8) = " << mtr.metric_entry(8, 8) << std::endl; // Must raise a runtime error for all metric spaces.
	std::cout << std::endl;

	std::cout << "M(6, 5) = " << mtr.metric_entry(6, 5) << std::endl;
	std::cout << std::endl;

	//std::cout << "M(<0>, <0>)" << metric_space<MetricSpaceType>::cmetric_entry<0, 0>::value << std::endl; // Must raise a compiler error for signed_metric_space.
	std::cout << "M(<1>, <1>) = " << metric_space<MetricSpaceType>::cmetric_entry<1, 1>::value << std::endl;
	std::cout << "M(<2>, <2>) = " << metric_space<MetricSpaceType>::cmetric_entry<2, 2>::value << std::endl;
	std::cout << "M(<3>, <3>) = " << metric_space<MetricSpaceType>::cmetric_entry<3, 3>::value << std::endl;
	std::cout << "M(<4>, <4>) = " << metric_space<MetricSpaceType>::cmetric_entry<4, 4>::value << std::endl;
	std::cout << "M(<5>, <5>) = " << metric_space<MetricSpaceType>::cmetric_entry<5, 5>::value << std::endl;
	std::cout << "M(<6>, <6>) = " << metric_space<MetricSpaceType>::cmetric_entry<6, 6>::value << std::endl;
	std::cout << "M(<7>, <7>) = " << metric_space<MetricSpaceType>::cmetric_entry<7, 7>::value << std::endl;
	//std::cout << "M(<8>, <8>) = " << metric_space<MetricSpaceType>::cmetric_entry<8, 8>::value << std::endl; // Must raise a compiler error for signed_metric_space.
	std::cout << std::endl;

	std::cout << "M(<6>, <5>) = " << metric_space<MetricSpaceType>::cmetric_entry<6, 5>::value << std::endl;
	std::cout << std::endl;

	{
		auto e1 = e(c<1>);
		auto e2 = e(c<2>);
		auto e3 = e(c<3>);
		auto e4 = e(c<4>);
		auto e5 = e(c<5>);
		auto e6 = e(c<6>);
		auto e7 = e(c<7>);
		auto e8 = e(c<8>);

		std::cout << "metric_factor<e1^e2>::value = " << metric_space<MetricSpaceType>::cmetric_factor<decltype(op(e1, e2, mtr))::element_type::basis_blade_type::value()>::value << std::endl;
		std::cout << "metric_factor<e3^e5>::value = " << metric_space<MetricSpaceType>::cmetric_factor<decltype(op(e3, e5, mtr))::element_type::basis_blade_type::value()>::value << std::endl;
		std::cout << "metric_factor<e5^e6>::value = " << metric_space<MetricSpaceType>::cmetric_factor<decltype(op(e5, e6, mtr))::element_type::basis_blade_type::value()>::value << std::endl;
		std::cout << "metric_factor<e5^e6^e7>::value = " << metric_space<MetricSpaceType>::cmetric_factor<decltype(op(op(e5, e6, mtr), e7, mtr))::element_type::basis_blade_type::value()>::value << std::endl;
		//std::cout << "metric_factor<e5^e6^e7^e8>::value = " << metric_space<MetricSpaceType>::cmetric_factor<decltype(e5^e6^e7^e8)::element_type::basis_blade_type::value()>::value << std::endl; // Must raise a compiler error for signed_metric_space.
		std::cout << std::endl;
	}

	{
		auto e1 = e(c<1>);
		auto e2 = e(c<2>);
		auto e3 = e(c<3>);
		auto e4 = e(c<4>);
		auto e5 = e(c<5>);
		auto e6 = e(c<6>);
		auto e7 = e(c<7>);
		auto e8 = e(c<8>);

		std::cout << "metric_factor(e1^e2) = " << mtr.metric_factor(op(e1, e2, mtr).element().basis_blade().value()) << std::endl;
		std::cout << "metric_factor(e3^e5) = " << mtr.metric_factor(op(e3, e5, mtr).element().basis_blade().value()) << std::endl;
		std::cout << "metric_factor(e5^e6) = " << mtr.metric_factor(op(e5, e6, mtr).element().basis_blade().value()) << std::endl;
		std::cout << "metric_factor(e5^e6^e7) = " << mtr.metric_factor(op(op(e5, e6, mtr), e7, mtr).element().basis_blade().value()) << std::endl;
		//std::cout << "metric_factor(e5^e6^e7^e8) = " << mtr.metric_factor((e5^e6^e7^e8).element().basis_blade().value()) << std::endl; // Must raise a runtime error for signed_metric_space.
		std::cout << std::endl;
	}
}

template<class SpaceType>
void test_pseudoscalar(space<SpaceType> const &spc, std::string const &name) {
	std::cout << "--- test_pseudoscalar(" << name << ")" << std::endl;
	std::cout << "I = " << pseudoscalar(spc) << std::endl;
	std::cout << std::endl;
}

void test_eval() {
	using namespace ga3c;

	std::cout << "--- test_eval()" << std::endl;

	auto exp0 = 5.0;
	std::cout << "exp0 = " << exp0 << std::endl;
	std::cout << "     = " << eval(exp0) << std::endl;
	std::cout << "     = " << eval(eval(exp0)) << std::endl;
	std::cout << std::endl;

	auto exp1 = 5.0 * e1 + 6 * e2;
	std::cout << "exp1 = " << exp1 << std::endl;
	std::cout << "     = " << eval(exp1) << std::endl;
	std::cout << "     = " << eval(eval(exp1)) << std::endl;
	std::cout << std::endl;

	auto exp2 = 5.0 * e(1) + 6 * e2;
	std::cout << "exp2 = " << exp2 << std::endl;
	std::cout << "     = " << eval(exp2) << std::endl;
	std::cout << "     = " << eval(eval(exp2)) << std::endl;
	std::cout << std::endl;

	auto exp3 = 5.0 * e(1) + 6 * e2 + (3 * (e1^e2));
	std::cout << "exp3 = " << exp3 << std::endl;
	std::cout << "     = " << eval(exp3) << std::endl;
	std::cout << "     = " << eval(eval(exp3)) << std::endl;
	std::cout << std::endl;

	auto exp4 = 5.0 * e(1) + 6 * e1;
	std::cout << "exp4 = " << exp4 << std::endl;
	std::cout << "     = " << eval(exp4) << std::endl;
	std::cout << "     = " << eval(eval(exp4)) << std::endl;
	std::cout << std::endl;

	auto exp5 = 5.0 * e(1) + 6 * e2 + (3 * (e1^e2)) - (7 * gp(e(1), e(2)));
	std::cout << "exp5 = " << exp5 << std::endl;
	std::cout << "     = " << eval(exp5) << std::endl;
	std::cout << "     = " << eval(eval(exp5)) << std::endl;
	std::cout << std::endl;
}

int main() {
	test_make_cvalue();

	test_make_scalarc();

	test_metric(euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>(), "euclidean");
	test_metric(signed_metric_space<3, 4>(), "signed<3, 4>");

	test_make_e();
	test_make_ec();

	test_uplus();
	test_plus();

	test_uminus();
	test_minus();

	test_op();
	test_scp(euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>(), "euclidean");
	test_lcont(euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>(), "euclidean");
	test_rcont(euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>(), "euclidean");
	test_gp(euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>(), "euclidean");

	test_take_grade();

	test_sign_change_operations();

	test_pseudoscalar(euclidean_metric_space<3>(), "euclidean<3>");
	test_pseudoscalar(euclidean_metric_space<2>(), "euclidean<2>");
	test_pseudoscalar(signed_metric_space<2, 1>(), "signed<2, 1>");

	test_eval();

	auto e1 = e(1);
	auto e2 = e(2);
	auto e3 = e(3);

	auto m = 1 + e1 + e2 + e3 + op(e1, e2, euclidean_metric_space<3>()) + op(e1, e3, euclidean_metric_space<3>()) + op(e2, e3, euclidean_metric_space<3>()) + op(op(e1, e2, euclidean_metric_space<3>()), e3, euclidean_metric_space<3>());
	std::cout << m << std::endl;

	auto v1 = c<5> * e(1) + c<5> * e(2);
	auto s1 = scp(v1, v1, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
	std::cout << "v1 = " << v1 << std::endl;
	std::cout << "s1 = " << s1 << std::endl;
	std::cout << std::endl;

	auto v2 = 10.0 * e(1) + 10.0 * e(2);
	auto s2 = scp(v2, v2, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
	std::cout << "v2 = " << v2 << std::endl;
	std::cout << "s2 = " << s2 << std::endl;
	std::cout << std::endl;

	auto e4 = e(4);
	auto e5 = e(5);
	auto e6 = e(6);

	//auto r = gp(e1^e2^e3^e4, e4^e6, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
	//
	//lcont(e(c<1>)^e(c<2>), e(c<1>)^e(c<2>)^e(c<3>)^e(c<4>), signed_metric_space<2, 1>());

	return EXIT_SUCCESS;
}
/*/
#include <ga5e.hpp>

int main() {
	using namespace ga5e;

	double x, y, z;
	std::cout << "x = "; std::cin >> x;
	std::cout << "y = "; std::cin >> y;
	std::cout << "z = "; std::cin >> z;
	std::cout << std::endl;

	auto p = (x * e1 + y * e2 + z * e3 + e4) ^ e5;
	std::cout << "p = " << p << std::endl;
	std::cout << std::endl;

	std::cout << "sizeof(empty) = " << sizeof(ga::detail::empty_expression) << std::endl;
	std::cout << "sizeof(x) = " << sizeof(decltype(x)) << std::endl;
	std::cout << "sizeof(e1) = " << sizeof(decltype(e1)) << std::endl;
	std::cout << "sizeof(p) = " << sizeof(decltype(p)) << std::endl;
	std::cout << std::endl;

	auto itr = ga::detail::begin(p);
	auto oitr = ga::detail::obegin(p);

	std::cout << "sizeof(itr) = " << sizeof(decltype(itr)) << std::endl;
	std::cout << "sizeof(oitr) = " << sizeof(decltype(oitr)) << std::endl;
	std::cout << std::endl;

	auto r = gp(p, e3);
	std::cout << "gp(p, e3) = " << r << std::endl;
	std::cout << "sizeof(gp(p, e3)) = " << sizeof(decltype(r)) << std::endl;
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
/**/
