#ifndef __GA_LAZY_EXPRESSION_ORDERING_HPP__
#define __GA_LAZY_EXPRESSION_ORDERING_HPP__

namespace ga {

	namespace common {

		namespace detail {

			// Value type ordering:
			//    value < everything, but value == value
			template<class LeftValueType, class RightExpressionType>
			struct lt<lazy::value<LeftValueType>, RightExpressionType> {
				constexpr static bool value = true;
			};

			template<class LeftExpressionType, class RightValueType>
			struct lt<LeftExpressionType, lazy::value<RightValueType> > {
				constexpr static bool value = false;
			};

			template<class LeftValueType, class RightValueType>
			struct lt<lazy::value<LeftValueType>, lazy::value<RightValueType> > {
				constexpr static bool value = false;
			};

			// Constant type ordering:
			//     constant[Value] < constant[Value+1]
			//     constant < variable
			//     constant < add
			//     constant < mul
			//     constant < power
			template<default_integral_t LeftValue, default_integral_t RightValue>
			struct lt<lazy::constant<LeftValue>, lazy::constant<RightValue> > {
				constexpr static bool value = LeftValue < RightValue;
			};

			template<default_integral_t LeftValue, id_t RightId, class RightValueType>
			struct lt<lazy::constant<LeftValue>, lazy::variable<RightId, RightValueType> > {
				constexpr static bool value = true;
			};

			template<id_t LeftId, class LeftValueType, default_integral_t RightValue>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::constant<RightValue> > {
				constexpr static bool value = false;
			};

			template<default_integral_t LeftValue, class... RightArgumentTypes>
			struct lt<lazy::constant<LeftValue>, lazy::detail::add<RightArgumentTypes...> > {
				constexpr static bool value = true;
			};

			template<class... LeftArgumentTypes, default_integral_t RightValue>
			struct lt<lazy::detail::add<LeftArgumentTypes...>, lazy::constant<RightValue> > {
				constexpr static bool value = false;
			};

			template<default_integral_t LeftValue, class RightLeftArgumentType, class... RightRightArgumentTypes>
			struct lt<lazy::constant<LeftValue>, lazy::detail::mul<RightLeftArgumentType, RightRightArgumentTypes...> > {
				constexpr static bool value = true;
			};

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, default_integral_t RightValue>
			struct lt<lazy::detail::mul<LeftLeftArgumentType, LeftRightArgumentTypes...> , lazy::constant<RightValue> > {
				constexpr static bool value = false;
			};

			template<default_integral_t LeftValue, class RightLeftArgumentType, class RightRightArgumentType>
			struct lt<lazy::constant<LeftValue>, lazy::detail::power<RightLeftArgumentType, RightRightArgumentType> > {
				constexpr static bool value = true;
			};

			template<class LeftLeftArgumentType, class LeftRightArgumentType, default_integral_t RightValue>
			struct lt<lazy::detail::power<LeftLeftArgumentType, LeftRightArgumentType>, lazy::constant<RightValue> > {
				constexpr static bool value = false;
			};

			// Variable type ordering:
			//     variable[Id] < variable[Id+1]
			//     variable < add, if variable <= add[Left]
			//     variable < mul, if variable <= mul[Left]
			//     variable < power, if variable <= power[Left]
			template<id_t LeftId, class LeftValueType, id_t RightId, class RightValueType>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::variable<RightId, RightValueType> > {
				constexpr static bool value = LeftId < RightId;
			};

			template<id_t LeftId, class LeftValueType, class RightLeftArgumentType, class... RightRightArgumentTypes>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::detail::add<RightLeftArgumentType, RightRightArgumentTypes...> > :
				le<lazy::variable<LeftId, LeftValueType>, RightLeftArgumentType> {
			};

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, id_t RightId, class RightValueType>
			struct lt<lazy::detail::add<LeftLeftArgumentType, LeftRightArgumentTypes...>, lazy::variable<RightId, RightValueType> > :
				lt<LeftLeftArgumentType, lazy::variable<RightId, RightValueType> > {
			};

			template<id_t LeftId, class LeftValueType, class RightLeftArgumentType, class... RightRightArgumentTypes>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::detail::mul<RightLeftArgumentType, RightRightArgumentTypes...> > :
				le<lazy::variable<LeftId, LeftValueType>, RightLeftArgumentType> {
			};

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, id_t RightId, class RightValueType>
			struct lt<lazy::detail::mul<LeftLeftArgumentType, LeftRightArgumentTypes...>, lazy::variable<RightId, RightValueType> > :
				lt<LeftLeftArgumentType, lazy::variable<RightId, RightValueType> > {
			};

			template<id_t LeftId, class LeftValueType, class RightLeftArgumentType, class RightRightArgumentType>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::detail::power<RightLeftArgumentType, RightRightArgumentType> > :
				le<lazy::variable<LeftId, LeftValueType>, RightLeftArgumentType> {
			};

			template<class LeftLeftArgumentType, class LeftRightArgumentType, id_t RightId, class RightValueType>
			struct lt<lazy::detail::power<LeftLeftArgumentType, LeftRightArgumentType>, lazy::variable<RightId, RightValueType> > :
				lt<LeftLeftArgumentType, lazy::variable<RightId, RightValueType> > {
			};

			// Addition type ordering:
			//     add_left < add_right, if add_left[Left] < add_right[Left] || (add_left[Left] == add_right[Left] && add_left[Right] < add_right[Right])
			//     add < mul, if add[Left] < mul
			//     add < power, if add[Left] < power
			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes>
			struct lt<lazy::detail::add<LeftLeftArgumentType, LeftRightArgumentTypes...>, lazy::detail::add<RightLeftArgumentType, RightRightArgumentTypes...> > {
				constexpr static bool value = lt<LeftLeftArgumentType, RightLeftArgumentType>::value || (eq<LeftLeftArgumentType, RightLeftArgumentType>::value && lt<typename lazy::detail::add<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type, typename lazy::detail::add<RightLeftArgumentType, RightRightArgumentTypes...>::right_type>::value);
			};

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes>
			struct lt<lazy::detail::add<LeftLeftArgumentType, LeftRightArgumentTypes...>, lazy::detail::mul<RightLeftArgumentType, RightRightArgumentTypes...> > :
				lt<LeftLeftArgumentType, lazy::detail::mul<RightLeftArgumentType, RightRightArgumentTypes...> > {
			};

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes>
			struct lt<lazy::detail::mul<LeftLeftArgumentType, LeftRightArgumentTypes...>, lazy::detail::add<RightLeftArgumentType, RightRightArgumentTypes...> > :
				le<lazy::detail::mul<LeftLeftArgumentType, LeftRightArgumentTypes...>, RightLeftArgumentType> {
			};

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class RightRightArgumentType>
			struct lt<lazy::detail::add<LeftLeftArgumentType, LeftRightArgumentTypes...>, lazy::detail::power<RightLeftArgumentType, RightRightArgumentType> > :
				lt<LeftLeftArgumentType, lazy::detail::power<RightLeftArgumentType, RightRightArgumentType> > {
			};

			template<class LeftLeftArgumentType, class LeftRightArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes>
			struct lt<lazy::detail::power<LeftLeftArgumentType, LeftRightArgumentType> , lazy::detail::add<RightLeftArgumentType, RightRightArgumentTypes...> > :
				le<lazy::detail::power<LeftLeftArgumentType, LeftRightArgumentType>, RightLeftArgumentType> {
			};

			// Multiplication type ordering:
			//     mul_left < mul_right, if mul_left[Left] < mul_right[Left] || (mul_left[Left] == mul_right[Left] && mul_left[Right] < mul_right[Right])
			//     mul < power, if mul[Left] < power
			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class... RightRightArgumentTypes>
			struct lt<lazy::detail::mul<LeftLeftArgumentType, LeftRightArgumentTypes...>, lazy::detail::mul<RightLeftArgumentType, RightRightArgumentTypes...> > {
				constexpr static bool value = lt<LeftLeftArgumentType, RightLeftArgumentType>::value || (eq<LeftLeftArgumentType, RightLeftArgumentType>::value && lt<typename lazy::detail::mul<LeftLeftArgumentType, LeftRightArgumentTypes...>::right_type, typename lazy::detail::mul<RightLeftArgumentType, RightRightArgumentTypes...>::right_type>::value);
			};

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightLeftArgumentType, class RightRightArgumentType>
			struct lt<lazy::detail::mul<LeftLeftArgumentType, LeftRightArgumentTypes...>, lazy::detail::power<RightLeftArgumentType, RightRightArgumentType> > :
				lt<LeftLeftArgumentType, lazy::detail::power<RightLeftArgumentType, RightRightArgumentType> > {
			};

			template<class LeftLeftArgumentType, class LeftRightArgumentType, class RightLeftArgumentType, class... RightRightArgumentTypes>
			struct lt<lazy::detail::power<LeftLeftArgumentType, LeftRightArgumentType>, lazy::detail::mul<RightLeftArgumentType, RightRightArgumentTypes...> > :
				le<lazy::detail::power<LeftLeftArgumentType, LeftRightArgumentType>, RightLeftArgumentType> {
			};

			// Exponentiation type ordering:
			//     power_left < lower_right, if power_left[Left] < power_right[Left] || (power_left[Left] == power_right[Left] && power_left[Right] < power_right[Right])
			template<class LeftLeftArgumentType, class LeftRightArgumentType, class RightLeftArgumentType, class RightRightArgumentType>
			struct lt<lazy::detail::power<LeftLeftArgumentType, LeftRightArgumentType>, lazy::detail::power<RightLeftArgumentType, RightRightArgumentType> > {
				constexpr static bool value = lt<LeftLeftArgumentType, RightLeftArgumentType>::value || (eq<LeftLeftArgumentType, RightLeftArgumentType>::value && lt<LeftRightArgumentType, RightRightArgumentType>::value);
			};

		}

	}

}

#endif // __GA_LAZY_EXPRESSION_ORDERING_HPP__
