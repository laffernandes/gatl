#ifndef __FUTURE_GA_ARITHMETIC_OPERATORS_HPP__
#define __FUTURE_GA_ARITHMETIC_OPERATORS_HPP__

namespace ga {

	template<class RightCoefficientType, class RightExpression>
	constexpr clifford_expression<RightCoefficientType, RightExpression> operator+(clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return rhs;
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator+(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		auto lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(clifford_expression<std::common_type_t<LeftCoefficientType, RightCoefficientType>, detail::addition_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1> > >());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType>
	constexpr decltype(auto) operator+(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return lhs + scalar(rhs);
	}

	template<class LeftType, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator+(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return scalar(lhs) + rhs;
	}

	template<class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator-(clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return gp(c<-1>, rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator-(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		auto const lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(lazy.argument<0>() + gp(c<-1>, lazy.argument<1>()));
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType>
	constexpr decltype(auto) operator-(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return lhs - scalar(rhs);
	}

	template<class LeftType, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator-(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return scalar(lhs) - rhs;
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator*(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return gp(lhs, rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType>
	constexpr decltype(auto) operator*(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return gp(lhs, rhs);
	}

	template<class LeftType, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator*(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return gp(lhs, rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator/(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return igp(lhs, rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType>
	constexpr decltype(auto) operator/(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return igp(lhs, rhs);
	}

	template<class LeftType, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator/(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return igp(lhs, rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression> > >
	constexpr decltype(auto) operator^(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return op(lhs, rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType>
	constexpr decltype(auto) operator^(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return op(lhs, rhs);
	}

	template<class LeftType, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator^(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return op(lhs, rhs);
	}

}

#endif // __FUTURE_GA_ARITHMETIC_OPERATORS_HPP__
