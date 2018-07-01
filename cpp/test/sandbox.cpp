/**/
#include <ga.hpp>

#include <ga1e.hpp>
#include <ga1h.hpp>
#include <ga1m.hpp>
#include <ga1c.hpp>

#include <ga2e.hpp>
#include <ga2h.hpp>
#include <ga2m.hpp>
#include <ga2c.hpp>

#include <ga3e.hpp>
#include <ga3h.hpp>
#include <ga3m.hpp>
#include <ga3c.hpp>

#include <ga4e.hpp>
#include <ga4h.hpp>

#include <ga5e.hpp>

using namespace ga;

void test_make_constant() {
	using namespace ga3e;

	auto v = euclidean_vector(c<0>, c<0>, 10.5);
	std::cout << v << std::endl;

	std::cout << "--- test_make_constant()" << std::endl;
	constexpr auto x = c<5>;
	std::cout << "5 = " << x << std::endl;
	std::cout << std::endl;
}

void test_make_scalarc() {
	using namespace ga3e;

	std::cout << "--- test_make_scalarc()" << std::endl;
	std::cout << "5 = " << c<5> << std::endl;
	auto nine = c<9>; std::cout << "9 = " << nine << std::endl;
	std::cout << std::endl;
}

decltype(auto) test_make_ek_func(index_t k) {
	return e(k);
}

void test_make_e() {
	using namespace ga5e;

	std::cout << "--- test_make_e()" << std::endl;
	std::cout << "e1 = " << e(1) << std::endl;
	std::cout << "e3 = " << e(3) << std::endl;
	std::cout << "e1 = " << test_make_ek_func(1) << std::endl;
	std::cout << "e3 = " << test_make_ek_func(3) << std::endl;
	auto e1 = e(1); std::cout << "e1 = " << e1 << std::endl;
	volatile index_t i = 5; std::cout << "e5 = " << e(i) << std::endl;
	std::cout << std::endl;
}

void test_make_ec() {
	using namespace ga3e;

	std::cout << "--- test_make_ec()" << std::endl;
	std::cout << "e1 = " << e(c<1>) << std::endl;
	std::cout << "e3 = " << e(c<3>) << std::endl;
	auto e1 = e(c<1>); std::cout << "e1 = " << e1 << std::endl;
	std::cout << std::endl;
}

void test_uplus() {
	using namespace ga3e;

	std::cout << "--- test_uplus()" << std::endl;
	auto e1 = +(e(1)); std::cout << "e1 = " << e1 << std::endl;
	auto e2 = +e(c<2>); std::cout << "e2 = " << e2 << std::endl;
	std::cout << std::endl;
}

void test_uminus() {
	using namespace ga3e;

	std::cout << "--- test_uminus()" << std::endl;
	auto e1 = -e(1); std::cout << "-e1 = " << e1 << std::endl;
	auto e2 = -e(c<2>); std::cout << "-e2 = " << e2 << std::endl;
	std::cout << std::endl;
}

void test_plus() {
	using namespace ga3e;

	std::cout << "--- test_plus()" << std::endl;
	std::cout << "e1 + e2 = " << (e(c<1>) + e(c<2>)) << std::endl;
	std::cout << "5 + 2 * e1 + e2 = " << (c<5> + e(c<1>) + e(c<2>) + e(c<1>)) << std::endl;
	std::cout << "5 + e1 + e2 = " << (5.0 + e(c<1>) + e(c<2>)) << std::endl;
	std::cout << "5 + 3 * e1 + e2 = " << (e(c<1>) + 5.0 + e(c<1>) + e(c<2>) + e(c<1>)) << std::endl;
	std::cout << std::endl;
}

void test_minus() {
	using namespace ga3e;

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
	std::cout << "e3^e3 = " << (e3 ^ e3) << std::endl;
	std::cout << "e3^(e3 + e1^e2) = " << (e3 ^ (e3 + (e1 ^ e2))) << std::endl;
	std::cout << std::endl;

	std::cout << "ei^ej = " << (ei ^ ej) << std::endl;
	std::cout << "ej^ei = " << (ej ^ ei) << std::endl;
	std::cout << "ek^ek = " << (ek ^ ek) << std::endl;
	auto xyz = (ek ^ (ek + (ei ^ ej)));
	std::cout << "ek^(ek + ei^ej) = " << xyz << std::endl;
	std::cout << std::endl;

	std::cout << "e1^ej = " << (e1 ^ ej) << std::endl;
	std::cout << "ej^e1 = " << (ej ^ e1) << std::endl;
	std::cout << "e3^(e3 + e1^ej) = " << (e3 ^ (e3 + (e1 ^ ej))) << std::endl;
	std::cout << std::endl;
}

void test_sp() {
	using namespace ga3e;

	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	auto eval = [&](auto const &arg) -> decltype(auto) {
		return arg;
	};

//	auto lazy = make_lazy_context(e(c<1>), e(c<2>), e(c<3>), e(1), e(2), e(3));
//	
//	auto e1 = lazy.argument<0>();
//	auto e2 = lazy.argument<1>();
//	auto e3 = lazy.argument<2>();
//	auto ei = lazy.argument<3>();
//	auto ej = lazy.argument<4>();
//	auto ek = lazy.argument<5>();
//	
//	auto eval = [&](auto const &arg) -> decltype(auto) {
//		return lazy.eval(arg);
//	};

	auto e1e2 = op(e1, e2);
	auto e1e3 = op(e1, e3);
	auto eiej = op(ei, ej);
	auto eiek = op(ei, ek);
	auto e1ej = op(e1, ej);

	std::cout << "--- test_sp(ga3e)" << std::endl;

	std::cout << "sp(e1, e1^e2) = " << eval(sp(e1, e1e2)) << std::endl;
	std::cout << "sp(e1^e2, e1^e2) = " << eval(sp(e1e2, e1e2)) << std::endl;
	std::cout << "sp(e1^e3, e1^e2) = " << eval(sp(e1e3, e1e2)) << std::endl;
	std::cout << std::endl;

	std::cout << "sp(ei, ei^ej) = " << eval(sp(ei, eiej)) << std::endl;
	std::cout << "sp(ei^ej, ei^ej) = " << eval(sp(eiej, eiej)) << std::endl;
	std::cout << "sp(ei^ek, ei^ej) = " << eval(sp(eiek, eiej)) << std::endl;
	std::cout << std::endl;

	std::cout << "sp(e1, e1^ej) = " << eval(sp(e1, e1ej)) << std::endl;
	std::cout << "sp(e1^ej, e1^ej) = " << eval(sp(e1ej, e1ej)) << std::endl;
	std::cout << "sp(e1^e3, e1^ej) = " << eval(sp(e1e3, e1ej)) << std::endl;
	std::cout << std::endl;
}

void test_lcont() {
	using namespace ga3e;

	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	auto e1e2 = op(e1, e2);
	auto e1e3 = op(e1, e3);
	auto eiej = op(ei, ej);
	auto eiek = op(ei, ek);
	auto e1ej = op(e1, ej);

	std::cout << "--- test_lcont(ga3e)" << std::endl;

	std::cout << "lcont(e1, e1^e2) = " << lcont(e1, e1e2) << std::endl;
	std::cout << "lcont(e2, e1^e2) = " << lcont(e2, e1e2) << std::endl;
	std::cout << "lcont(e1^e2, e2) = " << lcont(e1e2, e2) << std::endl;
	std::cout << "lcont(e3, e1^e2) = " << lcont(e3, e1e2) << std::endl;
	std::cout << std::endl;

	std::cout << "lcont(ei, ei^ej) = " << lcont(ei, eiej) << std::endl;
	std::cout << "lcont(ej, ei^ej) = " << lcont(ej, eiej) << std::endl;
	std::cout << "lcont(ei^ej, ej) = " << lcont(eiej, ej) << std::endl;
	std::cout << "lcont(ek, ei^ej) = " << lcont(ek, eiej) << std::endl;
	std::cout << std::endl;

	std::cout << "lcont(e1, e1^ej) = " << lcont(e1, e1ej) << std::endl;
	std::cout << "lcont(ej, e1^ej) = " << lcont(ej, e1ej) << std::endl;
	std::cout << "lcont(e1^ej, ej) = " << lcont(e1ej, ej) << std::endl;
	std::cout << "lcont(e3, e1^ej) = " << lcont(e3, e1ej) << std::endl;
	std::cout << std::endl;
}

void test_rcont() {
	using namespace ga3e;

	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	auto e1e2 = op(e1, e2);
	auto e1e3 = op(e1, e3);
	auto eiej = op(ei, ej);
	auto eiek = op(ei, ek);
	auto e1ej = op(e1, ej);

	std::cout << "--- test_rcont(ga3e)" << std::endl;

	std::cout << "rcont(e1^e2, e1) = " << rcont(e1e2, e1) << std::endl;
	std::cout << "rcont(e1^e2, e2) = " << rcont(e1e2, e2) << std::endl;
	std::cout << "rcont(e2, e1^e2) = " << rcont(e2, e1e2) << std::endl;
	std::cout << "rcont(e1^e2, e3) = " << rcont(e1e2, e3) << std::endl;
	std::cout << std::endl;

	std::cout << "rcont(ei^ej, ei) = " << rcont(eiej, ei) << std::endl;
	std::cout << "rcont(ei^ej, ej) = " << rcont(eiej, ej) << std::endl;
	std::cout << "rcont(ej, ei^ej) = " << rcont(ej, eiej) << std::endl;
	std::cout << "rcont(ei^ej, ek) = " << rcont(eiej, ek) << std::endl;
	std::cout << std::endl;

	std::cout << "rcont(e1^ej, e1) = " << rcont(e1ej, e1) << std::endl;
	std::cout << "rcont(e1^ej, ej) = " << rcont(e1ej, ej) << std::endl;
	std::cout << "rcont(ej, e1^ej) = " << rcont(ej, e1ej) << std::endl;
	std::cout << "rcont(e1^ej, e3) = " << rcont(e1ej, e3) << std::endl;
	std::cout << std::endl;
}

void test_gp() {
	using namespace ga3e;

	auto e1 = e(c<1>);
	auto e2 = e(c<2>);
	auto e3 = e(c<3>);
	auto ei = e(1);
	auto ej = e(2);
	auto ek = e(3);

	auto e1e2 = op(e1, e2);
	auto e1e3 = op(e1, e3);
	auto eiej = op(ei, ej);
	auto eiek = op(ei, ek);
	auto e1ej = op(e1, ej);

	std::cout << "--- test_gp(ga3e)" << std::endl;

	std::cout << "gp(e1, e1^e2) = " << gp(e1, e1e2) << std::endl;
	std::cout << "gp(e2, e1^e2) = " << gp(e2, e1e2) << std::endl;
	std::cout << "gp(e1^e2, e2) = " << gp(e1e2, e2) << std::endl;
	std::cout << "gp(e3, e1^e2) = " << gp(e3, e1e2) << std::endl;
	std::cout << std::endl;

	std::cout << "gp(ei, ei^ej) = " << gp(ei, eiej) << std::endl;
	std::cout << "gp(ej, ei^ej) = " << gp(ej, eiej) << std::endl;
	std::cout << "gp(ei^ej, ej) = " << gp(eiej, ej) << std::endl;
	std::cout << "gp(ek, ei^ej) = " << gp(ek, eiej) << std::endl;
	std::cout << std::endl;

	std::cout << "gp(e1, e1^ej) = " << gp(e1, e1ej) << std::endl;
	std::cout << "gp(ej, e1^ej) = " << gp(ej, e1ej) << std::endl;
	std::cout << "gp(e1^ej, ej) = " << gp(e1ej, ej) << std::endl;
	std::cout << "gp(e3, e1^ej) = " << gp(e3, e1ej) << std::endl;
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
	std::array<std::string, 7> const basis_vectors = { "e1", "e2", "e3", "e4", "e5", "e6", "e7" };
	auto e1 = e(c<1>); auto e2 = e(c<2>); auto e3 = e(c<3>); auto e4 = e(c<4>); auto e5 = e(c<5>); auto e6 = e(c<6>); auto e7 = e(c<7>);

	std::cout << "--- test_sign_change_operations()" << std::endl;
	std::cout << "+ - - + + - - + = "; write(std::cout, conjugation(1 + op(e1, (1 + op(e2, (1 + op(e3, (1 + op(e4, (1 + op(e5, (1 + op(e6, (1 + e7), mtr)), mtr)), mtr)), mtr)), mtr)), mtr)), basis_vectors) << std::endl;
	std::cout << "+ - + - + - + - = "; write(std::cout, involution(1 + op(e1, (1 + op(e2, (1 + op(e3, (1 + op(e4, (1 + op(e5, (1 + op(e6, (1 + e7), mtr)), mtr)), mtr)), mtr)), mtr)), mtr)), basis_vectors) << std::endl;
	std::cout << "+ + - - + + - - = "; write(std::cout, reversion(1 + op(e1, (1 + op(e2, (1 + op(e3, (1 + op(e4, (1 + op(e5, (1 + op(e6, (1 + e7), mtr)), mtr)), mtr)), mtr)), mtr)), mtr)), basis_vectors) << std::endl;
	std::cout << std::endl;
}

template<typename MetricSpaceType, std::size_t N>
void test_pseudoscalar(metric_space<MetricSpaceType> const &spc, std::string const &name, std::array<std::string, N> const &basis_vectors) {
	std::cout << "--- test_pseudoscalar(" << name << ")" << std::endl;
	std::cout << "I = "; write(std::cout, pseudoscalar(spc), basis_vectors) << std::endl;
	std::cout << std::endl;
}

void test_simplification() {
	using namespace ga3e;

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
	auto addition = [](auto const &x, auto const &y, auto eval) {
		using namespace ga3h;

		auto r = x + x + y;

		std::cout << "r = " << eval(r) << std::endl;
		std::cout << std::endl;
	};

	auto subtraction = [](auto const &x, auto eval) {
		using namespace ga3h;

		auto r = x - x;

		std::cout << "r = " << eval(r) << std::endl;
		std::cout << std::endl;
	};

	auto product = [](auto const &x, auto const &y, auto eval) {
		using namespace ga3h;

		auto p = ep + x * e1 + y * e3;
		auto d = x * e1 + y * e2;
		auto r = p ^ d;

		std::cout << "p = " << eval(p) << std::endl;
		std::cout << "d = " << eval(d) << std::endl;
		std::cout << "r = " << eval(r) << std::endl;
		std::cout << std::endl;
	};

	auto span_line = [](auto const &x, auto const &y, auto const &z, auto eval) {
		using namespace ga3h;

		auto p = ep + x * e1 + y * e2 + z * e3;
		auto d = x * e1 + y * e2 + z * e3;
		auto r = p ^ d;

		std::cout << "p = " << eval(p) << std::endl;
		std::cout << "d = " << eval(d) << std::endl;
		std::cout << "r = " << eval(r) << std::endl;
		std::cout << std::endl;
	};

	std::cout << "--- test_variable()" << std::endl;

	auto const lazy = make_lazy_context(scalar(5.0), scalar(3.0), scalar(10.0), scalar(-7.0));
	auto eval = [&](auto const &arg) -> decltype(auto) { return arg; };
	auto lazy_eval = [&](auto const &arg) -> decltype(auto) { return lazy.eval(arg); };

	addition(5.0, 3.0, eval);
	addition(lazy.argument<0>(), lazy.argument<1>(), lazy_eval);

	subtraction(5.0, eval);
	subtraction(lazy.argument<0>(), lazy_eval);

	product(5.0, 3.0, eval);
	product(lazy.argument<0>(), lazy.argument<1>(), lazy_eval);

	span_line(10.0, 5.0, -7.0, eval);
	span_line(lazy.argument<2>(), lazy.argument<0>(), lazy.argument<3>(), lazy_eval);
}

void test_grade() {
	using namespace ga3e;

	std::cout << "--- test_grade()" << std::endl;

	std::cout << "grade(c<0>) = " << grade(c<0>) << std::endl;
	std::cout << "grade(8.0) = " << grade(8.0) << std::endl;
	std::cout << "grade(c<1>) = " << grade(c<1>) << std::endl;
	std::cout << "grade(e1) = " << grade(e1) << std::endl;
	std::cout << "grade(c<5> - e1) = " << grade(c<5, double> - e1) << std::endl;
	std::cout << "grade(5.0 - e1) = " << grade(5.0 - e1) << std::endl;
	std::cout << "grade(e1^e2) = " << grade(e1^e2) << std::endl;
	std::cout << "grade(e1^e2 + e1^e3) = " << grade((e1^e2) + (e1^e3)) << std::endl;
	std::cout << "grade(e(1)^e2 + e1^e3) = " << grade((e(1)^e2) + (e1^e3)) << std::endl;
	std::cout << "grade(9.0 * e1^e2 + e1^e3) = " << grade((9.0 * e1^e2) + (e1^e3)) << std::endl;
	std::cout << "grade(9 * e(1)^e2 + e1^e3) = " << grade((9 * e(1)^e2) + (e1^e3)) << std::endl;

	std::cout << std::endl;
}

void test_general_metric() {
	std::cout << "--- test_general_metric()" << std::endl;
	std::cout << std::endl;

	double p1 = 5.0;
	double p2 = 2.0;
	double p3 = -4.5;

	double q1 = 10.0;
	double q2 = -5.0;
	double q3 = 3.0;

	{
		using namespace ga3m;

		auto vp = p1 * e1 + p2 * e2 + p3 * e3;
		auto p = no + vp + (sp(vp, vp) / c<2>) * ni;

		auto vq = q1 * e1 + q2 * e2 + q3 * e3;
		auto q = no + vq + (sp(vq, vq) / c<2>) * ni;

		std::cout << "ga3m" << std::endl;
		std::cout << "------------------------------------------------------------------------" << std::endl;
		std::cout << "p = " << p << std::endl;
		std::cout << "q = " << q << std::endl;
		std::cout << std::endl;
		std::cout << "sp(vp, vp) = " << sp(vp, vp) << std::endl;
		std::cout << std::endl;
		std::cout << "gp(p, p) = " << gp(p, p) << std::endl;
		std::cout << "gp(p, q) = " << gp(p, q) << std::endl;
		std::cout << "gp(p, no) = " << gp(p, no) << std::endl;
		std::cout << "gp(q, no) = " << gp(q, no) << std::endl;

		std::cout << std::endl;
		auto xxx = gp(p, q);
		std::cout << sp(xxx, e1^e2) << std::endl;
		std::cout << sp(xxx, e1^e3) << std::endl;
		std::cout << sp(xxx, e1^no) << std::endl;
		std::cout << sp(xxx, e1^ni) << std::endl;
		std::cout << sp(xxx, e2^e3) << std::endl;
		std::cout << sp(xxx, e2^no) << std::endl;
		std::cout << sp(xxx, e2^ni) << std::endl;
		std::cout << sp(xxx, e3^no) << std::endl;
		std::cout << sp(xxx, e3^ni) << std::endl;
		std::cout << sp(xxx, no^ni) << std::endl;
	}

	std::cout << std::endl;

	{
		using namespace ga3c;

		typedef conformal_metric_space<3> GeneralMetricSpace;
		typedef detail::general_metric_mapping<GeneralMetricSpace, detail::gp_mapping> mappping;
		typedef mappping::multiply<detail::basis_blade_t<decltype(e1)::expression_type>, detail::basis_blade_t<decltype(e2)::expression_type> > e1e2;

		auto vp = p1 * e1 + p2 * e2 + p3 * e3;
		auto test = sp(vp, vp);

		auto p = no + vp + (sp(vp, vp) / c<2>) * ni;

		auto vq = q1 * e1 + q2 * e2 + q3 * e3;
		auto q = no + vq + (sp(vq, vq) / c<2>) * ni;

		std::cout << "ga3c" << std::endl;
		std::cout << "------------------------------------------------------------------------" << std::endl;
		std::cout << "p = " << p << std::endl;
		std::cout << "q = " << q << std::endl;
		std::cout << std::endl;
		std::cout << "sp(vp, vp) = " << sp(vp, vp) << std::endl;
		std::cout << std::endl;
		std::cout << "gp(p, p) = " << gp(p, p) << std::endl;
		std::cout << "gp(p, q) = " << gp(p, q) << std::endl;
		std::cout << "gp(p, no) = " << gp(p, no) << std::endl;
		std::cout << "gp(q, no) = " << gp(q, no) << std::endl;
	
		std::cout << std::endl;
		auto xxx = gp(p, q);
		std::cout << sp(xxx, e1^e2) << std::endl;
		std::cout << sp(xxx, e1^e3) << std::endl;
		std::cout << sp(xxx, e1^no) << std::endl;
		std::cout << sp(xxx, e1^ni) << std::endl;
		std::cout << sp(xxx, e2^e3) << std::endl;
		std::cout << sp(xxx, e2^no) << std::endl;
		std::cout << sp(xxx, e2^ni) << std::endl;
		std::cout << sp(xxx, e3^no) << std::endl;
		std::cout << sp(xxx, e3^ni) << std::endl;
		std::cout << sp(xxx, no^ni) << std::endl;
	}

	std::cout << std::endl;
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
	test_sp();
	test_lcont();
	test_rcont();
	test_gp();

	test_take_grade();

	test_sign_change_operations();

	test_pseudoscalar(euclidean_metric_space<3>(), "euclidean<3>", std::array<std::string, 3>{ "e1", "e2", "e3" });
	test_pseudoscalar(euclidean_metric_space<2>(), "euclidean<2>", std::array<std::string, 2>{ "e1", "e2" });
	test_pseudoscalar(signed_metric_space<2, 1>(), "signed<2, 1>", std::array<std::string, 3>{ "e1", "e2", "em" });

	test_simplification();

	test_variable();

	test_grade();

	test_general_metric();

	{
		using namespace ga3e;

		auto e1 = e(1);
		auto e2 = e(2);
		auto e3 = e(3);

		auto m = 1 + e1 + e2 + e3 + op(e1, e2, euclidean_metric_space<3>()) + op(e1, e3, euclidean_metric_space<3>()) + op(e2, e3, euclidean_metric_space<3>()) + op(op(e1, e2, euclidean_metric_space<3>()), e3, euclidean_metric_space<3>());
		std::cout << m << std::endl;

		auto v1 = c<5> * e(1) + c<5> * e(2);
		auto s1 = sp(v1, v1, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		std::cout << "v1 = " << v1 << std::endl;
		std::cout << "s1 = " << s1 << std::endl;
		std::cout << std::endl;

		auto v2 = 10.0 * e(1) + 10.0 * e(2);
		auto s2 = sp(v2, v2, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
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
	}

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

	{
		using namespace ga3m;

		double c1 = 5.0;
		double c2 = 2.0;
		double c3 = -4.5;

		auto v = c1 * e1 + c2 * e2 + c3 * e3;
		auto p = no + v + (sp(v, v) / c<2>) * ni;

		auto x1 = sp(p, e1);
		double d1 = x1;
		std::cout << x1 << " = " << d1 << std::endl;

		auto x2 = sqrt(sp(e1, e1));
		double d2 = x2;
		std::cout << x2 << " = " << d2 << std::endl;

		auto x3 = pow(c<2> * sp(e1, e1), c<-3>);
		double d3 = x3;
		std::cout << x3 << " = " << d3 << std::endl;

		std::cout << std::endl;
	}

	auto test = c<3> / c<2>;

	{
		default_bitset_t bits = 235;
		std::cout << "left  = " << detail::leftmost_set_bit(bits) << std::endl;
		std::cout << "right = " << detail::rightmost_set_bit(bits) << std::endl;
		std::cout << std::endl;

		ndims_t n = 5;
		default_bitset_t comb = 3;
		default_bitset_t mask = (default_bitset_t(1) << n) - 1;
		do {
			std::cout << '[';
			index_t index = 1;
			default_bitset_t temp = comb;
			for (default_bitset_t i = 1; temp; i *= 2, ++index) {
				if (i & temp) {
					std::cout << index << ", ";
					temp -= i;
				}
			}
			std::cout << ']' << std::endl;
		} while ((comb = detail::next_combination(comb, mask)) != default_bitset_t(0));
	}

	{
		using namespace ga2m;

		std::cout << I << std::endl;
		std::cout << Ie << std::endl;

	}

	{
		using namespace ga2m;

		auto const pi = (4 * atan(1));
		std::cout << "pi = " << pi << std::endl;

		auto alpha = pi / 2;
		std::cout << "alpha = " << alpha << ", exp(-(alpha / 2) * (e1^e2)) = " << exp(-(alpha / 2) * (e1^e2)) << std::endl;
	}

	{
		using namespace ga4e;

		unit_constant_basis_blade_t<1, 3, 4> xxx;
		auto yyy = e1^e3^e4;

		std::cout << xxx << std::endl;
		std::cout << yyy << std::endl;
	}

	return EXIT_SUCCESS;
}
/*/
#include <ga5e.hpp>

int main() {
	using namespace ga5e;

	auto x1 = c<5> + pow(c<2>, c<10>);
	auto x2 = scalar(5.0);

	auto lazy = make_lazy_context(scalar(5.0), scalar(7), scalar(7.0));

	auto x3 = lazy.argument<0>() + lazy.argument<1>();
	auto x4 = c<5> + sqrt(lazy.argument<2>());
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
	//std::cout << "size(sqrt(<-4>)) = " << sizeof(decltype(sqrt(c<-4>))) << "\t sqrt(<4>) = " << sqrt(c<-4>) << std::endl;
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

	auto r = gp(p, e3);
	std::cout << "gp(p, e3) = " << r << std::endl;
	std::cout << "sizeof(gp(p, e3)) = " << sizeof(decltype(r)) << std::endl;
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
/**/
