//TODO Rever para remover a boost

template<template<class, class, class> class BinaryMetricExpression, class FirstArgument, class SecondArgument, class MetricArgument, class Composition>
class binary_metric_expression :
	private first_argument_storage_for_expression<FirstArgument>,
	private second_argument_storage_for_expression<SecondArgument>,
	private metric_argument_storage_for_expression<MetricArgument>,
	public expression<BinaryMetricExpression<FirstArgument, SecondArgument, MetricArgument> > {
private:

	typedef expression<BinaryMetricExpression<FirstArgument, SecondArgument, MetricArgument> > super;
	typedef first_argument_storage_for_expression<FirstArgument>                               first_storage;
	typedef second_argument_storage_for_expression<SecondArgument>                             second_storage;
	typedef metric_argument_storage_for_expression<MetricArgument>                             metric_storage;

public:

	typedef typename first_storage::first_argument_type              first_argument_type;
	typedef typename first_storage::first_argument_reference         first_argument_reference;
	typedef typename first_storage::first_argument_const_reference   first_argument_const_reference;

	typedef typename second_storage::second_argument_type            second_argument_type;
	typedef typename second_storage::second_argument_reference       second_argument_reference;
	typedef typename second_storage::second_argument_const_reference second_argument_const_reference;

	typedef typename metric_storage::metric_argument_type            metric_argument_type;
	typedef typename metric_storage::metric_argument_reference       metric_argument_reference;
	typedef typename metric_storage::metric_argument_const_reference metric_argument_const_reference;

private:

	typedef typename std::common_type<typename std::common_type<typename first_argument_type::coefficient_type, typename second_argument_type::coefficient_type>::type, typename metric_argument_type::factor_type>::type coefficient_type;

public:

	typedef Composition composition;

	typedef multivector<coefficient_type, typename std::conditional<is_compile_time<composition>::value, composition, binary_metric_expression>::type> lazy_type;
	typedef multivector<coefficient_type, typename make_concrete<composition>::type>                                                                   concrete_type;

public:

	inline
	concrete_type eval() const {
		concrete_type result;
		composition::eval(result.make_storage_iterator(), this->instance());
		return result;
	}

	using first_storage::first;
	using second_storage::second;
	using metric_storage::metric;

protected:

	inline
	binary_metric_expression(first_argument_const_reference first_argument, second_argument_const_reference second_argument, metric_argument_const_reference metric_argument) :
		first_storage(first_argument), second_storage(second_argument), metric_storage(metric_argument) {}
};
