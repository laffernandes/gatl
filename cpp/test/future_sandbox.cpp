/**
#include <future/ga.hpp>
#include <future/ga3e.hpp>
#include <future/ga3h.hpp>
#include <future/ga3m.hpp>

using namespace future::ga;

void test_make_constant() {
	std::cout << "--- test_make_constant()" << std::endl;
	constexpr auto x = c<5>;
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
void test_pseudoscalar(metric_space<MetricSpaceType> const &spc, std::string const &name) {
	std::cout << "--- test_pseudoscalar(" << name << ")" << std::endl;
	std::cout << "I = " << pseudoscalar(spc) << std::endl;
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

	auto const lazy = make_lazy_context(scalar(10.0), scalar(5.0), scalar(3.0));
	std::cout << lazy.eval(lazy.argument<0>() * (lazy.argument<1>() + lazy.argument<2>())) << std::endl;
	std::cout << lazy.eval(lazy.argument<0>() * c<0>) << std::endl;
	std::cout << lazy.eval(c<0> * lazy.argument<0>()) << std::endl;
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

	auto const lazy = make_lazy_context(scalar(5.0), scalar(3.0), scalar(10.0), scalar(-7.0));

	addition(5.0, 3.0);
	addition(lazy.argument<0>(), lazy.argument<1>());

	subtraction(5.0);
	subtraction(lazy.argument<0>());

	product(5.0, 3.0);
	product(lazy.argument<0>(), lazy.argument<1>());

	span_line(10.0, 5.0, -7.0);
	span_line(lazy.argument<2>(), lazy.argument<0>(), lazy.argument<3>());
}

int main() {
	test_make_constant();

	test_make_scalarc();

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

	auto const lazy = make_lazy_context(scalar(3), scalar(10), scalar(5));
	
	auto xxx = (c<4> * ((lazy.argument<0>() * e(c<1>) * c<5>) * c<2>)) * (lazy.argument<2>() + lazy.argument<1>());
	std::cout << lazy.eval(xxx) << std::endl;
	std::cout << std::endl;

	auto yyy = (c<4> + ((lazy.argument<0>() * e(c<1>) * c<5>) + c<2>)) * (lazy.argument<2>() + lazy.argument<1>());
	std::cout << lazy.eval(yyy) << std::endl;
	std::cout << std::endl;

	{
		using namespace ga3e;

		auto copy_in = 5 + 3 * ga3e::e1 + 7 * (ga3e::e1^ga3e::e2);
		std::cout << " in = " << copy_in << std::endl;

		auto copy_out = 0. + 0. * ga3e::e1 + 0. * (ga3e::e1^ga3e::e2) + 10. * ga3e::e2;
		std::cout << "out = " << copy_out << std::endl;

		//TODO Implementar
		//copy_out = copy_in;
		//std::cout << "out = " << copy_out << std::endl;

		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}
/*/
#include <future/ga.hpp>

int main() {
	using namespace future::ga;

	auto xxx = detail::gp_mapping::possible_grades_result<1, 2, GA_MAX_BASIS_VECTOR_INDEX>::value;
	
	auto a = c<5> * e(1);
	auto b = c<5> * e(2);

	auto v1 = a + b;
	auto s1 = scp(v1, v1, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());

	return EXIT_SUCCESS;
}
/**/
