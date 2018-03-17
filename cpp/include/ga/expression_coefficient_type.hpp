#ifndef __GA_EXPRESSION_COEFFICIENT_TYPE_HPP__
#define __GA_EXPRESSION_COEFFICIENT_TYPE_HPP__

namespace ga {

	namespace detail {

		template<class Type>
		struct common_coefficient_type;

		template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
		struct common_coefficient_type<expression<ElementType, LeftSubtreeType, RightSubtreeType> > : std::common_type<
			typename ElementType::coefficient_type,
			typename common_coefficient_type<LeftSubtreeType>::type,
			typename common_coefficient_type<RightSubtreeType>::type
		> {
		};

		template<class ElementType, class RightSubtreeType>
		struct common_coefficient_type<expression<ElementType, empty_expression, RightSubtreeType> > : std::common_type<
			typename ElementType::coefficient_type,
			typename common_coefficient_type<RightSubtreeType>::type
		> {
		};

		template<class ElementType, class LeftSubtreeType>
		struct common_coefficient_type<expression<ElementType, LeftSubtreeType, empty_expression> > : std::common_type<
			typename ElementType::coefficient_type,
			typename common_coefficient_type<LeftSubtreeType>::type
		> {
		};

		template<class ElementType>
		struct common_coefficient_type<expression<ElementType, empty_expression, empty_expression> > {
			typedef typename ElementType::coefficient_type type;
		};

		template<>
		struct common_coefficient_type<empty_expression> {
			typedef default_integral_t type;
		};

	}

}

#endif // __GA_EXPRESSION_COEFFICIENT_TYPE_HPP__
