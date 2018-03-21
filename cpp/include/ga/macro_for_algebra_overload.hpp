#ifndef __GA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
#define __GA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__

#define GA_SIGNED_ALGEBRA_OVERLOAD(NAMESPACE_MNEMONIC, P, Q) \
	namespace NAMESPACE_MNEMONIC { \
		\
		static ga::signed_metric_space<P, Q> const space; \
		\
		using ga::grade_t; \
		using ga::index_t; \
		using ga::ndims_t; \
		\
		using ga::abs; \
		using ga::exp; \
		using ga::sqrt; \
		using ga::cos; \
		using ga::sin; \
		using ga::tan; \
		using ga::cosh; \
		using ga::sinh; \
		using ga::tanh; \
		\
		using ga::uminus; \
		using ga::uplus; \
		\
		using ga::minus; \
		using ga::plus; \
		\
		using ga::conjugation; \
		using ga::involution; \
		using ga::reversion; \
		\
		using ga::take_grade; \
		\
		using ga::c; \
		using ga::e; \
		using ga::native; \
		\
		constexpr decltype(auto) pseudoscalar() { \
			return ga::pseudoscalar(space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) gp(LeftType const &lhs, RightType const &rhs) { \
			return ga::gp(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) lcont(LeftType const &lhs, RightType const &rhs) { \
			return ga::lcont(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) op(LeftType const &lhs, RightType const &rhs) { \
			return ga::op(lhs, rhs, space); \
		} \
		\
		template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType, typename std::enable_if<!ga::detail::may_cast_to_native<ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> >::value && !ga::detail::may_cast_to_native<ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> >::value, int>::type = 0> \
		constexpr decltype(auto) operator^(ga::detail::expression<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, ga::detail::expression<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) { \
			return ga::op(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) rcont(LeftType const &lhs, RightType const &rhs) { \
			return ga::rcont(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) scp(LeftType const &lhs, RightType const &rhs) { \
			return ga::scp(lhs, rhs, space); \
		} \
		\
		template<class LeftType, class RightType> \
		constexpr decltype(auto) igp(LeftType const &lhs, RightType const &rhs) { \
			return ga::igp(lhs, rhs, space); \
		} \
		\
		template<class ElementType, class LeftSubtreeType, class RightSubtreeType, typename std::enable_if<!ga::detail::may_cast_to_native<ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> >::value, int>::type = 0> \
		constexpr decltype(auto) exp(ga::detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) { \
			return ga::exp(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) inv(Type const &arg) { \
			return ga::inv(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) rnorm_sqr(Type const &arg) { \
			return ga::rnorm_sqr(arg, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) rnorm(Type const &arg) { \
			return ga::rnorm(arg, space); \
		} \
		\
		template<class Type, class PseudoscalarType> \
		constexpr decltype(auto) dual(Type const &arg, PseudoscalarType const &pseudoscalar) { \
			return ga::dual(arg, pseudoscalar, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) dual(Type const &arg) { \
			return ga::dual(arg, ga::pseudoscalar(space), space); \
		} \
		\
		template<class Type, class PseudoscalarType> \
		constexpr decltype(auto) undual(Type const &arg, PseudoscalarType const &pseudoscalar) { \
			return ga::undual(arg, pseudoscalar, space); \
		} \
		\
		template<class Type> \
		constexpr decltype(auto) undual(Type const &arg) { \
			return ga::undual(arg, ga::pseudoscalar(space), space); \
		} \
		\
	}

#endif // __GA_MACRO_FOR_ALGEBRA_OVERLOAD_HPP__
