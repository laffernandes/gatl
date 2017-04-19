// Binary minus expression (A - B).
//   FirstArgument must be a multivector<> structure.
//   SecondArgument must be a multivector<> structure.
template<class FirstArgument, class SecondArgument>
class minus_expression : protected plus_expression<FirstArgument, typename uminus_expression<SecondArgument>::lazy_type> {
private:

	typedef uminus_expression<SecondArgument>                              first_step;
	typedef plus_expression<FirstArgument, typename first_step::lazy_type> second_step;

public:

	typedef typename second_step::first_argument_type first_argument_type;
	typedef typename first_step::single_argument_type second_argument_type;

	typedef typename second_step::composition         composition;

	typedef typename second_step::lazy_type           lazy_type;
	typedef typename second_step::concrete_type       concrete_type;

public:

	inline static
	lazy_type bind(const first_argument_type &first_argument, const second_argument_type &second_argument) {
		return lazy_type(minus_expression(first_argument, first_step::bind(second_argument)));
	}

public:

	using second_step::eval;
	using second_step::first;
	using second_step::second;

protected:

	inline
	minus_expression(const first_argument_type &first_argument, const typename first_step::lazy_type &second_argument) :
		second_step(first_argument, second_argument) {}
};
