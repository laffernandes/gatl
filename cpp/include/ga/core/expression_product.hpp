#ifndef __GA_CORE_EXPRESSION_PRODUCT_HPP__
#define __GA_CORE_EXPRESSION_PRODUCT_HPP__

namespace ga {

	namespace detail {

		// Returns the simpler rational constant.
		template<default_integral_t Numerator, default_integral_t Denominator, default_integral_t GreatestCommonDivisor = gcd(iabs(Numerator), iabs(Denominator))>
		struct simpler_rational_constant {
			typedef product_t<constant_value<(sign(Numerator) * sign(Denominator)) * (iabs(Numerator) / GreatestCommonDivisor)>, power_t<constant_value<iabs(Denominator) / GreatestCommonDivisor>, constant_value<-1> >, value_mapping> type;
		};

		template<default_integral_t Numerator, default_integral_t Denominator>
		struct simpler_rational_constant<Numerator, Denominator, 1> {
			typedef mul_t<constant_value<(sign(Numerator) * sign(Denominator)) * iabs(Numerator)>, power_t<constant_value<iabs(Denominator)>, constant_value<-1> > > type;
		};

		template<default_integral_t Numerator, default_integral_t Denominator>
		using simpler_rational_constant_t = typename simpler_rational_constant<Numerator, Denominator>::type;

		// Specialization of _product_level5<LeftExpression, RightExpression> with simple bind or sort-and-bind patterns.
		template<typename LeftExpression, typename RightExpression>
		struct _product_level5 {
			typedef std::conditional_t<
				lt_v<LeftExpression, RightExpression>,
				mul_t<LeftExpression, RightExpression>, // bind
				mul_t<RightExpression, LeftExpression> // sort and bind
			> type;
		};

		// Specializations of _product_level5<LeftExpression, RightExpression> with at least one constant argument (simplify).
		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _product_level5<constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<LeftValue * RightValue> type; // A * B = C, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _product_level5<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> > > {
			typedef simpler_rational_constant_t<LeftValue, RightValue> type; // A * B^{-1} = simpler (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _product_level5<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue> > {
			typedef simpler_rational_constant_t<RightValue, LeftValue> type; // A^{-1} * B = simpler (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _product_level5<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> > > {
			typedef power_t<constant_value<LeftValue * RightValue>, constant_value<-1> > type; // A^{-1} * B^{-1} = (A * B)^{-1}, end of recursion (simplify)
		};

		// Specializations of _product_level4<LeftExpression, RightExpression> with some patterns to simplify (simplify).
		template<typename LeftExpression, typename RightExpression>
		struct _product_level4 {
			typedef typename _product_level5<LeftExpression, RightExpression>::type type;
		};

		template<typename CommonExpression>
		struct _product_level4<CommonExpression, CommonExpression> {
			typedef power_t<CommonExpression, constant_value<2> > type; // A * A = A^{2}, end of recursion (simplify)
		};

		template<typename CommonArgument, typename LeftRightArgument>
		struct _product_level4<power<CommonArgument, LeftRightArgument>, CommonArgument> {
			typedef power_t<CommonArgument, addition_t<LeftRightArgument, constant_value<1> > > type; // A^{P} * A = A^{P + 1}, end of recursion (simplify)
		};

		template<typename CommonArgument, typename RightRightArgument>
		struct _product_level4<CommonArgument, power<CommonArgument, RightRightArgument> > {
			typedef power_t<CommonArgument, addition_t<constant_value<1>, RightRightArgument> > type; // A * A^{Q} = A^{1 + Q}, end of recursion (simplify)
		};

		template<typename CommonArgument, typename LeftRightArgument, typename RightRightArgument>
		struct _product_level4<power<CommonArgument, LeftRightArgument>, power<CommonArgument, RightRightArgument> > {
			typedef power_t<CommonArgument, addition_t<LeftRightArgument, RightRightArgument> > type; // A^{P} * A^{Q} = A^{P + Q}, end of recursion (simplify)
		};

		template<typename CommonLeftArgument, typename CommonRightArgument>
		struct _product_level4<power<CommonLeftArgument, CommonRightArgument>, power<CommonLeftArgument, CommonRightArgument> > {
			typedef power_t<CommonLeftArgument, product_t<constant_value<2>, CommonRightArgument, value_mapping> > type; // A^{P} * A^{P} = A^{2 * P}, end of recursion (simplify)
		};

		// Specialization of _product_level3<LeftExpression, RightExpression> (merge mul<...>).
		template<typename LeftExpression, typename RightExpression, typename Enable = void>
		struct _product_level3;
		
		template<typename LeftExpression, typename RightExpression>
		struct _product_level3<LeftExpression, RightExpression, std::enable_if_t<!(is_function_v<name_t::mul, LeftExpression> || is_function_v<name_t::mul, RightExpression>)> > {
			typedef typename _product_level4<LeftExpression, RightExpression>::type type;
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
		struct _product_level3<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, std::enable_if_t<le_v<LeftArgument, RightArgument> > > {
			typedef product_t<LeftArgument, product_t<mul_t<LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, value_mapping>, value_mapping> type; // merge
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
		struct _product_level3<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftArgument> > > {
			typedef product_t<RightArgument, product_t<mul<LeftArgument, LeftNextArguments...>, mul_t<RightNextArguments...>, value_mapping>, value_mapping> type; // merge
		};

		template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
		struct _product_level3<LeftExpression, mul<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::mul, LeftExpression> && lt_v<RightArgument, LeftExpression> > > {
			typedef product_t<RightArgument, product_t<LeftExpression, mul_t<RightNextArguments...>, value_mapping>, value_mapping> type; // merge
		};

		template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
		struct _product_level3<LeftExpression, mul<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::mul, LeftExpression> && le_v<LeftExpression, RightArgument> && !std::is_same_v<product_t<LeftExpression, RightArgument, value_mapping>, mul<LeftExpression, RightArgument> > > > {
			typedef product_t<product_t<LeftExpression, RightArgument, value_mapping>, mul_t<RightNextArguments...>, value_mapping> type; // simplification found (simplify-and-merge)
		};

		template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
		struct _product_level3<LeftExpression, mul<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::mul, LeftExpression> && le_v<LeftExpression, RightArgument> && std::is_same_v<product_t<LeftExpression, RightArgument, value_mapping>, mul<LeftExpression, RightArgument> > > > {
			typedef mul_t<LeftExpression, RightArgument, RightNextArguments...> type; // no simplification found (bind)
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
		struct _product_level3<mul<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!is_function_v<name_t::mul, RightExpression> && le_v<LeftArgument, RightExpression> > > {
			typedef product_t<LeftArgument, product_t<mul_t<LeftNextArguments...>, RightExpression, value_mapping>, value_mapping> type; // merge
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
		struct _product_level3<mul<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!is_function_v<name_t::mul, RightExpression> && lt_v<RightExpression, LeftArgument> > > {
			typedef product_t<RightExpression, mul<LeftArgument, LeftNextArguments...>, value_mapping> type; // merge
		};

		// Specialization of _product_level2<LeftExpression, RightExpression>.
		template<typename LeftExpression, typename RightExpression>
		struct _product_level2 {
			typedef typename _product_level3<LeftExpression, RightExpression>::type type;
		};

		template<typename LeftExpression>
		struct _product_level2<LeftExpression, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<typename RightExpression>
		struct _product_level2<constant_value<0>, RightExpression> {
			typedef constant_value<0> type; // simplify
		};

		template<>
		struct _product_level2<constant_value<0>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<typename LeftExpression>
		struct _product_level2<LeftExpression, constant_value<1> > {
			typedef LeftExpression type; // simplify
		};

		template<typename RightExpression>
		struct _product_level2<constant_value<1>, RightExpression> {
			typedef RightExpression type; // simplify
		};

		template<>
		struct _product_level2<constant_value<1>, constant_value<1> > {
			typedef constant_value<1> type; // simplify
		};

		template<>
		struct _product_level2<constant_value<0>, constant_value<1> > {
			typedef constant_value<0> type; // simplify
		};

		template<>
		struct _product_level2<constant_value<1>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		// Specialization of _product_level1<LeftExpression, RightExpression, Mapping> (multiply components).
		template<typename LeftExpression, typename RightExpression, typename Mapping>
		struct _product_level1 {
			typedef typename _product_level2<LeftExpression, RightExpression>::type type;
		};

		template<typename Scalar, typename Components>
		struct _product_level1_distribute;

		template<typename Scalar, typename Coefficient, typename BasisBlade, typename... NextComponents>
		struct _product_level1_distribute<Scalar, add<component<Coefficient, BasisBlade>, NextComponents...> > {
			typedef addition_t<component_t<product_t<Scalar, Coefficient, value_mapping>, BasisBlade>, typename _product_level1_distribute<Scalar, add_t<NextComponents...> >::type> type;
		};

		template<typename Scalar, typename Coefficient, typename BasisBlade>
		struct _product_level1_distribute<Scalar, component<Coefficient, BasisBlade> > {
			typedef component_t<product_t<Scalar, Coefficient, value_mapping>, BasisBlade> type;
		};

		template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename Mapping>
		struct _product_level1<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping> :
			_product_level1_distribute<product_t<LeftCoefficient, RightCoefficient, value_mapping>, typename Mapping::template multiply<LeftBasisBlade, RightBasisBlade>::type> {
		};

		// Specialization of _product<add<...>, add<...>, Mapping>, product<LeftExpression, add<...>, Mapping>, and product<RightExpression, add<...>, Mapping> (distributive property over addition).
		template<typename LeftExpression, typename RightExpression, typename Mapping>
		struct _product {
			typedef typename _product_level1<LeftExpression, RightExpression, Mapping>::type type;
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments, typename Mapping>
		struct _product<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, Mapping> {
			typedef addition_t<addition_t<product_t<LeftArgument, RightArgument, Mapping>, product_t<add_t<LeftNextArguments...>, RightArgument, Mapping> >, addition_t<product_t<LeftArgument, add_t<RightNextArguments...>, Mapping>, product_t<add_t<LeftNextArguments...>, add_t<RightNextArguments...>, Mapping> > > type;
		};

		template<typename LeftExpression, typename RightArgument, typename... RightNextArguments, typename Mapping>
		struct _product<LeftExpression, add<RightArgument, RightNextArguments...>, Mapping> {
			typedef addition_t<product_t<LeftExpression, RightArgument, Mapping>, product_t<LeftExpression, add_t<RightNextArguments...>, Mapping> > type;
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression, typename Mapping>
		struct _product<add<LeftArgument, LeftNextArguments...>, RightExpression, Mapping> {
			typedef addition_t<product_t<LeftArgument, RightExpression, Mapping>, product_t<add_t<LeftNextArguments...>, RightExpression, Mapping> > type;
		};

	}

}

#endif // __GA_CORE_EXPRESSION_PRODUCT_HPP__
