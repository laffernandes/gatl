#ifndef __GA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define GA_SIGNED_ALGEBRA_OVERLOAD(NAMESPACE_MNEMONIC, P, Q) \
	namespace NAMESPACE_MNEMONIC { \
		\
		static ga::clifford::signed_metric_space<P, Q> const space; \
		\
		using ga::id_t; \
		\
		using ga::grade_t; \
		using ga::index_t; \
		using ga::ndims_t; \
		\
		using ga::clifford::operator+; \
		using ga::clifford::operator-; \
		using ga::clifford::operator*; \
		using ga::clifford::operator/; \
		using ga::clifford::operator^; \
		using ga::clifford::operator<<; \
		\
		using ga::clifford::abs; \
		using ga::clifford::cbrt; \
		using ga::clifford::exp; \
		using ga::clifford::sqrt; \
		using ga::clifford::cos; \
		using ga::clifford::sin; \
		using ga::clifford::tan; \
		using ga::clifford::cosh; \
		using ga::clifford::sinh; \
		using ga::clifford::tanh; \
		\
		using ga::clifford::conjugation; \
		using ga::clifford::involution; \
		using ga::clifford::reversion; \
		\
		using ga::clifford::grade; \
		using ga::clifford::take_grade; \
		\
		using ga::lazy::c; \
		using ga::lazy::val; \
		using ga::lazy::var; \
		\
		using ga::clifford::e; \
		using ga::clifford::native; \
		\
		using ga::clifford::eval; \
		\
		constexpr decltype(auto) pseudoscalar() { \
			return ga::clifford::pseudoscalar(space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) gp(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::gp(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) lcont(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::lcont(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) op(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::op(lhs, rhs, space); \
		} \
		\
		template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<!(ga::clifford::detail::may_cast_to_native<LeftExpressionType>::value || ga::clifford::detail::may_cast_to_native<RightExpressionType>::value), int>::type = 0> \
		constexpr decltype(auto) operator^(ga::clifford::clifford_expression<LeftExpressionType> const &lhs, ga::clifford::clifford_expression<RightExpressionType> const &rhs) { \
			return ga::clifford::op(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) rcont(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::rcont(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) scp(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::scp(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) igp(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::igp(lhs, rhs, space); \
		} \
		\
		template<class ExpressionType, typename std::enable_if<!ga::clifford::detail::may_cast_to_native<ExpressionType>::value, int>::type = 0> \
		constexpr decltype(auto) exp(ga::clifford::clifford_expression<ExpressionType> const &arg) { \
			return ga::clifford::exp(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) inv(Type const &arg) { \
			return ga::clifford::inv(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) rnorm_sqr(Type const &arg) { \
			return ga::clifford::rnorm_sqr(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) rnorm(Type const &arg) { \
			return ga::clifford::rnorm(arg, space); \
		} \
		\
		template<class Type, class PseudoscalarType> \
		constexpr decltype(auto) dual(Type const &arg, PseudoscalarType const &pseudoscalar) { \
			return ga::clifford::dual(arg, pseudoscalar, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) dual(Type const &arg) { \
			return ga::clifford::dual(arg, ga::clifford::pseudoscalar(space), space); \
		} \
		\
		template<class Type, class PseudoscalarType> \
		constexpr decltype(auto) undual(Type const &arg, PseudoscalarType const &pseudoscalar) { \
			return ga::clifford::undual(arg, pseudoscalar, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) undual(Type const &arg) { \
			return ga::clifford::undual(arg, ga::clifford::pseudoscalar(space), space); \
		} \
		\
	}

#define GA_CONFORMAL_ALGEBRA_OVERLOAD(NAMESPACE_MNEMONIC, N) \
	namespace NAMESPACE_MNEMONIC { \
		\
		static ga::clifford::conformal_metric_space<N> const space; \
		\
		using ga::id_t; \
		\
		using ga::grade_t; \
		using ga::index_t; \
		using ga::ndims_t; \
		\
		using ga::clifford::operator+; \
		using ga::clifford::operator-; \
		using ga::clifford::operator*; \
		using ga::clifford::operator/; \
		using ga::clifford::operator^; \
		using ga::clifford::operator<<; \
		\
		using ga::clifford::abs; \
		using ga::clifford::cbrt; \
		using ga::clifford::exp; \
		using ga::clifford::sqrt; \
		using ga::clifford::cos; \
		using ga::clifford::sin; \
		using ga::clifford::tan; \
		using ga::clifford::cosh; \
		using ga::clifford::sinh; \
		using ga::clifford::tanh; \
		\
		using ga::clifford::conjugation; \
		using ga::clifford::involution; \
		using ga::clifford::reversion; \
		\
		using ga::clifford::grade; \
		using ga::clifford::take_grade; \
		\
		using ga::lazy::c; \
		using ga::lazy::val; \
		using ga::lazy::var; \
		\
		using ga::clifford::e; \
		using ga::clifford::native; \
		\
		using ga::clifford::eval; \
		\
		constexpr decltype(auto) pseudoscalar() { \
			return ga::clifford::pseudoscalar(space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) gp(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::gp(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) lcont(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::lcont(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) op(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::op(lhs, rhs, space); \
		} \
		\
		template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<!(ga::clifford::detail::may_cast_to_native<LeftExpressionType>::value || ga::clifford::detail::may_cast_to_native<RightExpressionType>::value), int>::type = 0> \
		constexpr decltype(auto) operator^(ga::clifford::clifford_expression<LeftExpressionType> const &lhs, ga::clifford::clifford_expression<RightExpressionType> const &rhs) { \
			return ga::clifford::op(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) rcont(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::rcont(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) scp(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::scp(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) igp(LeftType const &lhs, RightType const &rhs) { \
			return ga::clifford::igp(lhs, rhs, space); \
		} \
		\
		template<class ExpressionType, typename std::enable_if<!ga::clifford::detail::may_cast_to_native<ExpressionType>::value, int>::type = 0> \
		constexpr decltype(auto) exp(ga::clifford::clifford_expression<ExpressionType> const &arg) { \
			return ga::clifford::exp(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) inv(Type const &arg) { \
			return ga::clifford::inv(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) rnorm_sqr(Type const &arg) { \
			return ga::clifford::rnorm_sqr(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) rnorm(Type const &arg) { \
			return ga::clifford::rnorm(arg, space); \
		} \
		\
		template<class Type, class PseudoscalarType> \
		constexpr decltype(auto) dual(Type const &arg, PseudoscalarType const &pseudoscalar) { \
			return ga::clifford::dual(arg, pseudoscalar, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) dual(Type const &arg) { \
			return ga::clifford::dual(arg, ga::clifford::pseudoscalar(space), space); \
		} \
		\
		template<class Type, class PseudoscalarType> \
		constexpr decltype(auto) undual(Type const &arg, PseudoscalarType const &pseudoscalar) { \
			return ga::clifford::undual(arg, pseudoscalar, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) undual(Type const &arg) { \
			return ga::clifford::undual(arg, ga::clifford::pseudoscalar(space), space); \
		} \
		\
	}

#endif // __GA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
