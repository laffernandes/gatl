#ifndef __GA_SCALAR_WRAPPER_HPP__
#define __GA_SCALAR_WRAPPER_HPP__

#define GA_DECLARE_SCALAR_WRAPPER(TYPE, SPECIFIER) \
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator+(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, TYPE const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator+(TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	SPECIFIER decltype(auto) operator+(ga::detail::empty_expression const &lhs, TYPE const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	SPECIFIER decltype(auto) operator+(TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator+(ga::detail::cvalue<Value> const &lhs, TYPE const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator+(TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator-(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, TYPE const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator-(TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	SPECIFIER decltype(auto) operator-(ga::detail::empty_expression const &lhs, TYPE const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	SPECIFIER decltype(auto) operator-(TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator-(ga::detail::cvalue<Value> const &lhs, TYPE const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator-(TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator*(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, TYPE const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator*(TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	SPECIFIER decltype(auto) operator*(ga::detail::empty_expression const &lhs, TYPE const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	SPECIFIER decltype(auto) operator*(TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator*(ga::detail::cvalue<Value> const &lhs, TYPE const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator*(TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator/(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, TYPE const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator/(TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	SPECIFIER decltype(auto) operator/(ga::detail::empty_expression const &lhs, TYPE const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator/(ga::detail::cvalue<Value> const &lhs, TYPE const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator/(TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator^(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, TYPE const &rhs) { \
		return ga::op(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	SPECIFIER decltype(auto) operator^(TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::op(lhs, rhs); \
	} \
	\
	SPECIFIER decltype(auto) operator^(ga::detail::empty_expression const &lhs, TYPE const &rhs) { \
		return ga::op(lhs, rhs); \
	} \
	\
	SPECIFIER decltype(auto) operator^(TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::op(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator^(ga::detail::cvalue<Value> const &lhs, TYPE const &rhs) { \
		return ga::op(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	SPECIFIER decltype(auto) operator^(TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::op(lhs, rhs); \
	}

GA_DECLARE_SCALAR_WRAPPER(std::int16_t, constexpr)
GA_DECLARE_SCALAR_WRAPPER(std::int32_t, constexpr)
GA_DECLARE_SCALAR_WRAPPER(std::int64_t, constexpr)

GA_DECLARE_SCALAR_WRAPPER(std::float_t, constexpr)
GA_DECLARE_SCALAR_WRAPPER(std::double_t, constexpr)

#endif // __GA_SCALAR_WRAPPER_HPP__
