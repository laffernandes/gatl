#ifndef __FUTURE_GA_ARITHMETIC_OPERATORS_HPP__
#define __FUTURE_GA_ARITHMETIC_OPERATORS_HPP__

namespace ga {

	template<class RightCoefficientType, class RightExpression>
	constexpr clifford_expression<RightCoefficientType, RightExpression> operator+(clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return rhs;
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator+(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		typedef detail::lazy_arguments<LeftExpression, RightExpression> lazy;
		return detail::eval<detail::addition_t<lazy::argument_expression_t<0>, lazy::argument_expression_t<1> > >(lhs, rhs);
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
		typedef detail::lazy_arguments<RightExpression> lazy;
		return detail::eval<detail::product_t<detail::constant_value<-1>, lazy::argument_expression_t<0>, detail::real_mapping> >(rhs);
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) operator-(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		typedef detail::lazy_arguments<LeftExpression, RightExpression> lazy;
		return detail::eval<detail::addition_t<lazy::argument_expression_t<0>, detail::product_t<detail::constant_value<-1>, lazy::argument_expression_t<1>, detail::real_mapping> > >(lhs, rhs);
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

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression>
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
