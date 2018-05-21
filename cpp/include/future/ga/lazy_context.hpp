#ifndef __FUTURE_GA_LAZY_CONTEXT_HPP__
#define __FUTURE_GA_LAZY_CONTEXT_HPP__

namespace ga {

	template<class FirstInputType, class... OtherInputTypes>
	class lazy_context;

	template<class FirstInputCoefficientType, class FirstInputExpression, class... OtherInputCoefficientTypes, class... OtherInputExpressions>
	class lazy_context<clifford_expression<FirstInputCoefficientType, FirstInputExpression>, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions>...> final {
	private:

		typedef std::tuple<clifford_expression<FirstInputCoefficientType, FirstInputExpression> const &, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions> const &...> arguments_type;

		typedef detail::lazy_arguments<FirstInputExpression, OtherInputExpressions...> lazy_arguments_type;

	public:

		constexpr lazy_context(lazy_context const &) = default;
		constexpr lazy_context(lazy_context &&) = default;

		constexpr lazy_context(clifford_expression<FirstInputCoefficientType, FirstInputExpression> const &arg0, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions> const &... args) :
			arguments_(arg0, args...) {
		}

		constexpr lazy_context & operator=(lazy_context const &) = delete;
		constexpr lazy_context & operator=(lazy_context &&) = delete;

		template<std::size_t Index>
		constexpr decltype(auto) argument() const {
			return clifford_expression<typename std::remove_const_t<std::remove_reference_t<std::tuple_element_t<Index, arguments_type> > >::coefficient_type, lazy_arguments_type::argument_expression_t<Index> >();
		}

		template<class CoefficientType, class ExpressionType>
		constexpr decltype(auto) eval(clifford_expression<CoefficientType, ExpressionType> const &) const {
			return detail::eval<ExpressionType>(arguments_);
		}

	private:

		arguments_type const arguments_;
	};

	template<class FirstInputType, class... OtherInputTypes>
	constexpr decltype(auto) make_lazy_context(FirstInputType const &arg0, OtherInputTypes const &... args) {
		return lazy_context<FirstInputType, OtherInputTypes...>(arg0, args...);
	}

}

#endif // __FUTURE_GA_LAZY_CONTEXT_HPP__
