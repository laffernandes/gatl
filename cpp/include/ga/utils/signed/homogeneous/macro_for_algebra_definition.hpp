#ifndef __GA_UTILS_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
#define __GA_UTILS_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_DEFINITION_HPP__

#define _GA_UTILS_HOMOGENEOUS_ALGEBRA_DEFINITION(SPACE, BASIS_VECTORS_NAMES, N, ...) \
	static homogeneous_metric_space<N> const SPACE; \
	static std::string const BASIS_VECTORS_NAMES [] = { __VA_ARGS__ , "ep" }; \
	\
	static auto const ep = e(c<N + 1>); \
	\
	static auto const I = pseudoscalar(SPACE); \
	static auto const Ie = rcont(I, ep, SPACE);

#endif // __GA_UTILS_SIGNED_HOMOGENEOUS_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
