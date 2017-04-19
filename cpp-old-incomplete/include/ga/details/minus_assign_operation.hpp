template<class BasisBlade, class PreviousAssignOperations, class Coefficient, class Operation>
struct minus_assign_operation<pack<single_basis_blade<BasisBlade, dynamic_value>, identity_operation>, PreviousAssignOperations, pack<single_basis_blade<BasisBlade, Coefficient>, Operation> > {

	typedef pack<single_basis_blade<BasisBlade, dynamic_value>, identity_operation> result_type;
	typedef pack<single_basis_blade<BasisBlade, Coefficient>, Operation>            argument_type;
	typedef minus_assign_operation                                                  type;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		PreviousAssignOperations::eval(result, arguments);
		
		result.coefficient() -= argument_type::coefficient(arguments);
	}
};

template<class BasisBlade, class PreviousAssignOperations, class Coefficient, class InnerPreviousAssignOperations, class InnerArgument>
struct minus_assign_operation<pack<single_basis_blade<BasisBlade, dynamic_value>, identity_operation>, PreviousAssignOperations, pack<single_basis_blade<BasisBlade, Coefficient>, plus_assign_operation<pack<single_basis_blade<BasisBlade, dynamic_value>, identity_operation>, InnerPreviousAssignOperations, InnerArgument> > > :
	plus_assign_operation<pack<single_basis_blade<BasisBlade, dynamic_value>, identity_operation>, PreviousAssignOperations, typename apply_uminus<pack<single_basis_blade<BasisBlade, Coefficient>, plus_assign_operation<pack<single_basis_blade<BasisBlade, dynamic_value>, identity_operation>, InnerPreviousAssignOperations, InnerArgument> > >::type> {};

template<class BasisBlade, class PreviousAssignOperations, class Coefficient, class InnerPreviousAssignOperations, class InnerArgument>
struct minus_assign_operation<pack<single_basis_blade<BasisBlade, dynamic_value>, identity_operation>, PreviousAssignOperations, pack<single_basis_blade<BasisBlade, Coefficient>, minus_assign_operation<pack<single_basis_blade<BasisBlade, dynamic_value>, identity_operation>, InnerPreviousAssignOperations, InnerArgument> > > :
	plus_assign_operation<pack<single_basis_blade<BasisBlade, dynamic_value>, identity_operation>, PreviousAssignOperations, typename apply_uminus<pack<single_basis_blade<BasisBlade, Coefficient>, minus_assign_operation<pack<single_basis_blade<BasisBlade, dynamic_value>, identity_operation>, InnerPreviousAssignOperations, InnerArgument> > >::type> {};

template<class ResultSteps, class ResultCount, class PreviousAssignOperations, class BasisBlade, class Coefficient, class Operation>
struct minus_assign_operation<pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation>, PreviousAssignOperations, pack<single_basis_blade<BasisBlade, Coefficient>, Operation> > {

	typedef pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation> result_type;
	typedef pack<single_basis_blade<BasisBlade, Coefficient>, Operation>              argument_type;
	typedef minus_assign_operation                                                    type;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		PreviousAssignOperations::eval(result, arguments);

		//TODO Parei aqui.
		/*
		ArgumentConstIterator argument_copy = go_to<argument_type>(get_argument<input_argument_id<Path> >(arguments));
		for (::size_t i = 0; i < argument_copy.stride(); ++i) {
			map<type>(result, argument_copy.basis_blade()).coefficient() -= argument_copy.coefficient();
			argument_copy.advance();
		}
		*/
	}
};

template<class ResultSteps, class ResultCount, class PreviousAssignOperations, class ArgumentSteps, class ArgumentCount, class Operation>
struct minus_assign_operation<pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation>, PreviousAssignOperations, pack<multiple_basis_blades<ArgumentSteps, ArgumentCount>, Operation> > {

	typedef pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation> result_type;
	typedef pack<multiple_basis_blades<ArgumentSteps, ArgumentCount>, Operation>      argument_type;
	typedef minus_assign_operation                                                    type;

	template<class ResultInserter, class Arguments>
	inline static
	void eval(ResultInserter &result, const Arguments &arguments) {
		PreviousAssignOperations::eval(result, arguments);

		//TODO Parei aqui.
		/*
		ArgumentConstIterator argument_copy = go_to<argument_type>(get_argument<input_argument_id<Path> >(arguments));
		for (::size_t i = 0; i < argument_copy.stride(); ++i) {
			map<type>(result, argument_copy.basis_blade()).coefficient() -= argument_copy.coefficient();
			argument_copy.advance();
		}
		*/
	}
};

template<class ResultSteps, class ResultCount, class PreviousAssignOperations, class Components, class InnerPreviousAssignOperations, class InnerArgument>
struct minus_assign_operation<pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation>, PreviousAssignOperations, pack<Components, plus_assign_operation<pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation>, InnerPreviousAssignOperations, InnerArgument> > > :
	plus_assign_operation<pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation>, PreviousAssignOperations, typename apply_uminus<pack<Components, plus_assign_operation<pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation>, InnerPreviousAssignOperations, InnerArgument> > >::type> {};

template<class ResultSteps, class ResultCount, class PreviousAssignOperations, class Components, class InnerPreviousAssignOperations, class InnerArgument>
struct minus_assign_operation<pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation>, PreviousAssignOperations, pack<Components, minus_assign_operation<pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation>, InnerPreviousAssignOperations, InnerArgument> > > :
	plus_assign_operation<pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation>, PreviousAssignOperations, typename apply_uminus<pack<Components, minus_assign_operation<pack<multiple_basis_blades<ResultSteps, ResultCount>, identity_operation>, InnerPreviousAssignOperations, InnerArgument> > >::type> {};
