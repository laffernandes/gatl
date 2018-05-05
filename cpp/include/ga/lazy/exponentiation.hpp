#ifndef __GA_LAZY_EXPONENTIATION_HPP__
#define __GA_LAZY_EXPONENTIATION_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			// Default exponentiation "bind" operation.
			template<class LeftArgumentType, class RightArgumentType>
			constexpr decltype(auto) exponentiation(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return make_power(lhs, rhs);
			}

			// Simplify exponentiation of values.
			template<class LeftValueType, class RightValueType>
			constexpr decltype(auto) exponentiation(value<LeftValueType> const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_power(lhs, rhs);
			}

			template<class LeftValueType, class RightArgumentType, typename std::enable_if<!(std::is_same<RightArgumentType, constant<0> >::value || std::is_same<RightArgumentType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) exponentiation(value<LeftValueType> const &lhs, RightArgumentType const &rhs) {
				return eval_lazy_power(lhs, rhs);
			}

			template<class LeftArgumentType, class RightValueType, typename std::enable_if<!std::is_same<LeftArgumentType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) exponentiation(LeftArgumentType const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_power(lhs, rhs);
			}

			// Simplify zero raised to the constant power of X (except for X <= 0).
			//     0^{X} = 0, for X > 0
			template<default_integral_t Value>
			constexpr default_integral_t sign(constant<Value> const &) {
				return sign(Value);
			}

			template<class LeftArgumentType, class... RightArgumentTypes, typename std::enable_if<is_lazy_constant<mul<LeftArgumentType, RightArgumentTypes...> >::value, int>::type = 0>
			constexpr default_integral_t sign(mul<LeftArgumentType, RightArgumentTypes...> const &arg) {
				return sign(arg.left()) * sign(arg.right());
			}

			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<is_lazy_constant<LeftArgumentType>::value && is_lazy_constant<RightArgumentType>::value, int>::type = 0>
			constexpr default_integral_t sign(power<LeftArgumentType, RightArgumentType> const &) {
				return sign(LeftArgumentType());
			}

			template<class RightArgumentType, typename std::enable_if<is_lazy_constant<RightArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) exponentiation(constant<0> const &, RightArgumentType const &) {
				static_assert(sign(RightArgumentType()) > 0, "The value of pow(0, N) is undefined for N <= 0.");
				return constant<0>();
			}

			// Simplify one raised to the power of X.
			//     1^{X} = 1
			template<class RightArgumentType>
			constexpr decltype(auto) exponentiation(constant<1> const &, RightArgumentType const &) {
				return constant<1>();
			}

			// Simplify minus one raised to the power of K, for integer K.
			//     (-1)^{K} =  1, if K is odd
			//              = -1, if K is even
			template<default_integral_t RightValue, typename std::enable_if<(RightValue & 1) == 0, int>::type = 0>
			constexpr decltype(auto) exponentiation(constant<-1> const &, constant<RightValue> const &) {
				return constant<1>();
			}

			template<default_integral_t RightValue, typename std::enable_if<(RightValue & 1) == 1, int>::type = 0>
			constexpr decltype(auto) exponentiation(constant<-1> const &, constant<RightValue> const &) {
				return constant<-1>();
			}

			// Simplify something raised to the power of zero (except for X == 0 and X == 1 and X == -1).
			//     X^{0} = 1
			template<class LeftArgumentType, typename std::enable_if<!(std::is_same<LeftArgumentType, constant<0> >::value || std::is_same<LeftArgumentType, constant<1> >::value || std::is_same<LeftArgumentType, constant<-1> >::value), int>::type = 0>
			constexpr decltype(auto) exponentiation(LeftArgumentType const &lhs, constant<0> const &) {
				return constant<1>();
			}

			// Simplify something raised to the power of one (except for X == 0 and X == 1 and X == -1).
			//     X^{1} = X
			template<class LeftArgumentType, typename std::enable_if<!(std::is_same<LeftArgumentType, constant<0> >::value || std::is_same<LeftArgumentType, constant<1> >::value || std::is_same<LeftArgumentType, constant<-1> >::value), int>::type = 0>
			constexpr LeftArgumentType exponentiation(LeftArgumentType const &lhs, constant<1> const &) {
				return lhs;
			}

			// Simplify square root of integers (except for X <= 1).
			//     sqrt(X) = Y, if it is possible simplify for given integer X and Y values
			constexpr default_integral_t isqrt_impl(default_integral_t sq, default_integral_t dlt, default_integral_t value) {
				return sq <= value ? isqrt_impl(sq + dlt, dlt + 2, value) : (dlt >> 1) - 1;
			}

			constexpr default_integral_t isqrt(default_integral_t value) {
				return isqrt_impl(1, 3, value);
			}

			template<default_integral_t Value>
			struct exponentiation_isqrt {
			private:

				constexpr static default_integral_t result = isqrt(Value);

				struct return_constant {
					constexpr static decltype(auto) bind() {
						return constant<result>();
					}
				};

				struct return_constant_sqrt {
					constexpr static decltype(auto) bind() {
						return make_power(constant<Value>(), make_power(constant<2>(), constant<-1>()));
					}
				};

			public:

				constexpr static decltype(auto) bind() {
					return std::conditional<(result * result) == Value, return_constant, return_constant_sqrt>::type::bind();
				}
			};

			template<default_integral_t LeftValue, typename std::enable_if<(LeftValue > 1), int>::type = 0>
			constexpr decltype(auto) exponentiation(constant<LeftValue> const &, power<constant<2>, constant<-1> > const &) {
				return exponentiation_isqrt<LeftValue>::bind();
			}

			// Simplify constant raised to the power of other constant (except for X == 0 or X == 1 and X == -1 and Y == 0).
			//     X^{Y} = simpler
			constexpr default_integral_t ipow(default_integral_t base, default_integral_t exponent) {
				return exponent == 1 ? base : (exponent == 0 ? 1 : (ipow(base, exponent >> 1) * ipow(base, exponent >> 1) * ipow(base, exponent % 2)));
			}

			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<(LeftValue < -1 || 1 < LeftValue) && (RightValue > 0), int>::type = 0>
			constexpr decltype(auto) exponentiation(constant<LeftValue> const &, constant<RightValue> const &) {
				return constant<ipow(LeftValue, RightValue)>();
			}

			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<(LeftValue < -1 || 1 < LeftValue) && (RightValue < 0), int>::type = 0>
			constexpr decltype(auto) exponentiation(constant<LeftValue> const &, constant<RightValue> const &) {
				return make_power(constant<ipow(LeftValue, -RightValue)>(), constant<-1>());
			}

			// Simplify to single exponentiation (except for C == 0 and C == 1).
			//     (A^{B})^{C} = A^{B * C}
			template<class LeftLeftArgumentType, class LeftRightArgumentType, class RightArgumentType, typename std::enable_if<!(std::is_same<RightArgumentType, constant<0> >::value || std::is_same<RightArgumentType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) exponentiation(power<LeftLeftArgumentType, LeftRightArgumentType> const &lhs, RightArgumentType const &rhs) {
				return exponentiation(lhs.left(), multiplication(lhs.right(), rhs));
			}

			// Distributive property over multiplication (except for C == 0 and C == 1).
			//     (A * B)^{C} = A^{C} * B^{C}
			template<class... LeftArgumentTypes, class RightArgumentType, typename std::enable_if<!(std::is_same<RightArgumentType, constant<0> >::value || std::is_same<RightArgumentType, constant<1> >::value), int>::type = 0>
			constexpr decltype(auto) exponentiation(mul<LeftArgumentTypes...> const &lhs, RightArgumentType const &rhs) {
				return multiplication(exponentiation(lhs.left(), rhs), exponentiation(lhs.right(), rhs));
			}

		}

	}

}

#endif // __GA_LAZY_EXPONENTIATION_HPP__
