#ifndef __GA_LAZY_MULTIPLICATION_HPP__
#define __GA_LAZY_MULTIPLICATION_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			// Default multiplication_bind operation.
			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) multiplication_bind(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return make_mul(lhs, rhs);
			}

			// Simplify multiplication of values (by sorting, "..." is an expression of constants or variables).
			//     A * B = simpler C
			//     A * (B * ...) = simpler C * ...
			template<class LeftValueType, class RightValueType>
			constexpr decltype(auto) multiplication_bind(value<LeftValueType> const &lhs, value<RightValueType> const &rhs) {
				return val(lhs.get() * rhs.get());
			}

			template<class LeftValueType, default_integral_t RightValue, typename std::enable_if<RightValue != 0 && RightValue != 1, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(value<LeftValueType> const &lhs, constant<RightValue> const &) {
				return val(lhs.get() * RightValue);
			}

			template<class LeftValueType, class RightValueType, class RightTailExpressionType>
			constexpr decltype(auto) multiplication_bind(value<LeftValueType> const &lhs, mul<value<RightValueType>, RightTailExpressionType> const &rhs) {
				return make_mul(val(lhs.get() * rhs.left().get()), rhs.right());
			}

			template<class LeftValueType, default_integral_t RightValue>
			constexpr decltype(auto) multiplication_bind(value<LeftValueType> const &lhs, power<constant<RightValue>, constant<-1> > const &) {
				typedef typename std::conditional<std::is_floating_point<LeftValueType>::value, default_integral_t, default_floating_point_t>::type constant_value_t;
				return val(lhs.get() / static_cast<constant_value_t>(RightValue));
			}

			// Simplify multiplication by zero.
			//     0 * X = 0
			//     X * 0 = 0
			//     0 * 0 = 0
			template<class RightExpressionType>
			constexpr decltype(auto) multiplication_bind(constant<0> const &, RightExpressionType const &) {
				return constant<0>();
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) multiplication_bind(LeftExpressionType const &, constant<0> const &) {
				return constant<0>();
			}

			constexpr decltype(auto) multiplication_bind(constant<0> const &, constant<0> const &) {
				return constant<0>();
			}

			// Simplify multiplication by one (except for X == 0).
			//     1 * X = X
			//     X * 1 = X
			//     1 * 1 = 1
			template<class RightExpressionType, typename std::enable_if<!std::is_same<RightExpressionType, constant<0> >::value, int>::type = 0>
			constexpr RightExpressionType multiplication_bind(constant<1> const &, RightExpressionType const &rhs) {
				return rhs;
			}

			template<class LeftExpressionType, typename std::enable_if<!std::is_same<LeftExpressionType, constant<0> >::value, int>::type = 0>
			constexpr LeftExpressionType multiplication_bind(LeftExpressionType const &lhs, constant<1> const &) {
				return lhs;
			}

			constexpr decltype(auto) multiplication_bind(constant<1> const &, constant<1> const &) {
				return constant<1>();
			}

			// Simplify multiplication of constants (except for A == 0 and A == 1 and B == 0 and B == 1 and A != B).
			//     A * B = simpler C
			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<LeftValue != 0 && LeftValue != 1 && RightValue != 0 && RightValue != 1 && LeftValue != RightValue, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(constant<LeftValue> const &, constant<RightValue> const &) {
				return constant<LeftValue * RightValue>();
			}

			// Simplify multiplication of constant rational numbers (except for A == 0 and A == 1 and A == B)
			//     A * B^{-1} = simpler
			//     B^{-1} * A = simpler
			//     A^{-1} * B^{-1} = simpler
			constexpr default_integral_t absolute(default_integral_t a) {
				return a >= 0 ? a : -a;
			}

			constexpr default_integral_t gcd(default_integral_t a, default_integral_t b) {
				return b == 0 ? a : gcd(b, a % b);
			}

			constexpr default_integral_t sign(default_integral_t a) {
				return a > 0 ? 1 : (a < 0 ? -1 : 0);
			}

			template<default_integral_t Numerator, default_integral_t Denominator, default_integral_t GreatestCommonDivisor = gcd(absolute(Numerator), absolute(Denominator))>
			struct multiplication_rational_constant {
				constexpr static decltype(auto) bind() {
					return multiplication(constant<(sign(Numerator) * sign(Denominator)) * (absolute(Numerator) / GreatestCommonDivisor)>(), exponentiation(constant<absolute(Denominator) / GreatestCommonDivisor>(), constant<-1>()));
				}
			};

			template<default_integral_t Numerator, default_integral_t Denominator>
			struct multiplication_rational_constant<Numerator, Denominator, 1> {
				constexpr static decltype(auto) bind() {
					return make_mul(constant<(sign(Numerator) * sign(Denominator)) * absolute(Numerator)>(), make_power(constant<absolute(Denominator)>(), constant<-1>()));
				}
			};

			template<default_integral_t RightValue, typename std::enable_if<RightValue != -1, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(constant<-1> const &, power<constant<RightValue>, constant<-1> > const &) {
				return make_power(constant<-RightValue>(), constant<-1>());
			}

			template<default_integral_t LeftValue, typename std::enable_if<LeftValue != -1, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(power<constant<LeftValue>, constant<-1> > const &, constant<-1> const &) {
				return make_power(constant<-LeftValue>(), constant<-1>());
			}

			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<LeftValue != 0 && LeftValue != 1 && LeftValue != -1 && LeftValue != RightValue, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(constant<LeftValue> const &, power<constant<RightValue>, constant<-1> > const &) {
				return multiplication_rational_constant<LeftValue, RightValue>::bind();
			}

			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<RightValue != 0 && RightValue != 1 && RightValue != -1 && LeftValue != RightValue, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(power<constant<LeftValue>, constant<-1> > const &, constant<RightValue> const &) {
				return multiplication_rational_constant<RightValue, LeftValue>::bind();
			}

			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<LeftValue != RightValue, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(power<constant<LeftValue>, constant<-1> > const &, power<constant<RightValue>, constant<-1> > const &) {
				return make_power(constant<LeftValue * RightValue>(), constant<-1>());
			}

			// Simplify to exponentiation (except for X == 0 and X == 1 and P == Q).
			//     X * X = X^{2}
			//     X^{P} * X = X^{P+1}
			//     X * X^{Q} = X^{1+Q}
			//     X^{P} * X^{Q} = X^{P+Q}
			template<class BaseExpressionType, typename std::enable_if<allows_lazy_simplification<BaseExpressionType>::value && !(std::is_same<BaseExpressionType, constant<0> >::value || std::is_same<BaseExpressionType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) multiplication_bind(BaseExpressionType const &lhs, BaseExpressionType const &) {
				return exponentiation(lhs, constant<2>());
			}

			template<class BaseExpressionType, class LeftPowerExpressionType, typename std::enable_if<allows_lazy_simplification<BaseExpressionType>::value && !(std::is_same<BaseExpressionType, constant<0> >::value || std::is_same<BaseExpressionType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) multiplication_bind(power<BaseExpressionType, LeftPowerExpressionType> const &lhs, BaseExpressionType const &) {
				return exponentiation(lhs.left(), addition(lhs.right(), constant<1>()));
			}

			template<class BaseExpressionType, class RightPowerExpressionType, typename std::enable_if<allows_lazy_simplification<BaseExpressionType>::value && !(std::is_same<BaseExpressionType, constant<0> >::value || std::is_same<BaseExpressionType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) multiplication_bind(BaseExpressionType const &, power<BaseExpressionType, RightPowerExpressionType> const &rhs) {
				return exponentiation(rhs.left(), addition(constant<1>(), rhs.right()));
			}

			template<class BaseExpressionType, class LeftPowerExpressionType, class RightPowerExpressionType, typename std::enable_if<allows_lazy_simplification<BaseExpressionType>::value && !std::is_same<LeftPowerExpressionType, RightPowerExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(power<BaseExpressionType, LeftPowerExpressionType> const &lhs, power<BaseExpressionType, RightPowerExpressionType> const &rhs) {
				return exponentiation(lhs.left(), addition(lhs.right(), rhs.right()));
			}
			
			// Multiplication merge.
			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<le<LeftExpressionType, RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return multiplication_bind(lhs, rhs);
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<lt<RightExpressionType, LeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return multiplication_bind(rhs, lhs);
			}

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<le<LeftExpressionType, RightLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(LeftExpressionType const &lhs, mul<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return multiplication_bind(lhs, rhs);
			}

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<lt<RightLeftExpressionType, LeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(LeftExpressionType const &lhs, mul<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return multiplication(rhs.left(), multiplication(lhs, rhs.right()));
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightExpressionType, typename std::enable_if<lt<RightExpressionType, LeftLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, RightExpressionType const &rhs) {
				return multiplication_bind(rhs, lhs);
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightExpressionType, typename std::enable_if<eq<LeftLeftExpressionType, RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, RightExpressionType const &rhs) {
				return multiplication(lhs.left(), multiplication(rhs, lhs.right()));
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightExpressionType, typename std::enable_if<lt<LeftLeftExpressionType, RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, RightExpressionType const &rhs) {
				return multiplication(lhs.left(), multiplication(lhs.right(), rhs));
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<eq<LeftLeftExpressionType, RightLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, mul<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return multiplication(lhs.left(), multiplication(rhs.left(), multiplication(lhs.right(), rhs.right())));
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<lt<LeftLeftExpressionType, RightLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, mul<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return multiplication(lhs.left(), multiplication(lhs.right(), rhs));
			}

			template<class LeftLeftExpressionType, class LeftRighExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<lt<RightLeftExpressionType, LeftLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftExpressionType, LeftRighExpressionType> const &lhs, mul<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return multiplication(rhs.left(), multiplication(lhs, rhs.right()));
			}

			// Distributive property over addition.
			//     A * (B + C) = (A * B) + (A * C)
			//     (A + B) * C = (A * C) + (B * C)
			//     (A + B) * (C + D) = ((A * C) + (B * C)) + ((A * D) + (B * D))
			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) multiplication(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return multiplication_merge(lhs, rhs);
			}

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			constexpr decltype(auto) multiplication(LeftExpressionType const &lhs, add<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return addition(multiplication(lhs, rhs.left()), multiplication(lhs, rhs.right()));
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType>
			constexpr decltype(auto) multiplication(add<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return addition(multiplication(lhs.left(), rhs), multiplication(lhs.right(), rhs));
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			constexpr decltype(auto) multiplication(add<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, add<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return addition(addition(multiplication(lhs.left(), rhs.left()), multiplication(lhs.right(), rhs.left())), addition(multiplication(lhs.left(), rhs.right()), multiplication(lhs.right(), rhs.right())));
			}

		}

	}

}

#endif // __GA_LAZY_MULTIPLICATION_HPP__
