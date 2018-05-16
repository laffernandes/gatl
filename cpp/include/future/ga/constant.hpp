#ifndef __FUTURE_GA_CONSTANT_HPP__
#define __FUTURE_GA_CONSTANT_HPP__

namespace ga {

	template<default_integral_t Value>
	using constant = clifford_expression<default_integral_t, detail::component<detail::constant_value<Value>, detail::constant_basis_blade<default_bitset_t(0)> > >;

	template<default_integral_t Value>
	constexpr auto c = constant<Value>();

}

#endif // __FUTURE_GA_CONSTANT_HPP__
