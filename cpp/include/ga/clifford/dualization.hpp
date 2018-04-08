#ifndef __GA_CLIFFORD_DUALIZATION_HPP__
#define __GA_CLIFFORD_DUALIZATION_HPP__

namespace ga {

	namespace clifford {

		template<class Type, class PseudoscalarType, class MetricSpaceType>
		constexpr decltype(auto) dual(Type const &arg, PseudoscalarType const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) {
			return lcont(arg, inv(pseudoscalar, mtr), mtr);
		}

		template<class Type, class PseudoscalarType, class MetricSpaceType>
		constexpr decltype(auto) undual(Type const &arg, PseudoscalarType const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) {
			return lcont(arg, pseudoscalar, mtr);
		}

	}

}

#endif // __GA_CLIFFORD_DUALIZATION_HPP__
