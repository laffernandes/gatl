namespace detail {

	// Functor for retrieving 0.
	//   GradeFirstComponent must be a dynamic_value or a static_value<> structure.
	//   GradeSecondComponent must be a dynamic_value or a static_value<> structure.
	template<class GradeFirstComponent, class GradeSecondComponent>
	struct scp_grade_selection {

		typedef static_value<0> result;

		inline static
		int32_t eval(int32_t&&, int32_t&&) = nullptr;
	};

	// Scalar product expression (A scp B).
	//   FirstArgument must be a multivector<> structure.
	//   SecondArgument must be a multivector<> structure.
	//   MetricArgument must be a metric<> structure.
	template<class FirstArgument, class SecondArgument, class MetricArgument>
	class scp_expression : public graded_gp_expression<
			FirstArgument,
			SecondArgument,
			MetricArgument,
			scp_grade_selection
		> {};

}

_GA_DEFINE_BINARY_METRIC_OPERATION(scp)
