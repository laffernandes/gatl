template<class Pack>
struct is_obsolete :
	eval_if<is_compile_time<Pack>, is_zero<typename Pack::components::coefficient>, is_same<typename Pack::operation, assign_zero_operation<pack<typename Pack::components, identity_operation> > > > {};

// Organize the given three. By doing so, multivectors with the same set of components are always identical.
template<class Tree>
struct organize {
private:

	typedef typename organize<typename Tree::left>::type  transformed_left_subtree;
	typedef typename organize<typename Tree::right>::type transformed_right_subtree;

public:

	typedef typename apply_plus<
		typename eval_if<is_obsolete<typename Tree::pack>,
			transformed_left_subtree,
			apply_plus<transformed_left_subtree, typename Tree::pack>
		>::type,
		transformed_right_subtree
	>::type type;
};

template<>
struct organize<empty_tree> :
	empty_tree {};
