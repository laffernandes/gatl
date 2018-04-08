#ifndef __GA_CLIFFORD_SCALAR_EXPRESSION_MATH_HPP__
#define __GA_CLIFFORD_SCALAR_EXPRESSION_MATH_HPP__

namespace ga {

	namespace clifford {

		using lazy::abs;

		constexpr detail::empty_expression_tree abs(detail::empty_expression_tree const &) {
			return detail::empty_expression_tree();
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) abs(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
			return abs(native(arg));
		}

		using lazy::cbrt;

		constexpr detail::empty_expression_tree cbrt(detail::empty_expression_tree const &) {
			return detail::empty_expression_tree();
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) cbrt(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
			return cbrt(native(arg));
		}

		using lazy::exp;

		template<class MetricSpaceType>
		constexpr decltype(auto) exp(detail::empty_expression_tree const &) {
			return detail::make_expression(detail::make_component(constant<1>(), detail::cbasis_blade<0>()), detail::empty_expression_tree(), detail::empty_expression_tree());
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType, typename std::enable_if<detail::may_cast_to_native<detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> >::value, int>::type = 0>
		constexpr decltype(auto) exp(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
			return exp(native(arg));
		}

		using lazy::sqrt;

		constexpr detail::empty_expression_tree sqrt(detail::empty_expression_tree const &) {
			return detail::empty_expression_tree();
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) sqrt(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
			return sqrt(native(arg));
		}

		using lazy::cos;

		constexpr decltype(auto) cos(detail::empty_expression_tree const &) {
			return detail::make_expression(detail::make_component(constant<1>(), detail::cbasis_blade<0>()), detail::empty_expression_tree(), detail::empty_expression_tree());
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) cos(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
			return cos(native(arg));
		}

		using lazy::sin;

		constexpr decltype(auto) sin(detail::empty_expression_tree const &) {
			return detail::empty_expression_tree();
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) sin(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
			return sin(native(arg));
		}

		using lazy::tan;

		constexpr detail::empty_expression_tree tan(detail::empty_expression_tree const &) {
			return detail::empty_expression_tree();
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) tan(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
			return tan(native(arg));
		}

		using lazy::cosh;

		constexpr decltype(auto) cosh(detail::empty_expression_tree const &) {
			return detail::make_expression(detail::make_component(constant<1>(), detail::cbasis_blade<0>()), detail::empty_expression_tree(), detail::empty_expression_tree());
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) cosh(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
			return cosh(native(arg));
		}

		using lazy::sinh;

		constexpr decltype(auto) sinh(detail::empty_expression_tree const &) {
			return detail::empty_expression_tree();
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) sinh(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
			return sinh(native(arg));
		}

		using lazy::tanh;

		constexpr decltype(auto) tanh(detail::empty_expression_tree const &) {
			return detail::empty_expression_tree();
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) tanh(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
			return tanh(native(arg));
		}

	}

}

#endif // __GA_CLIFFORD_SCALAR_EXPRESSION_MATH_HPP__
