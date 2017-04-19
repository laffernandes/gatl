template<class FirstArgumentType, class SecondArgumentType, class FactorType, class Definition>
inline
auto undual(FirstArgumentType&& m, SecondArgumentType&& pseudoscalar, metric<FactorType, Definition>&& metric)->decltype(lcont(m, pseudoscalar, metric)) {
	return lcont(m, pseudoscalar, metric);
}

template<class FirstArgumentType, class SecondArgumentType>
inline
auto undual_em(FirstArgumentType&& m, SecondArgumentType&& pseudoscalar)->decltype(undual(m, pseudoscalar, euclidean_metric())) {
	return undual(m, pseudoscalar, euclidean_metric());
}
