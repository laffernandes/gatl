#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_INSERT_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_INSERT_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ExpressionType, class NewElementType>
			struct _insert;

			template<class CoefficientType, class BasisBladeType>
			struct _insert_non_zero {
				template<class ExpressionType, class NewElementType>
				constexpr static decltype(auto) bind(ExpressionType const &expression, NewElementType const &element) {
					return _insert<ExpressionType, NewElementType>::bind(expression, element);
				}
			};

			template<class BasisBladeType>
			struct _insert_non_zero<constant<0>, BasisBladeType> {
				template<class ExpressionType, class NewElementType>
				constexpr static ExpressionType bind(ExpressionType const &expression, NewElementType const &) {
					return expression;
				}
			};

			template<class CoefficientType>
			struct _insert_non_zero<CoefficientType, dbasis_blade<default_bitset_t(0)> > {
				template<class ExpressionType, class NewElementType>
				constexpr static ExpressionType bind(ExpressionType const &expression, NewElementType const &) {
					return expression;
				}
			};

			template<>
			struct _insert_non_zero<constant<0>, dbasis_blade<default_bitset_t(0)> > {
				template<class ExpressionType, class NewElementType>
				constexpr static ExpressionType bind(ExpressionType const &expression, NewElementType const &) {
					return expression;
				}
			};

			struct _insert_element_next {
				template<class ElementType, class... OtherElementTypes, class NewElementType>
				constexpr static decltype(auto) bind(clifford_expression<ElementType, OtherElementTypes...> const &expression, NewElementType const &element) {
					return clifford_expression<ElementType, NewElementType, OtherElementTypes...>(expression.element(), insert(expression.next(), element));
				}
			};

			struct _insert_element_here {
				template<class ElementType, class... OtherElementTypes, class NewElementType>
				constexpr static decltype(auto) bind(clifford_expression<ElementType, OtherElementTypes...> const &expression, NewElementType const &element) {
					return clifford_expression<NewElementType, ElementType, OtherElementTypes...>(element, expression);
				}
			};

			template<class ElementType, class... OtherElementTypes, class NewElementType>
			struct _insert<clifford_expression<ElementType, OtherElementTypes...>, NewElementType> : std::conditional<
				lt<ElementType, NewElementType>::value,
				_insert_element_next,
				_insert_element_here
			>::type {
			};

			template<class NewElementType>
			struct _insert<clifford_expression<>, NewElementType> {
				constexpr static decltype(auto) bind(clifford_expression<> const &, NewElementType const &element) {
					return make_simple_clifford_expression(element);
				}
			};

			template<class ExpressionType, class NewElementType>
			constexpr decltype(auto) insert(ExpressionType const &expression, NewElementType const &element) {
				return _insert_non_zero<typename NewElementType::coefficient_type, typename NewElementType::basis_blade_type>::bind(expression, element);
			}

		}

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_INSERT_HPP__
