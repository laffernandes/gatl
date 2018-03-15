#ifndef __GA_BINARY_MINUS_HPP__
#define __GA_BINARY_MINUS_HPP__

namespace ga {

	namespace detail {

		struct _binary_minus_add_no_end;
		struct _binary_minus_add_left;
		struct _binary_minus_add_right;
		struct _binary_minus_add_both;
		struct _binary_minus_add_end;

		template<class LeftItrType, class RightItrType>
		constexpr decltype(auto) binary_minus(LeftItrType const &lhs, RightItrType const &rhs) {
			return std::conditional<is_end<LeftItrType>::value && is_end<RightItrType>::value, _binary_minus_add_end, typename std::conditional<is_end<RightItrType>::value, _binary_minus_add_left, typename std::conditional<is_end<LeftItrType>::value, _binary_minus_add_right, _binary_minus_add_no_end>::type>::type>::type::bind(lhs, rhs);
		}

		struct _binary_minus_add_no_end {
			template<class LeftItrType, class RightItrType>
			constexpr static decltype(auto) bind(LeftItrType const &lhs, RightItrType const &rhs) {
				return std::conditional<lt<typename LeftItrType::element_type, typename RightItrType::element_type>::value, _binary_minus_add_left, typename std::conditional<lt<typename RightItrType::element_type, typename LeftItrType::element_type>::value, _binary_minus_add_right, _binary_minus_add_both>::type>::type::bind(lhs, rhs);
			}
		};

		struct _binary_minus_add_left {
			template<class LeftItrType, class RightItrType>
			constexpr static decltype(auto) bind(LeftItrType const &lhs, RightItrType const &rhs) {
				return insert(binary_minus(next(lhs), rhs), lhs.element());
			}
		};

		struct _binary_minus_add_right {
			template<class LeftItrType, class RightItrType>
			constexpr static decltype(auto) bind(LeftItrType const &lhs, RightItrType const &rhs) {
				return insert(binary_minus(lhs, next(rhs)), unary_minus_element(rhs.element()));
			}
		};

		struct _binary_minus_add_both {
			template<class LeftItrType, class RightItrType>
			constexpr static decltype(auto) bind(LeftItrType const &lhs, RightItrType const &rhs) {
				return insert(binary_minus(next(lhs), next(rhs)), binary_minus_element(lhs.element(), rhs.element()));
			}
		};

		struct _binary_minus_add_end {
			template<class LeftItrType, class RightItrType>
			constexpr static empty_expression bind(LeftItrType const &, RightItrType const &) {
				return empty_expression();
			}
		};

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
