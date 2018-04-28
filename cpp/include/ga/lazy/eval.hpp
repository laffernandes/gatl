#ifndef __GA_LAZY_EVAL__
#define __GA_LAZY_EVAL__

namespace ga {

	namespace lazy {

		namespace detail {

			//TODO Aplicar padrões na avaliação da expression.

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_add(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(lhs.get() + rhs.get());
			}

			template<default_integral_t LeftValue, default_integral_t RightValue>
			constexpr decltype(auto) eval_lazy_add(constant<LeftValue> const &, constant<RightValue> const &) {
				return constant<LeftValue + RightValue>();
			}

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_mul(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(lhs.get() * rhs.get());
			}

			template<class RightExpressionType>
			constexpr decltype(auto) eval_lazy_mul(constant<-1> const &, RightExpressionType const &rhs) {
				return val(-rhs.get());
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_lazy_mul(LeftExpressionType const &lhs, constant<-1> const &) {
				return val(-lhs.get());
			}

			constexpr decltype(auto) eval_lazy_mul(constant<-1> const &, constant<-1> const &) {
				return constant<1>();
			}

			template<default_integral_t LeftValue, default_integral_t RightValue>
			constexpr decltype(auto) eval_lazy_mul(constant<LeftValue> const &, constant<RightValue> const &) {
				return constant<LeftValue * RightValue>();
			}

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_div(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(lhs.get() / rhs.get());
			}

			template<default_integral_t LeftValue, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_div(constant<LeftValue> const &, RightExpressionType const &rhs) {
				typedef typename std::conditional<std::is_floating_point<typename RightExpressionType::value_type>::value, default_integral_t, default_floating_point_t>::type constant_value_t;
				return val(static_cast<constant_value_t>(LeftValue) / rhs.get());
			}

			template<class LeftExpressionType, default_integral_t RightValue>
			constexpr decltype(auto) eval_lazy_div(LeftExpressionType const &lhs, constant<RightValue> const &rhs) {
				typedef typename std::conditional<std::is_floating_point<typename LeftExpressionType::value_type>::value, default_integral_t, default_floating_point_t>::type constant_value_t;
				return val(lhs.get() / static_cast<constant_value_t>(RightValue));
			}

			template<default_integral_t LeftValue, default_integral_t RightValue>
			constexpr decltype(auto) eval_lazy_div(constant<LeftValue> const &, constant<RightValue> const &) {
				return val(static_cast<default_floating_point_t>(LeftValue) / RightValue);
			}

			template<default_integral_t Value>
			constexpr constant<Value> eval_lazy_expression(constant<Value> const &) {
				return constant<Value>();
			}

			template<class ValueType>
			constexpr value<ValueType> eval_lazy_expression(value<ValueType> const &arg) {
				return arg;
			}

			template<id_t Id, class ValueType>
			constexpr value<ValueType> eval_lazy_expression(variable<Id, ValueType> const &arg) {
				return val(arg.get());
			}

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_expression(add<LeftExpressionType, RightExpressionType> const &arg) {
				return eval_lazy_add(eval_lazy_expression(arg.left()), eval_lazy_expression(arg.right()));
			}

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_expression(mul<LeftExpressionType, RightExpressionType> const &arg) {
				return eval_lazy_mul(eval_lazy_expression(arg.left()), eval_lazy_expression(arg.right()));
			}
			
			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_expression(mul<LeftExpressionType, power<RightExpressionType, constant<-1> > > const &arg) {
				return eval_lazy_div(eval_lazy_expression(arg.left()), eval_lazy_expression(arg.right().left()));
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_lazy_expression(power<LeftExpressionType, constant<-1> > const &arg) {
				return eval_lazy_div(constant<1>(), eval_lazy_expression(arg.left()));
			}

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_expression(power<LeftExpressionType, RightExpressionType> const &arg) {
				return val(pow(eval_lazy_expression(arg.left()).get(), eval_lazy_expression(arg.right()).get()));
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_lazy_expression(power<LeftExpressionType, power<constant<2>, constant<-1> > > const &arg) {
				return val(sqrt(eval_lazy_expression(arg.left()).get()));
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_lazy_expression(power<LeftExpressionType, power<constant<3>, constant<-1> > > const &arg) {
				return val(cbrt(eval_lazy_expression(arg.left()).get()));
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
