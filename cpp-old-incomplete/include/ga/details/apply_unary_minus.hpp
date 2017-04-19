// Apply unary minus metafunction.
//   T may be a tree<>, empty_tree, pack<>, or some structure implementing one of the AssignOperation concepts.
template<class T>
struct apply_uminus;

template<class Pack, class LeftSubtree, class RightSubtree>
struct apply_uminus<tree<Pack, LeftSubtree, RightSubtree> > :
	distribute<tree<Pack, LeftSubtree, RightSubtree>, ga::details::apply_uminus> {};

template<>
struct apply_uminus<empty_tree> :
	empty_tree {};

template<class Bitset, int Value>
struct apply_uminus<
		pack<single_basis_blade<basis_vectors<Bitset>, static_value<Value> >, identity_operation>
	> :
	pack<
		single_basis_blade<basis_vectors<Bitset>, static_value<-Value> >,
		identity_operation> {};

template<class BasisBlade, int Value, class Operation>
struct apply_uminus<
		pack<single_basis_blade<BasisBlade, static_value<Value> >, Operation>
	> :
	pack<
		single_basis_blade<BasisBlade, static_value<-Value> >,
		Operation> {};

template<class Components>
struct apply_uminus<
		pack<Components, assign_zero_operation<pack<Components, identity_operation> > >
	> :
	pack<
		Components,
		assign_zero_operation<pack<Components, identity_operation> > > {};

template<class Components, class Result, class PreviousAssignOperations, class Argument>
struct apply_uminus<
		pack<Components, minus_assign_operation<Result, PreviousAssignOperations, Argument> >
	> :
	pack<
		Components,
		typename apply_uminus<minus_assign_operation<Result, PreviousAssignOperations, Argument> >::type> {};

template<class Components, class Result, class PreviousAssignOperations, class Argument>
struct apply_uminus<
		pack<Components, plus_assign_operation<Result, PreviousAssignOperations, Argument> >
	> :
	pack<
		Components,
		typename apply_uminus<plus_assign_operation<Result, PreviousAssignOperations, Argument> >::type> {};

template<class Components, class Operation>
struct apply_uminus<
		pack<Components, Operation>
	> :
	pack<
		Components,
		typename minus_assign_operation<pack<Components, identity_operation>, assign_zero_operation<pack<Components, identity_operation> >, pack<Components, Operation> >::type> {};

template<class Components>
struct apply_uminus<assign_zero_operation<pack<Components, identity_operation> > > :
	assign_zero_operation<pack<Components, identity_operation> > {};

template<class Result, class PreviousAssignOperations, class Argument>
struct apply_uminus<minus_assign_operation<Result, PreviousAssignOperations, Argument> > :
	plus_assign_operation<Result, typename apply_uminus<PreviousAssignOperations>::type, Argument> {};

template<class Result, class PreviousAssignOperations, class Argument>
struct apply_uminus<plus_assign_operation<Result, PreviousAssignOperations, Argument> > :
	minus_assign_operation<Result, typename apply_uminus<PreviousAssignOperations>::type, Argument> {};
