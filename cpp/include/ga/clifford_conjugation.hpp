namespace detail {

	// Functor for computing (-1)^{k * (k + 1) / 2}, for k = grade(A)
	//   GradeComponent must be a dynamic_value or a static_value<> structure.
	template<class GradeComponent>
	struct clifford_conjugation_sign_change {

		typedef dynamic_value result;

		inline static
		int32_t eval(int32_t&& grade) {
			return (((grade * (grade + 1)) & 2) != 0) ? -1 : +1;
		}
	};

	template<int32_t Value>
	struct clifford_conjugation_sign_change<static_value<Value> > {
		
		typedef static_value<(((Value * (Value + 1)) & 2) != 0) ? -1 : +1> result;

		inline static
		int32_t eval(int32_t&&) = nullptr;
	};

	// Clifford conjugation expression (clifford_conjugation(A)).
	//   Argument must be a multivector<> structure.
	template<class Argument>
	class clifford_conjugation_expression : public sign_change_expression<
			Argument,
			clifford_conjugation_sign_change
		> {};

}

_GA_DEFINE_UNARY_NON_METRIC_OPERATION(clifford_conjugation)
