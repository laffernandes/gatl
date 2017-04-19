// Initialization operation (A = 0).
//   Result is a pack<..., idenity_operation>.
template<class Result>
struct assign_zero_operation;

// Subtraction assignment operation (A -= B).
//   Result is a pack<..., idenity_operation>.
//   PreviousAssignOperations defines a sequence of plus_assign_operation<> and minus_assign_operation<> structures.
//   Argument is a pack<> whose coefficient is composed by an inner operation (Operation structure), or the identification of a concrete argument (Argument structure).
template<class Result, class PreviousAssignOperations, class Argument>
struct minus_assign_operation;

// Addition assignment operation (A += B).
//   Result is a pack<..., idenity_operation>.
//   PreviousAssignOperations defines a sequence of plus_assign_operation<> and minus_assign_operation<> structures.
//   Argument is a pack<> whose coefficient is composed by an inner operation (Operation structure), or the identification of a concrete argument (Argument structure).
template<class Result, class PreviousAssignOperations, class Argument>
struct plus_assign_operation;

// Metafunction that merges two structures implementing the Assign concept.
//   AssignOperations1 is the first set of assign operations.
//   AssignOperations2 is the second set of assign operations.
template<class AssignOperations1, class AssignOperations2>
struct merge_assign_operations;

template<class Result>
struct merge_assign_operations<assign_zero_operation<Result>, assign_zero_operation<Result> > :
	assign_zero_operation<Result> {};

template<class Result, class PreviousAssignOperations1, class Argument1>
struct merge_assign_operations<minus_assign_operation<Result, PreviousAssignOperations1, Argument1>, assign_zero_operation<Result> > :
	minus_assign_operation<Result, PreviousAssignOperations1, Argument1> {};

template<class Result, class PreviousAssignOperations1, class Argument1>
struct merge_assign_operations<plus_assign_operation<Result, PreviousAssignOperations1, Argument1>, assign_zero_operation<Result> > :
	plus_assign_operation<Result, PreviousAssignOperations1, Argument1> {};

template<class Result, class PreviousAssignOperations2, class Argument2>
struct merge_assign_operations<assign_zero_operation<Result>, minus_assign_operation<Result, PreviousAssignOperations2, Argument2> > :
	minus_assign_operation<Result, PreviousAssignOperations2, Argument2> {};

template<class Result, class PreviousAssignOperations2, class Argument2>
struct merge_assign_operations<assign_zero_operation<Result>, plus_assign_operation<Result, PreviousAssignOperations2, Argument2> > :
	plus_assign_operation<Result, PreviousAssignOperations2, Argument2> {};

template<class PreviousAssignOperations1, class PreviousAssignOperations2>
struct _merge_assign_operations;

template<class Result, class PreviousAssignOperations1, class Argument1, class PreviousAssignOperations2, class Argument2>
struct merge_assign_operations<
		minus_assign_operation<Result, PreviousAssignOperations1, Argument1>,
		minus_assign_operation<Result, PreviousAssignOperations2, Argument2>
	> :
	eval_if<
		less<Argument1, Argument2>,
		_merge_assign_operations<minus_assign_operation<Result, PreviousAssignOperations1, Argument1>, minus_assign_operation<Result, PreviousAssignOperations2, Argument2> >,
		_merge_assign_operations<minus_assign_operation<Result, PreviousAssignOperations2, Argument2>, minus_assign_operation<Result, PreviousAssignOperations1, Argument1> >
	> {};

template<class Result, class PreviousAssignOperations1, class Argument1, class PreviousAssignOperations2, class Argument2>
struct merge_assign_operations<
		plus_assign_operation<Result, PreviousAssignOperations1, Argument1>,
		minus_assign_operation<Result, PreviousAssignOperations2, Argument2>
	> :
	eval_if<
		less<Argument1, Argument2>,
		_merge_assign_operations<plus_assign_operation<Result, PreviousAssignOperations1, Argument1>, minus_assign_operation<Result, PreviousAssignOperations2, Argument2> >,
		_merge_assign_operations<minus_assign_operation<Result, PreviousAssignOperations2, Argument2>, plus_assign_operation<Result, PreviousAssignOperations1, Argument1> >
	> {};

template<class Result, class PreviousAssignOperations1, class Argument1, class PreviousAssignOperations2, class Argument2>
struct merge_assign_operations<
		minus_assign_operation<Result, PreviousAssignOperations1, Argument1>,
		plus_assign_operation<Result, PreviousAssignOperations2, Argument2>
	> :
	eval_if<
		less<Argument1, Argument2>,
		_merge_assign_operations<minus_assign_operation<Result, PreviousAssignOperations1, Argument1>, plus_assign_operation<Result, PreviousAssignOperations2, Argument2> >,
		_merge_assign_operations<plus_assign_operation<Result, PreviousAssignOperations2, Argument2>, minus_assign_operation<Result, PreviousAssignOperations1, Argument1> >
	> {};

template<class Result, class PreviousAssignOperations1, class Argument1, class PreviousAssignOperations2, class Argument2>
struct merge_assign_operations<
		plus_assign_operation<Result, PreviousAssignOperations1, Argument1>,
		plus_assign_operation<Result, PreviousAssignOperations2, Argument2>
	> :
	eval_if<
		less<Argument1, Argument2>,
		_merge_assign_operations<plus_assign_operation<Result, PreviousAssignOperations1, Argument1>, plus_assign_operation<Result, PreviousAssignOperations2, Argument2> >,
		_merge_assign_operations<plus_assign_operation<Result, PreviousAssignOperations2, Argument2>, plus_assign_operation<Result, PreviousAssignOperations1, Argument1> >
	> {};

template<class Result, class PreviousAssignOperations1, class InnerPreviousAssignOperations2, class InnerArgument2>
struct _merge_assign_operations<
		PreviousAssignOperations1,
		minus_assign_operation<Result, InnerPreviousAssignOperations2, InnerArgument2>
	> :
	minus_assign_operation<Result, typename merge_assign_operations<PreviousAssignOperations1, InnerPreviousAssignOperations2>::type, InnerArgument2> {};

template<class Result, class PreviousAssignOperations1, class InnerPreviousAssignOperations2, class InnerArgument2>
struct _merge_assign_operations<
		PreviousAssignOperations1,
		plus_assign_operation<Result, InnerPreviousAssignOperations2, InnerArgument2>
	> :
	plus_assign_operation<Result, typename merge_assign_operations<PreviousAssignOperations1, InnerPreviousAssignOperations2>::type, InnerArgument2> {};
