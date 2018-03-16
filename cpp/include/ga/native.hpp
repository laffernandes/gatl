#ifndef __GA_NATIVE_HPP__
#define __GA_NATIVE_HPP__

namespace ga {

	template<default_integral_t Value>
	constexpr default_integral_t native(detail::cvalue<Value> const &) {
		return Value;
	}

	template<class Type>
	constexpr Type native(Type const &arg) {
		return arg;
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	detail::empty_expression native(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &) = delete;

	template<class CoefficientType>
	constexpr decltype(auto) native(detail::expression<detail::component<CoefficientType, detail::cbasis_blade<0> >, detail::empty_expression, detail::empty_expression> const &arg) {
		return native(arg.element().coefficient());
	}

	template<class CoefficientType>
	constexpr decltype(auto) native(detail::expression<detail::components<CoefficientType, default_bitset_t(1)>, detail::empty_expression, detail::empty_expression> const &arg) {
		return native(arg.element().begin()->second);
	}

	constexpr decltype(auto) native(detail::empty_expression const &) {
		return 0;
	}

}

#endif // __GA_NATIVE_HPP__
