// Apply unary minus metafunction.
//   T may be a tree<>, empty_tree, pack<>, or some structure implementing some Operation concept.
//   ArgumentTag is a metafunction implementing the ArgumentTag concept.
template<class T, template<class> class ArgumentTag>
struct update_argument_tag;

template<class Pack, class LeftSubtree, class RightSubtree, template<class> class ArgumentTag>
struct update_argument_tag<tree<Pack, LeftSubtree, RightSubtree>, ArgumentTag> :
	tree<typename update_argument_tag<Pack, ArgumentTag>::type, typename update_argument_tag<LeftSubtree, ArgumentTag>::type, typename update_argument_tag<RightSubtree, ArgumentTag>::type> {};

template<template<class> class ArgumentTag>
struct update_argument_tag<empty_tree, ArgumentTag> :
	empty_tree {};

template<class Bitset, int Value, template<class> class ArgumentTag>
struct update_argument_tag<pack<single_basis_blade<basis_vectors<Bitset>, static_value<Value> >, identity_operation>, ArgumentTag> :
	pack<single_basis_blade<basis_vectors<Bitset>, static_value<Value> >, identity_operation> {};

template<class Components, class Operation, template<class> class ArgumentTag>
struct update_argument_tag<pack<Components, Operation>, ArgumentTag> :
	pack<Components, typename update_argument_tag<Operation, ArgumentTag>::type> {};

template<class Components, template<class> class ArgumentTag>
struct update_argument_tag<pack<Components, identity_operation>, ArgumentTag> :
	pack<Components, ArgumentTag<pack<Components, identity_operation> > > {};

template<class Components, class InnerArgument, template<class> class ArgumentTag>
struct update_argument_tag<pack<Components, first_argument_tag<InnerArgument> >, ArgumentTag> :
	pack<Components, ArgumentTag<pack<Components, first_argument_tag<InnerArgument> > > > {};

template<class Components, class InnerArgument, template<class> class ArgumentTag>
struct update_argument_tag<pack<Components, second_argument_tag<InnerArgument> >, ArgumentTag> :
	pack<Components, ArgumentTag<pack<Components, second_argument_tag<InnerArgument> > > > {};

template<class Components, class InnerArgument, template<class> class ArgumentTag>
struct update_argument_tag<pack<Components, single_argument_tag<InnerArgument> >, ArgumentTag> :
	pack<Components, ArgumentTag<pack<Components, single_argument_tag<InnerArgument> > > > {};

template<class Result, template<class> class ArgumentTag>
struct update_argument_tag<assign_zero_operation<Result>, ArgumentTag> :
	assign_zero_operation<Result> {};

template<class Result, class PreviousAssignOperations, class Argument, template<class> class ArgumentTag>
struct update_argument_tag<minus_assign_operation<Result, PreviousAssignOperations, Argument>, ArgumentTag> :
	minus_assign_operation<Result, typename update_argument_tag<PreviousAssignOperations, ArgumentTag>::type, typename update_argument_tag<Argument, ArgumentTag>::type> {};

template<class Result, class PreviousAssignOperations, class Argument, template<class> class ArgumentTag>
struct update_argument_tag<plus_assign_operation<Result, PreviousAssignOperations, Argument>, ArgumentTag> :
	plus_assign_operation<Result, typename update_argument_tag<PreviousAssignOperations, ArgumentTag>::type, typename update_argument_tag<Argument, ArgumentTag>::type> {};
