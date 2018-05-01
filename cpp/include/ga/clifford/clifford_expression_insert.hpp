#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_INSERT_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_INSERT_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ExpressionType, class ElementType>
			struct _insert;

			template<class ElementType>
			struct _insert<empty_clifford_expression, ElementType> {
				constexpr static decltype(auto) bind(empty_clifford_expression const &, ElementType const &element) {
					return make_simple_clifford_expression(element);
				}
			};

			template<class CoefficientType, class BasisBladeType>
			struct _insert_non_zero {
				template<class ExpressionType, class ElementType>
				constexpr static decltype(auto) bind(ExpressionType const &root, ElementType const &element) {
					return _insert<ExpressionType, ElementType>::bind(root, element);
				}
			};

			template<class BasisBladeType>
			struct _insert_non_zero<constant<0>, BasisBladeType> {
				template<class ExpressionType, class ElementType>
				constexpr static ExpressionType bind(ExpressionType const &root, ElementType const &) {
					return root;
				}
			};

			template<class CoefficientType>
			struct _insert_non_zero<CoefficientType, dbasis_blade<default_bitset_t(0)> > {
				template<class ExpressionType, class ElementType>
				constexpr static ExpressionType bind(ExpressionType const &root, ElementType const &) {
					return root;
				}
			};

			template<>
			struct _insert_non_zero<constant<0>, dbasis_blade<default_bitset_t(0)> > {
				template<class ExpressionType, class ElementType>
				constexpr static ExpressionType bind(ExpressionType const &root, ElementType const &) {
					return root;
				}
			};

			template<class ExpressionType, class ElementType>
			constexpr decltype(auto) insert(ExpressionType const &root, ElementType const &element) {
				return _insert_non_zero<typename ElementType::coefficient_type, typename ElementType::basis_blade_type>::bind(root, element);
			}

		}

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_INSERT_HPP__
