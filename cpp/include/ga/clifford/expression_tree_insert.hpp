#ifndef __GA_CLIFFORD_EXPRESSION_TREE_INSERT_HPP__
#define __GA_CLIFFORD_EXPRESSION_TREE_INSERT_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class ExpressionType>
			struct _height;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct _height<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > {
			private:

				constexpr static int height_left = _height<LeftSubtreeType>::value;
				constexpr static int height_right = _height<RightSubtreeType>::value;

			public:

				constexpr static int value = 1 + ((height_left >= height_right) ? height_left : height_right);
			};

			template<>
			struct _height<empty_clifford_expression> {
				constexpr static int value = -1;
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) rotate_left(ElementType const &element, LeftSubtreeType const &left, RightSubtreeType const &right) {
				return make_expression_tree(right.element(), make_expression_tree(element, left, right.left()), right.right());
			}

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			constexpr decltype(auto) rotate_right(ElementType const &element, LeftSubtreeType const &left, RightSubtreeType const &right) {
				return make_expression_tree(left.element(), left.left(), make_expression_tree(element, left.right(), right));
			}

			template<class ElementType>
			struct _insert_element_left {
			private:

				template<bool Rotate>
				struct _rotate_left_too;

				template<>
				struct _rotate_left_too<true> {
					template<class ExpressionType>
					constexpr static decltype(auto) bind(ExpressionType const &aux) {
						return rotate_right(aux.element(), rotate_left(aux.left().element(), aux.left().left(), aux.left().right()), aux.right());
					}
				};

				template<>
				struct _rotate_left_too<false> {
					template<class ExpressionType>
					constexpr static decltype(auto) bind(ExpressionType const &aux) {
						return rotate_right(aux.element(), aux.left(), aux.right());
					}
				};

				template<bool Rotate>
				struct _balance;

				template<>
				struct _balance<true> {
					template<class AuxElementType, class AuxLeftSubtreeType, class AuxRightSubtreeType>
					constexpr static decltype(auto) bind(expression_tree<AuxElementType, AuxLeftSubtreeType, AuxRightSubtreeType> const &aux) {
						return _rotate_left_too<ge<ElementType, typename AuxLeftSubtreeType::element_type>::value>::bind(aux);
					}
				};

				template<>
				struct _balance<false> {
					template<class ExpressionType>
					constexpr static ExpressionType bind(ExpressionType const &aux) {
						return aux;
					}
				};

				template<class AuxElementType, class AuxLeftSubtreeType, class AuxRightSubtreeType>
				constexpr static decltype(auto) balance(expression_tree<AuxElementType, AuxLeftSubtreeType, AuxRightSubtreeType> const &aux) {
					return _balance<(_height<AuxLeftSubtreeType>::value - _height<AuxRightSubtreeType>::value) == 2>::bind(aux);
				}

			public:

				template<class ExpressionType>
				constexpr static decltype(auto) bind(ExpressionType const &root, ElementType const &element) {
					return balance(make_expression_tree(root.element(), insert(root.left(), element), root.right()));
				}
			};

			template<class ElementType>
			struct _insert_element_right {
			private:

				template<bool Rotate>
				struct _rotate_right_too;

				template<>
				struct _rotate_right_too<true> {
					template<class ExpressionType>
					constexpr static decltype(auto) bind(ExpressionType const &aux) {
						return rotate_left(aux.element(), aux.left(), rotate_right(aux.right()));
					}
				};

				template<>
				struct _rotate_right_too<false> {
					template<class ExpressionType>
					constexpr static decltype(auto) bind(ExpressionType const &aux) {
						return rotate_left(aux.element(), aux.left(), aux.right());
					}
				};

				template<bool Rotate>
				struct _balance;

				template<>
				struct _balance<true> {
					template<class AuxElementType, class AuxLeftSubtreeType, class AuxRightSubtreeType>
					constexpr static decltype(auto) bind(expression_tree<AuxElementType, AuxLeftSubtreeType, AuxRightSubtreeType> const &aux) {
						return _rotate_right_too<le<ElementType, typename AuxRightSubtreeType::element_type>::value>::bind(aux);
					}
				};

				template<>
				struct _balance<false> {
					template<class ExpressionType>
					constexpr static ExpressionType bind(ExpressionType const &aux) {
						return aux;
					}
				};

				template<class AuxElementType, class AuxLeftSubtreeType, class AuxRightSubtreeType>
				constexpr static decltype(auto) balance(expression_tree<AuxElementType, AuxLeftSubtreeType, AuxRightSubtreeType> const &aux) {
					return _balance<(_height<AuxLeftSubtreeType>::value - _height<AuxRightSubtreeType>::value) == -2>::bind(aux);
				}

			public:

				template<class ExpressionType>
				constexpr static decltype(auto) bind(ExpressionType const &root, ElementType const &element) {
					return balance(make_expression_tree(root.element(), root.left(), insert(root.right(), element)));
				}
			};

			template<class ExpressionType, class ElementType>
			struct _insert;

			template<class RootElementType, class LeftSubtreeType, class RightSubtreeType, class ElementType>
			struct _insert<expression_tree<RootElementType, LeftSubtreeType, RightSubtreeType>, ElementType> : std::conditional<
				lt<ElementType, RootElementType>::value,
				_insert_element_left<ElementType>,
				typename std::conditional<
					lt<RootElementType, ElementType>::value,
					_insert_element_right<ElementType>,
					std::nullptr_t // It should not be called.
				>::type
			>::type {
			};

			template<class ElementType>
			struct _insert<empty_clifford_expression, ElementType> {
				constexpr static decltype(auto) bind(empty_clifford_expression const &, ElementType const &element) {
					return make_expression_tree(element, empty_clifford_expression(), empty_clifford_expression());
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

#endif // __GA_CLIFFORD_EXPRESSION_TREE_INSERT_HPP__
