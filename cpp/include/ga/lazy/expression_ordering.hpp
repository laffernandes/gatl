#ifndef __GA_LAZY_EXPRESSION_ORDERING_HPP__
#define __GA_LAZY_EXPRESSION_ORDERING_HPP__

namespace ga {

	namespace common {

		namespace detail {

			template<default_integral_t LeftValue, default_integral_t RightValue>
			struct lt<lazy::constant<LeftValue>, lazy::constant<RightValue> > {
				constexpr static bool value = false;
			};

			template<default_integral_t LeftValue, class RightValueType>
			struct lt<lazy::constant<LeftValue>, lazy::value<RightValueType> > {
				constexpr static bool value = false;
			};

			template<default_integral_t LeftValue, id_t RightId, class RightValueType>
			struct lt<lazy::constant<LeftValue>, lazy::variable<RightId, RightValueType> > {
				constexpr static bool value = true;
			};

			template<default_integral_t LeftValue, class RightLeftExpression, class RightRightExpression>
			struct lt<lazy::constant<LeftValue>, lazy::detail::pow<RightLeftExpression, RightRightExpression> > : lt<lazy::constant<LeftValue>, RightLeftExpression> {
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

			template<class LeftValueType, class RightLeftExpression, class RightRightExpression>
			struct lt<lazy::value<LeftValueType>, lazy::detail::pow<RightLeftExpression, RightRightExpression> > : lt<lazy::value<LeftValueType>, RightLeftExpression> {
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

			template<id_t LeftId, class LeftValueType, class RightLeftExpression, class RightRightExpression>
			struct lt<lazy::variable<LeftId, LeftValueType>, lazy::detail::pow<RightLeftExpression, RightRightExpression> > : lt<lazy::variable<LeftId, LeftValueType>, RightLeftExpression> {
			};

			template<class LeftLeftExpression, class LeftRightExpression, default_integral_t RightValue>
			struct lt<lazy::detail::pow<LeftLeftExpression, LeftRightExpression>, lazy::constant<RightValue> > : lt<LeftLeftExpression, lazy::constant<RightValue> > {
			};

			template<class LeftLeftExpression, class LeftRightExpression, class RightValueType>
			struct lt<lazy::detail::pow<LeftLeftExpression, LeftRightExpression>, lazy::value<RightValueType> > : lt<LeftLeftExpression, lazy::value<RightValueType> > {
			};

			template<class LeftLeftExpression, class LeftRightExpression, id_t RightId, class RightValueType>
			struct lt<lazy::detail::pow<LeftLeftExpression, LeftRightExpression>, lazy::variable<RightId, RightValueType> > : lt<LeftLeftExpression, lazy::variable<RightId, RightValueType> > {
			};

			template<class LeftLeftExpression, class LeftRightExpression, class RightLeftExpression, class RightRightExpression>
			struct lt<lazy::detail::pow<LeftLeftExpression, LeftRightExpression>, lazy::detail::pow<RightLeftExpression, RightRightExpression> > : lt<LeftLeftExpression, RightLeftExpression> {
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = is_lazy_constant<LeftLeftExpressionType>::value ? (is_lazy_constant<RightLeftExpressionType>::value ? lt<LeftRightExpressionType, RightRightExpressionType>::value : lt<LeftRightExpressionType, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> >::value) : (is_lazy_constant<RightLeftExpressionType>::value ? lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, RightRightExpressionType>::value : lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value));
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, RightExpressionType> {
				constexpr static bool value = !is_lazy_constant<RightExpressionType>::value && std::conditional<is_lazy_constant<LeftLeftExpressionType>::value, lt<LeftRightExpressionType, RightExpressionType>, lt<LeftLeftExpressionType, RightExpressionType> >::type::value;
			};

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<LeftExpressionType, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = is_lazy_constant<LeftExpressionType>::value || std::conditional<is_lazy_constant<RightLeftExpressionType>::value, lt<LeftExpressionType, RightRightExpressionType>, lt<LeftExpressionType, RightLeftExpressionType> >::type::value;
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = is_lazy_constant<LeftLeftExpressionType>::value ? (is_lazy_constant<RightLeftExpressionType>::value ? lt<LeftRightExpressionType, RightRightExpressionType>::value : lt<LeftRightExpressionType, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> >::value) : (is_lazy_constant<RightLeftExpressionType>::value ? lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, RightRightExpressionType>::value : lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value));
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightExpressionType>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, RightExpressionType> {
				constexpr static bool value = !is_lazy_constant<RightExpressionType>::value && std::conditional<is_lazy_constant<LeftLeftExpressionType>::value, lt<LeftRightExpressionType, RightExpressionType>, lt<LeftLeftExpressionType, RightExpressionType> >::type::value;
			};

			template<class LeftExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<LeftExpressionType, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = is_lazy_constant<LeftExpressionType>::value || std::conditional<is_lazy_constant<RightLeftExpressionType>::value, lt<LeftExpressionType, RightRightExpressionType>, lt<LeftExpressionType, RightLeftExpressionType> >::type::value;
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = is_lazy_constant<LeftLeftExpressionType>::value ? (is_lazy_constant<RightLeftExpressionType>::value ? lt<LeftRightExpressionType, RightRightExpressionType>::value : lt<LeftRightExpressionType, lazy::detail::mul<RightLeftExpressionType, RightRightExpressionType> >::value) : (is_lazy_constant<RightLeftExpressionType>::value ? lt<lazy::detail::add<LeftLeftExpressionType, LeftRightExpressionType>, RightRightExpressionType>::value : lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value));
			};

			template<class LeftLeftExpressionType, class LeftRightExpressionType, class RightLeftExpressionType, class RightRightExpressionType>
			struct lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> > {
				constexpr static bool value = is_lazy_constant<LeftLeftExpressionType>::value ? (is_lazy_constant<RightLeftExpressionType>::value ? lt<LeftRightExpressionType, RightRightExpressionType>::value : lt<LeftRightExpressionType, lazy::detail::add<RightLeftExpressionType, RightRightExpressionType> >::value) : (is_lazy_constant<RightLeftExpressionType>::value ? lt<lazy::detail::mul<LeftLeftExpressionType, LeftRightExpressionType>, RightRightExpressionType>::value : lt<LeftLeftExpressionType, RightLeftExpressionType>::value || (eq<LeftLeftExpressionType, RightLeftExpressionType>::value && lt<LeftRightExpressionType, RightRightExpressionType>::value));
			};

		}

	}

}

#endif // __GA_LAZY_EXPRESSION_ORDERING_HPP__
