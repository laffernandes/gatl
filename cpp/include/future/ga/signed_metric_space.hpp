#ifndef __FUTURE_GA_SIGNED_METRIC_SPACE_HPP__
#define __FUTURE_GA_SIGNED_METRIC_SPACE_HPP__

namespace ga {

	// Orthogonal metric space with signature (P,Q).
	template<ndims_t P, ndims_t Q>
	class signed_metric_space : public metric_space<signed_metric_space<P, Q> > {
	public:

		typedef signed_metric_space metric_space_type;

		constexpr static default_bitset_t basis_vectors = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (P + Q)));
		constexpr static ndims_t vector_space_dimensions = P + Q;

	private:

		constexpr static default_bitset_t positive = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - P));
		constexpr static default_bitset_t negative = basis_vectors - positive;

	public:

		template<class LazyBasisVectorsBitset>
		struct lazy_metric_factor {
			typedef detail::lazy_if_else_t<detail::lazy_eq_t<detail::lazy_bitwise_and_t<detail::lazy_ones_t<detail::lazy_bitwise_and_t<LazyBasisVectorsBitset, detail::lazy_constant_bitset<negative> > >, detail::constant<1> >, detail::constant<0> >, detail::constant<1>, detail::constant<-1> > type;
		};

		static_assert((P + Q) <= GA_MAX_BASIS_VECTOR_INDEX, "ga::signed_metric_space<P, Q> is ill-defined. It is expectated (P + Q) <= GA_MAX_BASIS_VECTOR_INDEX.");
	};

	// Euclidean metric space.
	template<ndims_t N>
	using euclidean_metric_space = signed_metric_space<N, 0>;

	// Minkowski metric space.
	template<ndims_t N>
	using minkowski_metric_space = signed_metric_space<N, 1>;

	// Specialization of is_orthogonal_metric_space<MetricSpaceType>.
	template<ndims_t P, ndims_t Q>
	struct is_orthogonal_metric_space<signed_metric_space<P, Q> > {
		constexpr static bool value = true;
	};

	namespace detail {
		
		// Helper for metric space of real numbers (it is used with scalar expressions).
		using real_metric_space = signed_metric_space<0, 0>;

	}

}

#endif // __FUTURE_GA_SIGNED_METRIC_SPACE_HPP__
