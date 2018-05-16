#ifndef __FUTURE_GA_ADDITION_HPP__
#define __FUTURE_GA_ADDITION_HPP__

namespace ga {

	namespace detail {

		// Specializations of addition<add<...>, add<...> > (merge).
		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct addition<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftArgument> > > {
			typedef addition_t<RightArgument, addition_t<add_t<LeftArgument, LeftNextArguments...>, add_t<RightNextArguments...> > > type;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct addition<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<!lt_v<RightArgument, LeftArgument> > > {
			typedef addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, add_t<RightArgument, RightNextArguments...> > > type;
		};

		// Specializations of addition<LeftExpression, add<...> > and addition<add<...>, RightExpression> (merge, simplify-and-merge, or bind).
		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct addition<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftExpression> && !std::is_same_v<LeftExpression, constant_value<0> > > > {
			typedef addition_t<RightArgument, addition_t<LeftExpression, add_t<RightNextArguments...> > > type; // merge
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct addition<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<LeftExpression, RightArgument> && !(std::is_same_v<addition_t<LeftExpression, RightArgument>, add_t<LeftExpression, RightArgument> > || std::is_same_v<LeftExpression, constant_value<0> >) > > {
			typedef addition_t<addition_t<LeftExpression, RightArgument>, add_t<RightNextArguments...> > type; // simplification found (simplify-and-merge)
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct addition<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<LeftExpression, RightArgument> && std::is_same_v<addition_t<LeftExpression, RightArgument>, add_t<LeftExpression, RightArgument> > && !std::is_same_v<LeftExpression, constant_value<0> > > > {
			typedef add_t<LeftExpression, RightArgument, RightNextArguments...> type; // no simplification found, end of recursion (bind)
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct addition<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<lt_v<RightExpression, LeftArgument> && !std::is_same_v<RightExpression, constant_value<0> > > > {
			typedef addition_t<RightExpression, add_t<LeftArgument, LeftNextArguments...> > type; // merge
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct addition<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!(lt_v<RightExpression, LeftArgument> || std::is_same_v<RightExpression, constant_value<0> >) > > {
			typedef addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, RightExpression> > type; // merge
		};

		// Specialization of addition<component<...>, component<...> > (simplify).
		template<class LeftCoefficient, class CommonBasisBlade, class RightCoefficient>
		struct addition<component<LeftCoefficient, CommonBasisBlade>, component<RightCoefficient, CommonBasisBlade>, std::enable_if_t<!(std::is_same_v<LeftCoefficient, constant_value<0> > || std::is_same_v<RightCoefficient, constant_value<0> >)> > {
			typedef component_t<addition_t<LeftCoefficient, RightCoefficient>, CommonBasisBlade> type; // A * Ei + B * Ei = (A + B) * Ei (simplify)
		};

		template<class LeftBasisBlade, class RightCoefficient, class RightBasisBlade>
		struct addition<component<constant_value<0>, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > {
			typedef component<RightCoefficient, RightBasisBlade> type; // 0 * Ei + A * Ej = A * Ej (simplify)
		};

		template<class LeftCoefficient, class LeftBasisBlade, class RightBasisBlade>
		struct addition<component<LeftCoefficient, LeftBasisBlade>, component<constant_value<0>, RightBasisBlade> > {
			typedef component<LeftCoefficient, LeftBasisBlade> type; // A * Ei + 0 * Ej = A * Ej (simplify)
		};

		template<class LeftBasisBlade, class RightBasisBlade>
		struct addition<component<constant_value<0>, LeftBasisBlade>, component<constant_value<0>, RightBasisBlade> > {
			typedef component_t<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > type; // 0 * Ei + 0 * Ej = 0 * 1 (simplify)
		};

		// Specializations of addition<LeftExpression, RightExpression> with general arguments (simplify or bind).
		template<class LeftExpression, class RightExpression>
		struct addition<LeftExpression, RightExpression, std::enable_if_t<!(std::is_same_v<LeftExpression, constant_value<0> > || std::is_same_v<RightExpression, constant_value<0> >) && lt_v<LeftExpression, RightExpression> > > {
			typedef add_t<LeftExpression, RightExpression> type; // A + B, end of recursion (bind)
		};

		template<class LeftExpression, class RightExpression>
		struct addition<LeftExpression, RightExpression, std::enable_if_t<!(std::is_same_v<LeftExpression, constant_value<0> > || std::is_same_v<RightExpression, constant_value<0> >) && lt_v<RightExpression, LeftExpression> > > {
			typedef add_t<RightExpression, LeftExpression> type; // A + B = B + A (sort and bind)
		};

		template<class CommonExpression>
		struct addition<CommonExpression, CommonExpression, std::enable_if_t<!std::is_same_v<CommonExpression, constant_value<0> > > > {
			typedef product_t<constant_value<2>, CommonExpression, real_mapping> type; // A + A = 2 * A, end of recursion (simplify)
		};

		// Specializations of addition<LeftExpression, RightExpression> with at least one constant_value argument (simplify).
		template<class RightExpression>
		struct addition<constant_value<0>, RightExpression, std::enable_if_t<!std::is_same_v<RightExpression, constant_value<0> > >> {
			typedef RightExpression type; // 0 + A = A, end of recursion (simplify)
		};

		template<class LeftExpression>
		struct addition<LeftExpression, constant_value<0>, std::enable_if_t<!std::is_same_v<LeftExpression, constant_value<0> > > > {
			typedef LeftExpression type; // A + 0 = A, end of recursion (simplify)
		};

		template<class LeftConstantArgument, class CommonArgument>
		struct addition<mul<LeftConstantArgument, CommonArgument>, CommonArgument, std::enable_if_t<is_constant_expression_v<LeftConstantArgument> && !is_any_v<addition_t<LeftConstantArgument, constant_value<1> >, add_t<LeftConstantArgument, constant_value<1> >, add_t<constant_value<1>, LeftConstantArgument> > && !std::is_same_v<CommonArgument, constant_value<0> > > > {
			typedef product_t<addition_t<LeftConstantArgument, constant_value<1> >, CommonArgument, real_mapping> type; // (P * A) + A = (P + 1) * A (simplify)
		};

		template<class LeftConstantArgument, class... CommonArguments>
		struct addition<mul<LeftConstantArgument, CommonArguments...>, mul<CommonArguments...>, std::enable_if_t<is_constant_expression_v<LeftConstantArgument> && !is_any_v<addition_t<LeftConstantArgument, constant_value<1> >, add_t<LeftConstantArgument, constant_value<1> >, add_t<constant_value<1>, LeftConstantArgument > > > > {
			typedef product_t<addition_t<LeftConstantArgument, constant_value<1> >, mul_t<CommonArguments...>, real_mapping> type; // (P * A * ...) + (A * ...) = (P + 1) * (A * ...) (simplify)
		};

		template<class CommonArgument, class RightConstantArgument>
		struct addition<CommonArgument, mul<RightConstantArgument, CommonArgument>, std::enable_if_t<is_constant_expression_v<RightConstantArgument> && !is_any_v<addition_t<constant_value<1>, RightConstantArgument>, add_t<constant_value<1>, RightConstantArgument>, add_t<RightConstantArgument, constant_value<1> > > && !std::is_same_v<CommonArgument, constant_value<0> > > > {
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

		// Specializations of addition<LeftExpression, RightExpression> with some patterns of constant arguments (simplify).
		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<constant_value<LeftValue>, constant_value<RightValue>, std::enable_if_t<LeftValue != 0 && RightValue != 0> > {
			typedef constant_value<LeftValue + RightValue> type; // A + B = C, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> >, std::enable_if_t<LeftValue != 0> > {
			typedef product_t<constant_value<LeftValue * RightValue + 1>, power_t<constant_value<RightValue>, constant_value<-1> >, real_mapping> type; // A + 1 / B = (A * B + 1) / B (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue>, std::enable_if_t<RightValue != 0> > {
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
