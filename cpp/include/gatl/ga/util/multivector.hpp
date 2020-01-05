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

#ifndef __GA_UTIL_MULTIVECTOR_HPP__
#define __GA_UTIL_MULTIVECTOR_HPP__

namespace ga {

    namespace detail {

        // Helper structures for defining the expression of a multivector type with runtime defined coefficients over an n-dimensional vector space.
        template<bitset_t BasisVectors, bitset_t Bitset>
        struct make_kvector_expression;

        template<bitset_t BasisVectors, bitset_t Bitset>
        using make_kvector_expression_t = typename make_kvector_expression<BasisVectors, Bitset>::type;

        template<bitset_t BasisVectors, bitset_t Bitset>
        struct make_kvector_expression {
            using type = addition_t<component_t<stored_value, constant_basis_blade<Bitset> >, make_kvector_expression_t<BasisVectors, next_combination(Bitset, BasisVectors)> >;
        };

        template<bitset_t BasisVectors>
        struct make_kvector_expression<BasisVectors, bitset_t(0)> {
            using type = component_t<constant_value<0>, constant_basis_blade<bitset_t(0)> >;
        };

        template<bitset_t BasisVectors, grade_t FirstGrade, grade_t LastGrade>
        struct make_multivector_expression;

        template<bitset_t BasisVectors, grade_t FirstGrade, grade_t LastGrade>
        using make_multivector_expression_t = typename make_multivector_expression<BasisVectors, FirstGrade, LastGrade>::type;

        template<bitset_t BasisVectors, grade_t CurrentGrade, grade_t LastGrade>
        struct make_multivector_expression {
            using type = addition_t<make_kvector_expression_t<BasisVectors, first_combination(CurrentGrade)>, make_multivector_expression_t<BasisVectors, CurrentGrade + 1, LastGrade> >;
        };

        template<bitset_t BasisVectors, grade_t LastGrade>
        struct make_multivector_expression<BasisVectors, LastGrade, LastGrade> {
            using type = make_kvector_expression_t<BasisVectors, first_combination(LastGrade)>;
        };

        template<bitset_t BasisVectors, grade_t LastGrade>
        struct make_multivector_expression<BasisVectors, 0, LastGrade> {
            using type = addition_t<component_t<stored_value, constant_basis_blade<bitset_t(0)> >, make_multivector_expression_t<BasisVectors, 1, LastGrade> >;
        };

        template<bitset_t BasisVectors>
        struct make_multivector_expression<BasisVectors, 0, 0> {
            using type = component_t<stored_value, constant_basis_blade<bitset_t(0)> >;
        };

        template<typename Expression>
        struct make_derived_multivector_expression;

        template<typename Expression>
        using make_derived_multivector_expression_t = typename make_derived_multivector_expression<Expression>::type;

        template<typename Coefficient, typename BasisBlade, typename... NextComponents>
        struct make_derived_multivector_expression<add<component<Coefficient, BasisBlade>, NextComponents...> > {
            using type = addition_t<component_t<stored_value, BasisBlade>, make_derived_multivector_expression_t<add_t<NextComponents...> > >;
        };

        template<bitset_t PossibleGrades, typename... NextComponents>
        struct make_derived_multivector_expression<add<component<stored_map_values, dynamic_basis_blade<PossibleGrades, stored_map_bitsets> >, NextComponents...> > {
            using type = addition_t<component_t<stored_map_values, dynamic_basis_blade<PossibleGrades, stored_map_bitsets> >, make_derived_multivector_expression_t<add_t<NextComponents...> > >;
        };

        template<typename Coefficient, typename BasisBlade>
        struct make_derived_multivector_expression<component<Coefficient, BasisBlade> > {
            using type = component_t<stored_value, BasisBlade>;
        };

        template<bitset_t PossibleGrades>
        struct make_derived_multivector_expression<component<stored_map_values, dynamic_basis_blade<PossibleGrades, stored_map_bitsets> > > {
            using type = component_t<stored_map_values, dynamic_basis_blade<PossibleGrades, stored_map_bitsets> >;
        };

    }

    // Helper for defining a multivector type with runtime defined coefficients over an n-dimensional vector space.
    template<typename CoefficientType, ndims_t VectorSpaceDimensions, grade_t FirstGrade = 0, grade_t LastGrade = VectorSpaceDimensions>
    using full_multivector_t = clifford_expression<CoefficientType, detail::make_multivector_expression_t<detail::first_combination(VectorSpaceDimensions), FirstGrade, LastGrade> >;

    // Helper for defining a k-vector type with runtime defined coefficients over an n-dimensional vector space.
    template<typename CoefficientType, ndims_t VectorSpaceDimensions, grade_t Grade>
    using full_kvector_t = full_multivector_t<CoefficientType, VectorSpaceDimensions, Grade, Grade>;

    // Helper for defining a vector type with runtime defined coefficients over an n-dimensional vector space.
    template<typename CoefficientType, ndims_t VectorSpaceDimensions>
    using full_vector_t = full_kvector_t<CoefficientType, VectorSpaceDimensions, 1>;

    // Helper for defining a multivector type with runtime defined coefficients in all components of the given expression.
    template<typename CoefficientType, typename Expression>
    using full_derived_multivector_t = clifford_expression<CoefficientType, detail::make_derived_multivector_expression_t<Expression> >;
}

#endif // __GA_UTIL_MULTIVECTOR_HPP__
