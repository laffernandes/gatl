#ifndef __GA_SCALAR_WRAPPER_HPP__
#define __GA_SCALAR_WRAPPER_HPP__

#define GA_DECLARE_SCALAR_WRAPPER(TYPE) \
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	constexpr decltype(auto) operator+(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, TYPE const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	constexpr decltype(auto) operator+(TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	constexpr decltype(auto) operator+(ga::detail::empty_expression const &lhs, TYPE const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	constexpr decltype(auto) operator+(TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	constexpr decltype(auto) operator+(ga::detail::cvalue<Value> const &lhs, TYPE const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	constexpr decltype(auto) operator+(TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::plus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	constexpr decltype(auto) operator-(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, TYPE const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	constexpr decltype(auto) operator-(TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	constexpr decltype(auto) operator-(ga::detail::empty_expression const &lhs, TYPE const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	constexpr decltype(auto) operator-(TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	constexpr decltype(auto) operator-(ga::detail::cvalue<Value> const &lhs, TYPE const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	constexpr decltype(auto) operator-(TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::minus(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	constexpr decltype(auto) operator*(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, TYPE const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	constexpr decltype(auto) operator*(TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	constexpr decltype(auto) operator*(ga::detail::empty_expression const &lhs, TYPE const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	constexpr decltype(auto) operator*(TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<ga::default_integral_t Value> \
	constexpr decltype(auto) operator*(ga::detail::cvalue<Value> const &lhs, TYPE const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<ga::default_integral_t Value> \
	constexpr decltype(auto) operator*(TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::gp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	constexpr decltype(auto) operator/(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, TYPE const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	constexpr decltype(auto) operator/(TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	constexpr decltype(auto) operator/(ga::detail::empty_expression const &lhs, TYPE const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<ga::default_integral_t Value> \
	constexpr decltype(auto) operator/(ga::detail::cvalue<Value> const &lhs, TYPE const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<ga::default_integral_t Value> \
	constexpr decltype(auto) operator/(TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::igp(lhs, rhs, ga::euclidean_metric_t()); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	constexpr decltype(auto) operator^(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, TYPE const &rhs) { \
		return ga::op(lhs, rhs); \
	} \
	\
	template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
	constexpr decltype(auto) operator^(TYPE const &lhs, ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
		return ga::op(lhs, rhs); \
	} \
	\
	constexpr decltype(auto) operator^(ga::detail::empty_expression const &lhs, TYPE const &rhs) { \
		return ga::op(lhs, rhs); \
	} \
	\
	constexpr decltype(auto) operator^(TYPE const &lhs, ga::detail::empty_expression const &rhs) { \
		return ga::op(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	constexpr decltype(auto) operator^(ga::detail::cvalue<Value> const &lhs, TYPE const &rhs) { \
		return ga::op(lhs, rhs); \
	} \
	\
	template<ga::default_integral_t Value> \
	constexpr decltype(auto) operator^(TYPE const &lhs, ga::detail::cvalue<Value> const &rhs) { \
		return ga::op(lhs, rhs); \
	}

GA_DECLARE_SCALAR_WRAPPER(std::int16_t)
GA_DECLARE_SCALAR_WRAPPER(std::int32_t)
GA_DECLARE_SCALAR_WRAPPER(std::int64_t)

GA_DECLARE_SCALAR_WRAPPER(std::float_t)
GA_DECLARE_SCALAR_WRAPPER(std::double_t)

#endif // __GA_SCALAR_WRAPPER_HPP__
