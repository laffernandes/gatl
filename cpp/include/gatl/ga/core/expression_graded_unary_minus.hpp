/* Copyright (C) Leandro Augusto Frata Fernandes
 * 
 * author     : Fernandes, Leandro A. F.
 * e-mail     : laffernandes@ic.uff.br
 * home page  : http://www.ic.uff.br/~laffernandes
 * repository : https://github.com/laffernandes/gatl.git
 * 
 * This file is part of The Geometric Algebra Template Library (GATL).
 * 
 * GATL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * GATL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GATL. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __GA_CORE_EXPRESSION_GRADED_UNARY_MINUS_HPP__
#define __GA_CORE_EXPRESSION_GRADED_UNARY_MINUS_HPP__

namespace ga {

    namespace detail {

        // Graded-based unary minus operation.
        template<typename Expression, bitset_t SignChangePattern>
        struct graded_unary_minus;

        template<typename Expression, bitset_t SignChangePattern>
        using graded_unary_minus_t = typename graded_unary_minus<Expression, SignChangePattern>::type;

        template<typename Argument, typename... NextArguments, bitset_t SignChangePattern>
        struct graded_unary_minus<add<Argument, NextArguments...>, SignChangePattern> {
            using type = addition_t<
                graded_unary_minus_t<Argument, SignChangePattern>,
                graded_unary_minus_t<add_t<NextArguments...>, SignChangePattern>
            >;
        };

        template<typename Coefficient, bitset_t BasisVectors, bitset_t SignChangePattern>
        struct graded_unary_minus<component<Coefficient, constant_basis_blade<BasisVectors> >, SignChangePattern> {

#pragma warning( push )
#pragma warning( disable : 4805 )

            using type = std::conditional_t<
                (SignChangePattern & (bitset_t(1) << ones(BasisVectors))) == bitset_t(0),
                component<Coefficient, constant_basis_blade<BasisVectors> >,
                component_t<product_t<constant_value<-1>, Coefficient, value_mapping>, constant_basis_blade<BasisVectors> >
            >;

#pragma warning( pop )
        };

        template<typename Coefficient, bitset_t PossibleGrades, typename Bitset, bitset_t SignChangePattern>
        struct graded_unary_minus<component<Coefficient, dynamic_basis_blade<PossibleGrades, Bitset> >, SignChangePattern> {
            using type = std::conditional_t<
                (PossibleGrades & SignChangePattern) == bitset_t(0),
                component<Coefficient, dynamic_basis_blade<PossibleGrades, Bitset> >,
                component_t<
                    if_else_t<
                        equal_t<bitwise_and_t<constant_bitset<SignChangePattern>, bitwise_left_shift_t<constant_bitset<bitset_t(1)>, count_one_bits_t<Bitset> > >, constant_bitset<bitset_t(0)> >,
                        Coefficient,
                        product_t<constant_value<-1>, Coefficient, value_mapping>
                    >,
                    dynamic_basis_blade<PossibleGrades, Bitset>
                >
            >;
        };

    }

}

#endif // __GA_CORE_EXPRESSION_GRADED_UNARY_MINUS_HPP__
