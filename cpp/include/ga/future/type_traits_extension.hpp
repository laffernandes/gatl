#ifndef __GA_TYPE_TRAITS_EXTENSION_HPP__
#define __GA_TYPE_TRAITS_EXTENSION_HPP__

namespace future {

	namespace detail {

		// Returns true if T and any element in Rest has the same type with the same const-volatile qualifications or false otherwise.
		template<class T, class... Rest>
		struct is_any : std::false_type {
		};

		template<class T, class First>
		struct is_any<T, First> : std::is_same<T, First> {
		};

		template<class T, class First, class... Rest>
		struct is_any<T, First, Rest...> : std::integral_constant<bool, std::is_same_v<T, First> || is_any<T, Rest...>::value> {
		};

		template<class T, class... Rest>
		constexpr bool is_any_v = is_any<T, Rest...>::value;

	}

}

#endif // __GA_TYPE_TRAITS_EXTENSION_HPP__
