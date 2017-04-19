template<class T1, class T2, template<class, class> class BinaryOperation>
struct binary_transform;

template<class RootPack1, class LeftSubtree1, class RightSubtree1, class RootPack2, class LeftSubtree2, class RightSubtree2, template<class, class> class BinaryOperation>
struct binary_transform<tree<RootPack1, LeftSubtree1, RightSubtree1>, tree<RootPack2, LeftSubtree2, RightSubtree2>, BinaryOperation> {
private:

	template<class Pack1>
	struct distribute_over_left {
	private:

		template<class Pack2>
		struct distribute_over_right :
			BinaryOperation<Pack1, Pack2> {};

	public:

		typedef typename unary_transform<tree<RootPack2, LeftSubtree2, RightSubtree2>, distribute_over_right>::type type;
	};

public:

	typedef typename unary_transform<tree<RootPack1, LeftSubtree1, RightSubtree1>, distribute_over_left>::type type;
};

template<class RootPack1, class LeftSubtree1, class RightSubtree1, class Pack2, template<class, class> class BinaryOperation>
struct binary_transform<tree<RootPack1, LeftSubtree1, RightSubtree1>, Pack2, BinaryOperation> {
private:

	template<class Pack1>
	struct distribute_over_left :
		BinaryOperation<Pack1, Pack2> {};

public:

	typedef typename unary_transform<tree<RootPack1, LeftSubtree1, RightSubtree1>, distribute_over_left>::type type;
};

template<class Pack1, class RootPack2, class LeftSubtree2, class RightSubtree2, template<class, class> class BinaryOperation>
struct binary_transform<Pack1, tree<RootPack2, LeftSubtree2, RightSubtree2>, BinaryOperation> {
private:

	template<class Pack2>
	struct distribute_over_right :
		BinaryOperation<Pack1, Pack2> {};

public:

	typedef typename unary_transform<tree<RootPack2, LeftSubtree2, RightSubtree2>, distribute_over_right>::type type;
};

template<class Pack1, class LeftSubtree1, class RightSubtree1, template<class, class> class BinaryOperation>
struct binary_transform<tree<Pack1, LeftSubtree1, RightSubtree1>, empty_tree, BinaryOperation> {

	typedef empty_tree type;
};

template<class Pack2, class LeftSubtree2, class RightSubtree2, template<class, class> class BinaryOperation>
struct binary_transform<empty_tree, tree<Pack2, LeftSubtree2, RightSubtree2>, BinaryOperation> {

	typedef empty_tree type;
};

template<class Pack1, template<class, class> class BinaryOperation>
struct binary_transform<Pack1, empty_tree, BinaryOperation> {

	typedef empty_tree type;
};

template<class Pack2, template<class, class> class BinaryOperation>
struct binary_transform<empty_tree, Pack2, BinaryOperation> {

	typedef empty_tree type;
};

template<template<class, class> class BinaryOperation>
struct binary_transform<empty_tree, empty_tree, BinaryOperation> {

	typedef empty_tree type;
};
