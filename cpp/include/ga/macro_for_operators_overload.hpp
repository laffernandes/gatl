#ifndef __GA_MACRO_FOR_OPERATORS_OVERLOAD_HPP__
#define __GA_MACRO_FOR_OPERATORS_OVERLOAD_HPP__

#define GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(SCALAR_TYPE, SPECIFIER) \
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator+(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator+(SCALAR_TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	SPECIFIER decltype(auto) operator+(ga::detail::empty_expression const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	SPECIFIER decltype(auto) operator+(SCALAR_TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator+(ga::detail::cvalue<Value> const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator+(SCALAR_TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator-(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator-(SCALAR_TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	SPECIFIER decltype(auto) operator-(ga::detail::empty_expression const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	SPECIFIER decltype(auto) operator-(SCALAR_TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator-(ga::detail::cvalue<Value> const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator-(SCALAR_TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator*(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator*(SCALAR_TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	SPECIFIER decltype(auto) operator*(ga::detail::empty_expression const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	SPECIFIER decltype(auto) operator*(SCALAR_TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator*(ga::detail::cvalue<Value> const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator*(SCALAR_TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator/(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator/(SCALAR_TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	SPECIFIER decltype(auto) operator/(ga::detail::empty_expression const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator/(ga::detail::cvalue<Value> const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator/(SCALAR_TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator^(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::op(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator^(SCALAR_TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::op(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	SPECIFIER decltype(auto) operator^(ga::detail::empty_expression const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::op(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	SPECIFIER decltype(auto) operator^(SCALAR_TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::op(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator^(ga::detail::cvalue<Value> const &lhs, SCALAR_TYPE const &rhs) { \
		return ga::op(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator^(SCALAR_TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::op(lhs, rhs, ga::euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
	}

#endif // __GA_MACRO_FOR_OPERATORS_OVERLOAD_HPP__
