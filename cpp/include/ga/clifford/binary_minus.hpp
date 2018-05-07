#ifndef __GA_CLIFFORD_BINARY_MINUS_HPP__
#define __GA_CLIFFORD_BINARY_MINUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class LeftElementType, class... LeftOtherElementTypes, class RightElementType, class... RightOtherElementTypes, typename std::enable_if<eq<LeftElementType, RightElementType>::value, int>::type = 0>
			constexpr decltype(auto) binary_minus(expression_list<LeftElementType, LeftOtherElementTypes...> const &lhs, expression_list<RightElementType, RightOtherElementTypes...> const &rhs) {
				return insert(binary_minus(lhs.next(), rhs.next()), binary_minus_element(lhs.element(), rhs.element()));
			}

			template<class LeftElementType, class... LeftOtherElementTypes, class RightElementType, class... RightOtherElementTypes, typename std::enable_if<lt<LeftElementType, RightElementType>::value, int>::type = 0>
			constexpr decltype(auto) binary_minus(expression_list<LeftElementType, LeftOtherElementTypes...> const &lhs, expression_list<RightElementType, RightOtherElementTypes...> const &rhs) {
				return insert(binary_minus(lhs.next(), rhs), lhs.element());
			}

			template<class LeftElementType, class... LeftOtherElementTypes>
			constexpr decltype(auto) binary_minus(expression_list<LeftElementType, LeftOtherElementTypes...> const &lhs, expression_list<> const &rhs) {
				return insert(binary_minus(lhs.next(), rhs), lhs.element());
			}

			template<class LeftElementType, class... LeftOtherElementTypes, class RightElementType, class... RightOtherElementTypes, typename std::enable_if<lt<RightElementType, LeftElementType>::value, int>::type = 0>
			constexpr decltype(auto) binary_minus(expression_list<LeftElementType, LeftOtherElementTypes...> const &lhs, expression_list<RightElementType, RightOtherElementTypes...> const &rhs) {
				return insert(binary_minus(lhs, rhs.next()), unary_minus_element(rhs.element()));
			}

			template<class RightElementType, class... RightOtherElementTypes>
			constexpr decltype(auto) binary_minus(expression_list<> const &lhs, expression_list<RightElementType, RightOtherElementTypes...> const &rhs) {
				return insert(binary_minus(lhs, rhs.next()), unary_minus_element(rhs.element()));
			}

			constexpr decltype(auto) binary_minus(expression_list<> const &, expression_list<> const &) {
				return make_empty_clifford_expression();
			}

		}

		using lazy::operator-;

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator-(clifford_expression<LeftExpressionType> const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return detail::try_cast_to_native(detail::binary_minus(detail::begin(lhs()), detail::begin(rhs())));
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator-(clifford_expression<LeftExpressionType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::try_cast_to_native(detail::binary_minus(detail::begin(lhs()), detail::begin(rhs)));
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator-(lazy_expression<LeftExpressionType> const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return detail::try_cast_to_native(detail::binary_minus(detail::begin(lhs), detail::begin(rhs())));
		}

		template<class LeftExpressionType, class RightType, typename std::enable_if<!(is_lazy_expression<RightType>::value || is_clifford_expression<RightType>::value), int>::type = 0>
		constexpr decltype(auto) operator-(clifford_expression<LeftExpressionType> const &lhs, RightType const &rhs) {
			return detail::try_cast_to_native(detail::binary_minus(detail::begin(lhs()), detail::begin(val(rhs))));
		}

		template<class LeftType, class RightExpressionType, typename std::enable_if<!(is_lazy_expression<LeftType>::value || is_clifford_expression<LeftType>::value), int>::type = 0>
		constexpr decltype(auto) operator-(LeftType const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return detail::try_cast_to_native(detail::binary_minus(detail::begin(val(lhs)), detail::begin(rhs())));
		}

	}

}

#endif // __GA_CLIFFORD_BINARY_MINUS_HPP__
