#ifndef __GA_CORE_MAPPING_HPP__
#define __GA_CORE_MAPPING_HPP__

namespace ga {

	namespace detail {

		// Mapping for non-metric products.
		template<ndims_t VectorSpaceDimensions>
		struct exterior_product_mapping;

		// Mapping for non-metric products.
		template<ndims_t VectorSpaceDimensions>
		struct regressive_product_mapping;

		// Mapping for products assuming spaces with orthogonal metric.
		template<typename OrthogonalMetricSpace, typename GradedProduct>
		struct orthogonal_metric_mapping;

		// Mapping for productes assuming spaces with general (non-orthogonal) metric.
		template<typename GeneralMetricSpace, typename GradedProduct>
		struct general_metric_mapping;

		// Returns the metric space mapping that fits the given arguments.
		template<typename MetricSpaceType, typename GradedProduct>
		struct _metric_space_mapping {
			typedef std::conditional_t<
				is_orthogonal_metric_space_v<MetricSpaceType>,
				orthogonal_metric_mapping<MetricSpaceType, GradedProduct>,
				std::conditional_t<
					is_general_metric_space_v<MetricSpaceType>,
					general_metric_mapping<MetricSpaceType, GradedProduct>,
					nullptr_t // should be impossible
				>
			> type;
		};
		
		template<typename MetricSpaceType, typename GradedProduct>
		using metric_space_mapping_t = typename _metric_space_mapping<MetricSpaceType, GradedProduct>::type;

	}

}

#endif // __GA_CORE_MAPPING_HPP__
