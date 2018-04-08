#ifndef __GA_CLIFFORD_MACRO_FOR_OPERATORS_OVERLOAD_HPP__
#define __GA_CLIFFORD_MACRO_FOR_OPERATORS_OVERLOAD_HPP__

#define GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(SCALAR_TYPE, SPECIFIER) \
	namespace ga { \
		\
		namespace clifford { \
			\
			template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
			SPECIFIER decltype(auto) operator+(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, SCALAR_TYPE const &rhs) { \
				return plus(lhs, rhs); \
			} \
			\
			template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
			SPECIFIER decltype(auto) operator+(SCALAR_TYPE const &lhs, detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
				return plus(lhs, rhs); \
			} \
			\
			SPECIFIER decltype(auto) operator+(detail::empty_expression_tree const &lhs, SCALAR_TYPE const &rhs) { \
				return plus(lhs, rhs); \
			} \
			\
			SPECIFIER decltype(auto) operator+(SCALAR_TYPE const &lhs, detail::empty_expression_tree const &rhs) { \
				return plus(lhs, rhs); \
			} \
			\
			template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
			SPECIFIER decltype(auto) operator-(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, SCALAR_TYPE const &rhs) { \
				return minus(lhs, rhs); \
			} \
			\
			template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
			SPECIFIER decltype(auto) operator-(SCALAR_TYPE const &lhs, detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
				return minus(lhs, rhs); \
			} \
			\
			SPECIFIER decltype(auto) operator-(detail::empty_expression_tree const &lhs, SCALAR_TYPE const &rhs) { \
				return minus(lhs, rhs); \
			} \
			\
			SPECIFIER decltype(auto) operator-(SCALAR_TYPE const &lhs, detail::empty_expression_tree const &rhs) { \
				return minus(lhs, rhs); \
			} \
			\
			template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
			SPECIFIER decltype(auto) operator*(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, SCALAR_TYPE const &rhs) { \
				return gp(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
			SPECIFIER decltype(auto) operator*(SCALAR_TYPE const &lhs, detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
				return gp(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			SPECIFIER decltype(auto) operator*(detail::empty_expression_tree const &lhs, SCALAR_TYPE const &rhs) { \
				return gp(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			SPECIFIER decltype(auto) operator*(SCALAR_TYPE const &lhs, detail::empty_expression_tree const &rhs) { \
				return gp(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
			SPECIFIER decltype(auto) operator/(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, SCALAR_TYPE const &rhs) { \
				return igp(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
			SPECIFIER decltype(auto) operator/(SCALAR_TYPE const &lhs, detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
				return igp(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			SPECIFIER decltype(auto) operator/(detail::empty_expression_tree const &lhs, SCALAR_TYPE const &rhs) { \
				return igp(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
			SPECIFIER decltype(auto) operator^(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &lhs, SCALAR_TYPE const &rhs) { \
				return op(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			template<class ElementType, class LeftSubtreeType, class RightSubtreeType> \
			SPECIFIER decltype(auto) operator^(SCALAR_TYPE const &lhs, detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &rhs) { \
				return op(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			SPECIFIER decltype(auto) operator^(detail::empty_expression_tree const &lhs, SCALAR_TYPE const &rhs) { \
				return op(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			SPECIFIER decltype(auto) operator^(SCALAR_TYPE const &lhs, detail::empty_expression_tree const &rhs) { \
				return op(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
		} \
		\
	}

#endif // __GA_CLIFFORD_MACRO_FOR_OPERATORS_OVERLOAD_HPP__
