#ifndef __GA_UTILS_SIGNED_HOMOGENEOUS_FLAT_SUPPORT_VECTOR_HPP__
#define __GA_UTILS_SIGNED_HOMOGENEOUS_FLAT_SUPPORT_VECTOR_HPP__

namespace ga {

	// Returns the support vector parameter of a given k-flat.
	template<class CoefficientType, class Expression, ndims_t N>
	constexpr decltype(auto) flat_support_vector(clifford_expression<CoefficientType, Expression> const &arg, homogeneous_metric_space<N> const &mtr) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(gp(lcont(e(c<N + 1>), op(e(c<N + 1>), lazy.argument<0>(), mtr), mtr), inv(lcont(e(c<N + 1>), lazy.argument<0>(), mtr), mtr), mtr));
	}

}

#endif // __GA_UTILS_SIGNED_HOMOGENEOUS_FLAT_SUPPORT_VECTOR_HPP__
