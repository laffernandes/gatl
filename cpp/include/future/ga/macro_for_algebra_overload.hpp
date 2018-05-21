#ifndef __FUTURE_GA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __FUTURE_GA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define GA_SIGNED_ALGEBRA_OVERLOAD(NAMESPACE_MNEMONIC, P, Q) \
	namespace NAMESPACE_MNEMONIC { \
		\
		using namespace future::ga; \
		\
		static signed_metric_space<P, Q> const space; \
		\
		constexpr decltype(auto) pseudoscalar() { \
			return pseudoscalar(space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) gp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return gp(lhs, rhs, space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) lcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return lcont(lhs, rhs, space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) op(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return op(lhs, rhs, space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) operator^(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return op(lhs, rhs, space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) rcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return rcont(lhs, rhs, space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) scp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return scp(lhs, rhs, space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) igp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return igp(lhs, rhs, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) inv(Type const &arg) { \
			return inv(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) rnorm_sqr(Type const &arg) { \
			return rnorm_sqr(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) rnorm(Type const &arg) { \
			return rnorm(arg, space); \
		} \
		\
		template<class Type, class PseudoscalarType> \
		constexpr decltype(auto) dual(Type const &arg, PseudoscalarType const &pseudoscalar) { \
			return dual(arg, pseudoscalar, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) dual(Type const &arg) { \
			return dual(arg, pseudoscalar(space), space); \
		} \
		\
		template<class Type, class PseudoscalarType> \
		constexpr decltype(auto) undual(Type const &arg, PseudoscalarType const &pseudoscalar) { \
			return undual(arg, pseudoscalar, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) undual(Type const &arg) { \
			return undual(arg, pseudoscalar(space), space); \
		} \
		\
	}

//TODO Rever
/*
		\
		template<class... ElementTypes, typename std::enable_if<!detail::may_cast_to_native<clifford_expression<ElementTypes...> >::value, int>::type = 0> \
		constexpr decltype(auto) exp(clifford_expression<ElementTypes...> const &arg) { \
			return exp(arg, space); \
		} \
*/

#define GA_CONFORMAL_ALGEBRA_OVERLOAD(NAMESPACE_MNEMONIC, N) \
	namespace NAMESPACE_MNEMONIC { \
		\
		using namespace future::ga; \
		\
		static conformal_metric_space<N> const space; \
		\
		constexpr decltype(auto) pseudoscalar() { \
			return pseudoscalar(space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) gp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return gp(lhs, rhs, space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) lcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return lcont(lhs, rhs, space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) op(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return op(lhs, rhs, space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) rcont(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return rcont(lhs, rhs, space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) scp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return scp(lhs, rhs, space); \
		} \
		\
		template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!(detail::is_scalar_expression_v<LeftExpression> || detail::is_scalar_expression_v<RightExpression>)> > \
		constexpr decltype(auto) igp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) { \
			return igp(lhs, rhs, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) inv(Type const &arg) { \
			return inv(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) rnorm_sqr(Type const &arg) { \
			return rnorm_sqr(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) rnorm(Type const &arg) { \
			return rnorm(arg, space); \
		} \
		\
		\
		template<class Type, class PseudoscalarType> \
		constexpr decltype(auto) dual(Type const &arg, PseudoscalarType const &pseudoscalar) { \
			return dual(arg, pseudoscalar, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) dual(Type const &arg) { \
			return dual(arg, pseudoscalar(space), space); \
		} \
		\
		template<class Type, class PseudoscalarType> \
		constexpr decltype(auto) undual(Type const &arg, PseudoscalarType const &pseudoscalar) { \
			return undual(arg, pseudoscalar, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) undual(Type const &arg) { \
			return undual(arg, pseudoscalar(space), space); \
		} \
		\
	}

//TODO Rever
/*
		template<class... ElementTypes, typename std::enable_if<!detail::may_cast_to_native<clifford_expression<ElementTypes...> >::value, int>::type = 0> \
		constexpr decltype(auto) exp(clifford_expression<ElementTypes...> const &arg) { \
			return exp(arg, space); \
		} \
*/

#endif // __FUTURE_GA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
