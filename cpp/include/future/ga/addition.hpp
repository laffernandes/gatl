#ifndef __FUTURE_GA_ADDITION_HPP__
#define __FUTURE_GA_ADDITION_HPP__

namespace ga {

	namespace detail {

		// Specializations of addition<LeftExpression, RightExpression> with add<...>.
		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct addition<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<le_v<LeftArgument, RightArgument> > > {
			typedef addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, add<RightArgument, RightNextArguments...> > > type; // merge
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct addition<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftArgument> > > {
			typedef addition_t<RightArgument, addition_t<add<LeftArgument, LeftNextArguments...>, add_t<RightNextArguments...> > > type; // merge
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct addition<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftExpression> > > {
			typedef addition_t<RightArgument, addition_t<LeftExpression, add_t<RightNextArguments...> > > type; // merge
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct addition<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<le_v<LeftExpression, RightArgument> && !std::is_same_v<addition_t<LeftExpression, RightArgument>, add<LeftExpression, RightArgument> > > > {
			typedef addition_t<addition_t<LeftExpression, RightArgument>, add_t<RightNextArguments...> > type; // simplification found (simplify-and-merge)
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct addition<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<le_v<LeftExpression, RightArgument> && std::is_same_v<addition_t<LeftExpression, RightArgument>, add<LeftExpression, RightArgument> > > > {
			typedef add_t<LeftExpression, RightArgument, RightNextArguments...> type; // no simplification found (bind)
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct addition<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<le_v<LeftArgument, RightExpression> > > {
			typedef addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, RightExpression> > type; // merge
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct addition<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<lt_v<RightExpression, LeftArgument> > > {
			typedef addition_t<RightExpression, add<LeftArgument, LeftNextArguments...> > type; // merge
		};

		// Specialization of addition<LeftExpression, RightExpression> with simple bind or sort-and-bind patterns.
		template<class LeftExpression, class RightExpression, class Enable = void>
		struct _addition_bind_sorted;
		
		template<class LeftExpression, class RightExpression>
		struct _addition_bind_sorted<LeftExpression, RightExpression, std::enable_if_t<lt_v<LeftExpression, RightExpression> > > {
			typedef add_t<LeftExpression, RightExpression> type; // bind
		};

		template<class LeftExpression, class RightExpression>
		struct _addition_bind_sorted<LeftExpression, RightExpression, std::enable_if_t<lt_v<RightExpression, LeftExpression> > > {
			typedef add_t<RightExpression, LeftExpression> type; // sort and bind
		};

		template<class LeftExpression, class RightExpression>
		using _addition_bind_sorted_t = typename _addition_bind_sorted<LeftExpression, RightExpression>::type;

		template<default_integral_t LeftValue, id_t RightId, std::size_t RightIndex>
		struct addition<constant_value<LeftValue>, get_value<RightId, RightIndex> > {
			typedef add_t<constant_value<LeftValue>, get_value<RightId, RightIndex> > type; // bind
		};

		template<id_t LeftId, std::size_t LeftIndex, default_integral_t RightValue>
		struct addition<get_value<LeftId, LeftIndex>, constant_value<RightValue> > {
			typedef add_t<constant_value<RightValue>, get_value<LeftId, LeftIndex> > type; // sort and bind
		};

		template<default_integral_t LeftValue>
		struct addition<constant_value<LeftValue>, stored_value> {
			typedef add_t<constant_value<LeftValue>, stored_value> type; // bind
		};

		template<default_integral_t RightValue>
		struct addition<stored_value, constant_value<RightValue> > {
			typedef add_t<constant_value<RightValue>, stored_value> type; // sort and bind
		};

		template<default_integral_t LeftValue, name_t RightName, class... RightArguments>
		struct addition<constant_value<LeftValue>, function<RightName, RightArguments...> > {
			typedef _addition_bind_sorted_t<constant_value<LeftValue>, function<RightName, RightArguments...> > type; // bind or sort-and-bind
		};

		template<name_t LeftName, class... LeftArguments, default_integral_t RightValue>
		struct addition<function<LeftName, LeftArguments...>, constant_value<RightValue> > {
			typedef _addition_bind_sorted_t<function<LeftName, LeftArguments...>, constant_value<RightValue> > type; // bind or sort-and-bind
		};

		template<id_t LeftId, std::size_t LeftIndex, id_t RightId, std::size_t RightIndex>
		struct addition<get_value<LeftId, LeftIndex>, get_value<RightId, RightIndex>, std::enable_if_t<LeftId != RightId && LeftIndex != RightIndex> > {
			typedef _addition_bind_sorted_t<get_value<LeftId, LeftIndex>, get_value<RightId, RightIndex> > type; // bind or sort-and-bind
		};

		template<id_t LeftId, std::size_t LeftIndex>
		struct addition<get_value<LeftId, LeftIndex>, stored_value> {
			typedef add_t<get_value<LeftId, LeftIndex>, stored_value> type; // bind
		};

		template<id_t RightId, std::size_t RightIndex>
		struct addition<stored_value, get_value<RightId, RightIndex> > {
			typedef add_t<get_value<RightId, RightIndex>, stored_value> type; // sort and bind
		};

		template<id_t LeftId, std::size_t LeftIndex, name_t RightName, class... RightArguments>
		struct addition<get_value<LeftId, LeftIndex>, function<RightName, RightArguments...> > {
			typedef _addition_bind_sorted_t<get_value<LeftId, LeftIndex>, function<RightName, RightArguments...> > type; // bind or sort-and-bind
		};

		template<name_t LeftName, class... LeftArguments, id_t RightId, std::size_t RightIndex>
		struct addition<function<LeftName, LeftArguments...>, get_value<RightId, RightIndex> > {
			typedef _addition_bind_sorted_t<function<LeftName, LeftArguments...>, get_value<RightId, RightIndex> > type; // bind or sort-and-bind
		};

		template<name_t RightName, class... RightArguments>
		struct addition<stored_value, function<RightName, RightArguments...> > {
			typedef _addition_bind_sorted_t<stored_value, function<RightName, RightArguments...> > type; // bind or sort-and-bind
		};

		template<name_t LeftName, class... LeftArguments>
		struct addition<function<LeftName, LeftArguments...>, stored_value> {
			typedef _addition_bind_sorted_t<function<LeftName, LeftArguments...>, stored_value> type; // bind or sort-and-bind
		};

		template<name_t LeftName, class... LeftArguments, name_t RightName, class... RightArguments>
		struct addition<function<LeftName, LeftArguments...>, function<RightName, RightArguments...>, std::enable_if_t<!std::is_same_v<function<LeftName, LeftArguments...>, function<RightName, RightArguments...> > > > {
			typedef _addition_bind_sorted_t<function<LeftName, LeftArguments...>, function<RightName, RightArguments...> > type; // bind or sort-and-bind
		};

		// Specialization of addition<component<...>, component<...> > (merge or simplify).
		template<class LeftCoefficient, class LeftBasisBlade, class RightCoefficient, class RightBasisBlade>
		struct addition<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, std::enable_if_t<!std::is_same_v<LeftBasisBlade, RightBasisBlade> && !(std::is_same_v<LeftCoefficient, constant_value<0> > || std::is_same_v<RightCoefficient, constant_value<0> >)> > {
			typedef _addition_bind_sorted_t<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > type; // bind or sort-and-bind
		};

		template<class LeftCoefficient, class CommonBasisBlade, class RightCoefficient>
		struct addition<component<LeftCoefficient, CommonBasisBlade>, component<RightCoefficient, CommonBasisBlade> > {
			typedef component_t<addition_t<LeftCoefficient, RightCoefficient>, CommonBasisBlade> type; // A * Ei + B * Ei = (A + B) * Ei (simplify)
		};

		template<class RightCoefficient, class RightBasisBlade>
		struct addition<component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >, component<RightCoefficient, RightBasisBlade> > {
			typedef component<RightCoefficient, RightBasisBlade> type; // 0 * 1 + A * Ej = A * Ej (simplify)
		};

		template<class LeftCoefficient, class LeftBasisBlade>
		struct addition<component<LeftCoefficient, LeftBasisBlade>, component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > > {
			typedef component<LeftCoefficient, LeftBasisBlade> type; // A * Ei + 0 * 1 = A * Ei (simplify)
		};

		template<>
		struct addition<component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >, component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > > {
			typedef component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > type; // 0 * 1 + 0 * 1 = 0 * 1 (simplify)
		};

		// Specializations of addition<LeftExpression, RightExpression> with at least one constant argument (simplify).
		template<class LeftConstantArgument, class CommonArgument>
		struct addition<mul<LeftConstantArgument, CommonArgument>, CommonArgument, std::enable_if_t<is_constant_expression_v<LeftConstantArgument> && !is_any_v<addition_t<LeftConstantArgument, constant_value<1> >, add_t<LeftConstantArgument, constant_value<1> >, add_t<constant_value<1>, LeftConstantArgument> > > > {
			typedef product_t<addition_t<LeftConstantArgument, constant_value<1> >, CommonArgument, real_mapping> type; // (P * A) + A = (P + 1) * A (simplify)
		};

		template<class LeftConstantArgument, class... CommonArguments>
		struct addition<mul<LeftConstantArgument, CommonArguments...>, mul<CommonArguments...>, std::enable_if_t<is_constant_expression_v<LeftConstantArgument> && !is_any_v<addition_t<LeftConstantArgument, constant_value<1> >, add_t<LeftConstantArgument, constant_value<1> >, add_t<constant_value<1>, LeftConstantArgument > > > > {
			typedef product_t<addition_t<LeftConstantArgument, constant_value<1> >, mul_t<CommonArguments...>, real_mapping> type; // (P * A * ...) + (A * ...) = (P + 1) * (A * ...) (simplify)
		};

		template<class CommonArgument, class RightConstantArgument>
		struct addition<CommonArgument, mul<RightConstantArgument, CommonArgument>, std::enable_if_t<is_constant_expression_v<RightConstantArgument> && !is_any_v<addition_t<constant_value<1>, RightConstantArgument>, add_t<constant_value<1>, RightConstantArgument>, add_t<RightConstantArgument, constant_value<1> > > > > {
			typedef product_t<addition_t<constant_value<1>, RightConstantArgument>, CommonArgument, real_mapping> type; // A + (P * A) = (1 + P) * A (simplify)
		};

		template<class... CommonArguments, class RightConstantArgument>
		struct addition<mul<CommonArguments...>, mul<RightConstantArgument, CommonArguments...>, std::enable_if_t<is_constant_expression_v<RightConstantArgument> && !is_any_v<addition_t<constant_value<1>, RightConstantArgument>, add_t<constant_value<1>, RightConstantArgument>, add_t<RightConstantArgument, constant_value<1> > > > > {
			typedef product_t<addition_t<constant_value<1>, RightConstantArgument>, mul_t<CommonArguments...>, real_mapping> type; // A * ... + (P * A * ...) = (1 + P) * (A * ...) (simplify)
		};

		template<class LeftConstantArgument, class CommmonArgument, class RightConstantArgument>
		struct addition<mul<LeftConstantArgument, CommmonArgument>, mul<RightConstantArgument, CommmonArgument>, std::enable_if_t<is_constant_expression_v<LeftConstantArgument> && is_constant_expression_v<RightConstantArgument> && !is_any_v<addition_t<LeftConstantArgument, RightConstantArgument>, add_t<LeftConstantArgument, RightConstantArgument>, add_t<RightConstantArgument, LeftConstantArgument> > > > {
			typedef product_t<addition_t<LeftConstantArgument, RightConstantArgument>, CommmonArgument, real_mapping> type; // (P * A) + (Q * A) = (P + Q) * A (simplify)
		};

		template<class LeftConstantArgument, class... CommonArguments, class RightConstantArgument>
		struct addition<mul<LeftConstantArgument, CommonArguments...>, mul<RightConstantArgument, CommonArguments...>, std::enable_if_t<is_constant_expression_v<LeftConstantArgument> && is_constant_expression_v<RightConstantArgument> && !is_any_v<addition_t<LeftConstantArgument, RightConstantArgument>, add_t<LeftConstantArgument, RightConstantArgument>, add_t<RightConstantArgument, LeftConstantArgument> > > > {
			typedef product_t<addition_t<LeftConstantArgument, RightConstantArgument>, mul_t<CommonArguments...>, real_mapping> type; // (P * A * ...) + (Q * A * ...) = (P + Q) * (A * ...) (simplify)
		};

		// Specializations of addition<LeftExpression, RightExpression> with some patterns to simplify (simplify).
		template<id_t CommonId, std::size_t CommonIndex>
		struct addition<get_value<CommonId, CommonIndex>, get_value<CommonId, CommonIndex> > {
			typedef product_t<constant_value<2>, get_value<CommonId, CommonIndex>, real_mapping> type; // A + A = 2 * A (simplify)
		};

		template<name_t CommonName, class... CommonArguments>
		struct addition<function<CommonName, CommonArguments...>, function<CommonName, CommonArguments...> > {
			typedef product_t<constant_value<2>, function<CommonName, CommonArguments...>, real_mapping> type; // A + A = 2 * A (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<LeftValue + RightValue> type; // A + B = C (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> > > {
			typedef product_t<constant_value<LeftValue * RightValue + 1>, power_t<constant_value<RightValue>, constant_value<-1> >, real_mapping> type; // A + 1 / B = (A * B + 1) / B (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue> > {
			typedef product_t<constant_value<1 + RightValue * LeftValue>, power_t<constant_value<LeftValue>, constant_value<-1> >, real_mapping> type; // 1 / A + B = (1 + B * A) / A (simplify)
		};

		template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightValue>
		struct addition<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, power<constant_value<RightValue>, constant_value<-1> > > {
			typedef product_t<constant_value<LeftLeftValue * RightValue + LeftRightValue>, power_t<constant_value<LeftRightValue * RightValue>, constant_value<-1> >, real_mapping> type; // A / B + 1 / C = (A * C + B) / (B * C) (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
		struct addition<power<constant_value<LeftValue>, constant_value<-1> >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
			typedef product_t<constant_value<RightRightValue + LeftValue * RightLeftValue>, power_t<constant_value<LeftValue * RightRightValue>, constant_value<-1> >, real_mapping> type; // 1 / C + A / B = (B + C * A) / (C * B) (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> > > {
			typedef product_t<constant_value<RightValue + LeftValue>, power_t<constant_value<LeftValue * RightValue>, constant_value<-1> >, real_mapping> type; // 1 / B + 1 / C = (C + B) / (B * C) (simplify)
		};

		template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
		struct addition<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
			typedef product_t<constant_value<LeftLeftValue * RightRightValue + LeftRightValue * RightLeftValue>, power_t<constant_value<LeftRightValue * RightRightValue>, constant_value<-1> >, real_mapping> type; // A / B + C / D = (A * D + B * C) / (B * D) (simplify)
		};

	}

}

#endif // __FUTURE_GA_ADDITION_HPP__
