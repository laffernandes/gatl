#ifndef __GA_CLIFFORD_GRADED_PRODUCT_HPP__
#define __GA_CLIFFORD_GRADED_PRODUCT_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class LeftItrType, class RightItrType, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product_inner_loop(LeftItrType const &lhs, RightItrType const &rhs, metric_space<MetricSpaceType> const &mtr, KeepIfGradesFunc const &keep) {
				return graded_product_inner_loop(lhs, next(rhs), mtr, keep) + graded_product_element(lhs.element(), rhs.element(), mtr, keep);
			}

			template<class LeftItrType, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr empty_clifford_expression graded_product_inner_loop(LeftItrType const &, itr_end const &, metric_space<MetricSpaceType> const &, KeepIfGradesFunc const &) {
				return empty_clifford_expression();
			}

			template<class LeftItrType, class RightItrType, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product(LeftItrType const &lhs, RightItrType const &rhs, metric_space<MetricSpaceType> const &mtr, KeepIfGradesFunc const &keep) {
				return graded_product(next(lhs), rhs, mtr, keep) + graded_product_inner_loop(lhs, rhs, mtr, keep);
			}

			template<class RightItrType, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr empty_clifford_expression graded_product(itr_end const &, RightItrType const &, metric_space<MetricSpaceType> const &, KeepIfGradesFunc const &) {
				return empty_clifford_expression();
			}

			template<class LeftItrType, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr empty_clifford_expression graded_product(LeftItrType const &, itr_end const &, metric_space<MetricSpaceType> const &, KeepIfGradesFunc const &) {
				return empty_clifford_expression();
			}

			template<class MetricSpaceType, class KeepIfGradesFunc>
			constexpr empty_clifford_expression graded_product(itr_end const &, itr_end const &, metric_space<MetricSpaceType> const &, KeepIfGradesFunc const &) {
				return empty_clifford_expression();
			}

		}

	}

}

#endif // __GA_CLIFFORD_GRADED_PRODUCT_HPP__
