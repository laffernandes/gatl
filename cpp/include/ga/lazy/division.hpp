#ifndef __GA_LAZY_DIVISION_HPP__
#define __GA_LAZY_DIVISION_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			// Evaluate the division of expressions, except for values.
			template<class LeftArgumentType, class RightArgumentType>
			constexpr decltype(auto) division(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return detail::multiplication(lhs, detail::exponentiation(rhs, constant<-1>()));
			}

			// Evaluate the division of values.
			template<class LeftValueType, class RightValueType>
			constexpr decltype(auto) division(value<LeftValueType> const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_div(lhs, rhs);
			}

			template<class LeftValueType, class RightArgumentType, typename std::enable_if<!(std::is_same<RightArgumentType, constant<0> >::value || std::is_same<RightArgumentType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) division(value<LeftValueType> const &lhs, RightArgumentType const &rhs) {
				return eval_lazy_div(lhs, rhs);
			}

			template<class LeftArgumentType, class RightValueType, typename std::enable_if<!(std::is_same<LeftArgumentType, constant<0> >::value || std::is_same<LeftArgumentType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) division(LeftArgumentType const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_div(lhs, rhs);
			}
		
		}

	}

}

#endif // __GA_LAZY_DIVISION_HPP__
