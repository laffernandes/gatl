#ifndef __GA_BINARY_PLUS_HPP__
#define __GA_BINARY_PLUS_HPP__

namespace ga {

	namespace detail {

		template<class LeftItrType, class RightItrType, typename std::enable_if<eq<typename LeftItrType::element_type, typename RightItrType::element_type>::value, int>::type = 0>
		constexpr decltype(auto) binary_plus(LeftItrType const &lhs, RightItrType const &rhs) {
			return insert(binary_plus(next(lhs), next(rhs)), binary_plus_element(lhs.element(), rhs.element()));
		}

		template<class LeftItrType, class RightItrType, typename std::enable_if<lt<typename LeftItrType::element_type, typename RightItrType::element_type>::value, int>::type = 0>
		constexpr decltype(auto) binary_plus(LeftItrType const &lhs, RightItrType const &rhs) {
			return insert(binary_plus(next(lhs), rhs), lhs.element());
		}

		template<class LeftItrType>
		constexpr decltype(auto) binary_plus(LeftItrType const &lhs, itr_end const &rhs) {
			return insert(binary_plus(next(lhs), rhs), lhs.element());
		}

		template<class LeftItrType, class RightItrType, typename std::enable_if<lt<typename RightItrType::element_type, typename LeftItrType::element_type>::value, int>::type = 0>
		constexpr decltype(auto) binary_plus(LeftItrType const &lhs, RightItrType const &rhs) {
			return insert(binary_plus(lhs, next(rhs)), rhs.element());
		}

		template<class RightItrType>
		constexpr decltype(auto) binary_plus(itr_end const &lhs, RightItrType const &rhs) {
			return insert(binary_plus(lhs, next(rhs)), rhs.element());
		}

		constexpr decltype(auto) binary_plus(itr_end const &, itr_end const &) {
			return empty_expression();
		}

	}

	template<class LeftType, class RightType>
	constexpr decltype(auto) plus(LeftType const &lhs, RightType const &rhs) {
		return detail::binary_plus(detail::obegin(lhs), detail::obegin(rhs));
	}

}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator+(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::plus(lhs, rhs);
}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType>
constexpr decltype(auto) operator+(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::plus(lhs, rhs);
}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, ga::default_integral_t RightValue>
constexpr decltype(auto) operator+(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::plus(lhs, rhs);
}

template<class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator+(ga::detail::empty_expression const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::plus(lhs, rhs);
}

constexpr decltype(auto) operator+(ga::detail::empty_expression const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::plus(lhs, rhs);
}

template<ga::default_integral_t RightValue>
constexpr decltype(auto) operator+(ga::detail::empty_expression const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::plus(lhs, rhs);
}

template<ga::default_integral_t LeftValue, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator+(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::plus(lhs, rhs);
}

template<ga::default_integral_t LeftValue>
constexpr decltype(auto) operator+(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::empty_expression const &rhs) {
	return ga::plus(lhs, rhs);
}

template<ga::default_integral_t LeftValue, ga::default_integral_t RightValue>
constexpr decltype(auto) operator+(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::plus(lhs, rhs);
}

#endif // __GA_BINARY_PLUS_HPP__
