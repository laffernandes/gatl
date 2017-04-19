template<class ArgumentType, class FactorType, class Definition>
inline
auto rnorm_sqr(ArgumentType&& m, metric<FactorType, Definition>&& metric)->decltype(scp(m, reverse(m), metric)) {
	return scp(m, reverse(m), metric);
}

template<class ArgumentType>
inline
auto rnorm_sqr_em(ArgumentType&& m)->decltype(rnorm_sqr(m, euclidean_metric())) {
	return rnorm_sqr(m, euclidean_metric());
}

template<class ArgumentType, class FactorType, class Definition>
inline
auto rnorm(ArgumentType&& m, metric<FactorType, Definition>&& metric)->decltype(sqrt(rnorm_sqr(m, metric))) {
	return sqrt(rnorm_sqr(m, metric));
}

template<class ArgumentType>
inline
auto rnorm_em(ArgumentType&& m)->decltype(rnorm(m, euclidean_metric())) {
	return rnorm(m, euclidean_metric());
}
