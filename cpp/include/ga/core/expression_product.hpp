/**
Copyright (C) 2018 Leandro Augusto Frata Fernandes

author     : Fernandes, Leandro A. F.
e-mail     : laffernandes@ic.uff.br
home page  : http://www.ic.uff.br/~laffernandes
repository : https://github.com/laffernandes/gatl.git

This file is part of The Geometric Algebra Template Library (GATL).

GATL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GATL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GATL. If not, see <https://www.gnu.org/licenses/>.
/**/

#ifndef __GA_CORE_EXPRESSION_PRODUCT_HPP__
#define __GA_CORE_EXPRESSION_PRODUCT_HPP__

namespace ga {

	namespace detail {

		// Returns the simpler rational constant.
		template<default_integral_t Numerator, default_integral_t Denominator, default_integral_t GreatestCommonDivisor = gcd(iabs(Numerator), iabs(Denominator))>
		struct simpler_rational_constant {
			using type = product_t<constant_value<(sign(Numerator) * sign(Denominator)) * (iabs(Numerator) / GreatestCommonDivisor)>, power_t<constant_value<iabs(Denominator) / GreatestCommonDivisor>, constant_value<-1> >, value_mapping>;
		};

		template<default_integral_t Numerator, default_integral_t Denominator>
		struct simpler_rational_constant<Numerator, Denominator, 1> {
			using type = mul_t<constant_value<(sign(Numerator) * sign(Denominator)) * iabs(Numerator)>, power_t<constant_value<iabs(Denominator)>, constant_value<-1> > >;
		};

		template<default_integral_t Numerator, default_integral_t Denominator>
		using simpler_rational_constant_t = typename simpler_rational_constant<Numerator, Denominator>::type;

		// Specialization of _product_level5<LeftExpression, RightExpression> with simple bind or sort-and-bind patterns.
		template<typename LeftExpression, typename RightExpression>
		struct _product_level5 {
			using type = std::conditional_t<
				lt_v<LeftExpression, RightExpression>,
				mul_t<LeftExpression, RightExpression>, // bind
				mul_t<RightExpression, LeftExpression> // sort and bind
			>;
		};

		// Specializations of _product_level5<LeftExpression, RightExpression> with at least one constant argument (simplify).
		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _product_level5<constant_value<LeftValue>, constant_value<RightValue> > {
			using type = constant_value<LeftValue * RightValue>; // A * B = C, end of recursion (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _product_level5<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> > > {
			using type = simpler_rational_constant_t<LeftValue, RightValue>; // A * B^{-1} = simpler (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _product_level5<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue> > {
			using type = simpler_rational_constant_t<RightValue, LeftValue>; // A^{-1} * B = simpler (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _product_level5<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> > > {
			using type = power_t<constant_value<LeftValue * RightValue>, constant_value<-1> >; // A^{-1} * B^{-1} = (A * B)^{-1}, end of recursion (simplify)
		};

		// Specializations of _product_level4<LeftExpression, RightExpression> with some patterns to simplify (simplify).
		template<typename LeftExpression, typename RightExpression>
		struct _product_level4 {
			using type = typename _product_level5<LeftExpression, RightExpression>::type;
		};

		template<typename CommonExpression>
		struct _product_level4<CommonExpression, CommonExpression> {
			using type = power_t<CommonExpression, constant_value<2> >; // A * A = A^{2}, end of recursion (simplify)
		};

		template<typename CommonArgument, typename LeftRightArgument>
		struct _product_level4<power<CommonArgument, LeftRightArgument>, CommonArgument> {
			using type = power_t<CommonArgument, addition_t<LeftRightArgument, constant_value<1> > >; // A^{P} * A = A^{P + 1}, end of recursion (simplify)
		};

		template<typename CommonArgument, typename RightRightArgument>
		struct _product_level4<CommonArgument, power<CommonArgument, RightRightArgument> > {
			using type = power_t<CommonArgument, addition_t<constant_value<1>, RightRightArgument> >; // A * A^{Q} = A^{1 + Q}, end of recursion (simplify)
		};

		template<typename CommonArgument, typename LeftRightArgument, typename RightRightArgument>
		struct _product_level4<power<CommonArgument, LeftRightArgument>, power<CommonArgument, RightRightArgument> > {
			using type = power_t<CommonArgument, addition_t<LeftRightArgument, RightRightArgument> >; // A^{P} * A^{Q} = A^{P + Q}, end of recursion (simplify)
		};

		template<typename CommonLeftArgument, typename CommonRightArgument>
		struct _product_level4<power<CommonLeftArgument, CommonRightArgument>, power<CommonLeftArgument, CommonRightArgument> > {
			using type = power_t<CommonLeftArgument, product_t<constant_value<2>, CommonRightArgument, value_mapping> >; // A^{P} * A^{P} = A^{2 * P}, end of recursion (simplify)
		};

		// Specialization of _product_level3<LeftExpression, RightExpression> (merge mul<...>).
		template<typename LeftExpression, typename RightExpression, typename Enable = void>
		struct _product_level3;
		
		template<typename LeftExpression, typename RightExpression>
		struct _product_level3<LeftExpression, RightExpression, std::enable_if_t<!(is_function_v<name_t::mul, LeftExpression> || is_function_v<name_t::mul, RightExpression>)> > {
			using type = typename _product_level4<LeftExpression, RightExpression>::type;
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
		struct _product_level3<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, std::enable_if_t<le_v<LeftArgument, RightArgument> > > {
			using type = product_t<LeftArgument, product_t<mul_t<LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, value_mapping>, value_mapping>; // merge
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
		struct _product_level3<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftArgument> > > {
			using type = product_t<RightArgument, product_t<mul<LeftArgument, LeftNextArguments...>, mul_t<RightNextArguments...>, value_mapping>, value_mapping>; // merge
		};

		template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
		struct _product_level3<LeftExpression, mul<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::mul, LeftExpression> && lt_v<RightArgument, LeftExpression> > > {
			using type = product_t<RightArgument, product_t<LeftExpression, mul_t<RightNextArguments...>, value_mapping>, value_mapping>; // merge
		};

		template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
		struct _product_level3<LeftExpression, mul<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::mul, LeftExpression> && le_v<LeftExpression, RightArgument> && !std::is_same_v<product_t<LeftExpression, RightArgument, value_mapping>, mul<LeftExpression, RightArgument> > > > {
			using type = product_t<product_t<LeftExpression, RightArgument, value_mapping>, mul_t<RightNextArguments...>, value_mapping>; // simplification found (simplify-and-merge)
		};

		template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
		struct _product_level3<LeftExpression, mul<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::mul, LeftExpression> && le_v<LeftExpression, RightArgument> && std::is_same_v<product_t<LeftExpression, RightArgument, value_mapping>, mul<LeftExpression, RightArgument> > > > {
			using type = mul_t<LeftExpression, RightArgument, RightNextArguments...>; // no simplification found (bind)
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
		struct _product_level3<mul<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!is_function_v<name_t::mul, RightExpression> && le_v<LeftArgument, RightExpression> > > {
			using type = product_t<LeftArgument, product_t<mul_t<LeftNextArguments...>, RightExpression, value_mapping>, value_mapping>; // merge
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
		struct _product_level3<mul<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!is_function_v<name_t::mul, RightExpression> && lt_v<RightExpression, LeftArgument> > > {
			using type = product_t<RightExpression, mul<LeftArgument, LeftNextArguments...>, value_mapping>; // merge
		};

		// Specialization of _product_level2<LeftExpression, RightExpression>.
		template<typename LeftExpression, typename RightExpression>
		struct _product_level2 {
			using type = typename _product_level3<LeftExpression, RightExpression>::type;
		};

		template<typename LeftExpression>
		struct _product_level2<LeftExpression, constant_value<0> > {
			using type = constant_value<0>; // simplify
		};

		template<typename RightExpression>
		struct _product_level2<constant_value<0>, RightExpression> {
			using type = constant_value<0>; // simplify
		};

		template<>
		struct _product_level2<constant_value<0>, constant_value<0> > {
			using type = constant_value<0>; // simplify
		};

		template<typename LeftExpression>
		struct _product_level2<LeftExpression, constant_value<1> > {
			using type = LeftExpression; // simplify
		};

		template<typename RightExpression>
		struct _product_level2<constant_value<1>, RightExpression> {
			using type = RightExpression; // simplify
		};

		template<>
		struct _product_level2<constant_value<1>, constant_value<1> > {
			using type = constant_value<1>; // simplify
		};

		template<>
		struct _product_level2<constant_value<0>, constant_value<1> > {
			using type = constant_value<0>; // simplify
		};

		template<>
		struct _product_level2<constant_value<1>, constant_value<0> > {
			using type = constant_value<0>; // simplify
		};

		// Specialization of _product_level1<LeftExpression, RightExpression, Mapping> (multiply components).
		template<typename LeftExpression, typename RightExpression, typename Mapping>
		struct _product_level1 {
			using type = typename _product_level2<LeftExpression, RightExpression>::type;
		};

		template<typename Scalar, typename Components>
		struct _product_level1_distribute;

		template<typename Scalar, typename Coefficient, typename BasisBlade, typename... NextComponents>
		struct _product_level1_distribute<Scalar, add<component<Coefficient, BasisBlade>, NextComponents...> > {
			using type = addition_t<component_t<product_t<Scalar, Coefficient, value_mapping>, BasisBlade>, typename _product_level1_distribute<Scalar, add_t<NextComponents...> >::type>;
		};

		template<typename Scalar, typename Coefficient, typename BasisBlade>
		struct _product_level1_distribute<Scalar, component<Coefficient, BasisBlade> > {
			using type = component_t<product_t<Scalar, Coefficient, value_mapping>, BasisBlade>;
		};

		template<typename LeftCoefficient, typename LeftBasisBlade, typename RightCoefficient, typename RightBasisBlade, typename Mapping>
		struct _product_level1<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade>, Mapping> :
			_product_level1_distribute<product_t<LeftCoefficient, RightCoefficient, value_mapping>, typename Mapping::template multiply<LeftBasisBlade, RightBasisBlade>::type> {
		};

		// Specialization of _product<add<...>, add<...>, Mapping>, product<LeftExpression, add<...>, Mapping>, and product<RightExpression, add<...>, Mapping> (distributive property over addition).
		template<typename LeftExpression, typename RightExpression, typename Mapping>
		struct _product {
			using type = typename _product_level1<LeftExpression, RightExpression, Mapping>::type;
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments, typename Mapping>
		struct _product<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, Mapping> {
			using type = addition_t<addition_t<product_t<LeftArgument, RightArgument, Mapping>, product_t<add_t<LeftNextArguments...>, RightArgument, Mapping> >, addition_t<product_t<LeftArgument, add_t<RightNextArguments...>, Mapping>, product_t<add_t<LeftNextArguments...>, add_t<RightNextArguments...>, Mapping> > >;
		};

		template<typename LeftExpression, typename RightArgument, typename... RightNextArguments, typename Mapping>
		struct _product<LeftExpression, add<RightArgument, RightNextArguments...>, Mapping> {
			using type = addition_t<product_t<LeftExpression, RightArgument, Mapping>, product_t<LeftExpression, add_t<RightNextArguments...>, Mapping> >;
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression, typename Mapping>
		struct _product<add<LeftArgument, LeftNextArguments...>, RightExpression, Mapping> {
			using type = addition_t<product_t<LeftArgument, RightExpression, Mapping>, product_t<add_t<LeftNextArguments...>, RightExpression, Mapping> >;
		};

	}

}

#endif // __GA_CORE_EXPRESSION_PRODUCT_HPP__
