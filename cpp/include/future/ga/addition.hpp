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
		struct addition<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftExpression> && !std::is_same_v<LeftExpression, constant<0> > > > {
			typedef addition_t<RightArgument, addition_t<LeftExpression, add_t<RightNextArguments...> > > type; // merge
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct addition<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<LeftExpression, RightArgument> && !(std::is_same_v<addition_t<LeftExpression, RightArgument>, add_t<LeftExpression, RightArgument> > || std::is_same_v<LeftExpression, constant<0> >) > > {
			typedef addition_t<addition_t<LeftExpression, RightArgument>, add_t<RightNextArguments...> > type; // simplification found (simplify-and-merge)
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct addition<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<LeftExpression, RightArgument> && std::is_same_v<addition_t<LeftExpression, RightArgument>, add_t<LeftExpression, RightArgument> > && !std::is_same_v<LeftExpression, constant<0> > > > {
			typedef add_t<LeftExpression, RightArgument, RightNextArguments...> type; // no simplification found, end of recursion (bind)
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct addition<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<lt_v<RightExpression, LeftArgument> && !std::is_same_v<RightExpression, constant<0> > > > {
			typedef addition_t<RightExpression, add_t<LeftArgument, LeftNextArguments...> > type; // merge
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct addition<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!(lt_v<RightExpression, LeftArgument> || std::is_same_v<RightExpression, constant<0> >) > > {
			typedef addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, RightExpression> > type; // merge
		};

		// Specialization of addition<component<...>, component<...> > (simplify).
		template<class LeftCoefficient, default_bitset_t BasisVectors, class RightCoefficient>
		struct addition<component<LeftCoefficient, constant_basis_blade<BasisVectors> >, component<RightCoefficient, constant_basis_blade<BasisVectors> > > {
			typedef make_component_t<addition_t<LeftCoefficient, RightCoefficient>, constant_basis_blade<BasisVectors> > type; // A * Ei + B * Ei = (A + B) * Ei or simpler, end of recursion (simplify)
		};

		// Specializations of addition<LeftExpression, RightExpression> with general arguments (simplify or bind).
		template<class LeftExpression, class RightExpression>
		struct addition<LeftExpression, RightExpression, std::enable_if_t<!(std::is_same_v<LeftExpression, constant<0> > || std::is_same_v<RightExpression, constant<0> >) && lt_v<LeftExpression, RightExpression> > > {
			typedef add_t<LeftExpression, RightExpression> type; // A + B, end of recursion (bind)
		};

		template<class LeftExpression, class RightExpression>
		struct addition<LeftExpression, RightExpression, std::enable_if_t<!(std::is_same_v<LeftExpression, constant<0> > || std::is_same_v<RightExpression, constant<0> >) && lt_v<RightExpression, LeftExpression> > > {
			typedef add_t<RightExpression, LeftExpression> type; // A + B = B + A (sort and bind)
		};

		template<class CommonExpression>
		struct addition<CommonExpression, CommonExpression, std::enable_if_t<!std::is_same_v<CommonExpression, constant<0> > > > {
			typedef product_t<constant<2>, CommonExpression, real_mapping> type; // A + A = 2 * A, end of recursion (simplify)
		};

		// Specializations of addition<LeftExpression, RightExpression> with at least one constant argument (simplify).
		template<class RightExpression>
		struct addition<constant<0>, RightExpression, std::enable_if_t<!std::is_same_v<RightExpression, constant<0> > >> {
			typedef RightExpression type; // 0 + A = A, end of recursion (simplify)
		};

		template<class LeftExpression>
		struct addition<LeftExpression, constant<0>, std::enable_if_t<!std::is_same_v<LeftExpression, constant<0> > > > {
			typedef LeftExpression type; // A + 0 = A, end of recursion (simplify)
		};

		//TODO Tentativa de generalização
		/**/
		template<class LeftConstantArgument, class CommonArgument>
		struct addition<mul<LeftConstantArgument, CommonArgument>, CommonArgument, std::enable_if_t<is_constant_expression_v<LeftConstantArgument> && !is_any_v<addition_t<LeftConstantArgument, constant<1> >, add_t<LeftConstantArgument, constant<1> >, add_t<constant<1>, LeftConstantArgument> > && !std::is_same_v<CommonArgument, constant<0> > > > {
			typedef product_t<addition_t<LeftConstantArgument, constant<1> >, CommonArgument, real_mapping> type; // (P * A) + A = (P + 1) * A (simplify)
		};

		template<class LeftConstantArgument, class... CommonArguments>
		struct addition<mul<LeftConstantArgument, CommonArguments...>, mul<CommonArguments...>, std::enable_if_t<is_constant_expression_v<LeftConstantArgument> && !is_any_v<addition_t<LeftConstantArgument, constant<1> >, add_t<LeftConstantArgument, constant<1> >, add_t<constant<1>, LeftConstantArgument > > > > {
			typedef product_t<addition_t<LeftConstantArgument, constant<1> >, mul_t<CommonArguments...>, real_mapping> type; // (P * A * ...) + (A * ...) = (P + 1) * (A * ...) (simplify)
		};

		template<class CommonArgument, class RightConstantArgument>
		struct addition<CommonArgument, mul<RightConstantArgument, CommonArgument>, std::enable_if_t<is_constant_expression_v<RightConstantArgument> && !is_any_v<addition_t<constant<1>, RightConstantArgument>, add_t<constant<1>, RightConstantArgument>, add_t<RightConstantArgument, constant<1> > > && !std::is_same_v<CommonArgument, constant<0> > > > {
			typedef product_t<addition_t<constant<1>, RightConstantArgument>, CommonArgument, real_mapping> type; // A + (P * A) = (1 + P) * A (simplify)
		};

		template<class... CommonArguments, class RightConstantArgument>
		struct addition<mul<CommonArguments...>, mul<RightConstantArgument, CommonArguments...>, std::enable_if_t<is_constant_expression_v<RightConstantArgument> && !is_any_v<addition_t<constant<1>, RightConstantArgument>, add_t<constant<1>, RightConstantArgument>, add_t<RightConstantArgument, constant<1> > > > > {
			typedef product_t<addition_t<constant<1>, RightConstantArgument>, mul_t<CommonArguments...>, real_mapping> type; // A * ... + (P * A * ...) = (1 + P) * (A * ...) (simplify)
		};

		template<class LeftConstantArgument, class CommmonArgument, class RightConstantArgument>
		struct addition<mul<LeftConstantArgument, CommmonArgument>, mul<RightConstantArgument, CommmonArgument>, std::enable_if_t<is_constant_expression_v<LeftConstantArgument> && is_constant_expression_v<RightConstantArgument> && !is_any_v<addition_t<LeftConstantArgument, RightConstantArgument>, add_t<LeftConstantArgument, RightConstantArgument>, add_t<RightConstantArgument, LeftConstantArgument> > > > {
			typedef product_t<addition_t<LeftConstantArgument, RightConstantArgument>, CommmonArgument, real_mapping> type; // (P * A) + (Q * A) = (P + Q) * A (simplify)
		};

		template<class LeftConstantArgument, class... CommonArguments, class RightConstantArgument>
		struct addition<mul<LeftConstantArgument, CommonArguments...>, mul<RightConstantArgument, CommonArguments...>, std::enable_if_t<is_constant_expression_v<LeftConstantArgument> && is_constant_expression_v<RightConstantArgument> && !is_any_v<addition_t<LeftConstantArgument, RightConstantArgument>, add_t<LeftConstantArgument, RightConstantArgument>, add_t<RightConstantArgument, LeftConstantArgument> > > > {
			typedef product_t<addition_t<LeftConstantArgument, RightConstantArgument>, mul_t<CommonArguments...>, real_mapping> type; // (P * A * ...) + (Q * A * ...) = (P + Q) * (A * ...) (simplify)
		};
		/*/
		template<default_integral_t LeftValue, class CommonArgument>
		struct addition<mul<constant<LeftValue>, CommonArgument>, CommonArgument, std::enable_if_t<!std::is_same_v<CommonArgument, constant<0> > > > {
			typedef product_t<constant<LeftValue + 1>, CommonArgument, real_mapping> type; // (P * A) + A = (P + 1) * A (simplify)
		};

		template<default_integral_t LeftValue, class... CommonArguments>
		struct addition<mul<constant<LeftValue>, CommonArguments...>, mul<CommonArguments...> > {
			typedef product_t<constant<LeftValue + 1>, mul_t<CommonArguments...>, real_mapping> type; // (P * A * ...) + (A * ...) = (P + 1) * (A * ...) (simplify)
		};

		template<class CommonArgument, default_integral_t RightValue>
		struct addition<CommonArgument, mul<constant<RightValue>, CommonArgument>, std::enable_if_t<!std::is_same_v<CommonArgument, constant<0> > > > {
			typedef product_t<constant<1 + RightValue>, CommonArgument, real_mapping> type; // A + (P * A) = (1 + P) * A (simplify)
		};

		template<class... CommonArguments, default_integral_t RightValue>
		struct addition<mul<CommonArguments...>, mul<constant<RightValue>, CommonArguments...> > {
			typedef product_t<constant<1 + RightValue>, mul_t<CommonArguments...>, real_mapping> type; // A * ... + (P * A * ...) = (1 + P) * (A * ...) (simplify)
		};

		template<default_integral_t LeftValue, class CommmonArgument, default_integral_t RightValue>
		struct addition<mul<constant<LeftValue>, CommmonArgument>, mul<constant<RightValue>, CommmonArgument> > {
			typedef product_t<constant<LeftValue + RightValue>, CommmonArgument, real_mapping> type; // (P * A) + (Q * A) = (P + Q) * A (simplify)
		};

		template<default_integral_t LeftValue, class... CommonArguments, default_integral_t RightValue>
		struct addition<mul<constant<LeftValue>, CommonArguments...>, mul<constant<RightValue>, CommonArguments...> > {
			typedef product_t<constant<LeftValue + RightValue>, mul_t<CommonArguments...>, real_mapping> type; // (P * A * ...) + (Q * A * ...) = (P + Q) * (A * ...) (simplify)
		};
		/**/

		// Specializations of addition<LeftExpression, RightExpression> with some patterns of constant arguments (simplify).
		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<constant<LeftValue>, constant<RightValue>, std::enable_if_t<LeftValue != 0 && RightValue != 0> > {
			typedef constant<LeftValue + RightValue> type; // A + B = C, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<constant<LeftValue>, power<constant<RightValue>, constant<-1> >, std::enable_if_t<LeftValue != 0> > {
			typedef product_t<constant<LeftValue * RightValue + 1>, power_t<constant<RightValue>, constant<-1> >, real_mapping> type; // A + 1 / B = (A * B + 1) / B (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<power<constant<LeftValue>, constant<-1> >, constant<RightValue>, std::enable_if_t<RightValue != 0> > {
			typedef product_t<constant<1 + RightValue * LeftValue>, power_t<constant<LeftValue>, constant<-1> >, real_mapping> type; // 1 / A + B = (1 + B * A) / A (simplify)
		};

		template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightValue>
		struct addition<mul<constant<LeftLeftValue>, power<constant<LeftRightValue>, constant<-1> > >, power<constant<RightValue>, constant<-1> > > {
			typedef product_t<constant<LeftLeftValue * RightValue + LeftRightValue>, power_t<constant<LeftRightValue * RightValue>, constant<-1> >, real_mapping> type; // A / B + 1 / C = (A * C + B) / (B * C) (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
		struct addition<power<constant<LeftValue>, constant<-1> >, mul<constant<RightLeftValue>, power<constant<RightRightValue>, constant<-1> > > > {
			typedef product_t<constant<RightRightValue + LeftValue * RightLeftValue>, power_t<constant<LeftValue * RightRightValue>, constant<-1> >, real_mapping> type; // 1 / C + A / B = (B + C * A) / (C * B) (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<power<constant<LeftValue>, constant<-1> >, power<constant<RightValue>, constant<-1> > > {
			typedef product_t<constant<RightValue + LeftValue>, power_t<constant<LeftValue * RightValue>, constant<-1> >, real_mapping> type; // 1 / B + 1 / C = (C + B) / (B * C) (simplify)
		};

		template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
		struct addition<mul<constant<LeftLeftValue>, power<constant<LeftRightValue>, constant<-1> > >, mul<constant<RightLeftValue>, power<constant<RightRightValue>, constant<-1> > > > {
			typedef product_t<constant<LeftLeftValue * RightRightValue + LeftRightValue * RightLeftValue>, power_t<constant<LeftRightValue * RightRightValue>, constant<-1> >, real_mapping> type; // A / B + C / D = (A * D + B * C) / (B * D) (simplify)
		};

	}

}

#endif // __FUTURE_GA_ADDITION_HPP__
