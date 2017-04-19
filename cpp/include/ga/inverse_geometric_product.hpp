template<class FirstArgumentType, class SecondArgumentType, class FactorType, class Definition>
inline
auto igp(FirstArgumentType&& m1, SecondArgumentType&& m2, metric<FactorType, Definition>&& metric)->decltype(gp(m1, inv(m2, metric), metric)) {
	return gp(m1, inv(m2, metric), metric);
}

template<class FirstArgumentType, class SecondArgumentType>
inline
auto igp_em(FirstArgumentType&& m1, SecondArgumentType&& m2)->decltype(gp_em(m1, inv_em(m2))) {
	return gp_em(m1, inv_em(m2));
}

template<class FirstArgumentType, class SecondArgumentType>
inline
auto operator / (FirstArgumentType&& m1, SecondArgumentType&& m2)->decltype(igp_em(m1, m2)) {
	return igp_em(m1, m2); //TODO Verificar se o segundo argumento é um escalar. Caso contrário, levantar ga::illegal_call_exception().
}
