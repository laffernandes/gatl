#ifndef __GA_CLIFFORD_GRADED_PRODUCT_HPP__
#define __GA_CLIFFORD_GRADED_PRODUCT_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class LeftElementType, class... LeftOtherElementTypes, class RightElementType, class... RightOtherElementTypes, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product_inner_loop(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &lhs, clifford_expression<RightElementType, RightOtherElementTypes...> const &rhs, metric_space<MetricSpaceType> const &mtr, KeepIfGradesFunc const &keep) {
				return (graded_product_inner_loop(lhs, rhs.next(), mtr, keep) + graded_product_element(lhs.element(), rhs.element(), mtr, keep));
			}

			template<class LeftElementType, class... LeftOtherElementTypes, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product_inner_loop(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &, clifford_expression<> const &, metric_space<MetricSpaceType> const &, KeepIfGradesFunc const &) {
				return clifford_expression<>();
			}

			template<class LeftElementType, class... LeftOtherElementTypes, class RightElementType, class... RightOtherElementTypes, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &lhs, clifford_expression<RightElementType, RightOtherElementTypes...> const &rhs, metric_space<MetricSpaceType> const &mtr, KeepIfGradesFunc const &keep) {
				return (graded_product(lhs.next(), rhs, mtr, keep) + graded_product_inner_loop(lhs, rhs, mtr, keep));
			}

			template<class RightElementType, class... RightOtherElementTypes, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product(clifford_expression<> const &, clifford_expression<RightElementType, RightOtherElementTypes...> const &, metric_space<MetricSpaceType> const &, KeepIfGradesFunc const &) {
				return clifford_expression<>();
			}

			template<class LeftElementType, class... LeftOtherElementTypes, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product(clifford_expression<LeftElementType, LeftOtherElementTypes...> const &, clifford_expression<> const &, metric_space<MetricSpaceType> const &, KeepIfGradesFunc const &) {
				return clifford_expression<>();
			}

			template<class MetricSpaceType, class KeepIfGradesFunc>
			constexpr decltype(auto) graded_product(clifford_expression<> const &, clifford_expression<> const &, metric_space<MetricSpaceType> const &, KeepIfGradesFunc const &) {
				return clifford_expression<>();
			}

		}

	}

}

#endif // __GA_CLIFFORD_GRADED_PRODUCT_HPP__
