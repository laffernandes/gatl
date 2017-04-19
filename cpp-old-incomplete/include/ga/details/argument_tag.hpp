// The identification of the first argument of a binary expression.
//   Argument is a pack<> structure.
template<class Argument>
struct first_argument_tag {

	typedef first_argument_tag type;
};

// The identification of the second argument of a binary expression.
//   Argument is a pack<> structure.
template<class Argument>
struct second_argument_tag {

	typedef second_argument_tag type;
};

// The identification of the single argument of an unary expression.
//   Argument is a pack<> structure.
template<class Argument>
struct single_argument_tag {

	typedef single_argument_tag type;
};
