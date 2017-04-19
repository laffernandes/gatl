// Count the number of packs having runtime-defined collections of components.
template<class Composition>
struct count_dynamic_packs;

template<class Expression>
struct count_dynamic_packs :
	count_dynamic_packs<typename Expression::composition> {};

template<class Pack, class LeftSubtree, class RightSubtree>
struct count_dynamic_packs<tree<Pack, LeftSubtree, RightSubtree> > :
	plus<if_<is_runtime<typename Pack::components::count>, static_value<1>, static_value<0> >, plus<count_dynamic_packs<LeftSubtree>, count_dynamic_packs<RightSubtree> > > {};

template<>
struct count_dynamic_packs<empty_tree> :
	static_value<0> {};

// Count the number of components a given steps<> may have.
template<class Steps>
struct count_possible_components :
	count_possible_components<typename Steps::type> {};

template<class N, class StepsBitset>
struct _count_possible_components;

template<class N, class StepsBitset>
struct _count_possible_components_step {
private:

	typedef typename count_trailing_zeros<StepsBitset>::type step;

public:

	typedef typename plus<combs<N, static_value<step::value> >, _count_possible_components<N, typename unset<StepsBitset, step::value>::type> >::type type;
};

template<class N, class StepsBitset>
struct _count_possible_components :
	eval_if<any<StepsBitset>, _count_possible_components_step<N, StepsBitset>, static_value<0> > {};

template<class SpaceBitset, class StepsBitset>
struct count_possible_components<steps<SpaceBitset, StepsBitset> > :
	_count_possible_components<typename cardinality<SpaceBitset>::type, StepsBitset> {};

// Count the number of basis blades values that must be stored in runtime.
template<class Composition>
struct count_stored_basis_blades;

template<class Expression>
struct count_stored_basis_blades :
	count_stored_basis_blades<typename Expression::composition> {};

template<class Pack, class LeftSubtree, class RightSubtree>
struct count_stored_basis_blades<tree<Pack, LeftSubtree, RightSubtree> > :
	plus<if_<is_runtime<typename Pack::components::basis_vectors>, typename Pack::components::max_count, static_value<0> >, plus<count_stored_basis_blades<LeftSubtree>, count_stored_basis_blades<RightSubtree> > > {};

template<>
struct count_stored_basis_blades<empty_tree> :
	static_value<0> {};

// Count the number of coefficient values that must be stored in runtime.
template<class Composition>
struct count_stored_coefficients;

template<class Expression>
struct count_stored_coefficients :
	count_stored_coefficients<typename Expression::composition> {};

template<class Pack, class LeftSubtree, class RightSubtree>
struct count_stored_coefficients<tree<Pack, LeftSubtree, RightSubtree> > :
	plus<if_<is_runtime<typename Pack::components::coefficient>, typename Pack::components::max_count, static_value<0> >, plus<count_stored_coefficients<LeftSubtree>, count_stored_coefficients<RightSubtree> > > {};

template<>
struct count_stored_coefficients<empty_tree> :
	static_value<0> {};

// Check whether a given composition (tree) of packs has packs with dynamic size.
template<class Composition>
struct has_dynamic_pack_count;

template<class Expression>
struct has_dynamic_pack_count :
	has_dynamic_pack_count<typename Expression::composition> {};

template<class Pack, class LeftSubtree, class RightSubtree>
struct has_dynamic_pack_count<tree<Pack, LeftSubtree, RightSubtree> > :
	or_<is_runtime<typename Pack::components::count>, has_dynamic_pack_count<LeftSubtree>, has_dynamic_pack_count<RightSubtree> > {};

template<>
struct has_dynamic_pack_count<empty_tree> :
	false_ {};

// Check whether a given composition (tree) of packs has uniform storage.
template<class Composition>
struct has_uniform_storage;

template<class Expression>
struct has_uniform_storage :
	has_uniform_storage<typename Expression::composition> {};

template<class Pack, class LeftSubtree, class RightSubtree>
struct has_uniform_storage<tree<Pack, LeftSubtree, RightSubtree> > :
	or_<
		and_<is_compile_time<typename Pack::components::basis_vectors>, is_compile_time<typename Pack::components::coefficient> >,
		and_<is_runtime<typename Pack::components::basis_vectors>, is_runtime<typename Pack::components::coefficient> > > {};

template<>
struct has_uniform_storage<empty_tree> :
	true_ {};

// Convert all the operations assigned to a given composition to identity operations.
template<class Composition>
struct make_concrete;

template<class Expression>
struct make_concrete :
	make_concrete<typename Expression::composition>{};

template<class Pack, class LeftSubtree, class RightSubtree>
struct make_concrete<tree<Pack, LeftSubtree, RightSubtree> > :
	tree<pack<typename Pack::components, identity_operation>, typename make_concrete<LeftSubtree>::type, typename make_concrete<RightSubtree>::type> {};

template<>
struct make_concrete<empty_tree> :
	empty_tree {};
