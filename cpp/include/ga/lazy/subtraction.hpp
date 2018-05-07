#ifndef __GA_LAZY_SUBTRACTION_HPP__
#define __GA_LAZY_SUBTRACTION_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			// Evaluate the subtraction of expressions, except for values.
			template<class LeftArgumentType, class RightArgumentType>
			constexpr decltype(auto) subtraction(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return detail::addition(lhs, detail::multiplication(constant<-1>(), rhs));
			}

			// Evaluate the subtraction of values.
			template<class LeftValueType, class RightValueType>
			constexpr decltype(auto) subtraction(value<LeftValueType> const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_sub(lhs, rhs);
			}

			template<class LeftValueType, class RightArgumentType, typename std::enable_if<!std::is_same<RightArgumentType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) subtraction(value<LeftValueType> const &lhs, RightArgumentType const &rhs) {
				return eval_lazy_sub(lhs, rhs);
			}

			template<class LeftArgumentType, class RightValueType, typename std::enable_if<!std::is_same<LeftArgumentType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) subtraction(LeftArgumentType const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_sub(lhs, rhs);
			}

		}

	}

}

#endif // __GA_LAZY_SUBTRACTION_HPP__
