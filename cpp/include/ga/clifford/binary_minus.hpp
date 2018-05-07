#ifndef __GA_CLIFFORD_BINARY_MINUS_HPP__
#define __GA_CLIFFORD_BINARY_MINUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class LeftElementType, class... LeftOtherElementTypes, class RightElementType, class... RightOtherElementTypes, typename std::enable_if<eq<LeftElementType, RightElementType>::value, int>::type = 0>
			constexpr decltype(auto) binary_minus(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &lhs, clifford_expression<RightElementType, RightOtherElementTypes...> const &rhs) {
				return insert(binary_minus(lhs.next(), rhs.next()), binary_minus_element(lhs.element(), rhs.element()));
			}

			template<class LeftElementType, class... LeftOtherElementTypes, class RightElementType, class... RightOtherElementTypes, typename std::enable_if<lt<LeftElementType, RightElementType>::value, int>::type = 0>
			constexpr decltype(auto) binary_minus(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &lhs, clifford_expression<RightElementType, RightOtherElementTypes...> const &rhs) {
				return insert(binary_minus(lhs.next(), rhs), lhs.element());
			}

			template<class LeftElementType, class... LeftOtherElementTypes>
			constexpr decltype(auto) binary_minus(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &lhs, clifford_expression<> const &rhs) {
				return insert(binary_minus(lhs.next(), rhs), lhs.element());
			}

			template<class LeftElementType, class... LeftOtherElementTypes, class RightElementType, class... RightOtherElementTypes, typename std::enable_if<lt<RightElementType, LeftElementType>::value, int>::type = 0>
			constexpr decltype(auto) binary_minus(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &lhs, clifford_expression<RightElementType, RightOtherElementTypes...> const &rhs) {
				return insert(binary_minus(lhs, rhs.next()), unary_minus_element(rhs.element()));
			}

			template<class RightElementType, class... RightOtherElementTypes>
			constexpr decltype(auto) binary_minus(clifford_expression<> const &lhs, clifford_expression<RightElementType, RightOtherElementTypes...> const &rhs) {
				return insert(binary_minus(lhs, rhs.next()), unary_minus_element(rhs.element()));
			}

			constexpr decltype(auto) binary_minus(clifford_expression<> const &, clifford_expression<> const &) {
				return make_empty_clifford_expression();
			}

		}

		using lazy::operator-;

		template<class... LeftElementTypes, class... RightElementTypes>
		constexpr decltype(auto) operator-(clifford_expression<LeftElementTypes...> const &lhs, clifford_expression<RightElementTypes...> const &rhs) {
			return detail::try_cast_to_native(detail::binary_minus(lhs, rhs));
		}

		template<class... LeftElementTypes, class RightExpressionType>
		constexpr decltype(auto) operator-(clifford_expression<LeftElementTypes...> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::try_cast_to_native(detail::binary_minus(lhs, detail::begin(rhs)));
		}

		template<class LeftExpressionType, class... RightElementTypes>
		constexpr decltype(auto) operator-(lazy_expression<LeftExpressionType> const &lhs, clifford_expression<RightElementTypes...> const &rhs) {
			return detail::try_cast_to_native(detail::binary_minus(detail::begin(lhs), rhs));
		}

		template<class... LeftElementTypes, class RightType, typename std::enable_if<!is_lazy_expression<RightType>::value, int>::type = 0>
		constexpr decltype(auto) operator-(clifford_expression<LeftElementTypes...> const &lhs, RightType const &rhs) {
			return detail::try_cast_to_native(detail::binary_minus(lhs, detail::begin(val(rhs))));
		}

		template<class LeftType, class... RightElementTypes, typename std::enable_if<!is_lazy_expression<LeftType>::value, int>::type = 0>
		constexpr decltype(auto) operator-(LeftType const &lhs, clifford_expression<RightElementTypes...> const &rhs) {
			return detail::try_cast_to_native(detail::binary_minus(detail::begin(val(lhs)), rhs));
		}

	}

}

#endif // __GA_CLIFFORD_BINARY_MINUS_HPP__
