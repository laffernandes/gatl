#ifndef __GA_EXPRESSION_TRAITS_HPP__
#define __GA_EXPRESSION_TRAITS_HPP__

namespace ga {

	namespace common {

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
		struct is_lazy_variable {
			constexpr static bool value = false;
		};

		template<class Type>
		struct is_clifford_expression {
			constexpr static bool value = false;
		};

	}

}

#endif // __GA_EXPRESSION_TRAITS_HPP__
