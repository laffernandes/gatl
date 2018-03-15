#ifndef __GA_UNARY_PLUS_HPP__
#define __GA_UNARY_PLUS_HPP__

namespace ga {

	template<class ValueType>
	constexpr ValueType uplus(ValueType const &rhs) {
		return rhs;
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	constexpr detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> uplus(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) {
		return rhs;
	}

	constexpr detail::empty_expression uplus(detail::empty_expression const &) {
		return detail::empty_expression();
	}

	template<default_integral_t Value>
	constexpr detail::cvalue<Value> uplus(detail::cvalue<Value> const &) {
		return detail::cvalue<Value>();
	}

}

template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
constexpr ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> operator+(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) {
	return rhs;
}

constexpr ga::detail::empty_expression operator+(ga::detail::empty_expression const &) {
	return ga::detail::empty_expression();
}

template<ga::default_integral_t Value>
constexpr ga::detail::cvalue<Value> operator+(ga::detail::cvalue<Value> const &) {
	return ga::detail::cvalue<Value>();
}

#endif // __GA_UNARY_PLUS_HPP__
