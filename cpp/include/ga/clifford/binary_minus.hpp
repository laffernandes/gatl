#ifndef __GA_CLIFFORD_BINARY_MINUS_HPP__
#define __GA_CLIFFORD_BINARY_MINUS_HPP__

namespace ga {

	namespace clifford {

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

			constexpr empty_clifford_expression binary_minus(itr_end const &, itr_end const &) {
				return empty_clifford_expression();
			}

		}

		using lazy::operator-;

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator-(clifford_expression<LeftExpressionType> const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return detail::try_to_cast_to_native(detail::binary_minus(detail::obegin(lhs), detail::obegin(rhs)));
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator-(clifford_expression<LeftExpressionType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::try_to_cast_to_native(detail::binary_minus(detail::obegin(lhs), detail::obegin(rhs)));
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator-(lazy_expression<LeftExpressionType> const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return detail::try_to_cast_to_native(detail::binary_minus(detail::obegin(lhs), detail::obegin(rhs)));
		}

		template<class LeftExpressionType, class RightType, typename std::enable_if<!(is_lazy_expression<RightType>::value || is_clifford_expression<RightType>::value), int>::type = 0>
		constexpr decltype(auto) operator-(clifford_expression<LeftExpressionType> const &lhs, RightType const &rhs) {
			return detail::try_to_cast_to_native(detail::binary_minus(detail::obegin(lhs), detail::obegin(val(rhs))));
		}

		template<class LeftType, class RightExpressionType, typename std::enable_if<!(is_lazy_expression<LeftType>::value || is_clifford_expression<LeftType>::value), int>::type = 0>
		constexpr decltype(auto) operator-(LeftType const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return detail::try_to_cast_to_native(detail::binary_minus(detail::obegin(val(lhs)), detail::obegin(rhs)));
		}

	}

}

#endif // __GA_CLIFFORD_BINARY_MINUS_HPP__
