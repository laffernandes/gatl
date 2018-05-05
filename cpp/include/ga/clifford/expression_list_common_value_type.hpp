#ifndef __GA_CLIFFORD_EXPRESSION_LIST_COMMON_VALUE_TYPE_HPP__
#define __GA_CLIFFORD_EXPRESSION_LIST_COMMON_VALUE_TYPE_HPP__

namespace ga {

	namespace common {

		namespace detail {

			template<class ElementType, class... OtherElementTypes>
			struct common_value_type<clifford::detail::expression_list<ElementType, OtherElementTypes...> > : std::common_type<
				typename ElementType::coefficient_type::value_type,
				typename common_value_type<typename clifford::detail::expression_list<ElementType, OtherElementTypes...>::next_type>::type
			> {
			};

			template<class ElementType>
			struct common_value_type<clifford::detail::expression_list<ElementType> > : std::common_type<
				typename ElementType::coefficient_type::value_type
			> {
			};

		}

	}

}

#endif // __GA_CLIFFORD_EXPRESSION_LIST_COMMON_VALUE_TYPE_HPP__
