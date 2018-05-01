#ifndef __GA_LAZY_ADDITION_HPP__
#define __GA_LAZY_ADDITION_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			// Default addition_bind operation.
			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) addition_bind(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return make_add(lhs, rhs);
			}

			// Simplify addition of values.
			template<class LeftValueType, class RightValueType>
			constexpr decltype(auto) addition_bind(value<LeftValueType> const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_add(lhs, rhs);
			}

			template<class LeftValueType, class RightExpressionType, typename std::enable_if<!std::is_same<RightExpressionType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) addition_bind(value<LeftValueType> const &lhs, RightExpressionType const &rhs) {
				return eval_lazy_add(lhs, rhs);
			}

			template<class LeftExpressionType, class RightValueType, typename std::enable_if<!std::is_same<LeftExpressionType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) addition_bind(LeftExpressionType const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_add(lhs, rhs);
			}

			// Simplify addition to zero.
			//     0 + X = X
			//     X + 0 = X
			//     0 + 0 = 0
			template<class RightExpressionType>
			constexpr RightExpressionType addition_bind(constant<0> const &, RightExpressionType const &rhs) {
				return rhs;
			}

			template<class LeftExpressionType>
			constexpr LeftExpressionType addition_bind(LeftExpressionType const &lhs, constant<0> const &) {
				return lhs;
			}

			constexpr decltype(auto) addition_bind(constant<0> const &, constant<0> const &) {
				return constant<0>();
			}

			// Simplify addition of constants (except for A == 0 and B == 0 and A == B).
			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<LeftValue != 0 && RightValue != 0 && LeftValue != RightValue, int>::type = 0>
			constexpr decltype(auto) addition_bind(constant<LeftValue> const &, constant<RightValue> const &) {
				return constant<LeftValue + RightValue>();
			}

			// Simplify addition of constant rational numbers
			//     A + 1/C = simpler (except for A == 0)
			//     1/C + A = simpler (except for A == 0)
			//     A/B + 1/C = simpler (except for B == C)
			//     1/C + A/B = simpler (except for C == B)
			//     1/B + 1/C = simpler (except for B == C)
			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<LeftValue != 0, int>::type = 0>
			constexpr decltype(auto) addition_bind(constant<LeftValue> const &, power<constant<RightValue>, constant<-1> > const &) {
				return multiplication(constant<LeftValue * RightValue + 1>(), make_power(constant<RightValue>(), constant<-1>()));
			}

			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<RightValue != 0, int>::type = 0>
			constexpr decltype(auto) addition_bind(power<constant<LeftValue>, constant<-1> > const &, constant<RightValue> const &) {
				return multiplication(constant<1 + RightValue * LeftValue>(), make_power(constant<LeftValue>(), constant<-1>()));
			}

			template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightValue, typename std::enable_if<LeftRightValue != RightValue, int>::type = 0>
			constexpr decltype(auto) addition_bind(mul<constant<LeftLeftValue>, power<constant<LeftRightValue>, constant<-1> > > const &, power<constant<RightValue>, constant<-1> > const &) {
				return multiplication(constant<LeftLeftValue * RightValue + LeftRightValue>(), make_power(constant<LeftRightValue * RightValue>(), constant<-1>()));
			}

			template<default_integral_t LeftValue, default_integral_t RightLeftValue, default_integral_t RightRightValue, typename std::enable_if<LeftValue != RightRightValue, int>::type = 0>
			constexpr decltype(auto) addition_bind(power<constant<LeftValue>, constant<-1> > const &, mul<constant<RightLeftValue>, power<constant<RightRightValue>, constant<-1> > > const &) {
				return multiplication(constant<RightRightValue + LeftValue * RightLeftValue>(), make_power(constant<LeftValue * RightRightValue>(), constant<-1>()));
			}

			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<LeftValue != RightValue, int>::type = 0>
			constexpr decltype(auto) addition_bind(power<constant<LeftValue>, constant<-1> > const &, power<constant<RightValue>, constant<-1> > const &) {
				return multiplication(constant<RightValue + LeftValue>(), make_power(constant<LeftValue * RightValue>(), constant<-1>()));
			}

			// Simplify to multiplication of contant by expression (by sorting, "..." is an expression of constants or variables).
			//     A + A = 2 * A
			//     A + (A + ...) = 2 * A + ...
			//     ... + (P * ...) = (1 + P) * ...
			//     (P * ...) + ... = (P + 1) * ...
			//     (P * ...) + (Q * ...) = (P + Q) * ...
			template<class ExpressionType, typename std::enable_if<allows_lazy_simplification<ExpressionType>::value && !std::is_same<ExpressionType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) addition_bind(ExpressionType const &lhs, ExpressionType const &) {
				return multiplication(constant<2>(), lhs);
			}

			template<class ExpressionType, class TailExpressionType, typename std::enable_if<allows_lazy_simplification<ExpressionType>::value && !std::is_same<ExpressionType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) addition_bind(ExpressionType const &lhs, add<ExpressionType, TailExpressionType> const &rhs) {
				return addition(multiplication(constant<2>(), lhs), rhs.right());
			}

			template<default_integral_t LeftValue, class TailExpressionType>
			constexpr decltype(auto) addition_bind(mul<constant<LeftValue>, TailExpressionType> const &, TailExpressionType const &rhs) {
				return multiplication(constant<LeftValue + 1>(), rhs);
			}

			template<class ExpressionType, class TailExpressionType, typename std::enable_if<allows_lazy_simplification<ExpressionType>::value && !std::is_same<ExpressionType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) addition_bind(add<ExpressionType, TailExpressionType> const &lhs, ExpressionType const &rhs) {
				return addition(multiplication(constant<2>(), rhs), lhs.right());
			}

			template<class TailExpressionType, default_integral_t RightValue>
			constexpr decltype(auto) addition_bind(TailExpressionType const &lhs, mul<constant<RightValue>, TailExpressionType> const &) {
				return multiplication(constant<1 + RightValue>(), lhs);
			}

			template<default_integral_t LeftValue, class TailExpressionType, default_integral_t RightValue, typename std::enable_if<LeftValue != RightValue, int>::type = 0>
			constexpr decltype(auto) addition_bind(mul<constant<LeftValue>, TailExpressionType> const &lhs, mul<constant<RightValue>, TailExpressionType> const &) {
				return multiplication(constant<LeftValue + RightValue>(), lhs.right());
			}

			// Addition merge.
			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<le<LeftExpressionType, RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return addition_bind(lhs, rhs);
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<lt<RightExpressionType, LeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return addition_bind(rhs, lhs);
			}

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<le<LeftExpressionType, RightLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(LeftExpressionType const &lhs, add<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return addition_bind(lhs, rhs);
			}

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<lt<RightLeftExpressionType, LeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(LeftExpressionType const &lhs, add<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return addition(rhs.left(), addition(lhs, rhs.right()));
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightExpressionType, typename std::enable_if<lt<RightExpressionType, LeftLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(add<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, RightExpressionType const &rhs) {
				return addition_bind(rhs, lhs);
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightExpressionType, typename std::enable_if<eq<LeftLeftExpressionType, RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(add<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, RightExpressionType const &rhs) {
				return addition(lhs.left(), addition(rhs, lhs.right()));
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightExpressionType, typename std::enable_if<lt<LeftLeftExpressionType, RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(add<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, RightExpressionType const &rhs) {
				return addition(lhs.left(), addition(lhs.right(), rhs));
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<eq<LeftLeftExpressionType, RightLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(add<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, add<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return addition(lhs.left(), addition(rhs.left(), addition(lhs.right(), rhs.right())));
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<lt<LeftLeftExpressionType, RightLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(add<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, add<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return addition(lhs.left(), addition(lhs.right(), rhs));
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<lt<RightLeftExpressionType, LeftLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) addition(add<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, add<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return addition(rhs.left(), addition(lhs, rhs.right()));
			}

		}

	}

}

#endif // __GA_LAZY_ADDITION_HPP__
