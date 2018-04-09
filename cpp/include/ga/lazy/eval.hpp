#ifndef __GA_LAZY_EVAL__
#define __GA_LAZY_EVAL__

namespace ga {

	namespace lazy {

		namespace detail {

			//TODO Aplicar padrões na avaliação da expression.
			//TODO Usar divisão no lugar de pow.

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

			template<default_integral_t LeftValue, default_integral_t RightValue>
			constexpr decltype(auto) eval_lazy_mul(constant<LeftValue> const &, constant<RightValue> const &) {
				return constant<LeftValue * RightValue>();
			}

			template<class LeftExpressionType, class RightExpressionType>
			constexpr decltype(auto) eval_lazy_pow(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return val(std::pow(lhs.get(), rhs.get()));
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
				return value<ValueType>(arg.get());
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
			constexpr decltype(auto) eval_lazy_expression(pow<LeftExpressionType, RightExpressionType> const &arg) {
				return eval_lazy_pow(eval_lazy_expression(arg.left()), eval_lazy_expression(arg.right()));
			}

			template<class LeftExpressionType>
			constexpr decltype(auto) eval_lazy_expression(pow<LeftExpressionType, pow<constant<2>, constant<-1> > > const &arg) {
				return val(std::sqrt(eval_lazy_expression(arg.left()).get()));
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
