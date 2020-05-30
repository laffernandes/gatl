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

#ifndef __GA_EXTRA_TAKE_GRADE_HPP__
#define __GA_EXTRA_TAKE_GRADE_HPP__

namespace ga {

    namespace detail {

        // Returns the k-grade part of the given Clifford expression.
        template<typename Expression, typename GradeExpression>
        struct keep_grade;

        template<typename Expression, typename GradeExpression>
        using keep_grade_t = typename keep_grade<Expression, GradeExpression>::type;

        template<typename Argument, typename... NextArguments, typename GradeExpression>
        struct keep_grade<add<Argument, NextArguments...>, GradeExpression> {
            using type = addition_t<
                keep_grade_t<Argument, GradeExpression>,
                keep_grade_t<add_t<NextArguments...>, GradeExpression>
            >;
        };

        template<typename Coefficient, bitset_t BasisVectors, default_integral_t GradeValue>
        struct keep_grade<component<Coefficient, constant_basis_blade<BasisVectors> >, component<constant_value<GradeValue>, constant_basis_blade<bitset_t(0)> > > {
            using type = std::conditional_t<
                ones(BasisVectors) == GradeValue,
                component<Coefficient, constant_basis_blade<BasisVectors> >,
                component<constant_value<0>, constant_basis_blade<bitset_t(0)> >
            >;
        };

        template<typename Coefficient, bitset_t PossibleGrades, typename Bitset, default_integral_t GradeValue>
        struct keep_grade<component<Coefficient, dynamic_basis_blade<PossibleGrades, Bitset> >, component<constant_value<GradeValue>, constant_basis_blade<bitset_t(0)> > > {
            using type = std::conditional_t<
                0 <= GradeValue && GradeValue <= GA_MAX_BASIS_VECTOR_INDEX && (PossibleGrades & (bitset_t(1) << GradeValue)) != bitset_t(0),
                component_t<
                    if_else_t<
                        equal_t<count_one_bits_t<Bitset>, constant_value<GradeValue> >,
                        Coefficient,
                        constant_value<0>
                    >,
                    dynamic_basis_blade_t<(bitset_t(1) << GradeValue), Bitset>
                >,
                component<constant_value<0>, constant_basis_blade<bitset_t(0)> >
            >;
        };

        template<typename Coefficient, typename BasisBlade, typename Grade>
        struct keep_grade<component<Coefficient, BasisBlade>, component<Grade, constant_basis_blade<bitset_t(0)> > > {
            using type = component_t<
                if_else_t<
                    equal_t<count_one_bits_t<basis_vectors_t<BasisBlade> >, Grade>,
                    Coefficient,
                    constant_value<0>
                >,
                BasisBlade
            >;
        };

    }

    // Returns the k-grade part of the given Clifford expression.
    template<typename CoefficientType, typename Expression, typename GradeCoefficientType, typename GradeCoefficient, std::enable_if_t<std::is_constructible_v<grade_t, GradeCoefficientType>, int> = 0>
    constexpr decltype(auto) take_grade(clifford_expression<CoefficientType, Expression> const &arg, scalar_clifford_expression<GradeCoefficientType, GradeCoefficient> const &k) GA_NOEXCEPT {
        auto lazy = make_lazy_context(arg, k);
        return lazy.eval(clifford_expression<default_integral_t, detail::keep_grade_t<typename decltype(lazy)::template argument_expression_t<0>, typename decltype(lazy)::template argument_expression_t<1> > >());
    }

    template<typename Type, typename GradeCoefficientType, typename GradeCoefficient, std::enable_if_t<std::is_constructible_v<grade_t, GradeCoefficientType>, int> = 0>
    constexpr decltype(auto) take_grade(Type const &arg, scalar_clifford_expression<GradeCoefficientType, GradeCoefficient> const &k) GA_NOEXCEPT {
        return take_grade(scalar(arg), k);
    }

    template<typename CoefficientType, typename Expression>
    constexpr decltype(auto) take_grade(clifford_expression<CoefficientType, Expression> const &arg, grade_t const k) GA_NOEXCEPT {
        return take_grade(arg, scalar(k));
    }

    template<typename Type>
    constexpr decltype(auto) take_grade(Type const &arg, grade_t const k) GA_NOEXCEPT {
        return take_grade(scalar(arg), scalar(k));
    }

    // Returns the portion of the given Clifford expression with the largest grade.
    template<typename CoefficientType, typename Expression, typename ToleranceType>
    constexpr decltype(auto) take_largest_grade(clifford_expression<CoefficientType, Expression> const &arg, ToleranceType const &tol) GA_NOEXCEPT {
        auto [lazy, arg_, tol_] = make_lazy_context_tuple(arg, scalar(tol));
        return lazy.eval(take_grade(arg_, largest_grade(arg_, tol_)));
    }

    template<typename CoefficientType, typename Expression>
    constexpr decltype(auto) take_largest_grade(clifford_expression<CoefficientType, Expression> const &arg) GA_NOEXCEPT {
        return take_largest_grade(arg, default_tolerance<CoefficientType>());
    }

    template<typename Type, typename ToleranceType>
    constexpr decltype(auto) take_largest_grade(Type const &arg, ToleranceType const &tol) GA_NOEXCEPT {
        return take_largest_grade(scalar(arg), tol);
    }

    template<typename Type>
    constexpr decltype(auto) take_largest_grade(Type const &arg) GA_NOEXCEPT {
        return take_largest_grade(scalar(arg), default_tolerance<Type>());
    }

}

#endif // __GA_EXTRA_TAKE_GRADE_HPP__
