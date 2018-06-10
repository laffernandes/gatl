#ifndef __GA_GENERAL_METRIC_MAPPING_HPP__
#define __GA_GENERAL_METRIC_MAPPING_HPP__

namespace ga {

	namespace detail {

		// The implementation of mapping for products assuming spaces with general (non-orthogonal) metric.
		template<class GeneralMetricSpace, class GradedProduct>
		struct general_metric_space_mapping {

			template<class LeftBasisBlade, class RightBasisBlade>
			struct multiply; //TODO Not supported yet (general metric space).
		};

	}

}

#endif // __GA_GENRAL_METRIC_MAPPING_HPP__
