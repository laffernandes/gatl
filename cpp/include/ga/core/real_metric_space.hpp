#ifndef __GA_CORE_REAL_METRIC_SPACE_HPP__
#define __GA_CORE_REAL_METRIC_SPACE_HPP__

namespace ga {

	namespace detail {

		// Helper for metric space of real numbers (it is used with scalar expressions).
		struct real_metric_space : public metric_space<real_metric_space> {
		public:

			typedef real_metric_space metric_space_type;

			constexpr static default_bitset_t basis_vectors = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - GA_MAX_BASIS_VECTOR_INDEX));
			constexpr static ndims_t vector_space_dimensions = GA_MAX_BASIS_VECTOR_INDEX;

		public:

			template<typename BasisVectorsBitset>
			struct metric_factor {
				typedef detail::constant_value<1> type;
			};
		};

	}

	// Specialization of is_orthogonal_metric_space<MetricSpaceType>.
	template<>
	struct is_orthogonal_metric_space<detail::real_metric_space> :
		std::true_type {
	};

}

#endif // __GA_CORE_REAL_METRIC_SPACE_HPP__
