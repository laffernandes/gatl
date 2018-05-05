#ifndef __GA_LAZY_ADDITION_HPP__
#define __GA_LAZY_ADDITION_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			// Default addition_bind operation.
			template<class LeftArgumentType, class RightArgumentType>
			constexpr decltype(auto) addition_make(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return add<LeftArgumentType, RightArgumentType>(lhs, rhs);
			}

			template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes>
			constexpr decltype(auto) addition_make(LeftArgumentType const &lhs, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return add<LeftArgumentType, RightLeftArgumentType, RightRightArgumentTypes...>(lhs, rhs);
			}

			template<class LeftArgumentType, class RightArgumentType>
			constexpr decltype(auto) addition_bind(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return addition_make(lhs, rhs);
			}

			// Simplify addition to zero.
			//     0 + X = X
			//     X + 0 = X
			//     0 + 0 = 0
			template<class RightArgumentType>
			constexpr RightArgumentType addition_bind(constant<0> const &, RightArgumentType const &rhs) {
				return rhs;
			}

			template<class LeftArgumentType>
			constexpr LeftArgumentType addition_bind(LeftArgumentType const &lhs, constant<0> const &) {
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
			template<class ArgumentType, typename std::enable_if<!std::is_same<ArgumentType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) addition_bind(ArgumentType const &lhs, ArgumentType const &) {
				return multiplication(constant<2>(), lhs);
			}

			template<class ArgumentType, class... RightRightArgumentTypes, typename std::enable_if<!std::is_same<ArgumentType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) addition_bind(ArgumentType const &lhs, add<ArgumentType, RightRightArgumentTypes...> const &rhs) {
				return addition(multiplication(constant<2>(), lhs), rhs.right());
			}

			template<default_integral_t LeftValue, class ArgumentType>
			constexpr decltype(auto) addition_bind(mul<constant<LeftValue>, ArgumentType> const &, ArgumentType const &rhs) {
				return multiplication(constant<LeftValue + 1>(), rhs);
			}

			template<default_integral_t LeftValue, class... ArgumentTypes>
			constexpr decltype(auto) addition_bind(mul<constant<LeftValue>, ArgumentTypes...> const &, mul<ArgumentTypes...> const &rhs) {
				return multiplication(constant<LeftValue + 1>(), rhs);
			}

			template<class ArgumentType, class... LeftRightArgumentTypes, typename std::enable_if<!std::is_same<ArgumentType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) addition_bind(add<ArgumentType, LeftRightArgumentTypes...> const &lhs, ArgumentType const &rhs) {
				return addition(multiplication(constant<2>(), rhs), lhs.right());
			}

			template<class ArgumentType, default_integral_t RightValue>
			constexpr decltype(auto) addition_bind(ArgumentType const &lhs, mul<constant<RightValue>, ArgumentType> const &) {
				return multiplication(constant<1 + RightValue>(), lhs);
			}

			template<class... ArgumentTypes, default_integral_t RightValue>
			constexpr decltype(auto) addition_bind(mul<ArgumentTypes...> const &lhs, mul<constant<RightValue>, ArgumentTypes...> const &) {
				return multiplication(constant<1 + RightValue>(), lhs);
			}

			template<default_integral_t LeftValue, class... ArgumentTypes, default_integral_t RightValue, typename std::enable_if<LeftValue != RightValue, int>::type = 0>
			constexpr decltype(auto) addition_bind(mul<constant<LeftValue>, ArgumentTypes...> const &lhs, mul<constant<RightValue>, ArgumentTypes...> const &) {
				return multiplication(constant<LeftValue + RightValue>(), lhs.right());
			}

			// Try to simplify the addition of constants (except for A == 0 and A == B).
			//     A + (B + C) = (A + B) + C
			struct _addition_bind_same_constant {
				template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes>
				constexpr static decltype(auto) bind(LeftArgumentType const &, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
					return addition_make(LeftArgumentType(), rhs);
				}
			};

			struct _addition_bind_simpler_constant {
				template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes>
				constexpr static decltype(auto) bind(LeftArgumentType const &, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
					return addition_bind(addition_bind(LeftArgumentType(), RightLeftArgumentType()), rhs.right());
				}
			};

			template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<is_lazy_constant<LeftArgumentType>::value && is_lazy_constant<RightLeftArgumentType>::value && !(std::is_same<LeftArgumentType, constant<0> >::value || std::is_same<LeftArgumentType, RightLeftArgumentType>::value), int>::type = 0>
			constexpr decltype(auto) addition_bind(LeftArgumentType const &, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return std::conditional<
					std::is_same<decltype(addition_bind(LeftArgumentType(), RightLeftArgumentType())), add<LeftArgumentType, RightLeftArgumentType> >::value,
					_addition_bind_same_constant,
					_addition_bind_simpler_constant
				>::type::bind(LeftArgumentType(), rhs);
			}

			// Addition merge (it is called by the default multiplication method).
			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<le<LeftArgumentType, RightArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return addition_bind(lhs, rhs);
			}

			template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<le<LeftArgumentType, RightLeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(LeftArgumentType const &lhs, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return addition_bind(lhs, rhs);
			}

			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<lt<RightArgumentType, LeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return addition_bind(rhs, lhs);
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightArgumentType, typename std::enable_if<lt<RightArgumentType, LeftLeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(add<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, RightArgumentType const &rhs) {
				return addition_bind(rhs, lhs);
			}

			template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<lt<RightLeftArgumentType, LeftArgumentType>::value && le<LeftArgumentType, typename add<RightLeftArgumentType, RightRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(LeftArgumentType const &lhs, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return addition_bind(rhs.left(), addition_bind(lhs, rhs.right()));
			}

			template<class LeftArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<lt<typename add<RightLeftArgumentType, RightRightArgumentTypes...>::right_type, LeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(LeftArgumentType const &lhs, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return addition_bind(rhs.left(), addition_bind(rhs.right(), lhs));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<lt<typename add<RightLeftArgumentType, RightRightArgumentTypes...>::right_type, LeftLeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(add<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return addition_bind(rhs.left(), addition_bind(rhs.right(), lhs));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightArgumentType, typename std::enable_if<le<typename add<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type, RightArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(add<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, RightArgumentType const &rhs) {
				return addition_bind(lhs.left(), addition_bind(lhs.right(), rhs));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<le<typename add<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type, RightLeftArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(add<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return addition_bind(lhs.left(), addition_bind(lhs.right(), rhs));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightArgumentType, typename std::enable_if<le<LeftLeftArgumentType, RightArgumentType>::value && lt<RightArgumentType, typename add<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(add<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, RightArgumentType const &rhs) {
				return addition_bind(lhs.left(), addition_bind(rhs, lhs.right()));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<le<LeftLeftArgumentType, RightLeftArgumentType>::value && lt<RightLeftArgumentType, typename add<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type>::value && le<typename add<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type, typename add<RightLeftArgumentType, RightRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(add<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return addition_bind(lhs.left(), addition_bind(rhs.left(), addition_bind(lhs.right(), rhs.right())));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<le<LeftLeftArgumentType, RightLeftArgumentType>::value && lt<typename add<RightLeftArgumentType, RightRightArgumentTypes...>::right_type, typename add<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(add<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return addition_bind(lhs.left(), addition_bind(rhs.left(), addition_bind(rhs.right(), lhs.right())));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<lt<RightLeftArgumentType, LeftLeftArgumentType>::value && le<typename add<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type, typename add<RightLeftArgumentType, RightRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(add<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return addition_bind(rhs.left(), addition_bind(lhs.left(), addition_bind(lhs.right(), rhs.right())));
			}

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes, typename std::enable_if<lt<RightLeftArgumentType, LeftLeftArgumentType>::value && le<LeftLeftArgumentType, typename add<RightLeftArgumentType, RightRightArgumentTypes...>::right_type>::value && lt<typename add<RightLeftArgumentType, RightRightArgumentTypes...>::right_type, typename add<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type>::value, int>::type = 0>
			constexpr decltype(auto) addition_merge(add<LeftLeftArgumentType, LeftRightArgumentTypes...> const &lhs, add<RightLeftArgumentType, RightRightArgumentTypes...> const &rhs) {
				return addition_bind(rhs.left(), addition_bind(lhs.left(), addition_bind(rhs.right(), lhs.right())));
			}

			template<class LeftArgumentType, class RightArgumentType>
			constexpr decltype(auto) addition(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return addition_merge(lhs, rhs);
			}

			// Evaluate the addition of values.
			template<class LeftValueType, class RightValueType>
			constexpr decltype(auto) addition(value<LeftValueType> const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_add(lhs, rhs);
			}

			template<class LeftValueType, class RightArgumentType, typename std::enable_if<!std::is_same<RightArgumentType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) addition(value<LeftValueType> const &lhs, RightArgumentType const &rhs) {
				return eval_lazy_add(lhs, rhs);
			}

			template<class LeftArgumentType, class RightValueType, typename std::enable_if<!std::is_same<LeftArgumentType, constant<0> >::value, int>::type = 0>
			constexpr decltype(auto) addition(LeftArgumentType const &lhs, value<RightValueType> const &rhs) {
				return eval_lazy_add(lhs, rhs);
			}

		}

	}

}

#endif // __GA_LAZY_ADDITION_HPP__
