#ifndef __GA_EXTRA_HPP__
#define __GA_EXTRA_HPP__

namespace ga {

	namespace detail {

		//TODO _inv_scalar

	}

	template<class Type, class MetricType>
	constexpr decltype(auto) inv(Type const &arg, metric<MetricType> const &mtr) {
		return gp(reversion(arg), detail::_inv_scalar(detail::begin(scp(arg, reversion(arg), mtr))), euclidean_metric_t());
	}

	template<class LeftType, class RightType, class MetricType>
	constexpr decltype(auto) igp(LeftType const &lhs, RightType const &rhs, metric<MetricType> const &mtr) {
		return gp(lhs, inv(rhs, mtr), mtr);
	}

	template<class Type, class PseudoscalarType, class MetricType>
	constexpr decltype(auto) dual(Type const &arg, PseudoscalarType const &pseudoscalar, metric<MetricType> const &mtr) {
		return gp(arg, inv(pseudoscalar, mtr), mtr);
	}

	template<class Type, class PseudoscalarType, class MetricType>
	constexpr decltype(auto) undual(Type const &arg, PseudoscalarType const &pseudoscalar, metric<MetricType> const &mtr) {
		return gp(arg, pseudoscalar, mtr);
	}

	template<class Type, class MetricType>
	constexpr decltype(auto) sqr_rnorm(Type const &arg, metric<MetricType> const &mtr) {
		return scp(arg, reversion(arg), mtr);
	}

	template<class Type, class MetricType>
	constexpr decltype(auto) rnorm(Type const &arg, metric<MetricType> const &mtr) {
		return sqrt(sqr_rnorm(arg, mtr));
	}

}

#endif // __GA_EXTRA_HPP__
