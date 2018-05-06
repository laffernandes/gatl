#ifndef __GA_LAZY_EVAL__
#define __GA_LAZY_EVAL__

namespace ga {

	namespace lazy {

		namespace detail {

			// Specializarions of the eval_constant_to_primitive() function.
			template<default_integral_t Value>
			constexpr decltype(auto) eval_constant_to_primitive(constant<Value> const &) {
				return constant<Value>();
			}

			template<class... ArgumentTypes>
			constexpr decltype(auto) eval_constant_to_primitive(add<ArgumentTypes...> const &arg) {
				return eval_lazy_add(arg.left(), arg.right());
			}

			template<class... ArgumentTypes>
			constexpr decltype(auto) eval_constant_to_primitive(mul<ArgumentTypes...> const &arg) {
				return eval_lazy_mul(arg.left(), arg.right());
			}

			template<class LeftArgumentType, class RightArgumentType>
			constexpr decltype(auto) eval_constant_to_primitive(power<LeftArgumentType, RightArgumentType> const &) {
				return val(pow(static_cast<default_floating_point_t>(eval_constant_to_primitive(LeftArgumentType()).get()), eval_constant_to_primitive(RightArgumentType()).get()));
			}

			template<class LeftArgumentType>
			constexpr decltype(auto) eval_constant_to_primitive(power<LeftArgumentType, constant<-1> > const &) {
				return val(static_cast<default_floating_point_t>(1) / eval_constant_to_primitive(LeftArgumentType()).get());
			}

			template<class LeftArgumentType>
			constexpr decltype(auto) eval_constant_to_primitive(power<LeftArgumentType, power<constant<2>, constant<-1> > > const &) {
				return val(sqrt(static_cast<default_floating_point_t>(eval_constant_to_primitive(LeftArgumentType()).get())));
			}

			template<class LeftArgumentType>
			constexpr decltype(auto) eval_constant_to_primitive(power<LeftArgumentType, power<constant<3>, constant<-1> > > const &) {
				return val(cbrt(static_cast<default_floating_point_t>(eval_constant_to_primitive(LeftArgumentType()).get())));
			}

			// Specializations of the eval_lazy_add() function.
			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<!(is_lazy_constant<LeftArgumentType>::value || is_lazy_constant<RightArgumentType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_add(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return val(eval_lazy_expression(lhs).get() + eval_lazy_expression(rhs).get()); // default when both arguments are not constant expressions
			}

			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<is_lazy_constant<LeftArgumentType>::value && !is_lazy_constant<RightArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_add(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return val(eval_constant_to_primitive(lhs).get() + eval_lazy_expression(rhs).get()); // default when only the left-hand side argument is a constant expression
			}

			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<!is_lazy_constant<LeftArgumentType>::value && is_lazy_constant<RightArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_add(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return val(eval_lazy_expression(lhs).get() + eval_constant_to_primitive(rhs).get()); // default when only the right-hand side argument is a constant expression
			}

			template<class LeftArgumentType, class... RightRightArgumentTypes>
			constexpr decltype(auto) eval_lazy_add(LeftArgumentType const &lhs, mul<constant<-1>, RightRightArgumentTypes...> const &rhs) {
				return val(eval_lazy_expression(lhs).get() - eval_lazy_expression(rhs.right()).get()); // A - B = R
			}

			template<class... LeftRightArgumentTypes, class RightArgumentType>
			constexpr decltype(auto) eval_lazy_add(mul<constant<-1>, LeftRightArgumentTypes...> const &lhs, RightArgumentType const &rhs) {
				return val(eval_lazy_expression(rhs).get() - eval_lazy_expression(lhs.right()).get()); // (-A) + B = B - A = R
			}

			template<class ArgumentType, class... LeftRightArgumentTypes, class... RightRightArgumentTypes>
			constexpr decltype(auto) eval_lazy_add(mul<ArgumentType, LeftRightArgumentTypes...> const &lhs, mul<ArgumentType, RightRightArgumentTypes...> const &rhs) {
				return eval_lazy_mul(lhs.left(), eval_lazy_add(lhs.right(), rhs.right()));
			}

			template<class LeftLeftArgumentType, class... ArgumentTypes, class RightLeftArgumentType>
			constexpr decltype(auto) eval_lazy_add(mul<LeftLeftArgumentType, ArgumentTypes...> const &lhs, mul<RightLeftArgumentType, ArgumentTypes...> const &rhs) {
				return eval_lazy_mul(eval_lazy_add(lhs.left(), rhs.left()), lhs.right()); // (A * C) + (B * C) = (A + B) * C
			}

			template<class LeftLeftArgumentType, class... ArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes>
			constexpr decltype(auto) eval_lazy_add(mul<LeftLeftArgumentType, ArgumentTypes...> const &lhs, add<mul<RightLeftArgumentType, ArgumentTypes...>, RightRightArgumentTypes...> const &rhs) {
				return eval_lazy_add(eval_lazy_mul(eval_lazy_add(lhs.left(), rhs.left().left()), lhs.right()), rhs.right()); // (A * C) + ((B * C) + D) = (A + B) * C + D
			}

			template<class LeftLeftArgumentType, class... ArgumentTypes, class... LeftRightArgumentTypes, class RightLeftArgumentType>
			constexpr decltype(auto) eval_lazy_add(add<mul<LeftLeftArgumentType, ArgumentTypes...>, LeftRightArgumentTypes...> const &lhs, mul<RightLeftArgumentType, ArgumentTypes...> const &rhs) {
				return eval_lazy_add(eval_lazy_mul(eval_lazy_add(lhs.left().left(), rhs.left()), rhs.right()), lhs.right()); // ((A * C) + D) + (B * C) = (A + B) * C + D
			}

			// Specializations of the eval_lazy_mul() function.
			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<!(is_lazy_constant<LeftArgumentType>::value || is_lazy_constant<RightArgumentType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_mul(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return val(eval_lazy_expression(lhs).get() * eval_lazy_expression(rhs).get()); // default when both arguments are not constant expressions
			}

			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<is_lazy_constant<LeftArgumentType>::value && !is_lazy_constant<RightArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_mul(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return val(eval_constant_to_primitive(lhs).get() * eval_lazy_expression(rhs).get()); // default when only the left-hand side argument is a constant expression
			}

			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<!is_lazy_constant<LeftArgumentType>::value && is_lazy_constant<RightArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_mul(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return val(eval_lazy_expression(lhs).get() * eval_constant_to_primitive(rhs).get()); // default when only the right-hand side argument is a constant expression
			}

			template<class RightArgumentType>
			constexpr decltype(auto) eval_lazy_mul(constant<-1> const &, RightArgumentType const &rhs) {
				return val(-eval_lazy_expression(rhs).get()); // (-1) * A = -A
			}

			template<class LeftArgumentType>
			constexpr decltype(auto) eval_lazy_mul(LeftArgumentType const &lhs, constant<-1> const &) {
				return val(-eval_lazy_expression(lhs).get()); // A * (-1) = -A
			}

			template<class LeftArgumentType, class RightLeftArgumentType, typename std::enable_if<!(is_lazy_constant<LeftArgumentType>::value || is_lazy_constant<RightLeftArgumentType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_mul(LeftArgumentType const &lhs, power<RightLeftArgumentType, constant<-1> > const &rhs) {
				return val(eval_lazy_expression(lhs).get() / eval_lazy_expression(rhs.left()).get()); // A * (1 / B) = A / B
			}

			template<class LeftLeftArgumentType, class RightArgumentType, typename std::enable_if<!(is_lazy_constant<LeftLeftArgumentType>::value || is_lazy_constant<RightArgumentType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_mul(power<LeftLeftArgumentType, constant<-1> > const &lhs, RightArgumentType const &rhs) {
				return val(eval_lazy_expression(rhs).get() / eval_lazy_expression(lhs.left()).get()); // (1 / A) * B = B / A
			}

			template<class LeftLeftArgumentType, class RightLeftArgumentType>
			constexpr decltype(auto) eval_lazy_mul(power<LeftLeftArgumentType, constant<-1> > const &lhs, power<RightLeftArgumentType, constant<-1> > const &rhs) {
				return eval_lazy_power(eval_lazy_mul(lhs.left(), rhs.left()), constant<-1>()); // (1 / A) * (1 / B) = 1 / (A * B)
			}

			// Specializations of the eval_lazy_power() function.
			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<!(is_lazy_constant<LeftArgumentType>::value || is_lazy_constant<RightArgumentType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_power(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return val(pow(eval_lazy_expression(lhs).get(), eval_lazy_expression(rhs).get())); // default when both arguments are not constant expressions
			}

			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<is_lazy_constant<LeftArgumentType>::value, int>::value>
			constexpr decltype(auto) eval_lazy_power(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return val(pow(eval_constant_to_primitive(lhs).get(), eval_lazy_expression(rhs).get())); // default when the left-hand side argument is a constant expression
			}

			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<is_lazy_constant<RightArgumentType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_power(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return val(pow(eval_lazy_expression(lhs).get(), eval_constant_to_primitive(rhs).get())); // default when the right-hand side argument is a constant expression
			}

			template<class LeftArgumentType>
			constexpr decltype(auto) eval_lazy_power(LeftArgumentType const &lhs, constant<-1> const &) {
				return val(static_cast<default_floating_point_t>(1) / eval_lazy_expression(lhs).get()); // pow(A, -1) = 1 / A
			}

			template<class LeftArgumentType>
			constexpr decltype(auto) eval_lazy_power(LeftArgumentType const &lhs, power<constant<2>, constant<-1> > const &) {
				return val(sqrt(eval_lazy_expression(lhs).get())); // pow(A, 1 / 2) = sqrt(A)
			}

			template<class LeftArgumentType>
			constexpr decltype(auto) eval_lazy_power(LeftArgumentType const &lhs, power<constant<3>, constant<-1> > const &) {
				return val(cbrt(eval_lazy_expression(lhs).get())); // pow(A, 1 / 3) = cbrt(A)
			}

			// Specializations of the eval_lazy_expression() function.
			template<class ExpressionType>
			constexpr decltype(auto) eval_lazy_expression(lazy_expression<ExpressionType> const &arg) {
				return eval_lazy_expression(arg());
			}

			template<default_integral_t Value>
			constexpr constant<Value> eval_lazy_expression(constant<Value> const &) {
				return constant<Value>();
			}

			template<class ValueType>
			constexpr value<ValueType> eval_lazy_expression(value<ValueType> const &arg) {
				return arg;
			}

			template<class ValueType, id_t Id, id_t... SubIds>
			constexpr value<ValueType> eval_lazy_expression(variable<ValueType, Id, SubIds...> const &arg) {
				return val(arg.get()); // Convertion to value
			}

			template<class... ArgumentTypes, typename std::enable_if<!is_lazy_constant<add<ArgumentTypes...> >::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_expression(add<ArgumentTypes...> const &arg) {
				return eval_lazy_add(arg.left(), arg.right()); // Proxy to eval_lazy_add
			}

			template<class... ArgumentTypes, typename std::enable_if<!is_lazy_constant<mul<ArgumentTypes...> >::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_expression(mul<ArgumentTypes...> const &arg) {
				return eval_lazy_mul(arg.left(), arg.right()); // Proxy to eval_lazy_mul
			}
			
			template<class LeftArgumentType, class RightArgumentType, typename std::enable_if<!(is_lazy_constant<LeftArgumentType>::value && is_lazy_constant<RightArgumentType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_expression(power<LeftArgumentType, RightArgumentType> const &arg) {
				return eval_lazy_power(arg.left(), arg.right()); // Proxy to eval_lazy_power
			}

		}

		template<class Type, typename std::enable_if<!(is_lazy_expression<Type>::value || is_clifford_expression<Type>::value), int>::type = 0>
		constexpr Type eval(Type const &arg) {
			return arg;
		}

		template<class ExpressionType>
		constexpr decltype(auto) eval(lazy_expression<ExpressionType> const &arg) {
			return detail::eval_lazy_expression(arg());
		}

	}

}

#endif // __GA_LAZY_EVAL__
