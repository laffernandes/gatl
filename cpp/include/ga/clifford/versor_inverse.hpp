#ifndef __GA_CLIFFORD_VERSOR_INVERSE_HPP__
#define __GA_CLIFFORD_VERSOR_INVERSE_HPP__

namespace ga {

	namespace clifford {

		template<class Type, class MetricSpaceType, typename std::enable_if<!is_clifford_expression<Type>::value, int>::type = 0>
		constexpr decltype(auto) inv(Type const &arg, metric_space<MetricSpaceType> const &) {
			return constant<1>() / arg;
		}

		template<class... ElementTypes, class MetricSpaceType, typename std::enable_if<detail::may_cast_to_native<clifford_expression<ElementTypes...> >::value, int>::type = 0>
		constexpr decltype(auto) inv(clifford_expression<ElementTypes...> const &arg, metric_space<MetricSpaceType> const &) {
			return constant<1>() / native(arg);
		}

		template<class... ElementTypes, class MetricSpaceType, typename std::enable_if<!detail::may_cast_to_native<clifford_expression<ElementTypes...> >::value, int>::type = 0>
		constexpr decltype(auto) inv(clifford_expression<ElementTypes...> const &arg, metric_space<MetricSpaceType> const &mtr) {
			return gp(reversion(arg), inv(rnorm_sqr(arg, mtr), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

	}

}

#endif // __GA_CLIFFORD_VERSOR_INVERSE_HPP__
