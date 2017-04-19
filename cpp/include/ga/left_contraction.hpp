namespace detail {

	// Functor for computing grade(B) - grade(A).
	//   GradeFirstComponent must be a dynamic_value or a static_value<> structure.
	//   GradeSecondComponent must be a dynamic_value or a static_value<> structure.
	template<class GradeFirstComponent, class GradeSecondComponent>
	struct lcont_grade_selection {

		typedef dynamic_value result;

		inline static
		int32_t eval(int32_t&& grade_first, int32_t&& grade_second) {
			return grade_second - grade_first;
		}
	};

	template<int32_t FirstValue, int32_t SecondValue>
	struct lcont_grade_selection<static_value<FirstValue>, static_value<SecondValue> > {
		
		typedef static_value<SecondValue - FirstValue> result;

		inline static
		int32_t eval(int32_t&&, int32_t&&) = nullptr;
	};

	// Left contraction expression (A lcont B).
	//   FirstArgument must be a multivector<> structure.
	//   SecondArgument must be a multivector<> structure.
	//   MetricArgument must be a metric<> structure.
	template<class FirstArgument, class SecondArgument, class MetricArgument>
	class lcont_expression : public graded_gp_expression<
			FirstArgument,
			SecondArgument,
			MetricArgument,
			lcont_grade_selection
		> {};

}

_GA_DEFINE_BINARY_METRIC_OPERATION(lcont)
