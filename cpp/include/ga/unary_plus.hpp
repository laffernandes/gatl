template<class CoefficientType, class Composition, ga::detail::container_class Container>
inline
auto uplus(const multivector<CoefficientType, Composition, Container>& m)->decltype(m) {
	return m;
}

template<class ScalarType>
inline
auto uplus(ScalarType&& m)->decltype(+m) {
	return +m;
}

template<class CoefficientType, class Composition, ga::detail::container_class Container>
inline
auto operator + (const multivector<CoefficientType, Composition, Container>& m)->decltype(m) {
	return m;
}
