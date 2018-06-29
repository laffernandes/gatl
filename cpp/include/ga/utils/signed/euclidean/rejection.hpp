#ifndef __GA_UTILS_SIGNED_EUCLIDEAN_REJECTION_HPP__
#define __GA_UTILS_SIGNED_EUCLIDEAN_REJECTION_HPP__

namespace ga {

	// Rejection of a subspace (lhs) by another subspace (rhs).
	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, ndims_t N>
	constexpr decltype(auto) reject(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, euclidean_metric_space<N> const &mtr) {
		auto const lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(lazy.argument<0>() - project(lazy.argument<0>(), lazy.argument<1>(), mtr));
	}

}

#endif // __GA_UTILS_SIGNED_EUCLIDEAN_REJECTION_HPP__
