#ifndef __GA_LAZY_EXPRESSION_ORDERING_HPP__
#define __GA_LAZY_EXPRESSION_ORDERING_HPP__

namespace ga {

	namespace common {

		namespace detail {

			// Basic types ordering:
			//     value < constant < variable[Id] < variable[Id+1]
			template<default_integral_t LeftValue, default_integral_t RightValue>
			struct lt<lazy::constant<LeftValue>, lazy::constant<RightValue> > {
				constexpr static bool value = LeftValue < RightValue;
			};

			template<default_integral_t LeftValue, class RightValueType>
			struct lt<lazy::constant<LeftValue>, lazy::value<RightValueType> > {
				constexpr static bool value = false;
			};

			template<default_integral_t LeftValue, id_t RightId, class RightValueType>
			struct lt<lazy::constant<LeftValue>, lazy::variable<RightId, RightValueType> > {
				constexpr static bool value = true;
			};

			template<class LeftValueType, default_integral_t RightValue>
			struct lt<lazy::value<LeftValueType>, lazy::constant<RightValue> > {
				constexpr static bool value = true;
			};

			template<class LeftValueType, class RightValueType>
			struct lt<lazy::value<LeftValueType>, lazy::value<RightValueType> > {
				constexpr static bool value = false;
			};

			template<class LeftValueType, id_t RightId, class RightValueType>
			struct lt<lazy::value<LeftValueType>, lazy::variable<RightId, RightValueType> > {
				constexpr static bool value = true;
			};

			template<id_t LeftId, class LeftValueType, default_integral_t RightValue>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::constant<RightValue> > {
				constexpr static bool value = false;
			};

			template<id_t LeftId, class LeftValueType, class RightValueType>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::value<RightValueType> > {
				constexpr static bool value = false;
			};

			template<id_t LeftId, class LeftValueType, id_t RightId, class RightValueType>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::variable<RightId, RightValueType> > {
				constexpr static bool value = LeftId < RightId;
			};

			// Addition ordering:
			//     add<LeftExpressionType, RightExpressionType> == RightExpressionType, if LeftExpressionType is constant
			//                                                  == LeftExpressionType, otherwise
			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = is_lazy_constant<LeftLeftExpressionType>::value ? (is_lazy_constant<RightLeftExpressionType>::value ? lt<LeftRightExpressionType, RightRightExpressionType>::value : lt<LeftRightExpressionType, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> >::value) : (is_lazy_constant<RightLeftExpressionType>::value ? lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, RightRightExpressionType>::value : lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value));
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, RightExpressionType> {
				constexpr static bool value = ((is_lazy_constant<LeftLeftExpressionType>::value || eq<LeftLeftExpressionType, RightExpressionType>::value) && lt<LeftRightExpressionType, RightExpressionType>::value) || (!is_lazy_constant<LeftLeftExpressionType>::value && lt<LeftLeftExpressionType, RightExpressionType>::value);
			};

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<LeftExpressionType, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = ((is_lazy_constant<RightLeftExpressionType>::value || eq<LeftExpressionType, RightLeftExpressionType>::value) && lt<LeftExpressionType, RightRightExpressionType>::value) || (!is_lazy_constant<RightLeftExpressionType>::value && lt<LeftExpressionType, RightLeftExpressionType>::value);
			};

			// Multiplication ordering:
			//     mul<LeftExpressionType, RightExpressionType> == RightExpressionType, if LeftExpressionType is constant
			//                                                  == LeftExpressionType, otherwise
			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = is_lazy_constant<LeftLeftExpressionType>::value ? (is_lazy_constant<RightLeftExpressionType>::value ? lt<LeftRightExpressionType, RightRightExpressionType>::value : lt<LeftRightExpressionType, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> >::value) : (is_lazy_constant<RightLeftExpressionType>::value ? lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, RightRightExpressionType>::value : lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value));
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, RightExpressionType> {
				constexpr static bool value = ((is_lazy_constant<LeftLeftExpressionType>::value || eq<LeftLeftExpressionType, RightExpressionType>::value) && lt<LeftRightExpressionType, RightExpressionType>::value) || (!is_lazy_constant<LeftLeftExpressionType>::value && lt<LeftLeftExpressionType, RightExpressionType>::value);
			};

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<LeftExpressionType, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = ((is_lazy_constant<RightLeftExpressionType>::value || eq<LeftExpressionType, RightLeftExpressionType>::value) && lt<LeftExpressionType, RightRightExpressionType>::value) || (!is_lazy_constant<RightLeftExpressionType>::value && lt<LeftExpressionType, RightLeftExpressionType>::value);
			};

			// Exponentiation ordering:
			//     power<BaseExpressionType, ...> == BaseExpressionType
			template<class LeftLeftExpressionType, class LeftRightExpressionType, default_integral_t RightValue>
			struct lt<lazy::detail::power<LeftLeftExpressionType, LeftRightExpressionType>, lazy::constant<RightValue> > : lt<LeftLeftExpressionType, lazy::constant<RightValue> > {
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightValueType>
			struct lt<lazy::detail::power<LeftLeftExpressionType, LeftRightExpressionType>, lazy::value<RightValueType> > : lt<LeftLeftExpressionType, lazy::value<RightValueType> > {
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, id_t RightId, class RightValueType>
			struct lt<lazy::detail::power<LeftLeftExpressionType, LeftRightExpressionType>, lazy::variable<RightId, RightValueType> > : lt<LeftLeftExpressionType, lazy::variable<RightId, RightValueType> > {
			};

			template<default_integral_t LeftValue, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::constant<LeftValue>, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > : lt<lazy::constant<LeftValue>, RightLeftExpressionType> {
			};

			template<class LeftValueType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::value<LeftValueType>, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > : lt<lazy::value<LeftValueType>, RightLeftExpressionType> {
			};

			template<id_t LeftId, class LeftValueType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > : lt<lazy::variable<LeftId, LeftValueType>, RightLeftExpressionType> {
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::power<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value);
			};

			// Compound types ordering.
			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = is_lazy_constant<LeftLeftExpressionType>::value ? (is_lazy_constant<RightLeftExpressionType>::value ? lt<LeftRightExpressionType, RightRightExpressionType>::value : lt<LeftRightExpressionType, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> >::value) : (is_lazy_constant<RightLeftExpressionType>::value ? lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, RightRightExpressionType>::value : lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value));
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = ((is_lazy_constant<LeftLeftExpressionType>::value || eq<LeftLeftExpressionType, RightLeftExpressionType>::value) && lt<LeftRightExpressionType, RightLeftExpressionType>::value) || (!is_lazy_constant<LeftLeftExpressionType>::value && lt<LeftLeftExpressionType, RightLeftExpressionType>::value);
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = is_lazy_constant<LeftLeftExpressionType>::value ? (is_lazy_constant<RightLeftExpressionType>::value ? lt<LeftRightExpressionType, RightRightExpressionType>::value : lt<LeftRightExpressionType, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> >::value) : (is_lazy_constant<RightLeftExpressionType>::value ? lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, RightRightExpressionType>::value : lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value));
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::power<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = ((is_lazy_constant<LeftLeftExpressionType>::value || eq<LeftLeftExpressionType, RightLeftExpressionType>::value) && lt<LeftRightExpressionType, RightLeftExpressionType>::value) || (!is_lazy_constant<LeftLeftExpressionType>::value && lt<LeftLeftExpressionType, RightLeftExpressionType>::value);
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::power<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = ((is_lazy_constant<RightLeftExpressionType>::value || eq<LeftLeftExpressionType, RightLeftExpressionType>::value) && lt<LeftLeftExpressionType, RightRightExpressionType>::value) || (!is_lazy_constant<RightLeftExpressionType>::value && lt<LeftLeftExpressionType, RightLeftExpressionType>::value);
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::power<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = ((is_lazy_constant<RightLeftExpressionType>::value || eq<LeftLeftExpressionType, RightLeftExpressionType>::value) && lt<LeftLeftExpressionType, RightRightExpressionType>::value) || (!is_lazy_constant<RightLeftExpressionType>::value && lt<LeftLeftExpressionType, RightLeftExpressionType>::value);
			};

		}

	}

}

#endif // __GA_LAZY_EXPRESSION_ORDERING_HPP__
