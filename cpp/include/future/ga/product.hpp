#ifndef __FUTURE_GA_PRODUCT_HPP__
#define __FUTURE_GA_PRODUCT_HPP__

namespace ga {

	namespace detail {

		// Specializations of product<LeftExpression, RightExpression> with mul<...>.
		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct product<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<le_v<LeftArgument, RightArgument> > > {
			typedef product_t<LeftArgument, product_t<mul_t<LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, real_mapping>, real_mapping> type; // merge
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct product<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<lt_v<RightArgument, LeftArgument> > > {
			typedef product_t<RightArgument, product_t<mul<LeftArgument, LeftNextArguments...>, mul_t<RightNextArguments...>, real_mapping>, real_mapping> type; // merge
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct product<LeftExpression, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<lt_v<RightArgument, LeftExpression> > > {
			typedef product_t<RightArgument, product_t<LeftExpression, mul_t<RightNextArguments...>, real_mapping>, real_mapping> type; // merge
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct product<LeftExpression, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<le_v<LeftExpression, RightArgument> && !std::is_same_v<product_t<LeftExpression, RightArgument, real_mapping>, mul<LeftExpression, RightArgument> > > > {
			typedef product_t<product_t<LeftExpression, RightArgument, real_mapping>, mul_t<RightNextArguments...>, real_mapping> type; // simplification found (simplify-and-merge)
		};

		template<class LeftExpression, class RightArgument, class... RightNextArguments>
		struct product<LeftExpression, mul<RightArgument, RightNextArguments...>, real_mapping, std::enable_if_t<le_v<LeftExpression, RightArgument> && std::is_same_v<product_t<LeftExpression, RightArgument, real_mapping>, mul<LeftExpression, RightArgument> > > > {
			typedef mul_t<LeftExpression, RightArgument, RightNextArguments...> type; // no simplification found (bind)
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct product<mul<LeftArgument, LeftNextArguments...>, RightExpression, real_mapping, std::enable_if_t<le_v<LeftArgument, RightExpression> > > {
			typedef product_t<LeftArgument, product_t<mul_t<LeftNextArguments...>, RightExpression, real_mapping>, real_mapping> type; // merge
		};

		template<class LeftArgument, class... LeftNextArguments, class RightExpression>
		struct product<mul<LeftArgument, LeftNextArguments...>, RightExpression, real_mapping, std::enable_if_t<lt_v<RightExpression, LeftArgument> > > {
			typedef product_t<RightExpression, mul<LeftArgument, LeftNextArguments...>, real_mapping> type; // merge
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

		// Specialization of product<LeftExpression, RightExpression, Mapping> with simple bind or sort-and-bind patterns.
		template<class LeftExpression, class RightExpression, class Enable = void>
		struct _product_bind_sorted;

		template<class LeftExpression, class RightExpression>
		struct _product_bind_sorted<LeftExpression, RightExpression, std::enable_if_t<lt_v<LeftExpression, RightExpression> > > {
			typedef mul_t<LeftExpression, RightExpression> type; // bind
		};

		template<class LeftExpression, class RightExpression>
		struct _product_bind_sorted<LeftExpression, RightExpression, std::enable_if_t<lt_v<RightExpression, LeftExpression> > > {
			typedef mul_t<RightExpression, LeftExpression> type; // sort and bind
		};

		template<class LeftExpression, class RightExpression>
		using _product_bind_sorted_t = typename _product_bind_sorted<LeftExpression, RightExpression>::type;

		template<default_integral_t LeftValue, id_t RightId, std::size_t RightIndex>
		struct product<constant_value<LeftValue>, get_value<RightId, RightIndex>, real_mapping> {
			typedef mul_t<constant_value<LeftValue>, get_value<RightId, RightIndex> > type; // bind
		};

		template<id_t LeftId, std::size_t LeftIndex, default_integral_t RightValue>
		struct product<get_value<LeftId, LeftIndex>, constant_value<RightValue>, real_mapping> {
			typedef mul_t<constant_value<RightValue>, get_value<LeftId, LeftIndex> > type; // sort and bind
		};

		template<default_integral_t LeftValue>
		struct product<constant_value<LeftValue>, stored_value, real_mapping> {
			typedef mul_t<constant_value<LeftValue>, stored_value> type; // bind
		};

		template<default_integral_t RightValue>
		struct product<stored_value, constant_value<RightValue>, real_mapping> {
			typedef mul_t<constant_value<RightValue>, stored_value> type; // sort and bind
		};

		template<default_integral_t LeftValue, name_t RightName, class... RightArguments>
		struct product<constant_value<LeftValue>, function<RightName, RightArguments...>, real_mapping, std::enable_if_t<RightName != name_t::add && RightName != name_t::mul> > {
			typedef _product_bind_sorted_t<constant_value<LeftValue>, function<RightName, RightArguments...> > type; // bind or sort-and-bind
		};

		template<name_t LeftName, class... LeftArguments, default_integral_t RightValue>
		struct product<function<LeftName, LeftArguments...>, constant_value<RightValue>, real_mapping, std::enable_if_t<LeftName != name_t::add && LeftName != name_t::mul> > {
			typedef _product_bind_sorted_t<function<LeftName, LeftArguments...>, constant_value<RightValue> > type; // bind or sort-and-bind
		};

		template<id_t LeftId, std::size_t LeftIndex, id_t RightId, std::size_t RightIndex>
		struct product<get_value<LeftId, LeftIndex>, get_value<RightId, RightIndex>, real_mapping, std::enable_if_t<LeftId != RightId && LeftIndex != RightIndex> > {
			typedef _product_bind_sorted_t<get_value<LeftId, LeftIndex>, get_value<RightId, RightIndex> > type; // bind or sort-and-bind
		};

		template<id_t LeftId, std::size_t LeftIndex>
		struct product<get_value<LeftId, LeftIndex>, stored_value, real_mapping> {
			typedef mul_t<get_value<LeftId, LeftIndex>, stored_value> type; // bind
		};

		template<id_t RightId, std::size_t RightIndex>
		struct product<stored_value, get_value<RightId, RightIndex>, real_mapping> {
			typedef mul_t<get_value<RightId, RightIndex>, stored_value> type; // sort and bind
		};

		template<id_t LeftId, std::size_t LeftIndex, name_t RightName, class... RightArguments>
		struct product<get_value<LeftId, LeftIndex>, function<RightName, RightArguments...>, real_mapping> {
			typedef _product_bind_sorted_t<get_value<LeftId, LeftIndex>, function<RightName, RightArguments...> > type; // bind or sort-and-bind
		};

		template<name_t LeftName, class... LeftArguments, id_t RightId, std::size_t RightIndex>
		struct product<function<LeftName, LeftArguments...>, get_value<RightId, RightIndex>, real_mapping> {
			typedef _product_bind_sorted_t<function<LeftName, LeftArguments...>, get_value<RightId, RightIndex> > type; // bind or sort-and-bind
		};

		template<name_t RightName, class... RightArguments>
		struct product<stored_value, function<RightName, RightArguments...>, real_mapping> {
			typedef _product_bind_sorted_t<stored_value, function<RightName, RightArguments...> > type; // bind or sort-and-bind
		};

		template<name_t LeftName, class... LeftArguments>
		struct product<function<LeftName, LeftArguments...>, stored_value, real_mapping> {
			typedef _product_bind_sorted_t<function<LeftName, LeftArguments...>, stored_value> type; // bind or sort-and-bind
		};

		template<name_t LeftName, class... LeftArguments, name_t RightName, class... RightArguments>
		struct product<function<LeftName, LeftArguments...>, function<RightName, RightArguments...>, real_mapping, std::enable_if_t<!std::is_same_v<function<LeftName, LeftArguments...>, function<RightName, RightArguments...> > > > {
			typedef _product_bind_sorted_t<function<LeftName, LeftArguments...>, function<RightName, RightArguments...> > type; // bind or sort-and-bind
		};

		// Specialization of product<component<...>, component<...>, Mapping> (merge or simplify).
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

		// Specializations of product<LeftExpression, RightExpression, Mapping> with at least one constant argument (simplify).
		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct product<constant_value<LeftValue>, constant_value<RightValue>, real_mapping> {
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
		struct product<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> >, real_mapping, std::enable_if_t<LeftValue != -1 && LeftValue != RightValue> > {
			typedef simpler_rational_constant_t<LeftValue, RightValue> type; // A * B^{-1} = simpler (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct product<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue>, real_mapping, std::enable_if_t<RightValue != -1 && LeftValue != RightValue> > {
			typedef simpler_rational_constant_t<RightValue, LeftValue> type; // A^{-1} * B = simpler (simplify)
		};

		// Specializations of product<LeftExpression, RightExpression, Mapping> with some patterns to simplify (simplify).
		template<id_t CommonId, std::size_t CommonIndex>
		struct product<get_value<CommonId, CommonIndex>, get_value<CommonId, CommonIndex>, real_mapping> {
			typedef exponentiation_t<get_value<CommonId, CommonIndex>, constant_value<2>()> type; // A * A = A^{2}, end of recursion (simplify)
		};

		template<name_t CommonName, class... CommonArguments>
		struct product<function<CommonName, CommonArguments...>, function<CommonName, CommonArguments...>, real_mapping> {
			typedef exponentiation_t<function<CommonName, CommonArguments...>, constant_value<2>()> type; // A * A = A^{2}, end of recursion (simplify)
		};

		template<class CommonArgument, class LeftRightArgument>
		struct product<power<CommonArgument, LeftRightArgument>, CommonArgument, real_mapping> {
			typedef exponentiation_t<CommonArgument, addition_t<LeftRightArgument, constant_value<1> > > type; // A^{P} * A = A^{P + 1}, end of recursion (simplify)
		};

		template<class CommonArgument, class RightRightArgument>
		struct product<CommonArgument, power<CommonArgument, RightRightArgument>, real_mapping> {
			typedef exponentiation_t<CommonArgument, addition_t<constant_value<1>, RightRightArgument> > type; // A * A^{Q} = A^{1 + Q}, end of recursion (simplify)
		};

		template<class CommonArgument, class LeftRightArgument, class RightRightArgument>
		struct product<power<CommonArgument, LeftRightArgument>, power<CommonArgument, RightRightArgument>, real_mapping, std::enable_if_t<!std::is_same_v<LeftRightArgument, RightRightArgument> > > {
			typedef exponentiation_t<CommonArgument, addition_t<LeftRightArgument, RightRightArgument> > type; // A^{P} * A^{Q} = A^{P + Q}, end of recursion (simplify)
		};

	}

}

#endif // __FUTURE_GA_PRODUCT_HPP__
