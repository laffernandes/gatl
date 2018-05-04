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

			template<default_integral_t LeftValue, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::constant<LeftValue>, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = true;
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, default_integral_t RightValue>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, lazy::constant<RightValue> > {
				constexpr static bool value = false;
			};

			template<default_integral_t LeftValue, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::constant<LeftValue>, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = true;
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, default_integral_t RightValue>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType> , lazy::constant<RightValue> > {
				constexpr static bool value = false;
			};

			template<default_integral_t LeftValue, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::constant<LeftValue>, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = true;
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, default_integral_t RightValue>
			struct lt<lazy::detail::power<LeftLeftExpressionType, LeftRightExpressionType>, lazy::constant<RightValue> > {
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

			template<id_t LeftId, class LeftValueType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> > :
				le<lazy::variable<LeftId, LeftValueType>, RightLeftExpressionType> {
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, id_t RightId, class RightValueType>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, lazy::variable<RightId, RightValueType> > :
				lt<LeftLeftExpressionType, lazy::variable<RightId, RightValueType>> {
			};

			template<id_t LeftId, class LeftValueType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > :
				le<lazy::variable<LeftId, LeftValueType>, RightLeftExpressionType> {
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, id_t RightId, class RightValueType>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, lazy::variable<RightId, RightValueType> > :
				lt<LeftLeftExpressionType, lazy::variable<RightId, RightValueType>> {
			};

			template<id_t LeftId, class LeftValueType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > :
				le<lazy::variable<LeftId, LeftValueType>, RightLeftExpressionType> {
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, id_t RightId, class RightValueType>
			struct lt<lazy::detail::power<LeftLeftExpressionType, LeftRightExpressionType>, lazy::variable<RightId, RightValueType> > :
				lt<LeftLeftExpressionType, lazy::variable<RightId, RightValueType>> {
			};

			// Addition type ordering:
			//     add_left < add_right, if add_left[Left] < add_right[Left] || (add_left[Left] == add_right[Left] && add_left[Right] < add_right[Right])
			//     add < mul, if add[Left] < mul
			//     add < power, if add[Left] < power
			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value);
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > :
				lt<LeftLeftExpressionType, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > {
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType>> :
				le<lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType>, LeftLeftExpressionType> {
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > :
				lt<LeftLeftExpressionType, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > {
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::power<LeftLeftExpressionType, LeftRightExpressionType> , lazy::detail::add<RightLeftExpressionType, RightRightExpressionType>> :
				le<lazy::detail::power<RightLeftExpressionType, RightRightExpressionType>, LeftLeftExpressionType> {
			};

			// Multiplication type ordering:
			//     mul_left < mul_right, if mul_left[Left] < mul_right[Left] || (mul_left[Left] == mul_right[Left] && mul_left[Right] < mul_right[Right])
			//     mul < power, if mul[Left] < power
			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value);
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > :
				lt<LeftLeftExpressionType, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > {
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::power<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType>> :
				le<lazy::detail::power<RightLeftExpressionType, RightRightExpressionType>, LeftLeftExpressionType> {
			};

			// Exponentiation type ordering:
			//     power_left < lower_right, if power_left[Left] < power_right[Left] || (power_left[Left] == power_right[Left] && power_left[Right] < power_right[Right])
			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::power<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value);
			};

		}

	}

}

#endif // __GA_LAZY_EXPRESSION_ORDERING_HPP__
