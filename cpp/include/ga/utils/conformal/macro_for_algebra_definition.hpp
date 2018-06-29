#ifndef __GA_UTILS_CONFORMAL_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
#define __GA_UTILS_CONFORMAL_MACRO_FOR_ALGEBRA_DEFINITION_HPP__

#define _GA_UTILS_CONFORMAL_ALGEBRA_DEFINITION(SPACE, BASIS_VECTORS_NAMES, N, ...) \
	static conformal_metric_space<N> const SPACE; \
	static std::array<std::string, N + 2> const BASIS_VECTORS_NAMES = { __VA_ARGS__ , "no", "ni" }; \
	\
	static auto const no = e(c<N + 1>); \
	static auto const ni = e(c<N + 2>); \
	\
	static auto const ep = (ni / c<2>) - no; \
	static auto const em = (ni / c<2>) + no; \
	\
	static auto const I = pseudoscalar(SPACE); \
	static auto const Ie = rcont(I, op(no, ni, SPACE), SPACE);


#endif // __GA_UTILS_CONFORMAL_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
