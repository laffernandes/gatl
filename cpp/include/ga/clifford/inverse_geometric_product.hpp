#ifndef __GA_CLIFFORD_INVERSE_GEOMETRIC_PRODUCT_HPP__
#define __GA_CLIFFORD_INVERSE_GEOMETRIC_PRODUCT_HPP___

namespace ga {

	namespace clifford {

		template<class LeftType, class RightType, class MetricSpaceType>
		constexpr decltype(auto) igp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &mtr) {
			return gp(lhs, inv(rhs, mtr), mtr);
		}

		using lazy::operator/;

		template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
		constexpr decltype(auto) operator/(detail::expression_tree<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, detail::expression_tree<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
			return igp(lhs, native(rhs), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

		template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightExpressionType>
		constexpr decltype(auto) operator/(detail::expression_tree<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return igp(lhs, rhs(), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

		template<class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
		constexpr decltype(auto) operator/(detail::empty_expression_tree const &lhs, detail::expression_tree<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
			return igp(lhs, native(rhs), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

		template<class RightExpressionType>
		constexpr decltype(auto) operator/(detail::empty_expression_tree const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return igp(lhs, rhs(), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

		template<class LeftExpressionType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
		constexpr decltype(auto) operator/(lazy_expression<LeftExpressionType> const &lhs, detail::expression_tree<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
			return igp(lhs(), native(rhs), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

	}

}

#endif // __GA_CLIFFORD_INVERSE_GEOMETRIC_PRODUCT_HPP__
