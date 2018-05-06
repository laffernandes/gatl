#ifndef __GA_CLIFFORD_EXPRESSION_TREE_NATIVE_HPP__
#define __GA_CLIFFORD_EXPRESSION_TREE_NATIVE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class CoefficientType>
			struct may_cast_to_native<expression_tree<component<CoefficientType, cbasis_blade<0> >, empty_expression_tree, empty_expression_tree> > {
				constexpr static bool value = true;
			};

			template<class CoefficientType>
			struct may_cast_to_native<expression_tree<component<CoefficientType, dbasis_blade<default_bitset_t(1)> >, empty_expression_tree, empty_expression_tree> > {
				constexpr static bool value = true;
			};

			template<class CoefficientType>
			struct may_cast_to_native<expression_tree<components<CoefficientType, default_bitset_t(1)>, empty_expression_tree, empty_expression_tree> > {
				constexpr static bool value = true;
			};

			template<>
			struct may_cast_to_native<empty_expression_tree> {
				constexpr static bool value = true;
			};

		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_tree<detail::component<CoefficientType, detail::cbasis_blade<0> >, detail::empty_expression_tree, detail::empty_expression_tree> const &arg) {
			return native(arg.element().coefficient());
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_tree<detail::component<CoefficientType, detail::dbasis_blade<default_bitset_t(1)> >, detail::empty_expression_tree, detail::empty_expression_tree> const &arg) {
			return native(arg.element().coefficient());
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_tree<detail::components<CoefficientType, default_bitset_t(1)>, detail::empty_expression_tree, detail::empty_expression_tree> const &arg) {
			return native(arg.element().begin()->second);
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) native(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &) = delete;

		constexpr decltype(auto) native(detail::empty_expression_tree const &) {
			return constant<0>();
		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_TREE_NATIVE_HPP__
