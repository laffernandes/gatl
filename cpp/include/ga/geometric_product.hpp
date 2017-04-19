_GA_DEFINE_BINARY_METRIC_OPERATION(gp)

template<class FirstArgumentType, class SecondArgumentType>
inline
auto operator * (FirstArgumentType&& m1, SecondArgumentType&& m2)->decltype(gp_em(m1, m2)) {
	///TODO Verificar se um dos dois argumentos é um escalar. Caso contrário, levantar ga::illegal_call_exception().
	return gp_em(m1, m2);
}
