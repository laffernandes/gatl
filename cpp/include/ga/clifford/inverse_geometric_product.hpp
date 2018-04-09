#ifndef __GA_CLIFFORD_INVERSE_GEOMETRIC_PRODUCT_HPP__
#define __GA_CLIFFORD_INVERSE_GEOMETRIC_PRODUCT_HPP___

namespace ga {

	namespace clifford {

		template<class LeftType, class RightType, class MetricSpaceType>
		constexpr decltype(auto) igp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &mtr) {
			return gp(lhs, inv(rhs, mtr), mtr);
		}

		using lazy::operator/;

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator/(clifford_expression<LeftExpressionType> const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return igp(lhs(), native(rhs()), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator/(clifford_expression<LeftExpressionType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return igp(lhs(), rhs(), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator/(lazy_expression<LeftExpressionType> const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return igp(lhs(), native(rhs()), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

	}

}

#endif // __GA_CLIFFORD_INVERSE_GEOMETRIC_PRODUCT_HPP__
