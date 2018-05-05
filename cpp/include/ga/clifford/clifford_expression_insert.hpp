#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_INSERT_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_INSERT_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ExpressionType, class NewElementType>
			struct _insert;

			template<class NewElementType>
			struct _insert<empty_clifford_expression, NewElementType> {
				constexpr static decltype(auto) bind(empty_clifford_expression const &, NewElementType const &element) {
					return make_simple_clifford_expression(element);
				}
			};

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

			template<class ExpressionType, class NewElementType>
			constexpr decltype(auto) insert(ExpressionType const &expression, NewElementType const &element) {
				return _insert_non_zero<typename NewElementType::coefficient_type, typename NewElementType::basis_blade_type>::bind(expression, element);
			}

		}

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_INSERT_HPP__
