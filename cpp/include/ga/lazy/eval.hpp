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

			template<class LeftExpressionType, class RightLeftExpressionType>
			constexpr decltype(auto) eval_constant_to_primitive(mul<LeftExpressionType, power<RightLeftExpressionType, constant<-1> > > const &) {
				return val(static_cast<default_floating_point_t>(eval_constant_to_primitive(LeftExpressionType()).get()) / eval_constant_to_primitive(RightLeftExpressionType()).get());
			}

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_constant_to_primitive(power<LeftExpressionType, RightExpressionType> const &) {
				return val(pow(static_cast<default_floating_point_t>(eval_constant_to_primitive(LeftExpressionType()).get()), eval_constant_to_primitive(RightExpressionType()).get()));
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_constant_to_primitive(power<LeftExpressionType, constant<-1> > const &) {
				return val(static_cast<default_floating_point_t>(1) / eval_constant_to_primitive(LeftExpressionType()).get());
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_constant_to_primitive(power<LeftExpressionType, power<constant<2>, constant<-1> > > const &) {
				return val(sqrt(static_cast<default_floating_point_t>(eval_constant_to_primitive(LeftExpressionType()).get())));
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_constant_to_primitive(power<LeftExpressionType, power<constant<3>, constant<-1> > > const &) {
				return val(cbrt(static_cast<default_floating_point_t>(eval_constant_to_primitive(LeftExpressionType()).get())));
			}

			// Specializations of the eval_lazy_add() function.
			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<!(is_lazy_constant<LeftExpressionType>::value || is_lazy_constant<RightExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_add(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(eval_lazy_expression(lhs).get() + eval_lazy_expression(rhs).get()); // default when both arguments are not constant expressions
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<is_lazy_constant<LeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_add(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(eval_constant_to_primitive(lhs).get() + eval_lazy_expression(rhs).get()); // default when the left-hand side argument is a constant expression
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<is_lazy_constant<RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_add(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(eval_lazy_expression(lhs).get() + eval_constant_to_primitive(rhs).get()); // default when the right-hand side argument is a constant expression
			}

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_add(LeftExpressionType const &lhs, mul<RightExpressionType, constant<-1> > const &rhs) {
				return val(eval_lazy_expression(lhs).get() - eval_lazy_expression(rhs.left()).get()); // A - B = R
			}

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_add(mul<LeftExpressionType, constant<-1> > const &lhs, RightExpressionType const &rhs) {
				return val(eval_lazy_expression(rhs).get() - eval_lazy_expression(lhs.left()).get()); // (-A) + B = B - A = R
			}

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_add(LeftExpressionType const &lhs, mul<constant<-1>, RightExpressionType> const &rhs) {
				return val(eval_lazy_expression(lhs).get() - eval_lazy_expression(rhs.right()).get()); // A - B = R
			}

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_add(mul<constant<-1>, LeftExpressionType> const &lhs, RightExpressionType const &rhs) {
				return val(eval_lazy_expression(rhs).get() - eval_lazy_expression(lhs.right()).get()); // (-A) + B = B - A = R
			}

			template<class LeftValueType, class TailExpressionType, class RightValueType, typename std::enable_if<allows_lazy_simplification<TailExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_add(mul<value<LeftValueType>, TailExpressionType> const &lhs, mul<value<RightValueType>, TailExpressionType> const &rhs) {
				return eval_lazy_mul(val(lhs.left().get() + rhs.left().get()), lhs.right()); // (A * C) + (B * C) = (A + B) * C, where C is an expression of constants or variables
			}

			template<class LeftValueType, class TailExpressionType, class RightValueType, class RightTailExpressionType, typename std::enable_if<allows_lazy_simplification<TailExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_add(mul<value<LeftValueType>, TailExpressionType> const &lhs, add<mul<value<RightValueType>, TailExpressionType>, RightTailExpressionType> const &rhs) {
				return eval_lazy_add(eval_lazy_mul(val(lhs.left().get() + rhs.left().left().get()), lhs.right()), rhs.right()); // (A * C) + ((B * C) + D) = (A + B) * C + D, where C is an expression of constants or variables
			}

			template<class LeftValueType, class TailExpressionType, class LeftTailExpressionType, class RightValueType, typename std::enable_if<allows_lazy_simplification<TailExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_add(add<mul<value<LeftValueType>, TailExpressionType>, LeftTailExpressionType> const &lhs, mul<value<RightValueType>, TailExpressionType> const &rhs) {
				return eval_lazy_add(eval_lazy_mul(val(lhs.left().left().get() + rhs.left().get()), rhs.right()), lhs.right()); // ((A * C) + D) + (B * C) = (A + B) * C + D, where C is an expression of constants or variables
			}

			// Specializations of the eval_lazy_mul() function.
			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<!(is_lazy_constant<LeftExpressionType>::value || is_lazy_constant<RightExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_mul(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(eval_lazy_expression(lhs).get() * eval_lazy_expression(rhs).get()); // default when both arguments are not constant expressions
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<is_lazy_constant<LeftExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_mul(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(eval_constant_to_primitive(lhs).get() * eval_lazy_expression(rhs).get()); // default when the left-hand side argument is a constant expression
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<is_lazy_constant<RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_mul(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(eval_lazy_expression(lhs).get() * eval_constant_to_primitive(rhs).get()); // default when the right-hand side argument is a constant expression
			}

			template<class RightExpressionType>
			constexpr decltype(auto) eval_lazy_mul(constant<-1> const &, RightExpressionType const &rhs) {
				return val(-eval_lazy_expression(rhs).get()); // (-1) * A = -A
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_lazy_mul(LeftExpressionType const &lhs, constant<-1> const &) {
				return val(-eval_lazy_expression(lhs).get()); // A * (-1) = -A
			}

			template<class LeftExpressionType, class RightLeftExpressionType, typename std::enable_if<!(is_lazy_constant<LeftExpressionType>::value || is_lazy_constant<RightLeftExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_mul(LeftExpressionType const &lhs, power<RightLeftExpressionType, constant<-1> > const &rhs) {
				return val(eval_lazy_expression(lhs).get() / eval_lazy_expression(rhs.left()).get()); // A * (1 / B) = A / B
			}

			template<class LeftLeftExpressionType, class RightExpressionType, typename std::enable_if<!(is_lazy_constant<LeftLeftExpressionType>::value || is_lazy_constant<RightExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_mul(power<LeftLeftExpressionType, constant<-1> > const &lhs, RightExpressionType const &rhs) {
				return val(eval_lazy_expression(rhs).get() / eval_lazy_expression(lhs.left()).get()); // (1 / A) * B = B / A
			}

			template<class LeftLeftExpressionType, class RightLeftExpressionType>
			constexpr decltype(auto) eval_lazy_mul(power<LeftLeftExpressionType, constant<-1> > const &lhs, power<RightLeftExpressionType, constant<-1> > const &rhs) {
				return eval_lazy_power(eval_lazy_mul(lhs.left(), rhs.left()), constant<-1>()); // (1 / A) * (1 / B) = 1 / (A * B)
			}

			// Specializations of the eval_lazy_power() function.
			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<!(is_lazy_constant<LeftExpressionType>::value || is_lazy_constant<RightExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_power(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(pow(eval_lazy_expression(lhs).get(), eval_lazy_expression(rhs).get())); // default when both arguments are not constant expressions
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<is_lazy_constant<LeftExpressionType>::value, int>::value>
			constexpr decltype(auto) eval_lazy_power(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(pow(eval_constant_to_primitive(lhs).get(), eval_lazy_expression(rhs).get())); // default when the left-hand side argument is a constant expression
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<is_lazy_constant<RightExpressionType>::value, int>::type = 0>
			constexpr decltype(auto) eval_lazy_power(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(pow(eval_lazy_expression(lhs).get(), eval_constant_to_primitive(rhs).get())); // default when the right-hand side argument is a constant expression
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_lazy_power(LeftExpressionType const &lhs, constant<-1> const &) {
				return val(static_cast<default_floating_point_t>(1) / eval_lazy_expression(lhs).get()); // pow(A, -1) = 1 / A
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_lazy_power(LeftExpressionType const &lhs, power<constant<2>, constant<-1> > const &) {
				return val(sqrt(eval_lazy_expression(lhs).get())); // pow(A, 1 / 2) = sqrt(A)
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_lazy_power(LeftExpressionType const &lhs, power<constant<3>, constant<-1> > const &) {
				return val(cbrt(eval_lazy_expression(lhs).get())); // pow(A, 1 / 3) = cbrt(A)
			}

			// Specializations of the eval_lazy_expression() function.
			template<class ExpressionType>
			constexpr ExpressionType eval_lazy_expression(ExpressionType const &arg) {
				return arg; // Identity for value and constant expressions
			}

			template<id_t Id, class ValueType>
			constexpr value<ValueType> eval_lazy_expression(variable<Id, ValueType> const &arg) {
				return val(arg.get()); // Convertion to value
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<!(is_lazy_constant<LeftExpressionType>::value && is_lazy_constant<RightExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_expression(add<LeftExpressionType, RightExpressionType> const &arg) {
				return eval_lazy_add(arg.left(), arg.right()); // Proxy to eval_lazy_add
			}

			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<!(is_lazy_constant<LeftExpressionType>::value && is_lazy_constant<RightExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_expression(mul<LeftExpressionType, RightExpressionType> const &arg) {
				return eval_lazy_mul(arg.left(), arg.right()); // Proxy to eval_lazy_mul
			}
			
			template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<!(is_lazy_constant<LeftExpressionType>::value && is_lazy_constant<RightExpressionType>::value), int>::type = 0>
			constexpr decltype(auto) eval_lazy_expression(power<LeftExpressionType, RightExpressionType> const &arg) {
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
