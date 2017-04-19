//TODO Rever para remover a boost

template<template<class> class UnaryExpression, class Argument, class Composition>
class unary_expression :
	private single_argument_storage_for_expression<Argument>,
	public expression<UnaryExpression<Argument> > {
private:

	typedef expression<UnaryExpression<Argument> >           super;
	typedef single_argument_storage_for_expression<Argument> single_storage;

public:

	typedef typename single_storage::single_argument_type            single_argument_type;
	typedef typename single_storage::single_argument_reference       single_argument_reference;
	typedef typename single_storage::single_argument_const_reference single_argument_const_reference;

	typedef Composition composition;

	typedef multivector<typename single_argument_type::coefficient_type, typename std::conditional<is_compile_time<composition>::value, composition, unary_expression>::type> lazy_type;
	typedef multivector<typename single_argument_type::coefficient_type, typename make_concrete<composition>::type>                                                           concrete_type;

public:

	inline
	concrete_type eval() const {
		concrete_type result;
		composition::eval(result.make_storage_iterator(), this->instance());
		return result;
	}
	
	using single_storage::single;

protected:

	inline
	unary_expression(single_argument_const_reference argument) :
		single_storage(argument) {}
};
