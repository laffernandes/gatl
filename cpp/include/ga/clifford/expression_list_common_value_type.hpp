#ifndef __GA_CLIFFORD_EXPRESSION_LIST_COMMON_VALUE_TYPE_HPP__
#define __GA_CLIFFORD_EXPRESSION_LIST_COMMON_VALUE_TYPE_HPP__

namespace ga {

	namespace common {

		namespace detail {

			template<class ElementType, class NextListType>
			struct common_value_type<clifford::detail::expression_list<ElementType, NextListType> > : std::common_type<
				typename ElementType::coefficient_type::value_type,
				typename common_value_type<NextListType>::type
			> {
			};

			template<class ElementType>
			struct common_value_type<clifford::detail::expression_list<ElementType, clifford::detail::empty_clifford_expression> > : std::common_type<
				typename ElementType::coefficient_type::value_type
			> {
			};

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_LIST_COMMON_VALUE_TYPE_HPP__
