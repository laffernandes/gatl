namespace detail {

	// Functor for computing (-1)^{k}, for k = grade(A)
	//   GradeComponent must be a dynamic_value or a static_value<> structure.
	template<class GradeComponent>
	struct grade_involution_sign_change {

		typedef dynamic_value result;

		inline static
		int32_t eval(int32_t&& grade) {
			return (grade & 1) != 0) ? -1 : +1;
		}
	};

	template<int32_t Value>
	struct grade_involution_sign_change<static_value<Value> > {
		
		typedef static_value<((Value & 1) != 0) ? -1 : +1> result;

		inline static
		int32_t eval(int32_t&&) = nullptr;
	};

	// Grade involution expression (grade_involution(A)).
	//   Argument must be a multivector<> structure.
	template<class Argument>
	class grade_involution_expression : public sign_change_expression<
			Argument,
			grade_involution_sign_change
		> {};

}

_GA_DEFINE_UNARY_NON_METRIC_OPERATION(grade_involution)
