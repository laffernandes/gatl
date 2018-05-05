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
		struct is_lazy_add {
			constexpr static bool value = false;
		};

		template<class Type>
		struct is_lazy_mul {
			constexpr static bool value = false;
		};

		template<class Type>
		struct allows_lazy_simplification {
			constexpr static bool value = !is_lazy_value<Type>::value;
		};

		template<class Type>
		struct common_value_type {
			typedef Type type;
		};

	}

}

#endif // __GA_EXPRESSION_TRAITS_HPP__
