#ifndef __GA_UTILS_SIGNED_MINKOWSKI_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
#define __GA_UTILS_SIGNED_MINKOWSKI_MACRO_FOR_ALGEBRA_DEFINITION_HPP__

#define _GA_UTILS_MINKOWSKI_ALGEBRA_DEFINITION(SPACE, BASIS_VECTORS_NAMES, N, ...) \
	static minkowski_metric_space<N> const SPACE; \
	static std::string const BASIS_VECTORS_NAMES [] = { __VA_ARGS__ , "ep", "em" }; \
	\
	static auto const ep = e(c<N + 1>); \
	static auto const em = e(c<N + 2>); \
	\
	static auto const no = (em - ep) / c<2>; \
	static auto const ni = ep + em; \
	\
	static auto const I = pseudoscalar(SPACE); \
	static auto const Ie = rcont(I, op(ep, em, SPACE), SPACE);

#endif // __GA_UTILS_SIGNED_MINKOWSKI_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
