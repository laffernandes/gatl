#ifndef __GA_CLIFFORD_BLADE_EXPONENTIAL_HPP__
#define __GA_CLIFFORD_BLADE_EXPONENTIAL_HPP__

namespace ga {

	namespace clifford {

		template<class Type, class MetricSpaceType, typename std::enable_if<!is_clifford_expression<Type>::value, int>::type = 0>
		constexpr decltype(auto) exp(Type const &arg, metric_space<MetricSpaceType> const &) {
			return exp(arg);
		}

		template<class ExpressionType, class MetricSpaceType, typename std::enable_if<detail::may_cast_to_native<ExpressionType>::value, int>::type = 0>
		constexpr decltype(auto) exp(clifford_expression<ExpressionType> const &arg, metric_space<MetricSpaceType> const &) {
			return exp(arg);
		}

		template<class ExpressionType, class MetricSpaceType, typename std::enable_if<!detail::may_cast_to_native<ExpressionType>::value, int>::type = 0>
		decltype(auto) exp(clifford_expression<ExpressionType> const &arg, metric_space<MetricSpaceType> const &mtr) {
			typedef decltype(sqrt(abs(scp(arg, arg, mtr)))) alpha_t;
			typedef typename std::common_type<decltype(cosh(alpha_t())), decltype(cos(alpha_t()))>::type scalar_t;
			//TODO lazy
			auto signed_alpha_sqr = scp(arg, arg, mtr);
			if (signed_alpha_sqr == 0) {
				return static_cast<scalar_t>(1) + (arg * static_cast<scalar_t>(1)); //TODO Gabiarra
			}
			else {
				alpha_t alpha = sqrt(abs(signed_alpha_sqr));
				if (signed_alpha_sqr > 0) {
					return cosh(alpha) + (arg * (sinh(alpha) / alpha));
				}
				else {
					return cos(alpha) + (arg * (sin(alpha) / alpha));
				}
			}
		}

	}

}

#endif // __GA_CLIFFORD_BLADE_EXPONENTIAL_HPP__
