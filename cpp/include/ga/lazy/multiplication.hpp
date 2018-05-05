#ifndef __GA_LAZY_MULTIPLICATION_HPP__
#define __GA_LAZY_MULTIPLICATION_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			// Default multiplication_bind operation.
			template<class LeftArgumentType, class RightArgumentType>
			constexpr decltype(auto) multiplication_make(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return mul<LeftArgumentType, RightArgumentType>(lhs, rhs);
			}

			template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes>
			constexpr decltype(auto) multiplication_make(LeftArgumentType const &lhs, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return mul<LeftArgumentType, RightLeftArgumentType, RightRightArgumentTypes...>(lhs, rhs);
			}

			template<class LeftArgumentType, class RightArgumentType>
			constexpr decltype(auto) multiplication_bind(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return multiplication_make(lhs, rhs);
			}

			// Simplify multiplication by zero.
			//     0 * X = 0
			//     X * 0 = 0
			//     0 * 0 = 0
			template<class RightArgumentType>
			constexpr decltype(auto) multiplication_bind(constant<0> const &, RightArgumentType const &) {
				return constant<0>();
			}

			template<class LeftArgumentType>
			constexpr decltype(auto) multiplication_bind(LeftArgumentType const &, constant<0> const &) {
				return constant<0>();
			}

			constexpr decltype(auto) multiplication_bind(constant<0> const &, constant<0> const &) {
				return constant<0>();
			}

			// Simplify multiplication by one (except for X == 0).
			//     1 * X = X
			//     X * 1 = X
			//     1 * 1 = 1
			template<class RightArgumentType, typename std::enable_if<!std::is_same<RightArgumentType, constant<0> >::value, int>::type = 0>
			constexpr RightArgumentType multiplication_bind(constant<1> const &, RightArgumentType const &rhs) {
				return rhs;
			}

			template<class LeftArgumentType, typename std::enable_if<!std::is_same<LeftArgumentType, constant<0> >::value, int>::type = 0>
			constexpr LeftArgumentType multiplication_bind(LeftArgumentType const &lhs, constant<1> const &) {
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
					return multiplication_make(constant<(sign(Numerator) * sign(Denominator)) * absolute(Numerator)>(), make_power(constant<absolute(Denominator)>(), constant<-1>()));
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
			template<class BaseArgumentType, typename std::enable_if<!(std::is_same<BaseArgumentType, constant<0> >::value || std::is_same<BaseArgumentType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) multiplication_bind(BaseArgumentType const &lhs, BaseArgumentType const &) {
				return exponentiation(lhs, constant<2>());
			}

			template<class BaseArgumentType, class LeftPowerArgumentType, typename std::enable_if<!(std::is_same<BaseArgumentType, constant<0> >::value || std::is_same<BaseArgumentType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) multiplication_bind(power<BaseArgumentType, LeftPowerArgumentType> const &lhs, BaseArgumentType const &) {
				return exponentiation(lhs.left(), addition(lhs.right(), constant<1>()));
			}

			template<class BaseArgumentType, class RightPowerArgumentType, typename std::enable_if<!(std::is_same<BaseArgumentType, constant<0> >::value || std::is_same<BaseArgumentType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) multiplication_bind(BaseArgumentType const &, power<BaseArgumentType, RightPowerArgumentType> const &rhs) {
				return exponentiation(rhs.left(), addition(constant<1>(), rhs.right()));
			}

			template<class BaseArgumentType, class LeftPowerArgumentType, class RightPowerArgumentType, typename std::enable_if<!std::is_same<LeftPowerArgumentType, RightPowerArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(power<BaseArgumentType, LeftPowerArgumentType> const &lhs, power<BaseArgumentType, RightPowerArgumentType> const &rhs) {
				return exponentiation(lhs.left(), addition(lhs.right(), rhs.right()));
			}

			// Try to simplify the multiplication of constants (except for A == 0 and A == 1 and B == 0 and B == 1 and A == B).
			//     A * (B * C) = (A * B) * C
			struct _multiplication_bind_same_constant {
				template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes>
				constexpr static decltype(auto) bind(LeftArgumentType const &, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
					return multiplication_make(LeftArgumentType(), rhs);
				}
			};

			struct _multiplication_bind_simpler_constant {
				template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes>
				constexpr static decltype(auto) bind(LeftArgumentType const &, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
					return multiplication_bind(multiplication_bind(LeftArgumentType(), RightLeftArgumentType()), rhs.right());
				}
			};

			template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<is_lazy_constant<LeftArgumentType>::value && is_lazy_constant<RightLeftArgumentType>::value && !(std::is_same<LeftArgumentType, constant<0> >::value || std::is_same<LeftArgumentType, constant<1> >::value || std::is_same<RightLeftArgumentType, constant<0> >::value || std::is_same<RightLeftArgumentType, constant<1> >::value || std::is_same<LeftArgumentType, RightLeftArgumentType>::value), int>::type = 0>
			constexpr decltype(auto) multiplication_bind(LeftArgumentType const &, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return std::conditional<
					std::is_same<decltype(multiplication_bind(LeftArgumentType(), RightLeftArgumentType())), mul<LeftArgumentType, RightLeftArgumentType> >::value,
					_multiplication_bind_same_constant,
					_multiplication_bind_simpler_constant
				>::type::bind(LeftArgumentType(), rhs);
			}

			// Multiplication merge (it is called by the default multiplication method).
			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<le<LeftArgumentType, RightArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return multiplication_bind(lhs, rhs);
			}

			template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<le<LeftArgumentType, RightLeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(LeftArgumentType const &lhs, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return multiplication_bind(lhs, rhs);
			}

			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<lt<RightArgumentType, LeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return multiplication_bind(rhs, lhs);
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightArgumentType, typename std::enable_if<lt<RightArgumentType, LeftLeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, RightArgumentType const &rhs) {
				return multiplication_bind(rhs, lhs);
			}

			template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<lt<RightLeftArgumentType, LeftArgumentType>::value && le<LeftArgumentType, typename mul<RightLeftArgumentType, RightRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(LeftArgumentType const &lhs, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return multiplication_bind(rhs.left(), multiplication_bind(lhs, rhs.right()));
			}

			template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<lt<typename mul<RightLeftArgumentType, RightRightArgumentTypes...>::right_type, LeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(LeftArgumentType const &lhs, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return multiplication_bind(rhs.left(), multiplication_bind(rhs.right(), lhs));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<lt<typename mul<RightLeftArgumentType, RightRightArgumentTypes...>::right_type, LeftLeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return multiplication_bind(rhs.left(), multiplication_bind(rhs.right(), lhs));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightArgumentType, typename std::enable_if<le<typename mul<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type, RightArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, RightArgumentType const &rhs) {
				return multiplication_bind(lhs.left(), multiplication_bind(lhs.right(), rhs));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<le<typename mul<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type, RightLeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return multiplication_bind(lhs.left(), multiplication_bind(lhs.right(), rhs));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightArgumentType, typename std::enable_if<le<LeftLeftArgumentType, RightArgumentType>::value && lt<RightArgumentType, typename mul<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, RightArgumentType const &rhs) {
				return multiplication_bind(lhs.left(), multiplication_bind(rhs, lhs.right()));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<le<LeftLeftArgumentType, RightLeftArgumentType>::value && lt<RightLeftArgumentType, typename mul<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type>::value && le<typename mul<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type, typename mul<RightLeftArgumentType, RightRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return multiplication_bind(lhs.left(), multiplication_bind(rhs.left(), multiplication_bind(lhs.right(), rhs.right())));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<le<LeftLeftArgumentType, RightLeftArgumentType>::value && lt<typename mul<RightLeftArgumentType, RightRightArgumentTypes...>::right_type, typename mul<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return multiplication_bind(lhs.left(), multiplication_bind(rhs.left(), multiplication_bind(rhs.right(), lhs.right())));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<lt<RightLeftArgumentType, LeftLeftArgumentType>::value && le<typename mul<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type, typename mul<RightLeftArgumentType, RightRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return multiplication_bind(rhs.left(), multiplication_bind(lhs.left(), multiplication_bind(lhs.right(), rhs.right())));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<lt<RightLeftArgumentType, LeftLeftArgumentType>::value && le<LeftLeftArgumentType, typename mul<RightLeftArgumentType, RightRightArgumentTypes...>::right_type>::value && lt<typename mul<RightLeftArgumentType, RightRightArgumentTypes...>::right_type, typename mul<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_merge(mul<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, mul<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return multiplication_bind(rhs.left(), multiplication_bind(lhs.left(), multiplication_bind(rhs.right(), lhs.right())));
			}

			template<class LeftArgumentType, class RightArgumentType>
			constexpr decltype(auto) multiplication(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return multiplication_merge(lhs, rhs);
			}

			// Apply the distributive property over addition (except for values).
			template<class LeftArgumentType, class... RightArgumentTypes, typename std::enable_if<!is_lazy_value<LeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication(LeftArgumentType const &lhs, add<RightArgumentTypes...> const &rhs) {
				return addition(multiplication(lhs, rhs.left()), multiplication(lhs, rhs.right()));
			}

			template<class... LeftArgumentTypes, class RightArgumentType, typename std::enable_if<!is_lazy_value<RightArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication(add<LeftArgumentTypes...> const &lhs, RightArgumentType const &rhs) {
				return addition(multiplication(lhs.left(), rhs), multiplication(lhs.right(), rhs));
			}

			template<class... LeftArgumentTypes, class... RightArgumentTypes>
			constexpr decltype(auto) multiplication(add<LeftArgumentTypes...> const &lhs, add<RightArgumentTypes...> const &rhs) {
				return addition(addition(multiplication(lhs.left(), rhs.left()), multiplication(lhs.right(), rhs.left())), addition(multiplication(lhs.left(), rhs.right()), multiplication(lhs.right(), rhs.right())));
			}

			// Evaluate the multiplication of values.
			template<class LeftValueType, class RightValueType>
			constexpr decltype(auto) multiplication(value<LeftValueType> const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_mul(lhs, rhs);
			}

			template<class LeftValueType, class RightArgumentType, typename std::enable_if<!(std::is_same<RightArgumentType, constant<0> >::value || std::is_same<RightArgumentType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) multiplication(value<LeftValueType> const &lhs, RightArgumentType const &rhs) {
				return eval_lazy_mul(lhs, rhs);
			}

			template<class LeftArgumentType, class RightValueType, typename std::enable_if<!(std::is_same<LeftArgumentType, constant<0> >::value || std::is_same<LeftArgumentType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) multiplication(LeftArgumentType const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_mul(lhs, rhs);
			}

		}

	}

}

#endif // __GA_LAZY_MULTIPLICATION_HPP__
