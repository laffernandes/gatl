/**/
#include <ga3e.hpp>
#include <ga3h.hpp>
#include <ga3m.hpp>

using namespace ga;
using namespace ga::lazy;
using namespace ga::clifford;

void test_make_constant() {
	std::cout << "--- test_make_constant()" << std::endl;
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

void test_uplus() {
	std::cout << "--- test_uplus()" << std::endl;
	auto e1 = +(e(1)); std::cout << "e1 = " << e1 << std::endl;
	auto e2 = +e(c<2>); std::cout << "e2 = " << e2 << std::endl;
	std::cout << std::endl;
}

void test_uminus() {
	std::cout << "--- test_uminus()" << std::endl;
	auto e1 = -e(1); std::cout << "-e1 = " << e1 << std::endl;
	auto e2 = -e(c<2>); std::cout << "-e2 = " << e2 << std::endl;
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

		std::cout << "metric_factor<e1^e2>::value = " << metric_space<MetricSpaceType>::cmetric_factor<decltype(op(e1, e2, mtr))::element_type::basis_blade_type::get()>::value << std::endl;
		std::cout << "metric_factor<e3^e5>::value = " << metric_space<MetricSpaceType>::cmetric_factor<decltype(op(e3, e5, mtr))::element_type::basis_blade_type::get()>::value << std::endl;
		std::cout << "metric_factor<e5^e6>::value = " << metric_space<MetricSpaceType>::cmetric_factor<decltype(op(e5, e6, mtr))::element_type::basis_blade_type::get()>::value << std::endl;
		std::cout << "metric_factor<e5^e6^e7>::value = " << metric_space<MetricSpaceType>::cmetric_factor<decltype(op(op(e5, e6, mtr), e7, mtr))::element_type::basis_blade_type::get()>::value << std::endl;
		//std::cout << "metric_factor<e5^e6^e7^e8>::value = " << metric_space<MetricSpaceType>::cmetric_factor<decltype(e5^e6^e7^e8)::element_type::basis_blade_type::get()>::value << std::endl; // Must raise a compiler error for signed_metric_space.
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

		std::cout << "metric_factor(e1^e2) = " << mtr.metric_factor(op(e1, e2, mtr).element().basis_blade().get()) << std::endl;
		std::cout << "metric_factor(e3^e5) = " << mtr.metric_factor(op(e3, e5, mtr).element().basis_blade().get()) << std::endl;
		std::cout << "metric_factor(e5^e6) = " << mtr.metric_factor(op(e5, e6, mtr).element().basis_blade().get()) << std::endl;
		std::cout << "metric_factor(e5^e6^e7) = " << mtr.metric_factor(op(op(e5, e6, mtr), e7, mtr).element().basis_blade().get()) << std::endl;
		//std::cout << "metric_factor(e5^e6^e7^e8) = " << mtr.metric_factor((e5^e6^e7^e8).element().basis_blade().get()) << std::endl; // Must raise a runtime error for signed_metric_space.
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
	using namespace ga3m;

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

	auto exp6 = ((5.0 * e1 + 6 * e2) ^ (sqrt(var1(3)) * e3)) - (7.0 * (e1^e3));
	std::cout << "exp6 = " << exp6 << std::endl;
	std::cout << "     = " << eval(exp6) << std::endl;
	std::cout << "     = " << eval(eval(exp6)) << std::endl;
	std::cout << std::endl;
}

void test_simplification() {
	std::cout << "--- test_simplification()" << std::endl;

	auto A = c<2> / c<3>;
	auto B = c<4>;
	auto C = c<7> / c<5>;

	std::cout << ((A * B) * C) << std::endl;
	std::cout << (A * (B * C)) << std::endl;
	std::cout << ((A * C) * B) << std::endl;
	std::cout << (A * (C * B)) << std::endl;
	std::cout << ((B * A) * C) << std::endl;
	std::cout << (B * (A * C)) << std::endl;
	std::cout << ((B * C) * A) << std::endl;
	std::cout << (B * (C * A)) << std::endl;
	std::cout << ((C * A) * B) << std::endl;
	std::cout << (C * (A * B)) << std::endl;
	std::cout << ((C * B) * A) << std::endl;
	std::cout << (C * (B * A)) << std::endl;
	std::cout << std::endl;

	std::cout << ((A + B) + C) << std::endl;
	std::cout << (A + (B + C)) << std::endl;
	std::cout << ((A + C) + B) << std::endl;
	std::cout << (A + (C + B)) << std::endl;
	std::cout << ((B + A) + C) << std::endl;
	std::cout << (B + (A + C)) << std::endl;
	std::cout << ((B + C) + A) << std::endl;
	std::cout << (B + (C + A)) << std::endl;
	std::cout << ((C + A) + B) << std::endl;
	std::cout << (C + (A + B)) << std::endl;
	std::cout << ((C + B) + A) << std::endl;
	std::cout << (C + (B + A)) << std::endl;
	std::cout << std::endl;

	std::cout << (10.0 * (var<1>(5.0) + var<2>(3.0))) << std::endl;
	std::cout << (10.0 * c<0>) << std::endl;
	std::cout << (c<0> * 10.0) << std::endl;
	std::cout << std::endl;
}

void test_variable() {
	auto addition = [](auto const &x, auto const &y) {
		auto r = x + x + y;

		std::cout << "r = " << r << std::endl;
		std::cout << std::endl;
	};

	auto subtraction = [](auto const &x) {
		auto r = x - x;

		std::cout << "r = " << r << std::endl;
		std::cout << std::endl;
	};

	auto product = [](auto const &x, auto const &y) {
		using namespace ga3h;

		auto p = ep + x * e1 + y * e3;
		auto d = x * e1 + y * e2;
		auto r = p ^ d;

		std::cout << "p = " << p << std::endl;
		std::cout << "d = " << d << std::endl;
		std::cout << "r = " << r << std::endl;
		std::cout << std::endl;
	};

	auto span_line = [](auto const &x, auto const &y, auto const &z) {
		using namespace ga3h;

		auto p = ep + x * e1 + y * e2 + z * e3;
		auto d = x * e1 + y * e2 + z * e3;
		auto r = p ^ d;

		std::cout << "p = " << p << std::endl;
		std::cout << "d = " << d << std::endl;
		std::cout << "r = " << r << std::endl;
		std::cout << std::endl;
	};

	std::cout << "--- test_variable()" << std::endl;

	addition(5.0, 3.0);
	addition(var1(5.0), var2(3.0));

	subtraction(5.0);
	subtraction(var1(5.0));

	product(5.0, 3.0);
	product(var1(5.0), var2(3.0));

	span_line(10.0, 5.0, -7.0);
	span_line(var1(10.0), var2(5.0), var3(-7.0));
}

int main() {
	test_make_constant();

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

	test_simplification();
	
	test_variable();

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

	auto xxx = (c<4> * ((var<1>(3) * e(c<1>) * c<5>) * c<2>)) * (var<2>(5) + var<1>(10));
	std::cout << xxx << std::endl;
	std::cout << eval(xxx) << std::endl;
	std::cout << std::endl;

	auto yyy = (c<4> +((var<1>(3) * e(c<1>) * c<5>) + c<2>)) * (var<2>(5) + var<1>(10));
	std::cout << yyy << std::endl;
	std::cout << eval(yyy) << std::endl;
	std::cout << std::endl;

	{
		using namespace ga3e;

		auto copy_in  = 5  + 3  * ga3e::e1 + 7  * (ga3e::e1^ga3e::e2);
		std::cout << " in = " << copy_in << std::endl;

		auto copy_out = 0. + 0. * ga3e::e1 + 0. * (ga3e::e1^ga3e::e2) + 10. * ga3e::e2;
		std::cout << "out = " << copy_out << std::endl;

		copy_out = copy_in;
		std::cout << "out = " << copy_out << std::endl;

		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}
/*/
#include <ga5e.hpp>

int main() {
	using namespace ga5e;

	auto x1 = c<5> + pow(c<2>, c<10>);
	auto x2 = val(5.0);
	auto x3 = var<1>(5.0) + var<2>(7.0);
	auto x4 = c<5> + sqrt(var<3>(7.0));
	auto x5 = c<5> + sqrt(c<7>) + cbrt(c<11>);
	std::cout << "size(x1) = " << sizeof(decltype(x1)) << "\t x1 = " << x1 << std::endl;
	std::cout << "size(x2) = " << sizeof(decltype(x2)) << "\t x2 = " << x2 << std::endl;
	std::cout << "size(x3) = " << sizeof(decltype(x3)) << "\t x3 = " << x3 << std::endl;
	std::cout << "size(x4) = " << sizeof(decltype(x4)) << "\t x4 = " << x4 << std::endl;
	std::cout << "size(x5) = " << sizeof(decltype(x5)) << "\t x5 = " << x5 << std::endl;
	std::cout << std::endl;

	auto y12 = x1 + x2;
	auto y13 = x1 + x3;
	auto y23 = x2 + x3;
	std::cout << "size(y12) = " << sizeof(decltype(y12)) << "\t y12 = " << y12 << std::endl;
	std::cout << "size(y13) = " << sizeof(decltype(y13)) << "\t y13 = " << y13 << std::endl;
	std::cout << "size(y23) = " << sizeof(decltype(y23)) << "\t y23 = " << y23 << std::endl;
	std::cout << std::endl;

	auto z12 = x1 * x2;
	auto z13 = x1 * x3;
	auto z23 = x2 * x3;
	std::cout << "size(z12) = " << sizeof(decltype(z12)) << "\t z12 = " << z12 << std::endl;
	std::cout << "size(z13) = " << sizeof(decltype(z13)) << "\t z13 = " << z13 << std::endl;
	std::cout << "size(z23) = " << sizeof(decltype(z23)) << "\t z23 = " << z23 << std::endl;
	std::cout << std::endl;

	std::cout << "size(sqrt(x1)) = " << sizeof(decltype(sqrt(x1))) << "\t sqrt(x1) = " << sqrt(x1) << std::endl;
	std::cout << "size(sqrt(x2)) = " << sizeof(decltype(sqrt(x2))) << "\t sqrt(x2) = " << sqrt(x2) << std::endl;
	std::cout << "size(sqrt(x3)) = " << sizeof(decltype(sqrt(x3))) << "\t sqrt(x3) = " << sqrt(x3) << std::endl;
	std::cout << std::endl;

	std::cout << "size(sqrt(<8>)) = " << sizeof(decltype(sqrt(c<8>))) << "\t sqrt(<8>) = " << sqrt(c<8>) << std::endl;
	std::cout << "size(sqrt(<4>)) = " << sizeof(decltype(sqrt(c<4>))) << "\t sqrt(<4>) = " << sqrt(c<4>) << std::endl;
	std::cout << "size(sqrt(<-4>)) = " << sizeof(decltype(sqrt(c<-4>))) << "\t sqrt(<4>) = " << sqrt(c<-4>) << std::endl;
	std::cout << std::endl;

	double x, y, z;
	std::cout << "x = "; std::cin >> x;
	std::cout << "y = "; std::cin >> y;
	std::cout << "z = "; std::cin >> z;
	std::cout << std::endl;

	auto p = (x * e1 + y * e2 + z * e3 + e4) ^ e5;
	std::cout << "p = " << p << std::endl;
	std::cout << std::endl;

	std::cout << "sizeof(x) = " << sizeof(decltype(x)) << std::endl;
	std::cout << "sizeof(e1) = " << sizeof(decltype(e1)) << std::endl;
	std::cout << "sizeof(e1 + e2 + e3) = " << sizeof(decltype(e1 + e2 + e3)) << std::endl;
	std::cout << "sizeof(p) = " << sizeof(decltype(p)) << std::endl;
	std::cout << std::endl;

	auto itr = ga::clifford::detail::begin(p);
	auto oitr = ga::clifford::detail::obegin(p);

	std::cout << "sizeof(itr) = " << sizeof(decltype(itr)) << std::endl;
	std::cout << "sizeof(oitr) = " << sizeof(decltype(oitr)) << std::endl;
	std::cout << std::endl;

	auto r = gp(p, e3);
	std::cout << "gp(p, e3) = " << r << std::endl;
	std::cout << "sizeof(gp(p, e3)) = " << sizeof(decltype(r)) << std::endl;
	std::cout << std::endl;

#if defined(GA_USE_CLIFFORD_EXPRESSION_TREE)
	typedef decltype(e(c<1>) + 3.0 * e(c<2>)) root;
	std::cout << "root = " << sizeof(root) << " bytes" << std::endl;
	std::cout << "root::element_type = " << sizeof(root::element_type) << " bytes" << std::endl;
	std::cout << "root::left_type = " << sizeof(root::left_type) << " bytes" << std::endl;
	std::cout << "root::right_type = " << sizeof(root::right_type) << " bytes" << std::endl;
#endif

	std::cout << "p = " << p << std::endl;
	std::cout << "var<1, 9>(p) = " << ga::lazy::var<1, 9>(p) << std::endl;
	std::cout << "sizeof(p) = " << sizeof(p) << std::endl;
	std::cout << "sizeof(var<1, 9>(p)) = " << sizeof(ga::lazy::var<1, 9>(p)) << std::endl;
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
/**/

//#include <ga.hpp>
//#include <ga/macro_for_algebra_overload.hpp>
//
////#define K 0
////#define N 1
//
////#define K 0
////#define K 1
////#define N 2
//
////#define K 0
////#define K 1
////#define K 2
////#define N 3
//
////#define K 0
////#define K 1
//#define K 2
////#define K 3
//#define N 4
//
//GA_SIGNED_ALGEBRA_OVERLOAD(dummy, N + 1, 1)
//
//using namespace dummy;
//
//static auto const ep = e(c<N + 1>);
//static auto const em = e(c<N + 2>);
//
//static auto const no = (em - ep) / c<2>;
//static auto const ni = ep + em;
//
//template<std::size_t Index>
//decltype(auto) _euclidean_vector_impl(double(&coeffs)[N]) {
//	return _euclidean_vector_impl<Index - 1>(coeffs)  + coeffs[Index - 1] * e(c<Index>);
//}
//
//template<>
//decltype(auto) _euclidean_vector_impl<0>(double(&coeffs)[N]) {
//	return ga::lazy::constant<0>();
//}
//
//decltype(auto) euclidean_vector(double(&coeffs)[N]) {
//	return _euclidean_vector_impl<N>(coeffs);
//}
//
//decltype(auto) point(double(&coeffs)[N]) {
//	auto v = euclidean_vector(coeffs);
//	return no + v + (scp(v, v) / c<2>) * ni;
//}
//
//template<std::size_t Index>
//decltype(auto) kdirection() {
//	return op(kdirection<Index - 1>(), e(c<Index>));
//}
//
//template<>
//decltype(auto) kdirection<0>() {
//	return c<1>;
//}
//
//template<class PointType, class RadiusType, class DirectionType>
//decltype(auto) ksphere(PointType const &p, RadiusType const &r, DirectionType const &d) {
//	return op(p + ((r * r) / c<2>) * ni, lcont(-p, op(involution(d), ni)));
//}
//
//template<class RoundType>
//decltype(auto) radius(RoundType const &x) {
//	auto aux = lcont(ni, x);
//	return native(scp(x, involution(x)) / scp(aux, aux));
//}
//
//template<class RoundType>
//decltype(auto) sign(RoundType const &x) {
//	return native(-scp(x, reversion(x)));
//}
//
//int main() {
//	double coeffs[N] = { -8.0 };
//	auto s = dual(-3 * ksphere(point(coeffs), 5.0, kdirection<K + 1>()));
//
//	std::cout << K << "-sphere = " << s << std::endl;
//	std::cout << std::endl;
//	std::cout << "radius^{2} = " << radius(s) << std::endl;
//	std::cout << std::endl;
//
//	std::cout << "      sign = " << sign(s) << std::endl;
//	std::cout << std::endl;
//
//	return EXIT_SUCCESS;
//}
