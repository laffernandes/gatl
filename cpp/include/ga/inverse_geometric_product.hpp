#ifndef __GA_INVERSE_GEOMETRIC_PRODUCT_HPP__
#define __GA_INVERSE_GEOMETRIC_PRODUCT_HPP___

namespace ga {

	template<class LeftType, class RightType, class MetricSpaceType>
	constexpr decltype(auto) igp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &mtr) {
		return gp(lhs, inv(rhs, mtr), mtr);
	}

}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator/(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::igp(lhs, ga::native(rhs), ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, ga::default_integral_t RightValue>
constexpr decltype(auto) operator/(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::igp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator/(ga::detail::empty_expression const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::igp(lhs, ga::native(rhs), ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<ga::default_integral_t RightValue>
constexpr decltype(auto) operator/(ga::detail::empty_expression const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::igp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<ga::default_integral_t LeftValue, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator/(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::igp(lhs, ga::native(rhs), ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

template<ga::default_integral_t LeftValue, ga::default_integral_t RightValue>
constexpr decltype(auto) operator/(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::igp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
}

#endif // __GA_INVERSE_GEOMETRIC_PRODUCT_HPP__
