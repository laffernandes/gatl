template<class Expression>
struct sugested_container_class :
	sugested_container_class<typename Expression::composition> {};

template<class Components, class Operation, class LeftSubtree, class RightSubtree>
struct sugested_container_class<tree<pack<Components, Operation>, LeftSubtree, RightSubtree> > {
private:

	static const container_class current_value = (is_compile_time<typename Components::max_count>::value) ? ((and_<is_compile_time<typename Components::basis_vectors>, is_compile_time<typename Components::coefficient> >::value) ? container_class::none : container_class::array) : container_class::vector; //TODO Rever a implementação, pois map não é usado.
	
	static const container_class left_subtree_value = sugested_container_class<LeftSubtree>::value;
	static const container_class right_subtree_value = sugested_container_class<RightSubtree>::value;
	static const container_class subtree_value = (left_subtree_value >= right_subtree_value) ? left_subtree_value : right_subtree_value;

public:

	static const container_class value = (current_value >= subtree_value) ? current_value : subtree_value;
};

template<>
struct sugested_container_class<empty_tree> {

	static const container_class value = container_class::none;
};
