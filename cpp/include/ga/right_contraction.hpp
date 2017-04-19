namespace detail {

	// Functor for computing grade(A) - grade(B).
	//   GradeFirstComponent must be a dynamic_value or a static_value<> structure.
	//   GradeSecondComponent must be a dynamic_value or a static_value<> structure.
	template<class GradeFirstComponent, class GradeSecondComponent>
	struct rcont_grade_selection {

		typedef dynamic_value result;

		inline static
		int32_t eval(int32_t&& grade_first, int32_t&& grade_second) {
			return grade_first - grade_second;
		}
	};

	template<int32_t FirstValue, int32_t SecondValue>
	struct rcont_grade_selection<static_value<FirstValue>, static_value<SecondValue> > {
		
		typedef static_value<FirstValue - SecondValue> result;

		inline static
		int32_t eval(int32_t&&, int32_t&&) = nullptr;
	};

	// Right contraction expression (A rcont B).
	//   FirstArgument must be a multivector<> structure.
	//   SecondArgument must be a multivector<> structure.
	//   MetricArgument must be a metric<> structure.
	template<class FirstArgument, class SecondArgument, class MetricArgument>
	class rcont_expression : public graded_gp_expression<
			FirstArgument,
			SecondArgument,
			MetricArgument,
			rcont_grade_selection
		> {};

}

_GA_DEFINE_BINARY_METRIC_OPERATION(rcont)
