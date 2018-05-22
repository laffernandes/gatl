#ifndef __FUTURE_GA_EXPRESSION_ADDITION_HPP__
#define __FUTURE_GA_EXPRESSION_ADDITION_HPP__

namespace ga {

	namespace detail {

		// Specialization of _addition_level3<LeftExpression, RightExpression> with simple bind or sort-and-bind patterns.
		template<class LeftExpression, class RightExpression>
		struct _addition_level4 {
			typedef std::conditional_t<
				lt_v<LeftExpression, RightExpression>,
				add_t<LeftExpression, RightExpression>, // bind
				add_t<RightExpression, LeftExpression> // sort and bind
			> type;
		};
		
		// Specializations of addition<LeftExpression, RightExpression> with at least one constant argument (simplify).
		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _addition_level4<constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<LeftValue + RightValue> type; // A + B = C (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _addition_level4<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> > > {
			typedef product_t<constant_value<LeftValue * RightValue + 1>, power_t<constant_value<RightValue>, constant_value<-1> >, real_mapping> type; // A + 1 / B = (A * B + 1) / B (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _addition_level4<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue> > {
			typedef product_t<constant_value<1 + RightValue * LeftValue>, power_t<constant_value<LeftValue>, constant_value<-1> >, real_mapping> type; // 1 / A + B = (1 + B * A) / A (simplify)
		};

		template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightValue>
		struct _addition_level4<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, power<constant_value<RightValue>, constant_value<-1> > > {
			typedef product_t<constant_value<LeftLeftValue * RightValue + LeftRightValue>, power_t<constant_value<LeftRightValue * RightValue>, constant_value<-1> >, real_mapping> type; // A / B + 1 / C = (A * C + B) / (B * C) (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
		struct _addition_level4<power<constant_value<LeftValue>, constant_value<-1> >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
			typedef product_t<constant_value<RightRightValue + LeftValue * RightLeftValue>, power_t<constant_value<LeftValue * RightRightValue>, constant_value<-1> >, real_mapping> type; // 1 / C + A / B = (B + C * A) / (C * B) (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _addition_level4<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> > > {
			typedef product_t<constant_value<RightValue + LeftValue>, power_t<constant_value<LeftValue * RightValue>, constant_value<-1> >, real_mapping> type; // 1 / B + 1 / C = (C + B) / (B * C) (simplify)
		};

		template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
		struct _addition_level4<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
			typedef product_t<constant_value<LeftLeftValue * RightRightValue + LeftRightValue * RightLeftValue>, power_t<constant_value<LeftRightValue * RightRightValue>, constant_value<-1> >, real_mapping> type; // A / B + C / D = (A * D + B * C) / (B * D) (simplify)
		};

		// Specializations of _addition_level3<LeftExpression, RightExpression> with some patterns to simplify (simplify).
		template<class LeftExpression, class RightExpression, class Enable = void>
		struct _addition_level3 {
			typedef typename _addition_level4<LeftExpression, RightExpression>::type type;
		};

		template<class LeftLeftArgument, class CommonArgument>
		struct _addition_level3<mul<LeftLeftArgument, CommonArgument>, CommonArgument, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, constant_value<1> >, add_t<LeftLeftArgument, constant_value<1> >, add_t<constant_value<1>, LeftLeftArgument> > > > {
			typedef product_t<addition_t<LeftLeftArgument, constant_value<1> >, CommonArgument, real_mapping> type; // (P * A) + A = (P + 1) * A (simplify)
		};

		template<class LeftLeftArgument, class... CommonArguments>
		struct _addition_level3<mul<LeftLeftArgument, CommonArguments...>, mul<CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, constant_value<1> >, add_t<LeftLeftArgument, constant_value<1> >, add_t<constant_value<1>, LeftLeftArgument > > > > {
			typedef product_t<addition_t<LeftLeftArgument, constant_value<1> >, mul_t<CommonArguments...>, real_mapping> type; // (P * A * ...) + (A * ...) = (P + 1) * (A * ...) (simplify)
		};

		template<class CommonArgument, class RightLeftArgument>
		struct _addition_level3<CommonArgument, mul<RightLeftArgument, CommonArgument>, std::enable_if_t<!is_any_v<addition_t<constant_value<1>, RightLeftArgument>, add_t<constant_value<1>, RightLeftArgument>, add_t<RightLeftArgument, constant_value<1> > > > > {
			typedef product_t<addition_t<constant_value<1>, RightLeftArgument>, CommonArgument, real_mapping> type; // A + (P * A) = (1 + P) * A (simplify)
		};

		template<class... CommonArguments, class RightLeftArgument>
		struct _addition_level3<mul<CommonArguments...>, mul<RightLeftArgument, CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<constant_value<1>, RightLeftArgument>, add_t<constant_value<1>, RightLeftArgument>, add_t<RightLeftArgument, constant_value<1> > > > > {
			typedef product_t<addition_t<constant_value<1>, RightLeftArgument>, mul_t<CommonArguments...>, real_mapping> type; // A * ... + (P * A * ...) = (1 + P) * (A * ...) (simplify)
		};

		template<class LeftLeftArgument, class CommmonArgument, class RightLeftArgument>
		struct _addition_level3<mul<LeftLeftArgument, CommmonArgument>, mul<RightLeftArgument, CommmonArgument>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, RightLeftArgument>, add_t<LeftLeftArgument, RightLeftArgument>, add_t<RightLeftArgument, LeftLeftArgument> > > > {
			typedef product_t<addition_t<LeftLeftArgument, RightLeftArgument>, CommmonArgument, real_mapping> type; // (P * A) + (Q * A) = (P + Q) * A (simplify)
		};

		template<class LeftLeftArgument, class... CommonArguments, class RightLeftArgument>
		struct _addition_level3<mul<LeftLeftArgument, CommonArguments...>, mul<RightLeftArgument, CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, RightLeftArgument>, add_t<LeftLeftArgument, RightLeftArgument>, add_t<RightLeftArgument, LeftLeftArgument> > > > {
			typedef product_t<addition_t<LeftLeftArgument, RightLeftArgument>, mul_t<CommonArguments...>, real_mapping> type; // (P * A * ...) + (Q * A * ...) = (P + Q) * (A * ...) (simplify)
		};

		template<class CommonExpression>
		struct _addition_level3<CommonExpression, CommonExpression> {
			typedef product_t<constant_value<2>, CommonExpression, real_mapping> type; // A + A = 2 * A (simplify)
		};

		// Specialization of _addition_level2<LeftExpression, RightExpression>.
		template<class LeftExpression, class RightExpression>
		struct _addition_level2 {
			typedef typename _addition_level3<LeftExpression, RightExpression>::type type;
		};

		template<class LeftArgument>
		struct _addition_level2<LeftArgument, constant_value<0> > {
			typedef LeftArgument type; // simplify
		};

		template<class RightExpression>
		struct _addition_level2<constant_value<0>, RightExpression> {
			typedef RightExpression type; // simplify
		};

		template<>
		struct _addition_level2<constant_value<0>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		// Specialization of _addition_level1<LeftExpression, RightExpression> (merge add<...>).
		template<class LeftExpression, class RightExpression, class Enable = void>
		struct _addition_level1;

		template<class LeftExpression, class RightExpression>
		struct _addition_level1<LeftExpression, RightExpression, std::enable_if_t<!(is_function_v<name_t::add, LeftExpression> || is_function_v<name_t::add, RightExpression>)> > {
			typedef typename _addition_level2<LeftExpression, RightExpression>::type type;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct _addition_level1<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<le_v<LeftArgument, RightArgument> > > {
			typedef addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, add<RightArgument, RightNextArguments...> > > type; // merge
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct _addition_level1<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftArgument> > > {
			typedef addition_t<RightArgument, addition_t<add<LeftArgument, LeftNextArguments...>, add_t<RightNextArguments...> > > type; // merge
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct _addition_level1<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::add, LeftExpression> && lt_v<RightArgument, LeftExpression> > > {
			typedef addition_t<RightArgument, addition_t<LeftExpression, add_t<RightNextArguments...> > > type; // merge
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct _addition_level1<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::add, LeftExpression> && le_v<LeftExpression, RightArgument> && !std::is_same_v<addition_t<LeftExpression, RightArgument>, add<LeftExpression, RightArgument> > > > {
			typedef addition_t<addition_t<LeftExpression, RightArgument>, add_t<RightNextArguments...> > type; // simplification found (simplify-and-merge)
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct _addition_level1<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::add, LeftExpression> && le_v<LeftExpression, RightArgument> && std::is_same_v<addition_t<LeftExpression, RightArgument>, add<LeftExpression, RightArgument> > > > {
			typedef add_t<LeftExpression, RightArgument, RightNextArguments...> type; // no simplification found (bind)
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct _addition_level1<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!is_function_v<name_t::add, RightExpression> && le_v<LeftArgument, RightExpression> > > {
			typedef addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, RightExpression> > type; // merge
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct _addition_level1<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!is_function_v<name_t::add, RightExpression> && lt_v<RightExpression, LeftArgument> > > {
			typedef addition_t<RightExpression, add<LeftArgument, LeftNextArguments...> > type; // merge
		};

		// Specialization of _addition<LeftExpression, RightExpression> (add components).
		template<class LeftExpression, class RightExpression>
		struct _addition {
			typedef typename _addition_level1<LeftExpression, RightExpression>::type type;
		};

		template<class LeftCoefficient, class LeftBasisBlade, class RightCoefficient, class RightBasisBlade>
		struct _addition<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > {
			typedef std::conditional_t<
				lt_v<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> >,
				add_t<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> >, // bind
				add_t<component<RightCoefficient, RightBasisBlade>, component<LeftCoefficient, LeftBasisBlade> > // sort and bind
			> type;
		};

		template<class LeftCoefficient, class CommonBasisBlade, class RightCoefficient>
		struct _addition<component<LeftCoefficient, CommonBasisBlade>, component<RightCoefficient, CommonBasisBlade> > {
			typedef component_t<addition_t<LeftCoefficient, RightCoefficient>, CommonBasisBlade> type; // A * Ei + B * Ei = (A + B) * Ei (simplify)
		};

		template<class RightCoefficient, class RightBasisBlade>
		struct _addition<component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >, component<RightCoefficient, RightBasisBlade> > {
			typedef component<RightCoefficient, RightBasisBlade> type; // 0 * 1 + A * Ej = A * Ej (simplify)
		};

		template<class LeftCoefficient, class LeftBasisBlade>
		struct _addition<component<LeftCoefficient, LeftBasisBlade>, component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > > {
			typedef component<LeftCoefficient, LeftBasisBlade> type; // A * Ei + 0 * 1 = A * Ei (simplify)
		};

		template<>
		struct _addition<component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >, component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > > {
			typedef component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > type; // 0 * 1 + 0 * 1 = 0 * 1 (simplify)
		};

	}

}

#endif // __FUTURE_GA_EXPRESSION_ADDITION_HPP__
