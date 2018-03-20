#ifndef __GA_BLADE_EXPONENTIAL_HPP__
#define __GA_BLADE_EXPONENTIAL_HPP__

namespace ga {

	template<class Type, class MetricSpaceType>
	constexpr decltype(auto) exp(Type const &arg, metric_space<MetricSpaceType> const &) {
		return exp(arg);
	}

	template<default_integral_t Value, class MetricSpaceType>
	constexpr decltype(auto) exp(detail::cvalue<Value> const &, metric_space<MetricSpaceType> const &) {
		return detail::exp(detail::cvalue<Value>());
	}

	template<class MetricSpaceType>
	constexpr decltype(auto) exp(detail::empty_expression const &, metric_space<MetricSpaceType> const &) {
		return exp(detail::empty_expression());
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType, class MetricSpaceType>
	decltype(auto) exp(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg, metric_space<MetricSpaceType> const &mtr) {
		//TODO lazy
		//TODO Possible return issues.
		auto signed_alpha_sqr = scp(arg, arg, mtr);
		auto native_signed_alpha_sqr = native(signed_alpha_sqr);
		if (native_signed_alpha_sqr == 0) {
			return cvalue<1>() + arg;
		}
		else {
			auto alpha = sqrt(abs(signed_alpha_sqr));
			if (native_signed_alpha_sqr > 0) {
				return cosh(alpha) + (arg * (sinh(alpha) / alpha));
			}
			else {
				return cos(alpha) + (arg * (sin(alpha) / alpha));
			}
		}
	}

}

#endif // __GA_BLADE_EXPONENTIAL_HPP__
