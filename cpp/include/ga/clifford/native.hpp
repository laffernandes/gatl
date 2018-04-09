#ifndef __GA_CLIFFORD_NATIVE_HPP__
#define __GA_CLIFFORD_NATIVE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class Type>
			struct may_cast_to_native {
				constexpr static bool value = false;
			};

			template<class CoefficientType>
			struct may_cast_to_native<expression_tree<component<CoefficientType, cbasis_blade<0> >, empty_clifford_expression, empty_clifford_expression> > {
				constexpr static bool value = true;
			};

			template<class CoefficientType>
			struct may_cast_to_native<expression_tree<component<CoefficientType, dbasis_blade<default_bitset_t(1)> >, empty_clifford_expression, empty_clifford_expression> > {
				constexpr static bool value = true;
			};

			template<class CoefficientType>
			struct may_cast_to_native<expression_tree<components<CoefficientType, default_bitset_t(1)>, empty_clifford_expression, empty_clifford_expression> > {
				constexpr static bool value = true;
			};

			template<>
			struct may_cast_to_native<empty_clifford_expression> {
				constexpr static bool value = true;
			};

			template<class ExpressionType>
			struct may_cast_to_native<clifford_expression<ExpressionType> > : may_cast_to_native<ExpressionType> {
			};

		}

		template<class Type>
		constexpr Type native(Type const &arg) {
			return arg;
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_tree<detail::component<CoefficientType, detail::cbasis_blade<0> >, detail::empty_clifford_expression, detail::empty_clifford_expression> const &arg) {
			return native(arg.element().coefficient());
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_tree<detail::component<CoefficientType, detail::dbasis_blade<default_bitset_t(1)> >, detail::empty_clifford_expression, detail::empty_clifford_expression> const &arg) {
			return native(arg.element().coefficient());
		}

		template<class CoefficientType>
		constexpr decltype(auto) native(detail::expression_tree<detail::components<CoefficientType, default_bitset_t(1)>, detail::empty_clifford_expression, detail::empty_clifford_expression> const &arg) {
			return native(arg.element().begin()->second);
		}

		constexpr constant<0> native(detail::empty_clifford_expression const &) {
			return constant<0>();
		}

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		constexpr decltype(auto) native(detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> const &) = delete;

		template<class ExpressionType>
		constexpr decltype(auto) native(clifford_expression<ExpressionType> const &arg) {
			return native(arg());
		}

	}

}

#endif // __GA_CLIFFORD_NATIVE_HPP__
