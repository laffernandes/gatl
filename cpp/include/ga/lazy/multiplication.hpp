#ifndef __GA_LAZY_MULTIPLICATION_HPP__
#define __GA_LAZY_MULTIPLICATION_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) multiplication_bind(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return make_mul(lhs, rhs);
			}

			template<default_integral_t LeftValue, default_integral_t RightValue>
			struct _division_bind_constant {
				constexpr static constant<LeftValue / RightValue> bind() {
					return constant<LeftValue / RightValue>();
				}
			};

			constexpr default_integral_t gcd(default_integral_t a, default_integral_t b) {
				return b == 0 ? a : gcd(b, a % b);
			}

			template<default_integral_t LeftValue, default_integral_t RightValue>
			struct _division_bind_constant_div {
			private:

				constexpr static default_integral_t divisor = gcd(LeftValue >= 0 ? LeftValue : -LeftValue, RightValue >= 0 ? RightValue : -RightValue);

				struct keep_as_is {
					constexpr static decltype(auto) bind() {
						return make_mul(constant<LeftValue / divisor>(), make_pow(constant<RightValue / divisor>(), constant<-1>()));
					}
				};

				struct move_sign_to_left {
					constexpr static decltype(auto) bind() {
						return make_mul(constant<-LeftValue / divisor>(), make_pow(constant<-RightValue / divisor>(), constant<-1>()));
					}
				};

			public:

				constexpr static decltype(auto) bind() {
					return std::conditional<(RightValue >= 0), keep_as_is, move_sign_to_left>::type::bind();
				}
			};

			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<LeftValue != 1 && LeftValue != 0 && LeftValue != RightValue, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(constant<LeftValue> const &, pow<constant<RightValue>, constant<-1> > const &) {
				return std::conditional<(LeftValue % RightValue) == 0, _division_bind_constant<LeftValue, RightValue>, _division_bind_constant_div<LeftValue, RightValue> >::type::bind();
			}

			template<class BaseExpressionType, class LeftRightExpressionType, class RightRightExpressionType, typename std::enable_if<is_constant<BaseExpressionType>::value || is_variable<BaseExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(pow<BaseExpressionType, LeftRightExpressionType> const &lhs, pow<BaseExpressionType, RightRightExpressionType> const &rhs) {
				return exponentiation(lhs.left(), addition(lhs.right(), rhs.right()));
			}

			template<class BaseExpressionType, class LeftRightExpressionType, typename std::enable_if<is_constant<BaseExpressionType>::value || is_variable<BaseExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(pow<BaseExpressionType, LeftRightExpressionType> const &lhs, BaseExpressionType const &) {
				return exponentiation(lhs.left(), addition(lhs.right(), constant<1>()));
			}

			template<class BaseExpressionType, class RightRightExpressionType, typename std::enable_if<is_constant<BaseExpressionType>::value || is_variable<BaseExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(BaseExpressionType const &lhs, pow<BaseExpressionType, RightRightExpressionType> const &rhs) {
				return exponentiation(lhs, addition(constant<1>(), rhs.right()));
			}

			template<class BaseExpressionType, typename std::enable_if<is_constant<BaseExpressionType>::value || is_variable<BaseExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication_bind(BaseExpressionType const &lhs, BaseExpressionType const &) {
				return exponentiation(lhs, constant<2>());
			}

			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<LeftValue != 1 && LeftValue != 0 && RightValue != 1 && RightValue != 0, int>::type = 0>
			constexpr constant<LeftValue * RightValue> multiplication_bind(constant<LeftValue> const &, constant<RightValue> const &) {
				return constant<LeftValue * RightValue>();
			}

			constexpr constant<1> multiplication_bind(constant<1> const &, constant<1> const &) {
				return constant<1>();
			}

			constexpr constant<0> multiplication_bind(constant<0> const &, constant<0> const &) {
				return constant<0>();
			}

			template<default_integral_t LeftValue, default_integral_t RightValue, class RightRightExpressionType>
			constexpr decltype(auto) multiplication_bind(constant<LeftValue> const &, mul<constant<RightValue>, RightRightExpressionType> const &rhs) {
				return multiplication(constant<LeftValue * RightValue>(), rhs.right());
			}

			template<class LeftExpressionType, typename std::enable_if<!(std::is_same<LeftExpressionType, constant<1> >::value || std::is_same<LeftExpressionType, constant<0> >::value), int>::type = 0>
			constexpr LeftExpressionType multiplication_bind(LeftExpressionType const &lhs, constant<1> const &) {
				return lhs;
			}

			template<class LeftExpressionType, typename std::enable_if<!(std::is_same<LeftExpressionType, constant<1> >::value || std::is_same<LeftExpressionType, constant<0> >::value), int>::type = 0>
			constexpr constant<0> multiplication_bind(LeftExpressionType const &, constant<0> const &) {
				return constant<0>();
			}

			template<class RightExpressionType, typename std::enable_if<!(std::is_same<RightExpressionType, constant<1> >::value || std::is_same<RightExpressionType, constant<0> >::value), int>::type = 0>
			constexpr RightExpressionType multiplication_bind(constant<1> const &, RightExpressionType const &rhs) {
				return rhs;
			}

			template<class RightExpressionType, typename std::enable_if<!(std::is_same<RightExpressionType, constant<1> >::value || std::is_same<RightExpressionType, constant<0> >::value), int>::type = 0>
			constexpr constant<0> multiplication_bind(constant<0> const &, RightExpressionType const &) {
				return constant<0>();
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<le<LeftExpressionType, RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return multiplication_bind(lhs, rhs);
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<lt<RightExpressionType, LeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return multiplication(rhs, lhs);
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType, typename std::enable_if<le<LeftLeftExpressionType, RightExpressionType>::value && le<LeftRightExpressionType, RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication(mul<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return multiplication(lhs.left(), multiplication(lhs.right(), rhs));
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType, typename std::enable_if<le<LeftLeftExpressionType, RightExpressionType>::value && lt<RightExpressionType, LeftRightExpressionType>::value && (eq<LeftLeftExpressionType, RightExpressionType>::value && !is_value<LeftLeftExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) multiplication(mul<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return multiplication(multiplication_bind(lhs.left(), rhs), lhs.right());
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType, typename std::enable_if<le<LeftLeftExpressionType, RightExpressionType>::value && lt<RightExpressionType, LeftRightExpressionType>::value && (lt<LeftLeftExpressionType, RightExpressionType>::value || is_value<LeftLeftExpressionType>::value || is_value<RightExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) multiplication(mul<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return multiplication(lhs.left(), multiplication(rhs, lhs.right()));
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType, typename std::enable_if<lt<RightExpressionType, LeftLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication(mul<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return multiplication(rhs, lhs);
			}

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<lt<LeftExpressionType, RightLeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication(LeftExpressionType const &lhs, mul<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return multiplication_bind(lhs, rhs);
			}

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<eq<LeftExpressionType, RightLeftExpressionType>::value && !is_value<LeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication(LeftExpressionType const &lhs, mul<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return multiplication(multiplication_bind(lhs, rhs.left()), rhs.right());
			}

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<lt<RightLeftExpressionType, LeftExpressionType>::value && le<LeftExpressionType, RightRightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication(LeftExpressionType const &lhs, mul<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return multiplication(rhs.left(), multiplication(lhs, rhs.right()));
			}

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType, typename std::enable_if<lt<RightRightExpressionType, LeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) multiplication(LeftExpressionType const &lhs, mul<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return multiplication(rhs, lhs);
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			constexpr decltype(auto) multiplication(mul<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, mul<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return multiplication(lhs.left(), multiplication(lhs.right(), rhs));
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			constexpr decltype(auto) multiplication(add<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, add<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return addition(addition(addition(lhs.left(), rhs.left()), addition(lhs.right(), rhs.left())), addition(addition(lhs.left(), rhs.right()), addition(lhs.right(), rhs.right())));
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			constexpr decltype(auto) multiplication(mul<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, add<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return addition(multiplication(lhs, rhs.left()), multiplication(lhs, rhs.right()));
			}

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			constexpr decltype(auto) multiplication(LeftExpressionType const &lhs, add<RightLeftExpressionType, RightRightExpressionType> const &rhs) {
				return addition(multiplication(lhs, rhs.left()), multiplication(lhs, rhs.right()));
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType>
			constexpr decltype(auto) multiplication(add<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return addition(multiplication(lhs.left(), rhs), multiplication(lhs.right(), rhs));
			}

		}

	}

}

#endif // __GA_LAZY_MULTIPLICATION_HPP__
