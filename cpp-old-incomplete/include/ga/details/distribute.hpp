// Apply the given operation to each pack in given three.
template<class Tree, template<class> class Operation>
struct distribute :
	apply_plus<typename apply_plus<
		typename distribute<typename Tree::left, Operation>::type,
		typename Operation<typename Tree::pack>::type>::type,
		typename distribute<typename Tree::right, Operation>::type
	> {};

template<template<class> class Operation>
struct distribute<empty_tree, Operation> :
	empty_tree {};
