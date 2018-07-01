#ifndef __GA_UTILS_SIGNED_EUCLIDEAN_ORTHOGONAL_PROJECTION_HPP__
#define __GA_UTILS_SIGNED_EUCLIDEAN_ORTHOGONAL_PROJECTION_HPP__

namespace ga {

	// Orthogonal projection of a subspace (lhs) ontho another subspace (rhs).
	template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, ndims_t N>
	constexpr decltype(auto) project(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, euclidean_metric_space<N> const &mtr) {
		auto const lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(lcont(lcont(lazy.argument<0>(), inv(lazy.argument<1>(), mtr), mtr), lazy.argument<1>(), mtr));
	}

}

#endif // __GA_UTILS_SIGNED_EUCLIDEAN_ORTHOGONAL_PROJECTION_HPP__
