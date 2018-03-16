#ifndef __GA_BINARY_PLUS_HPP__
#define __GA_BINARY_PLUS_HPP__

namespace ga {

	namespace detail {

		//TODO Adição e subtração não agrupam component<CoefficientType, dbasis_blade<X> > com components<CoefficientType, X>.

		struct _binary_plus_add_no_end;
		struct _binary_plus_add_left;
		struct _binary_plus_add_right;
		struct _binary_plus_add_both;
		struct _binary_plus_add_end;

		template<class LeftItrType, class RightItrType>
		constexpr decltype(auto) binary_plus(LeftItrType const &lhs, RightItrType const &rhs) {
			return std::conditional<is_end<LeftItrType>::value && is_end<RightItrType>::value, _binary_plus_add_end, typename std::conditional<is_end<RightItrType>::value, _binary_plus_add_left, typename std::conditional<is_end<LeftItrType>::value, _binary_plus_add_right, _binary_plus_add_no_end>::type>::type>::type::bind(lhs, rhs);
		}

		struct _binary_plus_add_no_end {
			template<class LeftItrType, class RightItrType>
			constexpr static decltype(auto) bind(LeftItrType const &lhs, RightItrType const &rhs) {
				return std::conditional<lt<typename LeftItrType::element_type, typename RightItrType::element_type>::value, _binary_plus_add_left, typename std::conditional<lt<typename RightItrType::element_type, typename LeftItrType::element_type>::value, _binary_plus_add_right, _binary_plus_add_both>::type>::type::bind(lhs, rhs);
			}
		};

		struct _binary_plus_add_left {
			template<class LeftItrType, class RightItrType>
			constexpr static decltype(auto) bind(LeftItrType const &lhs, RightItrType const &rhs) {
				return insert(binary_plus(next(lhs), rhs), lhs.element());
			}
		};

		struct _binary_plus_add_right {
			template<class LeftItrType, class RightItrType>
			constexpr static decltype(auto) bind(LeftItrType const &lhs, RightItrType const &rhs) {
				return insert(binary_plus(lhs, next(rhs)), rhs.element());
			}
		};

		struct _binary_plus_add_both {
			template<class LeftItrType, class RightItrType>
			constexpr static decltype(auto) bind(LeftItrType const &lhs, RightItrType const &rhs) {
				return insert(binary_plus(next(lhs), next(rhs)), binary_plus_element(lhs.element(), rhs.element()));
			}
		};

		struct _binary_plus_add_end {
			template<class LeftItrType, class RightItrType>
			constexpr static empty_expression bind(LeftItrType const &, RightItrType const &) {
				return empty_expression();
			}
		};

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
