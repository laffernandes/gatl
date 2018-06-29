#ifndef __GA_UTILS_SIGNED_EUCLIDEAN_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
#define __GA_UTILS_SIGNED_EUCLIDEAN_MACRO_FOR_ALGEBRA_DEFINITION_HPP__

#define _GA_UTILS_EUCLIDEAN_ALGEBRA_DEFINITION(SPACE, BASIS_VECTORS_NAMES, N, ...) \
	static euclidean_metric_space<N> const SPACE; \
	static std::array<std::string, N> const BASIS_VECTORS_NAMES = { __VA_ARGS__ }; \
	\
	static auto const I = pseudoscalar(SPACE); \
	static auto const Ie = I;

#endif // __GA_UTILS_SIGNED_EUCLIDEAN_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
