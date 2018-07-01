#ifndef __GA_UTILS_SIGNED_HOMOGENEOUS_FLAT_MOMENT_HPP__
#define __GA_UTILS_SIGNED_HOMOGENEOUS_FLAT_MOMENT_HPP__

namespace ga {

	// Returns the moment parameter of a given k-flat.
	template<typename CoefficientType, typename Expression, ndims_t N>
	constexpr decltype(auto) flat_moment(clifford_expression<CoefficientType, Expression> const &flat, homogeneous_metric_space<N> const &mtr) {
		auto const lazy = make_lazy_context(flat);
		return lazy.eval(lcont(e(c<N + 1>), op(e(c<N + 1>), lazy.argument<0>(), mtr), mtr));
	}

}

#endif // __GA_UTILS_SIGNED_HOMOGENEOUS_FLAT_MOMENT_HPP__
