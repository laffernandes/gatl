#ifndef __GA_FUTURE_ADDITION_HPP__
#define __GA_FUTURE_ADDITION_HPP__

namespace future {

	namespace detail {

		// Specializations of addition<add<...>, add<...> > (merge operation).
		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct addition<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftArgument> > > {
			typedef addition_t<RightArgument, addition_t<add<LeftArgument, LeftNextArguments...>, add<RightNextArguments...> > > type;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct addition<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<!lt_v<RightArgument, LeftArgument> > > {
			typedef addition_t<LeftArgument, addition_t<add<LeftNextArguments...>, add<RightArgument, RightNextArguments...> > > type;
		};

		template<class LeftArgument, class... LeftNextArguments>
		struct addition<add<LeftArgument, LeftNextArguments...>, add<> > {
			typedef add<LeftArgument, LeftNextArguments...> type; // end of recursion
		};

		template<class RightArgument, class... RightNextArguments>
		struct addition<add<>, add<RightArgument, RightNextArguments...> > {
			typedef add<RightArgument, RightNextArguments...> type; // end of recursion
		};

		template<>
		struct addition<add<>, add<> > {
			typedef constant<0> type; // end of recursion
		};

		// Specializations of addition<LeftType, add<...> > and addition<add<...>, RightType> (merge, simplify-and-merge, or bind operations).
		template<class LeftType, class RightArgument, class... RightNextArguments>
		struct addition<LeftType, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftType> && !std::is_same_v<LeftType, constant<0> > > > {
			typedef addition_t<RightArgument, addition_t<LeftType, add<RightNextArguments...> > > type; // merge
		};

		template<class LeftType, class RightArgument, class... RightNextArguments>
		struct addition<LeftType, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<LeftType, RightArgument> && !(std::is_same_v<addition_t<LeftType, RightArgument>, add<LeftType, RightArgument> > || std::is_same_v<LeftType, constant<0> >) > > {
			typedef addition_t<addition_t<LeftType, RightArgument>, add<RightNextArguments...> > type; // simplification found (simplify-and-merge)
		};

		template<class LeftType, class RightArgument, class... RightNextArguments>
		struct addition<LeftType, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<LeftType, RightArgument> && std::is_same_v<addition_t<LeftType, RightArgument>, add<LeftType, RightArgument> > && !std::is_same_v<LeftType, constant<0> > > > {
			typedef add<LeftType, RightArgument, RightNextArguments...> type; // no simplification found, end of recursion (bind)
		};

		template<class LeftType>
		struct addition<LeftType, add<>, std::enable_if_t<!std::is_same_v<LeftType, constant<0> > > > {
			typedef LeftType type; // end of recursion.
		};

		template<class LeftArgument, class... LeftNextArguments, class RightType>
		struct addition<add<LeftArgument, LeftNextArguments...>, RightType, std::enable_if_t<lt_v<RightType, LeftArgument> && !std::is_same_v<RightType, constant<0> > > > {
			typedef addition_t<RightType, add<LeftArgument, LeftNextArguments...> > type; // merge
		};

		template<class LeftArgument, class... LeftNextArguments, class RightType>
		struct addition<add<LeftArgument, LeftNextArguments...>, RightType, std::enable_if_t<!(lt_v<RightType, LeftArgument> || std::is_same_v<RightType, constant<0> >) > > {
			typedef addition_t<LeftArgument, addition_t<add<LeftNextArguments...>, RightType> > type; // merge
		};

		template<class RightType>
		struct addition<add<>, RightType, std::enable_if_t<!std::is_same_v<RightType, constant<0> > > > {
			typedef RightType type; // end of recursion
		};

		// Specialization of addition<component<...>, component<...> > (simplify operation).
		template<class LeftCoefficient, default_bitset_t BasisVectors, class RightCoefficient>
		struct addition<component<LeftCoefficient, constant_basis_blade<BasisVectors> >, component<RightCoefficient, constant_basis_blade<BasisVectors> > > {
			typedef make_component_t<addition_t<LeftCoefficient, RightCoefficient>, constant_basis_blade<BasisVectors> > type; // A * Ei + B * Ei = (A + B) * Ei or simpler, end of recursion (simplify)
		};

		// Specializations of addition<LeftType, RightType> (simplify or bind operations).
		template<class LeftType, class RightType>
		struct addition<LeftType, RightType, std::enable_if_t<!(std::is_same_v<LeftType, constant<0> > || std::is_same_v<RightType, constant<0> >) && lt_v<LeftType, RightType> > > {
			typedef add<LeftType, RightType> type; // A + B, end of recursion (bind)
		};

		template<class LeftType, class RightType>
		struct addition<LeftType, RightType, std::enable_if_t<!(std::is_same_v<LeftType, constant<0> > || std::is_same_v<RightType, constant<0> >) && lt_v<RightType, LeftType> > > {
			typedef add<RightType, LeftType> type; // A + B = B + A, end of recursion (sort and bind)
		};

		template<class Type>
		struct addition<Type, Type, std::enable_if_t<!std::is_same_v<Type, constant<0> > > > {
			typedef product_t<constant<2>, Type, real_mapping> type; // A + A = 2 * A, end of recursion (simplify)
		};

		template<>
		struct addition<constant<0>, constant<0> > {
			typedef constant<0> type; // 0 + 0 = 0, end of recursion (simplify)
		};

		template<class RightType>
		struct addition<constant<0>, RightType> {
			typedef RightType type; // 0 + A = A, end of recursion (simplify)
		};

		template<class LeftType>
		struct addition<LeftType, constant<0> > {
			typedef LeftType type; // A + 0 = A, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<constant<LeftValue>, constant<RightValue>, std::enable_if_t<LeftValue != 0 && RightValue != 0> > {
			typedef constant<LeftValue + RightValue> type; // A + B = C, end of recursion (simplify)
		};
		
		template<default_integral_t LeftValue, class CommonArgument>
		struct addition<mul<constant<LeftValue>, CommonArgument>, CommonArgument, std::enable_if_t<!std::is_same_v<CommonArgument, constant<0> > > > {
			typedef product_t<constant<LeftValue + 1>, CommonArgument, real_mapping> type; // (P * A) + A = (P + 1) * A (simplify)
		};

		template<default_integral_t LeftValue, class... CommonArguments>
		struct addition<mul<constant<LeftValue>, CommonArguments...>, mul<CommonArguments...> > {
			typedef product_t<constant<LeftValue + 1>, mul<CommonArguments...>, real_mapping> type; // (P * A * ...) + (A * ...) = (P + 1) * (A * ...) (simplify)
		};

		template<class CommonArgument, default_integral_t RightValue>
		struct addition<CommonArgument, mul<constant<RightValue>, CommonArgument>, std::enable_if_t<!std::is_same_v<CommonArgument, constant<0> > > > {
			typedef product_t<constant<1 + RightValue>, CommonArgument, real_mapping> type; // A + (P * A) = (1 + P) * A (simplify)
		};

		template<class... CommonArguments, default_integral_t RightValue>
		struct addition<mul<CommonArguments...>, mul<constant<RightValue>, CommonArguments...> > {
			typedef product_t<constant<1 + RightValue>, mul<CommonArguments...>, real_mapping> type; // A * ... + (P * A * ...) = (1 + P) * (A * ...) (simplify)
		};

		template<default_integral_t LeftValue, class Argument, default_integral_t RightValue>
		struct addition<mul<constant<LeftValue>, Argument>, mul<constant<RightValue>, Argument> > {
			typedef product_t<constant<LeftValue + RightValue>, Argument, real_mapping> type; // (P * A) + (Q * A) = (P + Q) * A (simplify)
		};

		template<default_integral_t LeftValue, class... CommonArguments, default_integral_t RightValue>
		struct addition<mul<constant<LeftValue>, CommonArguments...>, mul<constant<RightValue>, CommonArguments...> > {
			typedef product_t<constant<LeftValue + RightValue>, mul<CommonArguments...>, real_mapping> type; // (P * A * ...) + (Q * A * ...) = (P + Q) * (A * ...) (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<constant<LeftValue>, power<constant<RightValue>, constant<-1> >, std::enable_if_t<LeftValue != 0> > {
			typedef product_t<constant<LeftValue * RightValue + 1>, power<constant<RightValue>, constant<-1> >, real_mapping> type; // A + 1 / B = (A * B + 1) / B (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<power<constant<LeftValue>, constant<-1> >, constant<RightValue>, std::enable_if_t<RightValue != 0> > {
			typedef product_t<constant<1 + RightValue * LeftValue>, power<constant<LeftValue>, constant<-1> >, real_mapping> type; // 1 / A + B = (1 + B * A) / A (simplify)
		};

		template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightValue>
		struct addition<mul<constant<LeftLeftValue>, power<constant<LeftRightValue>, constant<-1> > >, power<constant<RightValue>, constant<-1> > > {
			typedef product_t<constant<LeftLeftValue * RightValue + LeftRightValue>, power<constant<LeftRightValue * RightValue>, constant<-1> >, real_mapping> type; // A / B + 1 / C = (A * C + B) / (B * C) (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
		struct addition<power<constant<LeftValue>, constant<-1> >, mul<constant<RightLeftValue>, power<constant<RightRightValue>, constant<-1> > > > {
			typedef product_t<constant<RightRightValue + LeftValue * RightLeftValue>, power<constant<LeftValue * RightRightValue>, constant<-1> >, real_mapping> type; // 1 / C + A / B = (B + C * A) / (C * B) (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct addition<power<constant<LeftValue>, constant<-1> >, power<constant<RightValue>, constant<-1> > > {
			typedef product_t<constant<RightValue + LeftValue>, power<constant<LeftValue * RightValue>, constant<-1> >, real_mapping> type; // 1 / B + 1 / C = (C + B) / (B * C) (simplify)
		};

		template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
		struct addition<mul<constant<LeftLeftValue>, power<constant<LeftRightValue>, constant<-1> > >, mul<constant<RightLeftValue>, power<constant<RightRightValue>, constant<-1> > > > {
			typedef product_t<constant<LeftLeftValue * RightRightValue + LeftRightValue * RightLeftValue>, power<constant<LeftRightValue * RightRightValue>, constant<-1> >, real_mapping> type; // A / B + C / D = (A * D + B * C) / (B * D) (simplify)
		};

	}

}

#endif // __GA_FUTURE_ADDITION_HPP__
