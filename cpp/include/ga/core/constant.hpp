#ifndef __GA_CORE_CONSTANT_HPP__
#define __GA_CORE_CONSTANT_HPP__

namespace ga {

	template<class CoefficientType, default_integral_t Value>
	using constant = scalar_clifford_expression<CoefficientType, detail::constant_value<Value> >;

	template<default_integral_t Value, class CoefficientType = default_integral_t>
	constexpr auto c = constant<CoefficientType, Value>();

}

#endif // __GA_CORE_CONSTANT_HPP__
