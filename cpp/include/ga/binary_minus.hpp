#ifndef __GA_BINARY_MINUS_HPP__
#define __GA_BINARY_MINUS_HPP__

namespace ga {

	namespace detail {

		template<class LeftItrType, class RightItrType, typename std::enable_if<eq<typename LeftItrType::element_type, typename RightItrType::element_type>::value, int>::type = 0>
		constexpr decltype(auto) binary_minus(LeftItrType const &lhs, RightItrType const &rhs) {
			return insert(binary_minus(next(lhs), next(rhs)), binary_minus_element(lhs.element(), rhs.element()));
		}

		template<class LeftItrType, class RightItrType, typename std::enable_if<lt<typename LeftItrType::element_type, typename RightItrType::element_type>::value, int>::type = 0>
		constexpr decltype(auto) binary_minus(LeftItrType const &lhs, RightItrType const &rhs) {
			return insert(binary_minus(next(lhs), rhs), lhs.element());
		}

		template<class LeftItrType>
		constexpr decltype(auto) binary_minus(LeftItrType const &lhs, itr_end const &rhs) {
			return insert(binary_minus(next(lhs), rhs), lhs.element());
		}

		template<class LeftItrType, class RightItrType, typename std::enable_if<lt<typename RightItrType::element_type, typename LeftItrType::element_type>::value, int>::type = 0>
		constexpr decltype(auto) binary_minus(LeftItrType const &lhs, RightItrType const &rhs) {
			return insert(binary_minus(lhs, next(rhs)), unary_minus_element(rhs.element()));
		}

		template<class RightItrType>
		constexpr decltype(auto) binary_minus(itr_end const &lhs, RightItrType const &rhs) {
			return insert(binary_minus(lhs, next(rhs)), unary_minus_element(rhs.element()));
		}

		constexpr decltype(auto) binary_minus(itr_end const &, itr_end const &) {
			return empty_expression();
		}

	}

	template<class LeftType, class RightType>
	constexpr decltype(auto) minus(LeftType const &lhs, RightType const &rhs) {
		return detail::binary_minus(detail::obegin(lhs), detail::obegin(rhs));
	}

}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator-(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::minus(lhs, rhs);
}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType>
constexpr decltype(auto) operator-(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::minus(lhs, rhs);
}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, ga::default_integral_t RightValue>
constexpr decltype(auto) operator-(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::minus(lhs, rhs);
}

template<class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator-(ga::detail::empty_expression const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::minus(lhs, rhs);
}

constexpr decltype(auto) operator-(ga::detail::empty_expression const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::minus(lhs, rhs);
}

template<ga::default_integral_t RightValue>
constexpr decltype(auto) operator-(ga::detail::empty_expression const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::minus(lhs, rhs);
}

template<ga::default_integral_t LeftValue, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator-(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::minus(lhs, rhs);
}

template<ga::default_integral_t LeftValue>
constexpr decltype(auto) operator-(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::minus(lhs, rhs);
}

template<ga::default_integral_t LeftValue, ga::default_integral_t RightValue>
constexpr decltype(auto) operator-(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::minus(lhs, rhs);
}

#endif // __GA_BINARY_MINUS_HPP__
