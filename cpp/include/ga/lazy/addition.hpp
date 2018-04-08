#ifndef __GA_LAZY_ADDITION_HPP__
#define __GA_LAZY_ADDITION_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) addition_bind(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return make_add(lhs, rhs);
			}

			template<id_t Id, class ValueType>
			constexpr decltype(auto) addition_bind(variable<Id, ValueType> const &lhs, variable<Id, ValueType> const &) {
				return multiplication(constant<2>(), lhs);
			}

			template<id_t Id, class ValueType, class RightTailExpressionType>
			constexpr decltype(auto) addition_bind(variable<Id, ValueType> const &lhs, add<variable<Id, ValueType>, RightTailExpressionType> const &rhs) {
				return addition(multiplication(constant<2>(), lhs), rhs.right());
			}

			template<class TailExpressionType, default_integral_t RightValue>
			constexpr decltype(auto) addition_bind(TailExpressionType const &lhs, mul<constant<RightValue>, TailExpressionType> const &) {
				return multiplication(constant<1 + RightValue>(), lhs);
			}

			template<default_integral_t LeftValue, class TailExpressionType>
			constexpr decltype(auto) addition_bind(mul<constant<LeftValue>, TailExpressionType> const &, TailExpressionType const &rhs) {
				return multiplication(constant<LeftValue + 1>(), rhs);
			}

			template<default_integral_t LeftValue, class TailExpressionType, default_integral_t RightValue>
			constexpr decltype(auto) addition_bind(mul<constant<LeftValue>, TailExpressionType> const &lhs, mul<constant<RightValue>, TailExpressionType> const &) {
				return multiplication(constant<LeftValue + RightValue>(), lhs.right());
			}

			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<LeftValue != 0 && RightValue != 0, int>::type = 0>
			constexpr constant<LeftValue + RightValue> addition_bind(constant<LeftValue> const &, constant<RightValue> const &) {
				return constant<LeftValue + RightValue>();
			}

			constexpr constant<0> addition_bind(constant<0> const &, constant<0> const &) {
				return constant<0>();
			}

			template<class LeftExpressionType, typename std::enable_if<!std::is_same<LeftExpressionType, constant<0> >::value, int>::type = 0>
			constexpr LeftExpressionType addition_bind(LeftExpressionType const &lhs, constant<0> const &) {
				return lhs;
			}

			template<class RightExpressionType, typename std::enable_if<!std::is_same<RightExpressionType, constant<0> >::value, int>::type = 0>
			constexpr RightExpressionType addition_bind(constant<0> const &, RightExpressionType const &rhs) {
				return rhs;
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<le<LeftExpressionType, RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return addition_bind(lhs, rhs);
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<lt<RightExpressionType, LeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return addition(rhs, lhs);
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType, typename std::enable_if<le<LeftLeftExpressionType, RightExpressionType>::value && le<LeftRightExpressionType, RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(add<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return addition(lhs.left(), addition(lhs.right(), rhs));
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType, typename std::enable_if<le<LeftLeftExpressionType, RightExpressionType>::value && lt<RightExpressionType, LeftRightExpressionType>::value && (is_constant<LeftLeftExpressionType>::value && is_constant<RightExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) addition(add<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return addition(addition_bind(lhs.left(), rhs), lhs.right());
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType, typename std::enable_if<le<LeftLeftExpressionType, RightExpressionType>::value && lt<RightExpressionType, LeftRightExpressionType>::value && !(is_constant<LeftLeftExpressionType>::value && is_constant<RightExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) addition(add<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return addition(lhs.left(), addition(rhs, lhs.right()));
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType, typename std::enable_if<lt<RightExpressionType, LeftLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(add<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return addition(rhs, lhs);
			}

		}

	}

}

#endif // __GA_LAZY_ADDITION_HPP__
