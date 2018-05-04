#ifndef __GA_EXPRESSION_TRAITS_HPP__
#define __GA_EXPRESSION_TRAITS_HPP__

namespace ga {

	namespace common {

		template<class Type>
		struct is_clifford_expression {
			constexpr static bool value = false;
		};

		template<class Type>
		struct is_lazy_expression {
			constexpr static bool value = false;
		};

		template<class Type>
		struct is_lazy_constant {
			constexpr static bool value = false;
		};

		template<class Type>
		struct is_lazy_value {
			constexpr static bool value = false;
		};

		template<class Type>
		struct allows_lazy_simplification {
			constexpr static bool value = !is_lazy_value<Type>::value;
		};

	}

}

#endif // __GA_EXPRESSION_TRAITS_HPP__
