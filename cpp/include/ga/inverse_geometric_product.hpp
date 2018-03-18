#ifndef __GA_INVERSE_GEOMETRIC_PRODUCT_HPP__
#define __GA_INVERSE_GEOMETRIC_PRODUCT_HPP___

namespace ga {

	template<class LeftType, class RightType, class MetricType>
	constexpr decltype(auto) igp(LeftType const &lhs, RightType const &rhs, metric<MetricType> const &mtr) {
		return gp(lhs, inv(rhs, mtr), mtr);
	}

	template<default_integral_t LeftValue, default_integral_t RightValue, class MetricType>
	constexpr decltype(auto) igp(detail::cvalue<LeftValue> const &lhs, detail::cvalue<RightValue> const &rhs, metric<MetricType> const &) {
		return detail::div(lhs, rhs);
	}

}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator/(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	static_assert(ga::detail::is_scalar_expression<ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> >::value, "The right hand side argument must be a scalar value.");
	return ga::igp(lhs, rhs, ga::euclidean_metric_t());
}

template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, ga::default_integral_t RightValue>
constexpr decltype(auto) operator/(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::igp(lhs, rhs, ga::euclidean_metric_t());
}

template<class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator/(ga::detail::empty_expression const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::igp(lhs, rhs, ga::euclidean_metric_t());
}

template<ga::default_integral_t RightValue>
constexpr decltype(auto) operator/(ga::detail::empty_expression const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::igp(lhs, rhs, ga::euclidean_metric_t());
}

template<ga::default_integral_t LeftValue, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
constexpr decltype(auto) operator/(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
	return ga::igp(lhs, rhs, ga::euclidean_metric_t());
}

template<ga::default_integral_t LeftValue, ga::default_integral_t RightValue>
constexpr decltype(auto) operator/(ga::detail::cvalue<LeftValue> const &lhs, ga::detail::cvalue<RightValue> const &rhs) {
	return ga::igp(lhs, rhs, ga::euclidean_metric_t());
}

#endif // __GA_INVERSE_GEOMETRIC_PRODUCT_HPP__
