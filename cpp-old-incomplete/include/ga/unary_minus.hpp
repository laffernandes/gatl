namespace result_of {

	template<class ArgumentType>
	struct uminus {

		typedef ArgumentType type;
	};

	template<class CoefficientType, class Composition, container_class Container>
	struct uminus<multivector<CoefficientType, Composition, Container> > {

		typedef typename ga::details::uminus_expression<multivector<CoefficientType, Composition, Container> >::lazy_type type;
	};

}

template<class CoefficientType, class Composition, container_class Container>
inline
typename result_of::uminus<multivector<CoefficientType, Composition, Container> >::type
uminus(const multivector<CoefficientType, Composition, Container> &m) {
	return details::uminus_expression<multivector<CoefficientType, Composition, Container> >::bind(m);
}

template<class ScalarType>
inline
ScalarType
uminus(const ScalarType &s) {
	return -s;
}

template<class CoefficientType, class Composition, container_class Container>
inline
auto
operator - (const multivector<CoefficientType, Composition, Container> &m)->decltype(uminus(m)) {
	return uminus(m);
}
