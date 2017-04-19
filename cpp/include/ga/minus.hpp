namespace detail {

	// Addition assignment operation (A -= B).
	//   Result is a pack<..., idenity_operation>.
	//   PreviousAssignOperations defines a sequence of minus_assign_operation<> and minus_assign_operation<> structures.
	//   Argument is a pack<> whose coefficient is composed by an inner operation (Operation structure), or the identification of a concrete argument (Argument structure).
	template<class Result, class PreviousAssignOperations, class Argument>
	struct minus_assign_operation;

	//TODO Implement it!

	// Minus expression (A - B).
	//   FirstArgument must be a multivector<> structure.
	//   SecondArgument must be a multivector<> structure.
	template<class FirstArgument, class SecondArgument>
	class minus_expression : public cummulative_expression<
			FirstArgument,
			SecondArgument,
			minus_assign_operation
		> {};

}

_GA_DEFINE_BINARY_NON_METRIC_OPERATION(minus)

template<class FirstArgumentType, class SecondArgumentType>
inline
auto operator - (FirstArgumentType&& m1, SecondArgumentType&& m2)->decltype(minus(m1, m2)) {
	return minus(m1, m2);
}
