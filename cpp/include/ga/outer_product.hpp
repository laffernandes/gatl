namespace detail {

	// Functor for computing grade(A) + grade(B).
	//   GradeFirstComponent must be a dynamic_value or a static_value<> structure.
	//   GradeSecondComponent must be a dynamic_value or a static_value<> structure.
	template<class GradeFirstComponent, class GradeSecondComponent>
	struct op_grade_selection {

		typedef dynamic_value result;

		inline static
		int32_t eval(int32_t&& grade_first, int32_t&& grade_second) {
			return grade_first + grade_second;
		}
	};

	template<int32_t FirstValue, int32_t SecondValue>
	struct op_grade_selection<static_value<FirstValue>, static_value<SecondValue> > {
		
		typedef static_value<FirstValue + SecondValue> result;

		inline static
		int32_t eval(int32_t&&, int32_t&&) = nullptr;
	};

	// Outer product expression (A op B).
	//   FirstArgument must be a multivector<> structure.
	//   SecondArgument must be a multivector<> structure.
	template<class FirstArgument, class SecondArgument>
	class op_expression : public graded_gp_expression<
			FirstArgument,
			SecondArgument,
			euclidean_metric,
			op_grade_selection
		> {};

}

_GA_DEFINE_BINARY_NON_METRIC_OPERATION(op)

template<class FirstArgumentType, class SecondArgumentType>
inline
auto operator ^ (FirstArgumentType&& m1, SecondArgumentType&& m2)->decltype(op(m1, m2)) {
	return op(m1, m2);
}
