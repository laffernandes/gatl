#ifndef __GA_FUTURE_PRODUCT_HPP__
#define __GA_FUTURE_PRODUCT_HPP__

namespace future {

	namespace detail {

		// Specializations of product<mul<...>, mul<...>, real_mapping> (merge operation).
		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct product<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, real_mapping,std::enable_if_t<lt_v<RightArgument, LeftArgument> > > {
			typedef product_t<RightArgument, product_t<mul<LeftArgument, LeftNextArguments...>, mul<RightNextArguments...>, real_mapping>, real_mapping> type;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct product<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<!lt_v<RightArgument, LeftArgument> > > {
			typedef product_t<LeftArgument, product_t<mul<LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, real_mapping>, real_mapping> type;
		};

		template<class LeftArgument, class... LeftNextArguments>
		struct product<mul<LeftArgument, LeftNextArguments...>, mul<>, real_mapping> {
			typedef mul<LeftArgument, LeftNextArguments...> type; // end of recursion
		};

		template<class RightArgument, class... RightNextArguments>
		struct product<mul<>, mul<RightArgument, RightNextArguments...>, real_mapping> {
			typedef mul<RightArgument, RightNextArguments...> type; // end of recursion
		};

		template<>
		struct product<mul<>, mul<>, real_mapping> {
			typedef constant<1> type; // end of recursion
		};

		// Specializations of product<LeftType, mul<...>, real_mapping> and product<mul<...>, RightType, real_mapping> (merge, simplify-and-merge, or bind operations).
		template<class LeftType, class RightArgument, class... RightNextArguments>
		struct product<LeftType, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<lt_v<RightArgument, LeftType> > > {
			typedef product_t<RightArgument, product_t<LeftType, mul<RightNextArguments...>, real_mapping>, real_mapping> type; // merge
		};

		template<class LeftType, class RightArgument, class... RightNextArguments>
		struct product<LeftType, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<lt_v<LeftType, RightArgument> && !std::is_same_v<product_t<LeftType, RightArgument, real_mapping>, mul<LeftType, RightArgument> > > > {
			typedef product_t<product_t<LeftType, RightArgument, real_mapping>, mul<RightNextArguments...>, real_mapping> type; // simplification found (simplify-and-merge)
		};

		template<class LeftType, class RightArgument, class... RightNextArguments>
		struct product<LeftType, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<lt_v<LeftType, RightArgument> && std::is_same_v<product_t<LeftType, RightArgument, real_mapping>, mul<LeftType, RightArgument> > > > {
			typedef mul<LeftType, RightArgument, RightNextArguments...> type; // no simplification found (bind)
		};

		template<class LeftType>
		struct product<LeftType, mul<>, real_mapping> {
			typedef LeftType type; // end of recursion
		};

		template<class LeftArgument, class... LeftNextArguments, class RightType>
		struct product<mul<LeftArgument, LeftNextArguments...>, RightType, real_mapping, std::enable_if_t<lt_v<RightType, LeftArgument> > > {
			typedef product_t<RightType, mul<LeftArgument, LeftNextArguments...>, real_mapping> type; // merge
		};

		template<class LeftArgument, class... LeftNextArguments, class RightType>
		struct product<mul<LeftArgument, LeftNextArguments...>, RightType, real_mapping, std::enable_if_t<!lt_v<RightType, LeftArgument> > > {
			typedef product_t<LeftArgument, product_t<mul<LeftNextArguments...>, RightType, real_mapping>, real_mapping> type; // merge
		};

		template<class RightType>
		struct product<mul<>, RightType, real_mapping> {
			typedef RightType type; // end of recursion
		};

		// Specialization of product<add<...>, add<...>, Mapping>, product<LeftType, add<...>, Mapping>, and product<RightType, add<...>, Mapping> (distributive property over addition).
		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments, class Mapping>
		struct product<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, Mapping> {
			typedef addition_t<addition_t<product_t<LeftArgument, RightArgument, Mapping>, product_t<add<LeftNextArguments...>, RightArgument, Mapping> >, addition_t<product_t<LeftArgument, add<RightNextArguments...>, Mapping>, product_t<add<LeftNextArguments...>, add<RightNextArguments...>, Mapping> > > type;
		};

		template<class LeftArgument, class... LeftNextArguments, class Mapping>
		struct product<add<LeftArgument, LeftNextArguments...>, add<>, Mapping> {
			typedef constant<0> type; // end of recursion
		};

		template<class RightArgument, class... RightNextArguments, class Mapping>
		struct product<add<>, add<RightArgument, RightNextArguments...>, Mapping> {
			typedef constant<0> type; // end of recursion
		};

		template<class Mapping>
		struct product<add<>, add<>, Mapping> {
			typedef constant<0> type; // end of recursion
		};

		template<class LeftType, class RightArgument, class... RightNextArguments, class Mapping>
		struct product<LeftType, add<RightArgument, RightNextArguments...>, Mapping> {
			typedef addition_t<product_t<LeftType, RightArgument, Mapping>, product_t<LeftType, add<RightNextArguments...>, Mapping> > type;
		};

		template<class LeftType, class Mapping>
		struct product<LeftType, add<>, Mapping> {
			typedef constant<0> type; // end of recursion
		};

		template<class LeftArgument, class... LeftNextArguments, class RightType, class Mapping>
		struct product<add<LeftArgument, LeftNextArguments...>, RightType, Mapping> {
			typedef addition_t<product_t<LeftArgument, RightType, Mapping>, product_t<add<LeftNextArguments...>, RightType, Mapping> > type;
		};

		template<class RightType, class Mapping>
		struct product<add<>, RightType, Mapping> {
			typedef constant<0> type; // end of recursion
		};

		// Specialization of product<component<...>, component<...>, Mapping>, product<LeftType, component<...>, Mapping>, and product<component<...>, RightType, Mapping> (simplify-and-bind operation).
		template<class LeftCoefficient, class LeftBasisBlade, class RightCoefficient, class RightBasisBlade, class Mapping>
		struct product<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping> {
			typedef product_t<LeftCoefficient, product_t<RightCoefficient, typename Mapping::template resulting_component<LeftBasisBlade, RightBasisBlade>::type, real_mapping>, real_mapping> type;
		};

		template<class LeftType, class RightCoefficient, class RightBasisBlade, class Mapping>
		struct product<LeftType, component<RightCoefficient, RightBasisBlade>, Mapping, std::enable_if_t<!is_any_v<LeftType, constant<0>, constant<1> > > > {
			typedef make_component_t<product_t<LeftType, RightCoefficient, real_mapping>, RightBasisBlade> type;
		};

		template<class LeftCoefficient, class LeftBasisBlade, class RightType, class Mapping>
		struct product<component<LeftCoefficient, LeftBasisBlade>, RightType, Mapping, std::enable_if_t<!is_any_v<RightType, constant<0>, constant<1> > > > {
			typedef make_component_t<product_t<LeftCoefficient, RightType, real_mapping>, LeftBasisBlade> type;
		};

		// Specializations of product<LeftType, RightType, Mapping> (simplify or bind operations).
		template<class LeftType, class RightType, class Mapping>
		struct product<LeftType, RightType, Mapping, std::enable_if_t<!(is_any_v<LeftType, constant<0>, constant<1> > || is_any_v<RightType, constant<0>, constant<1> >) && lt_v<LeftType, RightType> > > {
			typedef mul<LeftType, RightType> type; // A * B, end of recursion (bind)
		};

		template<class LeftType, class RightType, class Mapping>
		struct product<LeftType, RightType, Mapping, std::enable_if_t<!(is_any_v<LeftType, constant<0>, constant<1> > || is_any_v<RightType, constant<0>, constant<1> >) && lt_v<RightType, LeftType> > > {
			typedef mul<RightType, LeftType> type; // A * B = B * A, end of recursion (sort and bind)
		};

		template<class Mapping>
		struct product<constant<0>, constant<0>, Mapping> {
			typedef constant<0> type; // 0 * 0 = 0, end of recursion (simplify)
		};

		template<class RightType, class Mapping>
		struct product<constant<0>, RightType, Mapping> {
			typedef constant<0> type; // 0 * A = 0, end of recursion (simplify)
		};

		template<class LeftType, class Mapping>
		struct product<LeftType, constant<0>, Mapping> {
			typedef constant<0> type; // A * 0 = 0, end of recursion (simplify)
		};

		template<class Mapping>
		struct product<constant<1>, constant<1>, Mapping> {
			typedef constant<1> type; // 1 * 1 = 1, end of recursion (simplify)
		};

		template<class RightType, class Mapping>
		struct product<constant<1>, RightType, Mapping, std::enable_if_t<!std::is_same_v<RightType, constant<0> > > > {
			typedef RightType type; // 1 * A = A, end of recursion (simplify)
		};

		template<class LeftType, class Mapping>
		struct product<LeftType, constant<1>, Mapping, std::enable_if_t<!std::is_same_v<LeftType, constant<0> > > > {
			typedef LeftType type; // A * 1 = 1, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue, class Mapping>
		struct product<constant<LeftValue>, constant<RightValue>, Mapping, std::enable_if_t<LeftValue != 0 && LeftValue != 1 && RightValue != 0 && RightValue != 1> > {
			typedef constant<LeftValue * RightValue> type; // A * B = C, end of recursion (simplify)
		};

		template<default_integral_t RightValue, class Mapping>
		struct product<constant<-1>, power<constant<RightValue>, constant<-1> >, Mapping> {
			typedef power<constant<-RightValue>, constant<-1> > type; // -1 * A^{-1} = (-A)^{-1}, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, class Mapping>
		struct product<power<constant<LeftValue>, constant<-1> >, constant<-1>, Mapping> {
			typedef power<constant<-LeftValue>, constant<-1> > type; // A^{-1} * -1 = (-A)^{-1}, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue, class Mapping>
		struct product<power<constant<LeftValue>, constant<-1> >, power<constant<RightValue>, constant<-1> >, Mapping, std::enable_if_t<LeftValue != RightValue> > {
			typedef power<constant<LeftValue * RightValue>(), constant<-1>()> type; // A^{-1} * B^{-1} = (A * B)^{-1}, end of recursion (simplify)
		};

		template<default_integral_t Numerator, default_integral_t Denominator, default_integral_t GreatestCommonDivisor = gcd(absolute(Numerator), absolute(Denominator))>
		struct simpler_rational_constant {
			typedef product_t<constant<(sign(Numerator) * sign(Denominator)) * (absolute(Numerator) / GreatestCommonDivisor)>, exponentiation_t<constant<absolute(Denominator) / GreatestCommonDivisor>, constant<-1> >, real_mapping> type;
		};

		template<default_integral_t Numerator, default_integral_t Denominator>
		struct simpler_rational_constant<Numerator, Denominator, 1> {
			typedef mul<constant<(sign(Numerator) * sign(Denominator)) * absolute(Numerator)>, power<constant<absolute(Denominator)>, constant<-1> > > type;
		};

		template<default_integral_t Numerator, default_integral_t Denominator>
		using simpler_rational_constant_t = typename simpler_rational_constant<Numerator, Denominator>::type;

		template<default_integral_t LeftValue, default_integral_t RightValue, class Mapping>
		struct product<constant<LeftValue>, power<constant<RightValue>, constant<-1> >, Mapping, std::enable_if_t<LeftValue != 0 && LeftValue != 1 && LeftValue != -1 && LeftValue != RightValue> > {
			typedef simpler_rational_constant_t<LeftValue, RightValue> type; // A * B^{-1} = simpler (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue, class Mapping>
		struct product<power<constant<LeftValue>, constant<-1> >, constant<RightValue>, Mapping, std::enable_if_t<RightValue != 0 && RightValue != 1 && RightValue != -1 && LeftValue != RightValue> > {
			typedef simpler_rational_constant_t<RightValue, LeftValue> type; // A^{-1} * B = simpler (simplify)
		};

		template<class Type, class Mapping>
		struct product<Type, Mapping, std::enable_if_t<!is_any_v<Type, constant<0>, constant<1> > > > {
			typedef exponentiation_t<Type, constant<2>()> type; // A * A = A^{2}, end of recursion (simplify)
		};

		template<class CommonArgument, class LeftRightArgument, class Mapping>
		struct product<power<CommonArgument, LeftRightArgument>, CommonArgument, Mapping, std::enable_if_t<!is_any_v<CommonArgument, constant<0>, constant<1> > > > {
			typedef exponentiation_t<CommonArgument, addition_t<LeftRightArgument, constant<1> > > type; // A^{P} * A = A^{P + 1}, end of recursion (simplify)
		};

		template<class CommonArgument, class RightRightArgument, class Mapping>
		struct product<CommonArgument, power<CommonArgument, RightRightArgument>, Mapping, std::enable_if_t<!is_any_v<CommonArgument, constant<0>, constant<1> > > > {
			typedef exponentiation_t<CommonArgument, addition_t<constant<1>, RightRightArgument> > type; // A * A^{Q} = A^{1 + Q}, end of recursion (simplify)
		};

		template<class CommonArgument, class LeftRightArgument, class RightRightArgument, class Mapping>
		struct product<power<CommonArgument, LeftRightArgument>, power<CommonArgument, RightRightArgument>, Mapping, std::enable_if_t<!std::is_same_v<LeftRightArgument, RightRightArgument> > > {
			typedef exponentiation_t<CommonArgument, addition_t<LeftRightArgument, RightRightArgument> > type; // A^{P} * A^{Q} = A^{P + Q}, end of recursion (simplify)
		};

	}

}

#endif // __GA_FUTURE_PRODUCT_HPP__
