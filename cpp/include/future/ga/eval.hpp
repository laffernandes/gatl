#ifndef __FUTURE_GA_EVAL_HPP__
#define __FUTURE_GA_EVAL_HPP__

namespace ga {

	namespace detail {

		template<class Expression, class FirstInputCoefficientType, class FirstInputExpression, class... OtherInputCoefficientTypes, class... OtherInputExpressions>
		constexpr decltype(auto) eval(std::tuple<clifford_expression<FirstInputCoefficientType, FirstInputExpression> const &, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions> const &...> const &args) {
			//TODO Implementar
			return clifford_expression<std::common_type_t<FirstInputCoefficientType, OtherInputCoefficientTypes...>, lazy_arguments<FirstInputExpression, OtherInputExpressions...>::result_expression_t<Expression> >();
		}

		template<class Expression, class FirstInputCoefficientType, class FirstInputExpression, class... OtherInputCoefficientTypes, class... OtherInputExpressions>
		constexpr decltype(auto) eval(clifford_expression<FirstInputCoefficientType, FirstInputExpression> const &arg0, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions> const &... args) {
			return eval<Expression>(std::tie(arg0, args...));
		}

	}

}

#endif // __FUTURE_GA_EVAL_HPP__
