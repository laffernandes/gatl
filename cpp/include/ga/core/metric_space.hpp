#ifndef __GA_CORE_METRIC_SPACE_HPP__
#define __GA_CORE_METRIC_SPACE_HPP__

namespace ga {

	// Base metric space class.
	template<class MetricSpaceType>
	class metric_space {

		typedef MetricSpaceType metric_space_type;

	protected:

		constexpr metric_space() = default;
		constexpr metric_space(metric_space const &) = default;
		constexpr metric_space(metric_space &&) = default;

		constexpr metric_space & operator=(metric_space const &) = default;
		constexpr metric_space & operator=(metric_space &&) = default;
	};

	// Returns whether the given metric space is orthogonal.
	template<class MetricSpaceType>
	struct is_orthogonal_metric_space {
		constexpr static bool value = false;
	};

	template<class MetricSpaceType>
	constexpr bool is_orthogonal_metric_space_v = is_orthogonal_metric_space<MetricSpaceType>::value;

	template<class MetricSpaceType>
	struct is_orthogonal_metric_space<metric_space<MetricSpaceType> > {
		constexpr static bool value = is_orthogonal_metric_space_v<MetricSpaceType>;
	};

	// Returns whether the given metric space is general.
	template<class MetricSpaceType>
	struct is_general_metric_space {
		constexpr static bool value = false;
	};

	template<class MetricSpaceType>
	constexpr bool is_general_metric_space_v = is_general_metric_space<MetricSpaceType>::value;

	template<class MetricSpaceType>
	struct is_general_metric_space<metric_space<MetricSpaceType> > {
		constexpr static bool value = is_general_metric_space_v<MetricSpaceType>;
	};

}

#endif // __GA_CORE_METRIC_SPACE_HPP__
