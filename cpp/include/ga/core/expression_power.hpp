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

#ifndef __GA_CORE_EXPRESSION_POWER_HPP__
#define __GA_CORE_EXPRESSION_POWER_HPP__

namespace ga {

    namespace detail {

        // Returns the power of the given integral value.
        template<default_integral_t Base, default_integral_t Exponent>
        struct simpler_ipow {
            using type = constant_value<ipow(Base, Exponent)>;
        };

        template<default_integral_t Base, default_integral_t Exponent>
        using simpler_ipow_t = typename simpler_ipow<Base, Exponent>::type;

        // Returns the square root of the given integral value.
        template<default_integral_t Value, typename Enable = void>
        struct simpler_isqrt;
        
        template<default_integral_t Value>
        struct simpler_isqrt<Value, std::enable_if_t<(Value > 0)> > {
        private:

            constexpr static default_integral_t result = isqrt(Value);

        public:

            using type = std::conditional_t<
                (result * result) == Value,
                constant_value<result>,
                power<constant_value<Value>, power<constant_value<2>, constant_value<-1> > >
            >;
        };

        template<default_integral_t Value>
        using simpler_isqrt_t = typename simpler_isqrt<Value>::type;

        // Specializations of _power_level2<LeftArgument, RightArgument>.
        template<typename LeftExpression, typename RightExpression>
        struct _power_level2 {
            using type = power<LeftExpression, RightExpression>; // default (bind)
        };

        template<typename RightExpression>
        struct _power_level2<constant_value<0>, RightExpression> {
            using type = std::conditional_t<
                is_constant_expression_v<RightExpression>,
                std::conditional_t<
                    may_be_positive_v<RightExpression>,
                    constant_value<0>, // 0^{X} = 0, for X > 0 (simplify)
                    nullptr_t // the value of pow(0, X) is undefined for X <= 0
                >,
                power<constant_value<0>, RightExpression>
            >;
        };

        template<typename RightExpression>
        struct _power_level2<constant_value<1>, RightExpression> {
            using type = constant_value<1>; // 1^{X} = 1 (simplify)
        };

        template<default_integral_t LeftValue, default_integral_t RightValue>
        struct _power_level2<constant_value<LeftValue>, constant_value<RightValue> > {
            using type = std::conditional_t<
                LeftValue == -1,
                std::conditional_t<
                    (RightValue & 1) == 0,
                    constant_value<1>, // (-1)^{K} = 1, if K is odd (simplify)
                    constant_value<-1> // (-1)^{K} = -1, if K is even (simplify)
                >,
                std::conditional_t<
                    (RightValue > 0),
                    simpler_ipow_t<LeftValue, iabs(RightValue)>, // X^{Y} = simpler (simplify)
                    power<simpler_ipow_t<LeftValue, iabs(RightValue)>, constant_value<-1> > // X^{Y} = simpler (simplify and bind)
                >
            >;
        };

        template<default_integral_t RightValue>
        struct _power_level2<constant_value<0>, constant_value<RightValue> > {
            using type = std::conditional_t<
                (RightValue > 0),
                constant_value<0>, // 0^{X} = 0, for X > 0 (simplify)
                nullptr_t // the value of pow(0, X) is undefined for X <= 0
            >;
        };

        template<default_integral_t RightValue>
        struct _power_level2<constant_value<1>, constant_value<RightValue> > {
            using type = constant_value<1>; // 1^{K} = 1 (simplify)
        };

        template<default_integral_t LeftValue>
        struct _power_level2<constant_value<LeftValue>, power<constant_value<2>, constant_value<-1> > > {
            using type = simpler_isqrt_t<LeftValue>; // sqrt(X) = Y, if it is possible simplify for given integer X and Y values (simplify)
        };

        template<>
        struct _power_level2<constant_value<0>, power<constant_value<2>, constant_value<-1> > > {
            using type = constant_value<0>; // sqrt(0) = 0 (simplify)
        };

        template<>
        struct _power_level2<constant_value<1>, power<constant_value<2>, constant_value<-1> > > {
            using type = constant_value<1>; // sqrt(1) = 1 (simplify)
        };

        // Specializations of _power_level1<LeftArgument, RightArgument>.
        template<typename LeftArgument, typename RightArgument>
        struct _power_level1 {
            using type = typename _power_level2<LeftArgument, RightArgument>::type;
        };

        template<typename LeftExpression>
        struct _power_level1<LeftExpression, constant_value<0> > {
            using type = constant_value<1>; // X^{0} = 1 (simplify)
        };

        template<typename LeftExpression>
        struct _power_level1<LeftExpression, constant_value<1> > {
            using type = LeftExpression; // X^{1} = X (simplify)
        };

        // Specializations of _power<LeftArgument, RightArgument> (distributive property over multiplication).
        template<typename LeftArgument, typename RightArgument>
        struct _power {
            using type = typename _power_level1<LeftArgument, RightArgument>::type;
        };

        template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
        struct _power<mul<LeftArgument, LeftNextArguments...>, RightExpression> {
            using type = product_t<power_t<LeftArgument, RightExpression>, power_t<mul_t<LeftNextArguments...>, RightExpression>, value_mapping>; // (A * B)^{C} = A^{C} * B^{C}
        };

        template<typename LeftLeftArgument, typename LeftRightArgument, typename RightExpression>
        struct _power<power<LeftLeftArgument, LeftRightArgument>, RightExpression> {
            using type = power_t<LeftLeftArgument, product_t<LeftRightArgument, RightExpression, value_mapping> >; // (A^{B})^{C} = A^{B * C} (simplify)
        };
    }

}

#endif // __GA_CORE_EXPRESSION_POWER_HPP__
