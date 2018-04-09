#ifndef __GA_CLIFFORD_BINARY_PLUS_HPP__
#define __GA_CLIFFORD_BINARY_PLUS_HPP__

namespace ga {

	namespace clifford {

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

			constexpr empty_clifford_expression binary_plus(itr_end const &, itr_end const &) {
				return empty_clifford_expression();
			}

		}

		using lazy::operator+;

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator+(clifford_expression<LeftExpressionType> const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return detail::binary_plus(detail::obegin(lhs), detail::obegin(rhs));
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator+(clifford_expression<LeftExpressionType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return detail::binary_plus(detail::obegin(lhs), detail::obegin(rhs));
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator+(lazy_expression<LeftExpressionType> const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return detail::binary_plus(detail::obegin(lhs), detail::obegin(rhs));
		}

		template<class LeftExpressionType, class RightType, typename std::enable_if<!(is_lazy_expression<RightType>::value || is_clifford_expression<RightType>::value), int>::type = 0>
		constexpr decltype(auto) operator+(clifford_expression<LeftExpressionType> const &lhs, RightType const &rhs) {
			return detail::binary_plus(detail::obegin(lhs), detail::obegin(value<RightType>(rhs)));
		}
		
		template<class LeftType, class RightExpressionType, typename std::enable_if<!(is_lazy_expression<LeftType>::value || is_clifford_expression<LeftType>::value), int>::type = 0>
		constexpr decltype(auto) operator+(LeftType const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return detail::binary_plus(detail::obegin(value<LeftType>(lhs)), detail::obegin(rhs));
		}

	}

}

#endif // __GA_CLIFFORD_BINARY_PLUS_HPP__
