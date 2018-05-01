#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_COMMON_VALUE_TYPE_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_COMMON_VALUE_TYPE_HPP__

namespace ga {

	namespace common {

		namespace detail {

			template<>
			struct common_value_type<clifford::detail::empty_clifford_expression> {
				typedef default_integral_t type;
			};

		}

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_COMMON_VALUE_TYPE_HPP__
