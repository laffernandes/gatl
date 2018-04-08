#ifndef __GA_CLIFFORD_EXPRESSION_TREE_COEFFICIENT_TYPE_HPP__
#define __GA_CLIFFORD_EXPRESSION_TREE_COEFFICIENT_TYPE_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class Type>
			struct common_coefficient_type;

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct common_coefficient_type<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > : std::common_type<
				typename ElementType::coefficient_type,
				typename common_coefficient_type<LeftSubtreeType>::type,
				typename common_coefficient_type<RightSubtreeType>::type
			> {
			};

			template<class ElementType, class RightSubtreeType>
			struct common_coefficient_type<expression_tree<ElementType, empty_expression_tree, RightSubtreeType> > : std::common_type<
				typename ElementType::coefficient_type,
				typename common_coefficient_type<RightSubtreeType>::type
			> {
			};

			template<class ElementType, class LeftSubtreeType>
			struct common_coefficient_type<expression_tree<ElementType, LeftSubtreeType, empty_expression_tree> > : std::common_type<
				typename ElementType::coefficient_type,
				typename common_coefficient_type<LeftSubtreeType>::type
			> {
			};

			template<class ElementType>
			struct common_coefficient_type<expression_tree<ElementType, empty_expression_tree, empty_expression_tree> > {
				typedef typename ElementType::coefficient_type type;
			};

			template<>
			struct common_coefficient_type<empty_expression_tree> {
				typedef constant<0> type;
			};

			template<class Type>
			struct native_coefficient_type {
				typedef Type type;
			};

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct native_coefficient_type<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > : native_coefficient_type<typename common_coefficient_type<expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> >::type> {
			};

			template<>
			struct native_coefficient_type<empty_expression_tree> : native_coefficient_type<typename common_coefficient_type<empty_expression_tree>::type> {
			};

			template<default_integral_t Value>
			struct native_coefficient_type<constant<Value> > {
				typedef typename constant<Value>::value_type type;
			};

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_TREE_COEFFICIENT_TYPE_HPP__
