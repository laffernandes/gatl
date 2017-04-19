// Unary minus expression (-A).
//   Argument must be a multivector<> structure.
template<class Argument>
class uminus_expression : public unary_expression<
		uminus_expression,
		Argument,
		typename organize<typename apply_uminus<typename update_argument_tag<typename Argument::composition, single_argument_tag>::type>::type>::type
	> {
private:

	typedef unary_expression<
			ga::details::uminus_expression,
			Argument,
			typename organize<typename apply_uminus<typename update_argument_tag<typename Argument::composition, single_argument_tag>::type>::type>::type
		> super;

public:

	typedef typename super::single_argument_type single_argument_type;

	typedef typename super::composition          composition;

	typedef typename super::lazy_type            lazy_type;
	typedef typename super::concrete_type        concrete_type;

public:

	inline static
	lazy_type bind(const single_argument_type &argument) {
		return lazy_type(uminus_expression(argument));
	}

public:

	using super::eval;
	using super::single;

protected:

	inline
	uminus_expression(const single_argument_type &argument) :
		super(argument) {}
};
