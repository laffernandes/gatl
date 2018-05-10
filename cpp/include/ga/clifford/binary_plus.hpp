#ifndef __GA_CLIFFORD_BINARY_PLUS_HPP__
#define __GA_CLIFFORD_BINARY_PLUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class LeftElementType, class... LeftOtherElementTypes, class RightElementType, class... RightOtherElementTypes, typename std::enable_if<eq<LeftElementType, RightElementType>::value, int>::type = 0>
			constexpr decltype(auto) binary_plus(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &lhs, clifford_expression<RightElementType, RightOtherElementTypes...> const &rhs) {
				return insert(binary_plus(lhs.next(), rhs.next()), binary_plus_element(lhs.element(), rhs.element()));
			}

			//TODO INSERIDO POR CAUSA DE BUG PÓS ATUALIZAÇÃO DO VISUAL STUDIO
			template<class LeftElementType, class RightElementType, typename std::enable_if<eq<LeftElementType, RightElementType>::value, int>::type = 0>
			constexpr decltype(auto) binary_plus(clifford_expression<LeftElementType> const &lhs, clifford_expression<RightElementType> const &rhs) {
				return make_simple_clifford_expression(binary_plus_element(lhs.element(), rhs.element()));
			}

			template<class LeftElementType, class... LeftOtherElementTypes, class RightElementType, class... RightOtherElementTypes, typename std::enable_if<lt<LeftElementType, RightElementType>::value, int>::type = 0>
			constexpr decltype(auto) binary_plus(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &lhs, clifford_expression<RightElementType, RightOtherElementTypes...> const &rhs) {
				return insert(binary_plus(lhs.next(), rhs), lhs.element());
			}

			template<class LeftElementType, class... LeftOtherElementTypes>
			constexpr clifford_expression<LeftElementType, LeftOtherElementTypes...> binary_plus(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &lhs, clifford_expression<> const &rhs) {
				return lhs;
			}

			template<class LeftElementType, class... LeftOtherElementTypes, class RightElementType, class... RightOtherElementTypes, typename std::enable_if<lt<RightElementType, LeftElementType>::value, int>::type = 0>
			constexpr decltype(auto) binary_plus(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &lhs, clifford_expression<RightElementType, RightOtherElementTypes...> const &rhs) {
				return insert(binary_plus(lhs, rhs.next()), rhs.element());
			}

			template<class RightElementType, class... RightOtherElementTypes>
			constexpr clifford_expression<RightElementType, RightOtherElementTypes...> binary_plus(clifford_expression<> const &lhs, clifford_expression<RightElementType, RightOtherElementTypes...> const &rhs) {
				return rhs;
			}

			constexpr decltype(auto) binary_plus(clifford_expression<> const &, clifford_expression<> const &) {
				return clifford_expression<>();
			}

		}

		using lazy::operator+;

		template<class... LeftElementTypes, class... RightElementTypes>
		constexpr decltype(auto) operator+(clifford_expression<LeftElementTypes...> const &lhs, clifford_expression<RightElementTypes...> const &rhs) {
			return detail::try_cast_to_native(detail::binary_plus(lhs, rhs));
		}

		template<class... LeftElementTypes, class RightExpressionType>
		constexpr decltype(auto) operator+(clifford_expression<LeftElementTypes...> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::try_cast_to_native(detail::binary_plus(lhs, detail::begin(rhs)));
		}

		template<class LeftExpressionType, class... RightElementTypes>
		constexpr decltype(auto) operator+(lazy_expression<LeftExpressionType> const &lhs, clifford_expression<RightElementTypes...> const &rhs) {
			return detail::try_cast_to_native(detail::binary_plus(detail::begin(lhs), rhs));
		}

		template<class... LeftElementTypes, class RightType, typename std::enable_if<!is_lazy_expression<RightType>::value, int>::type = 0>
		constexpr decltype(auto) operator+(clifford_expression<LeftElementTypes...> const &lhs, RightType const &rhs) {
			return detail::try_cast_to_native(detail::binary_plus(lhs, detail::begin(val(rhs))));
		}
		
		template<class LeftType, class... RightElementTypes, typename std::enable_if<!is_lazy_expression<LeftType>::value, int>::type = 0>
		constexpr decltype(auto) operator+(LeftType const &lhs, clifford_expression<RightElementTypes...> const &rhs) {
			return detail::try_cast_to_native(detail::binary_plus(detail::begin(val(lhs)), rhs));
		}

	}

}

#endif // __GA_CLIFFORD_BINARY_PLUS_HPP__
