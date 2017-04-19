#define _GA_DEFINE_BINARY_METRIC_OPERATION(OPERATION) \
	template<class FirstCoefficientType, class FirstComposition, ga::detail::container_class FirstContainer, class SecondCoefficientType, class SecondComposition, ga::detail::container_class SecondContainer, class FactorType, class Definition> \
	inline \
	auto OPERATION##(multivector<FirstCoefficientType, FirstComposition, FirstContainer>&& m1, multivector<SecondCoefficientType, SecondComposition, SecondContainer>&& m2, metric<FactorType, Definition>&& metric)->decltype(ga::detail::##OPERATION##_expression<multivector<FirstCoefficientType, FirstComposition, FirstContainer>, multivector<SecondCoefficientType, SecondComposition, SecondContainer>, metric<FactorType, Definition> >::bind(m1, m2, metric)) { \
		return ga::detail::##OPERATION##_expression<multivector<FirstCoefficientType, FirstComposition, FirstContainer>, multivector<SecondCoefficientType, SecondComposition, SecondContainer>, metric<FactorType, Definition> >::bind(m1, m2, metric); \
	} \
	\
	template<class FirstCoefficientType, class FirstComposition, ga::detail::container_class FirstContainer, class ScalarType, class FactorType, class Definition> \
	inline \
	auto OPERATION##(multivector<FirstCoefficientType, FirstComposition, FirstContainer>&& m1, ScalarType&& m2, metric<FactorType, Definition>&& metric)->decltype(OPERATION##(m1, make_scalar(m2), metric)) { \
		return OPERATION##(m1, make_scalar(m2), metric); \
	} \
	\
	template<class ScalarType, class SecondCoefficientType, class SecondComposition, ga::detail::container_class SecondContainer, class FactorType, class Definition> \
	inline \
	auto OPERATION##(ScalarType&& m1, multivector<SecondCoefficientType, SecondComposition, SecondContainer>&& m2, metric<FactorType, Definition>&& metric)->decltype(OPERATION##(make_scalar(m1), m2, metric)) { \
		return OPERATION##(make_scalar(m1), m2, metric); \
	} \
	\
	template<class FirstScalarType, class SecondScalarType, class FactorType, class Definition> \
	inline \
	auto OPERATION##(FirstScalarType&& m1, SecondScalarType&& m2, metric<FactorType, Definition>&& metric)->decltype(OPERATION##(make_scalar(m1), make_scalar(m2), metric)) { \
		return OPERATION##(make_scalar(m1), make_scalar(m2), metric); \
	} \
	\
	template<class FirstArgumentType, class SecondArgumentType> \
	inline \
	auto OPERATION##_em(FirstArgumentType&& m1, SecondArgumentType&& m2)->decltype(OPERATION##(m1, m2, euclidean_metric())) { \
		return OPERATION##_em(m1, m2, euclidean_metric()); \
	}

#define _GA_DEFINE_BINARY_NON_METRIC_OPERATION(OPERATION) \
	template<class FirstCoefficientType, class FirstComposition, ga::detail::container_class FirstContainer, class SecondCoefficientType, class SecondComposition, ga::detail::container_class SecondContainer> \
	inline \
	auto OPERATION##(multivector<FirstCoefficientType, FirstComposition, FirstContainer>&& m1, multivector<SecondCoefficientType, SecondComposition, SecondContainer>&& m2)->decltype(ga::detail::##OPERATION##_expression<multivector<FirstCoefficientType, FirstComposition, FirstContainer>, multivector<SecondCoefficientType, SecondComposition, SecondContainer> >::bind(m1, m2)) { \
		return ga::detail::##OPERATION##_expression<multivector<FirstCoefficientType, FirstComposition, FirstContainer>, multivector<SecondCoefficientType, SecondComposition, SecondContainer> >::bind(m1, m2); \
	} \
	\
	template<class FirstCoefficientType, class FirstComposition, ga::detail::container_class FirstContainer, class ScalarType> \
	inline \
	auto OPERATION##(multivector<FirstCoefficientType, FirstComposition, FirstContainer>&& m1, ScalarType&& m2)->decltype(OPERATION##(m1, make_scalar(m2))) { \
		return OPERATION##(m1, make_scalar(m2)); \
	} \
	\
	template<class ScalarType, class SecondCoefficientType, class SecondComposition, ga::detail::container_class SecondContainer> \
	inline \
	auto OPERATION##(ScalarType&& m1, multivector<SecondCoefficientType, SecondComposition, SecondContainer>&& m2)->decltype(OPERATION##(make_scalar(m1), m2)) { \
		return OPERATION##(make_scalar(m1), m2); \
	} \
	\
	template<class FirstScalarType, class SecondScalarType> \
	inline \
	auto OPERATION##(FirstScalarType&& m1, SecondScalarType&& m2)->decltype(OPERATION##(make_scalar(m1), make_scalar(m2))) { \
		return OPERATION##(make_scalar(m1), make_scalar(m2)); \
	}

#define _GA_DEFINE_UNARY_NON_METRIC_OPERATION(OPERATION) \
	template<class CoefficientType, class Composition, ga::detail::container_class Container> \
	inline \
	auto OPERATION##(multivector<CoefficientType, Composition, Container>&& m)->decltype(ga::detail::##OPERATION##_expression<multivector<CoefficientType, Composition, Container> >::bind(m)) { \
		return ga::detail::##OPERATION##_expression<multivector<CoefficientType, Composition, Container> >::bind(m); \
	} \
	\
	template<class ScalarType> \
	inline \
	auto OPERATION##(ScalarType&& m)->decltype(OPERATION##(make_scalar(m))) { \
		return OPERATION##(make_scalar(m)); \
	}
