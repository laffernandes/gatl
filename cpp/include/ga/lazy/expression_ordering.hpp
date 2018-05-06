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

			template<default_integral_t LeftValue, class RightValueType, id_t RightId, id_t... RightSubIds>
			struct lt<lazy::constant<LeftValue>, lazy::variable<RightValueType, RightId, RightSubIds...> > {
				constexpr static bool value = true;
			};

			template<class LeftValueType, id_t LeftId, id_t... LeftSubIds, default_integral_t RightValue>
			struct lt<lazy::variable<LeftValueType, LeftId, LeftSubIds...>, lazy::constant<RightValue> > {
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
			template<id_t LeftId, id_t... LeftSubIds>
			struct _variable_id_cmp {
				template<id_t RightId, id_t... RightSubIds>
				struct lt {
					constexpr static bool value = LeftId < RightId;
				};

				template<id_t... RightSubIds>
				struct lt<LeftId, RightSubIds...> : _variable_id_cmp<LeftSubIds...>::template lt<RightSubIds...> {
				};

				template<>
				struct lt<LeftId> {
					constexpr static bool value = false;
				};
			};

			template<id_t LeftId>
			struct _variable_id_cmp<LeftId> {
				template<id_t RightId, id_t... RightSubIds>
				struct lt {
					constexpr static bool value = LeftId < RightId;
				};

				template<id_t... RightSubIds>
				struct lt<LeftId, RightSubIds...> {
					constexpr static bool value = true;
				};

				template<>
				struct lt<LeftId> {
					constexpr static bool value = false;
				};
			};

			template<class LeftValueType, id_t LeftId, id_t... LeftSubIds, class RightValueType, id_t RightId, id_t... RightSubIds>
			struct lt<lazy::variable<LeftValueType, LeftId, LeftSubIds...>, lazy::variable<RightValueType, RightId, RightSubIds...> > {
				constexpr static bool value = _variable_id_cmp<LeftId, LeftSubIds...>::template lt<RightId, RightSubIds...>::value;
			};

			template<class LeftValueType, id_t LeftId, id_t... LeftSubIds, class RightLeftArgumentType, class... RightRightArgumentTypes>
			struct lt<lazy::variable<LeftValueType, LeftId, LeftSubIds...>, lazy::detail::add<RightLeftArgumentType, RightRightArgumentTypes...> > :
				le<lazy::variable<LeftValueType, LeftId, LeftSubIds...>, RightLeftArgumentType> {
			};

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightValueType, id_t RightId, id_t... RightSubIds>
			struct lt<lazy::detail::add<LeftLeftArgumentType, LeftRightArgumentTypes...>, lazy::variable<RightValueType, RightId, RightSubIds...> > :
				lt<LeftLeftArgumentType, lazy::variable<RightValueType, RightId, RightSubIds...> > {
			};

			template<class LeftValueType, id_t LeftId, id_t... LeftSubIds, class RightLeftArgumentType, class... RightRightArgumentTypes>
			struct lt<lazy::variable<LeftValueType, LeftId, LeftSubIds...>, lazy::detail::mul<RightLeftArgumentType, RightRightArgumentTypes...> > :
				le<lazy::variable<LeftValueType, LeftId, LeftSubIds...>, RightLeftArgumentType> {
			};

			template<class LeftLeftArgumentType, class... LeftRightArgumentTypes, class RightValueType, id_t RightId, id_t... RightSubIds>
			struct lt<lazy::detail::mul<LeftLeftArgumentType, LeftRightArgumentTypes...>, lazy::variable<RightValueType, RightId, RightSubIds...> > :
				lt<LeftLeftArgumentType, lazy::variable<RightValueType, RightId, RightSubIds...> > {
			};

			template<class LeftValueType, id_t LeftId, id_t... LeftSubIds, class RightLeftArgumentType, class RightRightArgumentType>
			struct lt<lazy::variable<LeftValueType, LeftId, LeftSubIds...>, lazy::detail::power<RightLeftArgumentType, RightRightArgumentType> > :
				le<lazy::variable<LeftValueType, LeftId, LeftSubIds...>, RightLeftArgumentType> {
			};

			template<class LeftLeftArgumentType, class LeftRightArgumentType, class RightValueType, id_t RightId, id_t... RightSubIds>
			struct lt<lazy::detail::power<LeftLeftArgumentType, LeftRightArgumentType>, lazy::variable<RightValueType, RightId, RightSubIds...> > :
				lt<LeftLeftArgumentType, lazy::variable<RightValueType, RightId, RightSubIds...> > {
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
