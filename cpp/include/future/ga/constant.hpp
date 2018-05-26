#ifndef __FUTURE_GA_CONSTANT_HPP__
#define __FUTURE_GA_CONSTANT_HPP__

namespace ga {

	template<class CoefficientType, default_integral_t Value>
	using constant = scalar_clifford_expression<CoefficientType, detail::constant_value<Value> >;

	template<default_integral_t Value, class CoefficientType = default_integral_t>
	constexpr auto c = constant<CoefficientType, Value>();

}

#endif // __FUTURE_GA_CONSTANT_HPP__
