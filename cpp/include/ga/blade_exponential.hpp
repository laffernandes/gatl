#ifndef __GA_BLADE_EXPONENTIAL_HPP__
#define __GA_BLADE_EXPONENTIAL_HPP__

namespace ga {

	//TODO Try it!

	using std::exp;
	using detail::exp;

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType, class MetricType>
	decltype(auto) exp(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg, metric<MetricType> const &mtr) {
		//TODO Lazy
		//TODO Could be improved to use cvalue<>?
		auto signed_alpha_sqr = native(gp(arg, arg, mtr));
		if (abs(signed_alpha_sqr) <= tol) {
			return static_cast<decltype(signed_alpha_sqr)>(1) + arg;
		}
		else {
			auto alpha = sqrt(abs(signed_alpha_sqr));
			if (signed_alpha_sqr > 0) {
				return cosh(alpha) + (arg * (sinh(alpha) / alpha));
			}
			else {
				return cos(alpha) + (arg * (sin(alpha) / alpha));
			}
		}
	}

	template<class MetricType>
	constexpr decltype(auto) exp(detail::empty_expression const &, metric<MetricType> const &) {
		return detail::make_expression(detail::cvalue<1>(), detail::empty_expression(), detail::empty_expression());
	}

	template<default_integral_t Value, class MetricType>
	constexpr decltype(auto) exp(detail::cvalue<Value> const &, metric<MetricType> const &) {
		return detail::exp(detail::cvalue<Value>());
	}

}

#endif // __GA_BLADE_EXPONENTIAL_HPP__
