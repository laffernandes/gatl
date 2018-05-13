#ifndef __FUTURE_GA_CONSTANT_HPP__
#define __FUTURE_GA_CONSTANT_HPP__

namespace ga {

	template<default_integral_t Value>
	using constant = clifford_expression<default_integral_t, detail::constant<Value> >;

	template<default_integral_t Value>
	constexpr auto c = constant<Value>();

}

#endif // __FUTURE_GA_CONSTANT_HPP__
