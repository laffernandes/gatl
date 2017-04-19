template<class FirstArgumentType, class SecondArgumentType, class FactorType, class Definition>
inline
auto dual(FirstArgumentType&& m, SecondArgumentType&& pseudoscalar, metric<FactorType, Definition>&& metric)->decltype(lcont(m, inv(pseudoscalar, metric), metric)) {
	return lcont(m, inv(pseudoscalar, metric), metric);
}

template<class FirstArgumentType, class SecondArgumentType>
inline
auto dual_em(FirstArgumentType&& m, SecondArgumentType&& pseudoscalar)->decltype(dual(m, pseudoscalar, euclidean_metric())) {
	return dual(m, pseudoscalar, euclidean_metric());
}
