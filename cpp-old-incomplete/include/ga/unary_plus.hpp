namespace result_of {

	template<class ArgumentType>
	struct uplus {

		typedef ArgumentType argument_type;

		typedef ArgumentType type;
	};

}

template<class CoefficientType, class Composition, container_class Container>
inline
typename result_of::uplus<multivector<CoefficientType, Composition, Container> >::type
uplus(const multivector<CoefficientType, Composition, Container> &m) {
	return m;
}

template<class ScalarType>
inline
auto
uplus(const ScalarType &s)->decltype(s) {
	return s;
}

template<class CoefficientType, class Composition, container_class Container>
inline
auto
operator + (const multivector<CoefficientType, Composition, Container> &m)->decltype(uplus(m)) {
	return uplus(m);
}
