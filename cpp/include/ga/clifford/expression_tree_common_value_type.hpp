#ifndef __GA_CLIFFORD_EXPRESSION_TREE_COMMON_VALUE_TYPE_HPP__
#define __GA_CLIFFORD_EXPRESSION_TREE_COMMON_VALUE_TYPE_HPP__

namespace ga {

	namespace common {

		namespace detail {

			template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
			struct common_value_type<clifford::detail::expression_tree<ElementType, LeftSubtreeType, RightSubtreeType> > : std::common_type<
				typename ElementType::coefficient_type::value_type,
				typename common_value_type<LeftSubtreeType>::type,
				typename common_value_type<RightSubtreeType>::type
			> {
			};

			template<class ElementType, class RightSubtreeType>
			struct common_value_type<clifford::detail::expression_tree<ElementType, clifford::detail::empty_clifford_expression, RightSubtreeType> > : std::common_type<
				typename ElementType::coefficient_type::value_type,
				typename common_value_type<RightSubtreeType>::type
			> {
			};

			template<class ElementType, class LeftSubtreeType>
			struct common_value_type<clifford::detail::expression_tree<ElementType, LeftSubtreeType, clifford::detail::empty_clifford_expression> > : std::common_type<
				typename ElementType::coefficient_type::value_type,
				typename common_value_type<LeftSubtreeType>::type
			> {
			};

			template<class ElementType>
			struct common_value_type<clifford::detail::expression_tree<ElementType, clifford::detail::empty_clifford_expression, clifford::detail::empty_clifford_expression> > {
				typedef typename ElementType::coefficient_type::value_type type;
			};

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_TREE_COMMON_VALUE_TYPE_HPP__
