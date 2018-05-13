#ifndef __FUTURE_GA_PRODUCT_HPP__
#define __FUTURE_GA_PRODUCT_HPP__

namespace ga {

	namespace detail {

		// Specializations of product<mul<...>, mul<...>, real_mapping> (merge).
		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct product<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, real_mapping,std::enable_if_t<lt_v<RightArgument, LeftArgument> > > {
			typedef product_t<RightArgument, product_t<mul_t<LeftArgument, LeftNextArguments...>, mul_t<RightNextArguments...>, real_mapping>, real_mapping> type;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct product<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<!lt_v<RightArgument, LeftArgument> > > {
			typedef product_t<LeftArgument, product_t<mul_t<LeftNextArguments...>, mul_t<RightArgument, RightNextArguments...>, real_mapping>, real_mapping> type;
		};

		// Specializations of product<LeftExpression, mul<...>, real_mapping> and product<mul<...>, RightExpression, real_mapping> (merge, simplify-and-merge, or bind).
		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct product<LeftExpression, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<lt_v<RightArgument, LeftExpression> > > {
			typedef product_t<RightArgument, product_t<LeftExpression, mul_t<RightNextArguments...>, real_mapping>, real_mapping> type; // merge
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct product<LeftExpression, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<lt_v<LeftExpression, RightArgument> && !std::is_same_v<product_t<LeftExpression, RightArgument, real_mapping>, mul_t<LeftExpression, RightArgument> > > > {
			typedef product_t<product_t<LeftExpression, RightArgument, real_mapping>, mul_t<RightNextArguments...>, real_mapping> type; // simplification found (simplify-and-merge)
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct product<LeftExpression, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<lt_v<LeftExpression, RightArgument> && std::is_same_v<product_t<LeftExpression, RightArgument, real_mapping>, mul_t<LeftExpression, RightArgument> > > > {
			typedef mul_t<LeftExpression, RightArgument, RightNextArguments...> type; // no simplification found (bind)
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct product<mul<LeftArgument, LeftNextArguments...>, RightExpression, real_mapping, std::enable_if_t<lt_v<RightExpression, LeftArgument> > > {
			typedef product_t<RightExpression, mul_t<LeftArgument, LeftNextArguments...>, real_mapping> type; // merge
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct product<mul<LeftArgument, LeftNextArguments...>, RightExpression, real_mapping, std::enable_if_t<!lt_v<RightExpression, LeftArgument> > > {
			typedef product_t<LeftArgument, product_t<mul_t<LeftNextArguments...>, RightExpression, real_mapping>, real_mapping> type; // merge
		};

		// Specialization of product<add<...>, add<...>, Mapping>, product<LeftExpression, add<...>, Mapping>, and product<RightExpression, add<...>, Mapping> (distributive property over addition).
		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments, class Mapping>
		struct product<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, Mapping> {
			typedef addition_t<addition_t<product_t<LeftArgument, RightArgument, Mapping>, product_t<add_t<LeftNextArguments...>, RightArgument, Mapping> >, addition_t<product_t<LeftArgument, add_t<RightNextArguments...>, Mapping>, product_t<add_t<LeftNextArguments...>, add_t<RightNextArguments...>, Mapping> > > type;
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments, class Mapping>
		struct product<LeftExpression, add<RightArgument, RightNextArguments...>, Mapping> {
			typedef addition_t<product_t<LeftExpression, RightArgument, Mapping>, product_t<LeftExpression, add_t<RightNextArguments...>, Mapping> > type;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression, class Mapping>
		struct product<add<LeftArgument, LeftNextArguments...>, RightExpression, Mapping> {
			typedef addition_t<product_t<LeftArgument, RightExpression, Mapping>, product_t<add_t<LeftNextArguments...>, RightExpression, Mapping> > type;
		};

		// Specialization of product<component<...>, component<...>, Mapping>, product<LeftExpression, component<...>, Mapping>, and product<component<...>, RightExpression, Mapping> (simplify-and-bind).
		template<class LeftCoefficient, class LeftBasisBlade, class RightCoefficient, class RightBasisBlade, class Mapping>
		struct product<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping> {
			typedef product_t<LeftCoefficient, product_t<RightCoefficient, typename Mapping::template multiply<LeftBasisBlade, RightBasisBlade>::type, real_mapping>, real_mapping> type;
		};

		template<class LeftExpression, class RightCoefficient, class RightBasisBlade, class Mapping>
		struct product<LeftExpression, component<RightCoefficient, RightBasisBlade>, Mapping, std::enable_if_t<!is_any_v<LeftExpression, constant<0>, constant<1> > > > {
			typedef make_component_t<product_t<LeftExpression, RightCoefficient, real_mapping>, RightBasisBlade> type;
		};

		template<class LeftCoefficient, class LeftBasisBlade, class RightExpression, class Mapping>
		struct product<component<LeftCoefficient, LeftBasisBlade>, RightExpression, Mapping, std::enable_if_t<!is_any_v<RightExpression, constant<0>, constant<1> > > > {
			typedef make_component_t<product_t<LeftCoefficient, RightExpression, real_mapping>, LeftBasisBlade> type;
		};

		// Specializations of product<LeftExpression, RightExpression, Mapping> (simplify or bind).
		template<class LeftExpression, class RightExpression, class Mapping>
		struct product<LeftExpression, RightExpression, Mapping, std::enable_if_t<!(is_any_v<LeftExpression, constant<0>, constant<1> > || is_any_v<RightExpression, constant<0>, constant<1> >) && lt_v<LeftExpression, RightExpression> > > {
			typedef mul_t<LeftExpression, RightExpression> type; // A * B, end of recursion (bind)
		};

		template<class LeftExpression, class RightExpression, class Mapping>
		struct product<LeftExpression, RightExpression, Mapping, std::enable_if_t<!(is_any_v<LeftExpression, constant<0>, constant<1> > || is_any_v<RightExpression, constant<0>, constant<1> >) && lt_v<RightExpression, LeftExpression> > > {
			typedef mul_t<RightExpression, LeftExpression> type; // A * B = B * A, end of recursion (sort and bind)
		};

		template<class Mapping>
		struct product<constant<0>, constant<0>, Mapping> {
			typedef constant<0> type; // 0 * 0 = 0, end of recursion (simplify)
		};

		template<class RightExpression, class Mapping>
		struct product<constant<0>, RightExpression, Mapping> {
			typedef constant<0> type; // 0 * A = 0, end of recursion (simplify)
		};

		template<class LeftExpression, class Mapping>
		struct product<LeftExpression, constant<0>, Mapping> {
			typedef constant<0> type; // A * 0 = 0, end of recursion (simplify)
		};

		template<class Mapping>
		struct product<constant<1>, constant<1>, Mapping> {
			typedef constant<1> type; // 1 * 1 = 1, end of recursion (simplify)
		};

		template<class RightExpression, class Mapping>
		struct product<constant<1>, RightExpression, Mapping, std::enable_if_t<!std::is_same_v<RightExpression, constant<0> > > > {
			typedef RightExpression type; // 1 * A = A, end of recursion (simplify)
		};

		template<class LeftExpression, class Mapping>
		struct product<LeftExpression, constant<1>, Mapping, std::enable_if_t<!std::is_same_v<LeftExpression, constant<0> > > > {
			typedef LeftExpression type; // A * 1 = 1, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue, class Mapping>
		struct product<constant<LeftValue>, constant<RightValue>, Mapping, std::enable_if_t<LeftValue != 0 && LeftValue != 1 && RightValue != 0 && RightValue != 1> > {
			typedef constant<LeftValue * RightValue> type; // A * B = C, end of recursion (simplify)
		};

		template<default_integral_t RightValue, class Mapping>
		struct product<constant<-1>, power<constant<RightValue>, constant<-1> >, Mapping> {
			typedef power_t<constant<-RightValue>, constant<-1> > type; // -1 * A^{-1} = (-A)^{-1}, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, class Mapping>
		struct product<power<constant<LeftValue>, constant<-1> >, constant<-1>, Mapping> {
			typedef power_t<constant<-LeftValue>, constant<-1> > type; // A^{-1} * -1 = (-A)^{-1}, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue, class Mapping>
		struct product<power<constant<LeftValue>, constant<-1> >, power<constant<RightValue>, constant<-1> >, Mapping, std::enable_if_t<LeftValue != RightValue> > {
			typedef power_t<constant<LeftValue * RightValue>(), constant<-1>()> type; // A^{-1} * B^{-1} = (A * B)^{-1}, end of recursion (simplify)
		};

		template<default_integral_t Numerator, default_integral_t Denominator, default_integral_t GreatestCommonDivisor = gcd(absolute(Numerator), absolute(Denominator))>
		struct simpler_rational_constant {
			typedef product_t<constant<(sign(Numerator) * sign(Denominator)) * (absolute(Numerator) / GreatestCommonDivisor)>, exponentiation_t<constant<absolute(Denominator) / GreatestCommonDivisor>, constant<-1> >, real_mapping> type;
		};

		template<default_integral_t Numerator, default_integral_t Denominator>
		struct simpler_rational_constant<Numerator, Denominator, 1> {
			typedef mul_t<constant<(sign(Numerator) * sign(Denominator)) * absolute(Numerator)>, power_t<constant<absolute(Denominator)>, constant<-1> > > type;
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

		template<class Expression, class Mapping>
		struct product<Expression, Mapping, std::enable_if_t<!is_any_v<Expression, constant<0>, constant<1> > > > {
			typedef exponentiation_t<Expression, constant<2>()> type; // A * A = A^{2}, end of recursion (simplify)
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

#endif // __FUTURE_GA_PRODUCT_HPP__
