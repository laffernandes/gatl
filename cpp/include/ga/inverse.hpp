template<class ArgumentType, class FactorType, class Definition>
inline
auto inv(ArgumentType&& m, metric<FactorType, Definition>&& metric)->decltype(gp(reverse(m), inv(scp(m, reverse(m), metric), metric), metric)) {
	auto&& reverse_m = reverse(m);
	return gp(reverse_m, inv(scp(m, reverse_m, metric), metric), metric);
}

template<class ArgumentType>
inline
auto inv_em(ArgumentType&& m)->decltype(inv(m, euclidean_metric())) {
	return inv(m, euclidean_metric());
}
