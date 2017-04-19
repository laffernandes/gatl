//TODO Rever para remover a boost

template<template<class, class> class BinaryExpression, class FirstArgument, class SecondArgument, class Composition>
class binary_expression :
	private first_argument_storage_for_expression<FirstArgument>,
	private second_argument_storage_for_expression<SecondArgument>,
	public expression<BinaryExpression<FirstArgument, SecondArgument> > {
private:

	typedef expression<BinaryExpression<FirstArgument, SecondArgument> > super;
	typedef first_argument_storage_for_expression<FirstArgument>         first_storage;
	typedef second_argument_storage_for_expression<SecondArgument>       second_storage;

public:

	typedef typename first_storage::first_argument_type              first_argument_type;
	typedef typename first_storage::first_argument_reference         first_argument_reference;
	typedef typename first_storage::first_argument_const_reference   first_argument_const_reference;

	typedef typename second_storage::second_argument_type            second_argument_type;
	typedef typename second_storage::second_argument_reference       second_argument_reference;
	typedef typename second_storage::second_argument_const_reference second_argument_const_reference;

private:

	typedef typename std::common_type<typename first_argument_type::coefficient_type, typename second_argument_type::coefficient_type>::type coefficient_type;

public:

	typedef Composition composition;

	typedef multivector<coefficient_type, typename std::conditional<is_compile_time<composition>::value, composition, binary_expression>::type> lazy_type;
	typedef multivector<coefficient_type, typename make_concrete<composition>::type>                                                            concrete_type;

public:

	inline
	concrete_type eval() const {
		concrete_type result;
		composition::eval(result.make_storage_iterator(), this->instance());
		return result;
	}

	using first_storage::first;
	using second_storage::second;

protected:

	inline
	binary_expression(first_argument_const_reference first_argument, second_argument_const_reference second_argument) :
		first_storage(first_argument), second_storage(second_argument) {}
};
