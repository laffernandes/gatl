#ifndef __GA_CLIFFORD_MACRO_FOR_OPERATORS_OVERLOAD_HPP__
#define __GA_CLIFFORD_MACRO_FOR_OPERATORS_OVERLOAD_HPP__

#define GA_OVERLOAD_OPERATORS_FOR_CUSTOM_SCALAR_TYPE(SCALAR_TYPE, SPECIFIER) \
	namespace ga { \
		\
		namespace clifford { \
			\
			template<class LeftExpressionType> \
			SPECIFIER decltype(auto) operator+(clifford_expression<LeftExpressionType> const &lhs, SCALAR_TYPE const &rhs) { \
				return detail::binary_plus(detail::obegin(lhs()), detail::obegin(value<SCALAR_TYPE>(rhs))); \
			} \
			\
			template<class RightExpressionType> \
			SPECIFIER decltype(auto) operator+(SCALAR_TYPE const &lhs, clifford_expression<RightExpressionType> const &rhs) { \
				return detail::binary_plus(detail::obegin(value<SCALAR_TYPE>(lhs)), detail::obegin(rhs())); \
			} \
			\
			template<class LeftExpressionType> \
			SPECIFIER decltype(auto) operator-(clifford_expression<LeftExpressionType> const &lhs, SCALAR_TYPE const &rhs) { \
				return detail::binary_minus(detail::obegin(lhs()), detail::obegin(value<SCALAR_TYPE>(rhs))); \
			} \
			\
			template<class RightExpressionType> \
			SPECIFIER decltype(auto) operator-(SCALAR_TYPE const &lhs, clifford_expression<RightExpressionType> const &rhs) { \
				return detail::binary_minus(detail::obegin(value<SCALAR_TYPE>(lhs)), detail::obegin(rhs())); \
			} \
			\
			template<class LeftExpressionType> \
			SPECIFIER decltype(auto) operator*(clifford_expression<LeftExpressionType> const &lhs, SCALAR_TYPE const &rhs) { \
				return gp(lhs(), value<SCALAR_TYPE>(rhs), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			template<class RightExpressionType> \
			SPECIFIER decltype(auto) operator*(SCALAR_TYPE const &lhs, clifford_expression<RightExpressionType> const &rhs) { \
				return gp(value<SCALAR_TYPE>(lhs), rhs(), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			template<class LeftExpressionType> \
			SPECIFIER decltype(auto) operator/(clifford_expression<LeftExpressionType> const &lhs, SCALAR_TYPE const &rhs) { \
				return igp(lhs(), value<SCALAR_TYPE>(rhs), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			template<class RightExpressionType> \
			SPECIFIER decltype(auto) operator/(SCALAR_TYPE const &lhs, clifford_expression<RightExpressionType> const &rhs) { \
				return igp(value<SCALAR_TYPE>(lhs), rhs(), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			template<class LeftExpressionType> \
			SPECIFIER decltype(auto) operator^(clifford_expression<LeftExpressionType> const &lhs, SCALAR_TYPE const &rhs) { \
				return op(lhs(), value<SCALAR_TYPE>(rhs), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
			template<class RightExpressionType> \
			SPECIFIER decltype(auto) operator^(SCALAR_TYPE const &lhs, clifford_expression<RightExpressionType> const &rhs) { \
				return op(value<SCALAR_TYPE>(lhs), rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>()); \
			} \
			\
		} \
		\
	}

#endif // __GA_CLIFFORD_MACRO_FOR_OPERATORS_OVERLOAD_HPP__
