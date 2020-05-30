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

#ifndef __GA_EXTRA_GRADE_HPP__
#define __GA_EXTRA_GRADE_HPP__

namespace ga {

    // Interpretation of the result produced by the ga::grade() function.
    enum grade_interpretation_t { LAZY_GRADE = -3, UNDETERMINED_GRADE = -2, MIXED_GRADE = -1, SINGLE_GRADE = 0 };

    // The result of the ga::grade() function.
    template<typename Value>
    class grade_result;
    
    template<typename Value>
    class grade_result<scalar_clifford_expression<grade_t, Value> > final {
    public:

        using value_type = scalar_clifford_expression<grade_t, Value>;

        constexpr grade_result(grade_result const &) = default;
        constexpr grade_result(grade_result &&) = default;

        constexpr grade_result(value_type const &) GA_NOEXCEPT {
        }

        constexpr operator value_type() const GA_NOEXCEPT {
            return value_type();
        }

        constexpr operator grade_t() const = delete;

        constexpr grade_interpretation_t flag() const GA_NOEXCEPT {
            return LAZY_GRADE;
        }
    };

    template<>
    class grade_result<scalar_clifford_expression<grade_t, detail::stored_value> > final {
    public:

        using value_type = scalar_clifford_expression<grade_t, detail::stored_value>;

        constexpr grade_result(grade_result const &) = default;
        constexpr grade_result(grade_result &&) = default;

        constexpr grade_result(value_type const &value) GA_NOEXCEPT :
            value_(value) {
        }

        constexpr operator value_type() const GA_NOEXCEPT {
            return value_;
        }

        constexpr operator grade_t() const GA_NOEXCEPT {
            return value_;
        }

        constexpr grade_interpretation_t flag() const GA_NOEXCEPT {
            return flag(*this);
        }

    private:

        constexpr grade_interpretation_t flag(grade_t const grade) const GA_NOEXCEPT {
            return grade >= 0 ? SINGLE_GRADE : (grade_interpretation_t)grade;
        }

        value_type const value_;
    };

    template<grade_t GradeValue>
    class grade_result<scalar_clifford_expression<grade_t, detail::constant_value<GradeValue> > > final {
    public:

        using value_type = scalar_clifford_expression<grade_t, detail::constant_value<GradeValue> >;

        constexpr grade_result(grade_result const &) = default;
        constexpr grade_result(grade_result &&) = default;

        constexpr grade_result(value_type const &) GA_NOEXCEPT {
        }

        constexpr operator value_type() const GA_NOEXCEPT {
            return value_type();
        }

        constexpr operator grade_t() const GA_NOEXCEPT {
            return static_cast<grade_t>(GradeValue);
        }

        constexpr grade_interpretation_t flag() const GA_NOEXCEPT {
            return GradeValue >= 0 ? SINGLE_GRADE : (grade_interpretation_t)GradeValue;
        }
    };

    namespace detail {

        template<typename Value>
        GA_ALWAYS_INLINE constexpr decltype(auto) make_grade_result(scalar_clifford_expression<grade_t, Value> const &arg) GA_NOEXCEPT {
            return grade_result<scalar_clifford_expression<grade_t, Value> >(arg);
        }

        // Grade deduction.
        template<typename Expression, typename ToleranceValue>
        struct deduce_grade_result;

        template<typename Expression, typename ToleranceValue>
        using deduce_grade_result_t = typename deduce_grade_result<Expression, ToleranceValue>::type;

        template<typename Argument, typename... NextArguments, typename ToleranceValue>
        struct deduce_grade_result<add<Argument, NextArguments...>, ToleranceValue> {
        private:
                
            using argument_grade = deduce_grade_result_t<Argument, ToleranceValue>;
            using next_arguments_grade = deduce_grade_result_t<add_t<NextArguments...>, ToleranceValue>;

        public:
                
            using type = if_else_t<
                equal_t<argument_grade, constant_value<MIXED_GRADE> >,
                constant_value<MIXED_GRADE>,
                if_else_t<
                    equal_t<next_arguments_grade, constant_value<MIXED_GRADE> >,
                    constant_value<MIXED_GRADE>,
                    if_else_t<
                        equal_t<argument_grade, constant_value<UNDETERMINED_GRADE> >,
                        next_arguments_grade,
                        if_else_t<
                            equal_t<next_arguments_grade, constant_value<UNDETERMINED_GRADE> >,
                            argument_grade,
                            if_else_t<
                                equal_t<argument_grade, next_arguments_grade>,
                                argument_grade,
                                constant_value<MIXED_GRADE>
                            >
                        >
                    >
                >
            >;
        };

        template<typename Coefficient, typename BasisBlade, typename ToleranceValue>
        struct deduce_grade_result<component<Coefficient, BasisBlade>, ToleranceValue> {
            using type = if_else_t<
                less_or_equal_t<absolute_t<Coefficient>, ToleranceValue>,
                constant_value<UNDETERMINED_GRADE>,
                count_one_bits_t<basis_vectors_t<BasisBlade> >
            >;
        };

        // Largest grade deduction.
        template<typename Expression, typename ToleranceValue>
        struct deduce_largest_grade_result;

        template<typename Expression, typename ToleranceValue>
        using deduce_largest_grade_result_t = typename deduce_largest_grade_result<Expression, ToleranceValue>::type;

        template<typename Argument, typename... NextArguments, typename ToleranceValue>
        struct deduce_largest_grade_result<add<Argument, NextArguments...>, ToleranceValue> {
        private:
                
            using argument_grade = deduce_largest_grade_result_t<Argument, ToleranceValue>;
            using next_arguments_grade = deduce_largest_grade_result_t<add_t<NextArguments...>, ToleranceValue>;

        public:
                
            using type = if_else_t<
                less_or_equal_t<argument_grade, next_arguments_grade>,
                next_arguments_grade,
                argument_grade
            >;
        };

        template<typename Coefficient, typename BasisBlade, typename ToleranceValue>
        struct deduce_largest_grade_result<component<Coefficient, BasisBlade>, ToleranceValue> {
            using type = if_else_t<
                less_or_equal_t<absolute_t<Coefficient>, ToleranceValue>,
                constant_value<UNDETERMINED_GRADE>,
                count_one_bits_t<basis_vectors_t<BasisBlade> >
            >;
        };

    }

    // Helper to deduce the largest possible grade value in the given Expression extracted from ga::clifford_expression<CoefficientType, Expression>.
    template<typename Expression>
    struct largest_possible_grade;

    template<typename Expression>
    constexpr grade_t largest_possible_grade_v = largest_possible_grade<Expression>::value;

    template<typename Coefficient, typename BasisBlade, typename... NextComponents>
    struct largest_possible_grade<detail::add<detail::component<Coefficient, BasisBlade>, NextComponents...> > {
        constexpr static grade_t value = std::max(grade_t(detail::set_bit_index(detail::leftmost_set_bit(detail::possible_grades_v<BasisBlade>))), largest_possible_grade_v<detail::add_t<NextComponents...> >);
    };

    template<typename Coefficient, typename BasisBlade>
    struct largest_possible_grade<detail::component<Coefficient, BasisBlade> > {
        constexpr static grade_t value = detail::set_bit_index(detail::leftmost_set_bit(detail::possible_grades_v<BasisBlade>));
    };

    // Helper to deduce the smallest possible grade value in the given Expression extracted from ga::clifford_expression<CoefficientType, Expression>.
    template<typename Expression>
    struct smallest_possible_grade;

    template<typename Expression>
    constexpr grade_t smallest_possible_grade_v = smallest_possible_grade<Expression>::value;

    template<typename Coefficient, typename BasisBlade, typename... NextComponents>
    struct smallest_possible_grade<detail::add<detail::component<Coefficient, BasisBlade>, NextComponents...> > {
        constexpr static grade_t value = std::min(grade_t(detail::set_bit_index(detail::rightmost_set_bit(detail::possible_grades_v<BasisBlade>))), smallest_possible_grade_v<detail::add_t<NextComponents...> >);
    };

    template<typename Coefficient, typename BasisBlade>
    struct smallest_possible_grade<detail::component<Coefficient, BasisBlade> > {
        constexpr static grade_t value = detail::set_bit_index(detail::rightmost_set_bit(detail::possible_grades_v<BasisBlade>));
    };

    // Returns the ga::grade_result<Value> structure representing the grade of the given Clifford expression.
    template<typename CoefficientType, typename Expression, typename ToleranceType>
    constexpr decltype(auto) grade(clifford_expression<CoefficientType, Expression> const &arg, ToleranceType const &tol) GA_NOEXCEPT {
        auto lazy = make_lazy_context(arg, scalar(tol));
        return detail::make_grade_result(lazy.eval(scalar_clifford_expression<grade_t, detail::deduce_grade_result_t<typename decltype(lazy)::template argument_expression_t<0>, detail::coefficient_t<typename decltype(lazy)::template argument_expression_t<1> > > >()));
    }

    template<typename Type, typename ToleranceType, std::enable_if_t<!is_clifford_expression_v<Type>, int> = 0>
    constexpr decltype(auto) grade(Type const &arg, ToleranceType const &tol) GA_NOEXCEPT {
        return grade(scalar(arg), tol);
    }

    template<typename CoefficientType, typename Expression>
    constexpr decltype(auto) grade(clifford_expression<CoefficientType, Expression> const &arg) GA_NOEXCEPT {
        return grade(arg, default_tolerance<CoefficientType>());
    }

    template<typename Type, std::enable_if_t<!is_clifford_expression_v<Type>, int> = 0>
    constexpr decltype(auto) grade(Type const &arg) GA_NOEXCEPT {
        return grade(scalar(arg), default_tolerance<Type>());
    }

    // Returns a scalar expression with the largest grade part of a given Clifford expression such that it is not zero.
    template<typename CoefficientType, typename Expression, typename ToleranceType>
    constexpr decltype(auto) largest_grade(clifford_expression<CoefficientType, Expression> const &arg, ToleranceType const &tol) GA_NOEXCEPT {
        auto lazy = make_lazy_context(arg, scalar(tol));
        return lazy.eval(scalar_clifford_expression<grade_t, detail::deduce_largest_grade_result_t<typename decltype(lazy)::template argument_expression_t<0>, detail::coefficient_t<typename decltype(lazy)::template argument_expression_t<1> > > >());
    }

    template<typename Type, typename ToleranceType, std::enable_if_t<!is_clifford_expression_v<Type>, int> = 0>
    constexpr decltype(auto) largest_grade(Type const &arg, ToleranceType const &tol) GA_NOEXCEPT {
        return largest_grade(scalar(arg), tol);
    }

    template<typename CoefficientType, typename Expression>
    constexpr decltype(auto) largest_grade(clifford_expression<CoefficientType, Expression> const &arg) GA_NOEXCEPT {
        return largest_grade(arg, default_tolerance<CoefficientType>());
    }

    template<typename Type, std::enable_if_t<!is_clifford_expression_v<Type>, int> = 0>
    constexpr decltype(auto) largest_grade(Type const &arg) GA_NOEXCEPT {
        return largest_grade(scalar(arg), default_tolerance<Type>());
    }

}

#endif // __GA_EXTRA_GRADE_HPP__
