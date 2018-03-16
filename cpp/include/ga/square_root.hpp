#ifndef __GA_SQUARE_ROOT_HPP__
#define __GA_SQUARE_ROOT_HPP__

namespace ga {

	using std::sqrt;
	using detail::sqrt;

	template<class CoefficientType>
	constexpr decltype(auto) sqrt(detail::expression<detail::component<CoefficientType, detail::cbasis_blade<0> >, detail::empty_expression, detail::empty_expression> const &arg) {
		return sqrt(arg.element().coefficient());
	}

	template<class CoefficientType>
	constexpr decltype(auto) sqrt(detail::expression<detail::components<CoefficientType, default_bitset_t(1)>, detail::empty_expression, detail::empty_expression> const &arg) {
		return sqrt(arg.element().begin()->second);
	}

	constexpr detail::empty_expression sqrt(detail::empty_expression const &) {
		return detail::empty_expression();
	}

}

#endif // __GA_SQUARE_ROOT_HPP__
