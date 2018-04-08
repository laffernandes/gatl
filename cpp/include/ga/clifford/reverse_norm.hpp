#ifndef __GA_CLIFFORD_REVERSE_NORM_HPP__
#define __GA_CLIFFORD_REVERSE_NORM_HPP__

namespace ga {

	namespace clifford {

		template<class Type, class MetricSpaceType>
		constexpr decltype(auto) rnorm_sqr(Type const &arg, metric_space<MetricSpaceType> const &mtr) {
			return scp(arg, reversion(arg), mtr);
		}

		template<class Type, class MetricSpaceType>
		constexpr decltype(auto) rnorm(Type const &arg, metric_space<MetricSpaceType> const &mtr) {
			return sqrt(rnorm_sqr(arg, mtr));
		}

	}

}

#endif // __GA_CLIFFORD_REVERSE_NORM_HPP__
