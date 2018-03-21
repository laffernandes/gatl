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

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType, class MetricSpaceType, typename std::enable_if<detail::may_cast_to_native<detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> >::value, int>::type = 0>
	constexpr decltype(auto) exp(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg, metric_space<MetricSpaceType> const &) {
		return exp(arg);
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType, class MetricSpaceType, typename std::enable_if<!detail::may_cast_to_native<detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> >::value, int>::type = 0>
	decltype(auto) exp(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg, metric_space<MetricSpaceType> const &mtr) {
		typedef decltype(sqrt(abs(scp(arg, arg, mtr)))) alpha_t;
		typedef typename std::common_type<decltype(cosh(alpha_t())), decltype(cos(alpha_t()))>::type scalar_t;
		//TODO lazy
		auto signed_alpha_sqr = scp(arg, arg, mtr);
		auto native_signed_alpha_sqr = native(signed_alpha_sqr);
		if (native_signed_alpha_sqr == 0) {
			return static_cast<scalar_t>(1) + (arg * static_cast<scalar_t>(1)); //TODO Gabiarra
		}
		else {
			alpha_t alpha = sqrt(abs(signed_alpha_sqr));
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
