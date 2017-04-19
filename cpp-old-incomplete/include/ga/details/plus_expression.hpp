// Binary plus expression (A + B).
//   FirstArgument must be a multivector<> structure.
//   SecondArgument must be a multivector<> structure.
template<class FirstArgument, class SecondArgument>
class plus_expression : public binary_expression<
		plus_expression,
		FirstArgument,
		SecondArgument,
		typename organize<typename apply_plus<typename update_argument_tag<typename FirstArgument::composition, first_argument_tag>::type, typename update_argument_tag<typename SecondArgument::composition, second_argument_tag>::type>::type>::type
	> {
private:

	typedef binary_expression<
			ga::details::plus_expression,
			FirstArgument,
			SecondArgument,
			typename organize<typename apply_plus<typename update_argument_tag<typename FirstArgument::composition, first_argument_tag>::type, typename update_argument_tag<typename SecondArgument::composition, second_argument_tag>::type>::type>::type
		> super;

public:

	typedef typename super::first_argument_type  first_argument_type;
	typedef typename super::second_argument_type second_argument_type;

	typedef typename super::composition          composition;

	typedef typename super::lazy_type            lazy_type;
	typedef typename super::concrete_type        concrete_type;

public:

	inline static
	lazy_type bind(const first_argument_type &first_argument, const second_argument_type &second_argument) {
		return lazy_type(plus_expression(first_argument, second_argument));
	}

public:

	using super::eval;
	using super::first;
	using super::second;

protected:

	inline
	plus_expression(const first_argument_type &first_argument, const second_argument_type &second_argument) :
		super(first_argument, second_argument) {}
};
