#ifndef __GA_CLIFFORD_UNARY_MINUS_HPP__
#define __GA_CLIFFORD_UNARY_MINUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ItrType>
			constexpr decltype(auto) unary_minus(ItrType const &arg) {
				return insert(unary_minus(next(arg)), unary_minus_element(element(arg)));
			}

			constexpr decltype(auto) unary_minus(itr_end const &) {
				return make_empty_clifford_expression();
			}

		}

		using lazy::operator-;

		template<class RightExpressionType>
		constexpr decltype(auto) operator-(clifford_expression<RightExpressionType> const &rhs) {
			return detail::unary_minus(detail::begin(rhs));
		}

	}

}

#endif // __GA_CLIFFORD_UNARY_MINUS_HPP__
