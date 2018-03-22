#ifndef __GA_GRADED_PRODUCT_HPP__
#define __GA_GRADED_PRODUCT_HPP__

namespace ga {

	namespace detail {

		struct _graded_product_iterate_left;
		struct _graded_product_iterate_right;
		struct _graded_product_end;

		template<class LeftItrType, class RightItrType, class MetricSpaceType, class KeepIfGradesFunc>
		constexpr decltype(auto) graded_product_inner_loop(LeftItrType const &lhs, RightItrType const &rhs, metric_space<MetricSpaceType> const &mtr, KeepIfGradesFunc const &keep) {
			return std::conditional<!is_end<RightItrType>::value, _graded_product_iterate_right, _graded_product_end>::type::bind(lhs, rhs, mtr, keep);
		}

		template<class LeftItrType, class RightItrType, class MetricSpaceType, class KeepIfGradesFunc>
		constexpr decltype(auto) graded_product(LeftItrType const &lhs, RightItrType const &rhs, metric_space<MetricSpaceType> const &mtr, KeepIfGradesFunc const &keep) {
			return std::conditional<!is_end<LeftItrType>::value, _graded_product_iterate_left, _graded_product_end>::type::bind(lhs, rhs, mtr, keep);
		}

		struct _graded_product_iterate_left {
			template<class LeftItrType, class RightItrType, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr static decltype(auto) bind(LeftItrType const &lhs, RightItrType const &rhs, metric_space<MetricSpaceType> const &mtr, KeepIfGradesFunc const &keep) {
				return plus(graded_product(next(lhs), rhs, mtr, keep), graded_product_inner_loop(lhs, rhs, mtr, keep));
			}
		};

		struct _graded_product_iterate_right {
			template<class LeftItrType, class RightItrType, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr static decltype(auto) bind(LeftItrType const &lhs, RightItrType const &rhs, metric_space<MetricSpaceType> const &mtr, KeepIfGradesFunc const &keep) {
				return plus(graded_product_inner_loop(lhs, next(rhs), mtr, keep), graded_product_element(lhs.element(), rhs.element(), mtr, keep));
			}
		};

		struct _graded_product_end {
			template<class LeftItrType, class RightItrType, class MetricSpaceType, class KeepIfGradesFunc>
			constexpr static empty_expression bind(LeftItrType const &, RightItrType const &, metric_space<MetricSpaceType> const &, KeepIfGradesFunc const &) {
				return empty_expression();
			}
		};

	}

}

#endif // __GA_GRADED_PRODUCT_HPP__
