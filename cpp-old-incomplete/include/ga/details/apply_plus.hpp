// Apply plus metafunction.
//   T1 may be a tree<>, empty_tree, or pack<> structure.
//   T2 may be a tree<>, empty_tree, or pack<> structure.
template<class T1, class T2>
struct apply_plus;

template<class Tree, class PartialResult>
struct _insert_all :
	_insert_all<
		typename Tree::right,
		typename apply_plus<
			typename _insert_all<typename Tree::left, PartialResult>::type,
			typename Tree::pack
		>::type
	> {};

template<class PartialResult>
struct _insert_all<empty_tree, PartialResult> {

	typedef PartialResult type;
};

template<class RootPack1, class LeftSubtree1, class RightSubtree1, class RootPack2, class LeftSubtree2, class RightSubtree2>
struct apply_plus<tree<RootPack1, LeftSubtree1, RightSubtree1>, tree<RootPack2, LeftSubtree2, RightSubtree2> > :
	_insert_all<tree<RootPack2, LeftSubtree2, RightSubtree2>, tree<RootPack1, LeftSubtree1, RightSubtree1> > {};

template<class Tree>
struct _height {
private:

	static const int height_left = _height<typename Tree::left>::value;
	static const int height_right = _height<typename Tree::right>::value;

public:

	static const int value = 1 + ((height_left >= height_right) ? height_left : height_right);
};

template<>
struct _height<empty_tree> {

	static const int value = -1;
};

template<class Tree>
struct _rotate_left :
	tree<typename Tree::right::pack, tree<typename Tree::pack, typename Tree::left, typename Tree::right::left>, typename Tree::right::right> {};

template<class Tree>
struct _rotate_right :
	tree<typename Tree::left::pack, typename Tree::left::left, tree<typename Tree::pack, typename Tree::left::right, typename Tree::right> > {};

template<class Tree>
struct _rotate_left_right :
	_rotate_right<tree<typename Tree::pack, typename _rotate_left<typename Tree::left>::type, typename Tree::right> > {};

template<class Tree>
struct _rotate_right_left :
	_rotate_left<tree<typename Tree::pack, typename Tree::left, typename _rotate_right<typename Tree::right>::type> > {};

template<class Pack, class RootPack, class LeftSubtree, class RightSubtree>
struct _apply_plus_pack_left {
private:

	typedef tree<RootPack, typename apply_plus<Pack, LeftSubtree>::type, RightSubtree> aux;

public:

	typedef typename eval_if_c<
		(_height<typename aux::left>::value - _height<typename aux::right>::value) == 2,
		eval_if<less<Pack, typename aux::left::pack>, _rotate_right<aux>, _rotate_left_right<aux> >,
		aux
	>::type type;
};

template<class Pack, class RootPack, class LeftSubtree, class RightSubtree>
struct _apply_plus_pack_right {
private:

	typedef tree<RootPack, LeftSubtree, typename apply_plus<Pack, RightSubtree>::type> aux;

public:

	typedef typename eval_if_c<
		(_height<typename aux::left>::value - _height<typename aux::right>::value) == -2,
		eval_if<greater<Pack, typename aux::right::pack>, _rotate_left<aux>, _rotate_right_left<aux> >,
		aux
	>::type type;
};

template<class Pack, class RootPack, class LeftSubtree, class RightSubtree>
struct _update_root :
	tree<typename apply_plus<Pack, RootPack>::type, LeftSubtree, RightSubtree> {};

template<class Pack, class RootPack, class LeftSubtree, class RightSubtree>
struct _apply_plus_not_less :
	eval_if<
		greater<Pack, RootPack>,
		_apply_plus_pack_right<Pack, RootPack, LeftSubtree, RightSubtree>,
		_update_root<Pack, RootPack, LeftSubtree, RightSubtree> > {};

template<class RootPack, class LeftSubtree, class RightSubtree, class Pack>
struct apply_plus<tree<RootPack, LeftSubtree, RightSubtree>, Pack> :
	eval_if<
		less<Pack, RootPack>,
		_apply_plus_pack_left<Pack, RootPack, LeftSubtree, RightSubtree>,
		_apply_plus_not_less<Pack, RootPack, LeftSubtree, RightSubtree> > {};

template<class Pack, class RootPack, class LeftSubtree, class RightSubtree>
struct apply_plus<Pack, tree<RootPack, LeftSubtree, RightSubtree> > :
	apply_plus<tree<RootPack, LeftSubtree, RightSubtree>, Pack> {};

template<class RootPack, class LeftSubtree, class RightSubtree>
struct apply_plus<tree<RootPack, LeftSubtree, RightSubtree>, empty_tree> :
	tree<RootPack, LeftSubtree, RightSubtree> {};

template<class RootPack, class LeftSubtree, class RightSubtree>
struct apply_plus<empty_tree, tree<RootPack, LeftSubtree, RightSubtree> > :
	tree<RootPack, LeftSubtree, RightSubtree> {};

template<class Pack>
struct apply_plus<Pack, empty_tree> :
	tree<Pack, empty_tree, empty_tree> {};

template<class Pack>
struct apply_plus<empty_tree, Pack> :
	tree<Pack, empty_tree, empty_tree> {};

template<>
struct apply_plus<empty_tree, empty_tree> :
	empty_tree {};

template<class Bitset, int Value1, int Value2>
struct apply_plus<
		pack<single_basis_blade<basis_vectors<Bitset>, static_value<Value1> >, identity_operation>,
		pack<single_basis_blade<basis_vectors<Bitset>, static_value<Value2> >, identity_operation>
	> :
	pack<
		single_basis_blade<basis_vectors<Bitset>, static_value<Value1 + Value2> >,
		identity_operation> {};

template<class Bitset, class Coefficient1, class Operation1, class Coefficient2, class Operation2>
struct apply_plus<
		pack<single_basis_blade<basis_vectors<Bitset>, Coefficient1>, Operation1>,
		pack<single_basis_blade<basis_vectors<Bitset>, Coefficient2>, Operation2>
	> :
	pack<
		single_basis_blade<basis_vectors<Bitset>, dynamic_value>,
		typename plus_assign_operation<pack<single_basis_blade<basis_vectors<Bitset>, dynamic_value>, identity_operation>,
		typename plus_assign_operation<pack<single_basis_blade<basis_vectors<Bitset>, dynamic_value>, identity_operation>,
			assign_zero_operation<pack<single_basis_blade<basis_vectors<Bitset>, dynamic_value>, identity_operation> >,
			pack<single_basis_blade<basis_vectors<Bitset>, Coefficient1>, Operation1> >::type,
			pack<single_basis_blade<basis_vectors<Bitset>, Coefficient2>, Operation2> >::type> {};

template<class Steps, class Coefficient1, class Operation1, class Coefficient2, class Operation2>
struct apply_plus<
		pack<single_basis_blade<Steps, Coefficient1>, Operation1>,
		pack<single_basis_blade<Steps, Coefficient2>, Operation2>
	> :
	pack<
		multiple_basis_blades<Steps, typename min<static_value<2>, typename count_possible_components<Steps>::type>::type>,
		typename plus_assign_operation<pack<multiple_basis_blades<Steps, typename min<static_value<2>, typename count_possible_components<Steps>::type>::type>, identity_operation>,
		typename plus_assign_operation<pack<multiple_basis_blades<Steps, typename min<static_value<2>, typename count_possible_components<Steps>::type>::type>, identity_operation>,
			assign_zero_operation<pack<multiple_basis_blades<Steps, typename min<static_value<2>, typename count_possible_components<Steps>::type>::type>, identity_operation> >,
			pack<single_basis_blade<Steps, Coefficient1>, Operation1> >::type,
			pack<single_basis_blade<Steps, Coefficient2>, Operation2> >::type> {};

template<class Steps, class Count1, class Operation1, class Coefficient2, class Operation2>
struct apply_plus<
		pack<multiple_basis_blades<Steps, Count1>, Operation1>,
		pack<single_basis_blade<Steps, Coefficient2>, Operation2>
	> :
	pack<
		multiple_basis_blades<Steps, typename min<typename plus<Count1, static_value<1> >::type, typename count_possible_components<Steps>::type>::type>,
		typename plus_assign_operation<pack<multiple_basis_blades<Steps, typename min<typename plus<Count1, static_value<1> >::type, typename count_possible_components<Steps>::type>::type>, identity_operation>,
		typename plus_assign_operation<pack<multiple_basis_blades<Steps, typename min<typename plus<Count1, static_value<1> >::type, typename count_possible_components<Steps>::type>::type>, identity_operation>,
			assign_zero_operation<pack<multiple_basis_blades<Steps, typename min<typename plus<Count1, static_value<1> >::type, typename count_possible_components<Steps>::type>::type>, identity_operation> >,
			pack<multiple_basis_blades<Steps, Count1>, Operation1> >::type,
			pack<single_basis_blade<Steps, Coefficient2>, Operation2> >::type> {};

template<class Steps, class Coefficient1, class Operation1, class Count2, class Operation2>
struct apply_plus<
		pack<single_basis_blade<Steps, Coefficient1>, Operation1>,
		pack<multiple_basis_blades<Steps, Count2>, Operation2>
	> :
	pack<
		multiple_basis_blades<Steps, typename min<typename plus<static_value<1>, Count2>::type, typename count_possible_components<Steps>::type>::type>,
		typename plus_assign_operation<pack<multiple_basis_blades<Steps, typename min<typename plus<static_value<1>, Count2>::type, typename count_possible_components<Steps>::type>::type>, identity_operation>,
		typename plus_assign_operation<pack<multiple_basis_blades<Steps, typename min<typename plus<static_value<1>, Count2>::type, typename count_possible_components<Steps>::type>::type>, identity_operation>,
			assign_zero_operation<pack<multiple_basis_blades<Steps, typename min<typename plus<static_value<1>, Count2>::type, typename count_possible_components<Steps>::type>::type>, identity_operation> >,
			pack<single_basis_blade<Steps, Coefficient1>, Operation1> >::type,
			pack<multiple_basis_blades<Steps, Count2>, Operation2> >::type> {};

template<class Steps, class Count1, class Operation1, class Count2, class Operation2>
struct apply_plus<
		pack<multiple_basis_blades<Steps, Count1>, Operation1>,
		pack<multiple_basis_blades<Steps, Count2>, Operation2>
	> :
	pack<
		multiple_basis_blades<Steps, typename min<typename plus<Count1, Count2>::type, typename count_possible_components<Steps>::type>::type>,
		typename plus_assign_operation<pack<multiple_basis_blades<Steps, typename min<typename plus<Count1, Count2>::type, typename count_possible_components<Steps>::type>::type>, identity_operation>,
		typename plus_assign_operation<pack<multiple_basis_blades<Steps, typename min<typename plus<Count1, Count2>::type, typename count_possible_components<Steps>::type>::type>, identity_operation>,
			assign_zero_operation<pack<multiple_basis_blades<Steps, typename min<typename plus<Count1, Count2>::type, typename count_possible_components<Steps>::type>::type>, identity_operation> >,
			pack<multiple_basis_blades<Steps, Count1>, Operation1> >::type,
			pack<multiple_basis_blades<Steps, Count2>, Operation2> >::type> {};
