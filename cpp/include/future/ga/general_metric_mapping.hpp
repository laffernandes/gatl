#ifndef __FUTURE_GA_GENERAL_METRIC_MAPPING_HPP__
#define __FUTURE_GA_GENERAL_METRIC_MAPPING_HPP__

namespace ga {

	namespace detail {

		// The implementation of mapping for spaces with general (non-orthogonal) metric (it is used with basis blades).
		template<class GeneralMetricSpace, class GradedProduct>
		struct general_metric_space_mapping {

			template<class LeftBasisBlade, class RightBasisBlade>
			struct multiply; //TODO Not supported yet (general metric space).
		};

	}

}

#endif // __FUTURE_GA_GENRAL_METRIC_MAPPING_HPP__
