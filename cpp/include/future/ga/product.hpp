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

		// Specialization of product<component<...>, component<...>, Mapping> (simplify-and-bind).
		template<class LeftCoefficient, class LeftBasisBlade, class RightCoefficient, class RightBasisBlade, class Mapping>
		struct product<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping> {
		private:

			typedef typename Mapping::template multiply<LeftBasisBlade, RightBasisBlade> result;

		public:

			typedef component_t<
				product_t<LeftCoefficient, product_t<RightCoefficient, typename result::coefficient_type, real_mapping>, real_mapping>,
				typename result::basis_blade_type
			> type;
		};

		// Specializations of product<LeftExpression, RightExpression> (simplify or bind).
		template<class LeftExpression, class RightExpression>
		struct product<LeftExpression, RightExpression, real_mapping, std::enable_if_t<!(is_any_v<LeftExpression, constant_value<0>, constant_value<1> > || is_any_v<RightExpression, constant_value<0>, constant_value<1> >) && lt_v<LeftExpression, RightExpression> > > {
			typedef mul_t<LeftExpression, RightExpression> type; // A * B, end of recursion (bind)
		};

		template<class LeftExpression, class RightExpression>
		struct product<LeftExpression, RightExpression, real_mapping, std::enable_if_t<!(is_any_v<LeftExpression, constant_value<0>, constant_value<1> > || is_any_v<RightExpression, constant_value<0>, constant_value<1> >) && lt_v<RightExpression, LeftExpression> > > {
			typedef mul_t<RightExpression, LeftExpression> type; // A * B = B * A, end of recursion (sort and bind)
		};

		template<>
		struct product<constant_value<0>, constant_value<0>, real_mapping> {
			typedef constant_value<0> type; // 0 * 0 = 0, end of recursion (simplify)
		};

		template<class RightExpression>
		struct product<constant_value<0>, RightExpression, real_mapping> {
			typedef constant_value<0> type; // 0 * A = 0, end of recursion (simplify)
		};

		template<class LeftExpression>
		struct product<LeftExpression, constant_value<0>, real_mapping> {
			typedef constant_value<0> type; // A * 0 = 0, end of recursion (simplify)
		};

		template<>
		struct product<constant_value<1>, constant_value<1>, real_mapping> {
			typedef constant_value<1> type; // 1 * 1 = 1, end of recursion (simplify)
		};

		template<class RightExpression>
		struct product<constant_value<1>, RightExpression, real_mapping, std::enable_if_t<!std::is_same_v<RightExpression, constant_value<0> > > > {
			typedef RightExpression type; // 1 * A = A, end of recursion (simplify)
		};

		template<class LeftExpression>
		struct product<LeftExpression, constant_value<1>, real_mapping, std::enable_if_t<!std::is_same_v<LeftExpression, constant_value<0> > > > {
			typedef LeftExpression type; // A * 1 = 1, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct product<constant_value<LeftValue>, constant_value<RightValue>, real_mapping, std::enable_if_t<LeftValue != 0 && LeftValue != 1 && RightValue != 0 && RightValue != 1> > {
			typedef constant_value<LeftValue * RightValue> type; // A * B = C, end of recursion (simplify)
		};

		template<default_integral_t RightValue>
		struct product<constant_value<-1>, power<constant_value<RightValue>, constant_value<-1> >, real_mapping> {
			typedef power_t<constant_value<-RightValue>, constant_value<-1> > type; // -1 * A^{-1} = (-A)^{-1}, end of recursion (simplify)
		};

		template<default_integral_t LeftValue>
		struct product<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<-1>, real_mapping> {
			typedef power_t<constant_value<-LeftValue>, constant_value<-1> > type; // A^{-1} * -1 = (-A)^{-1}, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct product<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> >, real_mapping, std::enable_if_t<LeftValue != RightValue> > {
			typedef power_t<constant_value<LeftValue * RightValue>(), constant_value<-1>()> type; // A^{-1} * B^{-1} = (A * B)^{-1}, end of recursion (simplify)
		};

		template<default_integral_t Numerator, default_integral_t Denominator, default_integral_t GreatestCommonDivisor = gcd(absolute(Numerator), absolute(Denominator))>
		struct simpler_rational_constant {
			typedef product_t<constant_value<(sign(Numerator) * sign(Denominator)) * (absolute(Numerator) / GreatestCommonDivisor)>, exponentiation_t<constant_value<absolute(Denominator) / GreatestCommonDivisor>, constant_value<-1> >, real_mapping> type;
		};

		template<default_integral_t Numerator, default_integral_t Denominator>
		struct simpler_rational_constant<Numerator, Denominator, 1> {
			typedef mul_t<constant_value<(sign(Numerator) * sign(Denominator)) * absolute(Numerator)>, power_t<constant_value<absolute(Denominator)>, constant_value<-1> > > type;
		};

		template<default_integral_t Numerator, default_integral_t Denominator>
		using simpler_rational_constant_t = typename simpler_rational_constant<Numerator, Denominator>::type;

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct product<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> >, real_mapping, std::enable_if_t<LeftValue != 0 && LeftValue != 1 && LeftValue != -1 && LeftValue != RightValue> > {
			typedef simpler_rational_constant_t<LeftValue, RightValue> type; // A * B^{-1} = simpler (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct product<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue>, real_mapping, std::enable_if_t<RightValue != 0 && RightValue != 1 && RightValue != -1 && LeftValue != RightValue> > {
			typedef simpler_rational_constant_t<RightValue, LeftValue> type; // A^{-1} * B = simpler (simplify)
		};

		template<class Expression>
		struct product<Expression, real_mapping, std::enable_if_t<!is_any_v<Expression, constant_value<0>, constant_value<1> > > > {
			typedef exponentiation_t<Expression, constant_value<2>()> type; // A * A = A^{2}, end of recursion (simplify)
		};

		template<class CommonArgument, class LeftRightArgument>
		struct product<power<CommonArgument, LeftRightArgument>, CommonArgument, real_mapping, std::enable_if_t<!is_any_v<CommonArgument, constant_value<0>, constant_value<1> > > > {
			typedef exponentiation_t<CommonArgument, addition_t<LeftRightArgument, constant_value<1> > > type; // A^{P} * A = A^{P + 1}, end of recursion (simplify)
		};

		template<class CommonArgument, class RightRightArgument>
		struct product<CommonArgument, power<CommonArgument, RightRightArgument>, real_mapping, std::enable_if_t<!is_any_v<CommonArgument, constant_value<0>, constant_value<1> > > > {
			typedef exponentiation_t<CommonArgument, addition_t<constant_value<1>, RightRightArgument> > type; // A * A^{Q} = A^{1 + Q}, end of recursion (simplify)
		};

		template<class CommonArgument, class LeftRightArgument, class RightRightArgument>
		struct product<power<CommonArgument, LeftRightArgument>, power<CommonArgument, RightRightArgument>, real_mapping, std::enable_if_t<!std::is_same_v<LeftRightArgument, RightRightArgument> > > {
			typedef exponentiation_t<CommonArgument, addition_t<LeftRightArgument, RightRightArgument> > type; // A^{P} * A^{Q} = A^{P + Q}, end of recursion (simplify)
		};

	}

}

#endif // __FUTURE_GA_PRODUCT_HPP__
