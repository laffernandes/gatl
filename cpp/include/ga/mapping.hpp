#ifndef __GA_MAPPING_HPP__
#define __GA_MAPPING_HPP__

namespace ga {

	namespace detail {

		// Mapping for products assuming spaces with orthogonal metric.
		template<class OrthogonalMetricSpace, class GradedProduct>
		struct orthogonal_metric_space_mapping;

		// Mapping for productes assuming spaces with general (non-orthogonal) metric.
		template<class GeneralMetricSpace, class GradedProduct>
		struct general_metric_space_mapping;

		// Returns the metric space mapping that fits the given arguments.
		template<class MetricSpaceType, class GradedProduct>
		struct _metric_space_mapping {
			typedef std::conditional_t<
				is_orthogonal_metric_space_v<MetricSpaceType>,
				orthogonal_metric_space_mapping<MetricSpaceType, GradedProduct>,
				std::conditional_t<
					is_general_metric_space_v<MetricSpaceType>,
					general_metric_space_mapping<MetricSpaceType, GradedProduct>,
					nullptr_t // should be impossible
				>
			> type;
		};
		
		template<class MetricSpace, class GradedProduct>
		using metric_space_mapping_t = typename _metric_space_mapping<MetricSpace, GradedProduct>::type;

	}

}

#endif // __GA_MAPPING_HPP__
