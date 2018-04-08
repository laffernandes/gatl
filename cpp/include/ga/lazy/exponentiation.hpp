#ifndef __GA_LAZY_EXPONENTIATION_HPP__
#define __GA_LAZY_EXPONENTIATION_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) exponentiation(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return make_pow(lhs, rhs);
			}

			constexpr std::uint64_t isqrt_impl(std::uint64_t sq, std::uint64_t dlt, std::uint64_t value) {
				return sq <= value ? isqrt_impl(sq + dlt, dlt + 2, value) : (dlt >> 1) - 1;
			}

			constexpr std::uint64_t isqrt(std::uint64_t value) {
				return isqrt_impl(1, 3, value);
			}

			template<default_integral_t Value>
			struct _sqrt_value {
			private:

				constexpr static default_integral_t result = static_cast<default_integral_t>(isqrt(Value));

				struct _return_constant {
					constexpr static decltype(auto) bind() {
						return constant<result>();
					}
				};

				struct _return_constant_sqrt {
					constexpr static decltype(auto) bind() {
						return make_pow(constant<Value>(), make_pow(constant<2>(), constant<-1>())); //TODO Pode ser melhorado
					}
				};

			public:

				constexpr static decltype(auto) bind() {
					return std::conditional<(result * result) == Value, _return_constant, _return_constant_sqrt>::type::bind();
				}
			};

			template<default_integral_t LeftValue, typename std::enable_if<(LeftValue >= 0), int>::type = 0>
			constexpr decltype(auto) exponentiation(constant<LeftValue> const &, pow<constant<2>, constant<-1> > const &) {
				return _sqrt_value<LeftValue>::bind();
			}

			template<default_integral_t LeftValue, default_integral_t RightValue, typename std::enable_if<(RightValue != 0) && (RightValue > 1), int>::type = 0>
			constexpr decltype(auto) exponentiation(constant<LeftValue> const &lhs, constant<RightValue> const &rhs) {
				return multiplication(multiplication(exponentiation(lhs, constant<RightValue / 2>()), exponentiation(lhs, constant<RightValue / 2>())), exponentiation(lhs, constant<RightValue % 2>()));
			}

			template<class LeftExpressionType>
			constexpr LeftExpressionType exponentiation(LeftExpressionType const &lhs, constant<1> const &) {
				return lhs;
			}

			template<class LeftExpressionType, typename std::enable_if<!std::is_same<LeftExpressionType, constant<0> >::value, int>::type = 0>
			constexpr constant<1> exponentiation(LeftExpressionType const &lhs, constant<0> const &) {
				return constant<1>();
			}

			template<class RightExpressionType, typename std::enable_if<!std::is_same<RightExpressionType, constant<0> >::value, int>::type = 0>
			constexpr constant<0> exponentiation(constant<0> const &, RightExpressionType const &rhs) {
				return constant<0>();
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType>
			constexpr decltype(auto) exponentiation(pow<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return exponentiation(lhs.left(), multiplication(lhs.right, rhs));
			}

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType>
			constexpr decltype(auto) exponentiation(mul<LeftLeftExpressionType, LeftRightExpressionType> const &lhs, RightExpressionType const &rhs) {
				return multiplication(exponentiation(lhs.left(), rhs), exponentiation(lhs.right(), rhs));
			}

		}

	}

}

#endif // __GA_LAZY_EXPONENTIATION_HPP__
