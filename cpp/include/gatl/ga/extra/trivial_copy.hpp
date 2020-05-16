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

#ifndef __GA_EXTRA_TRIVIAL_COPY_HPP__
#define __GA_EXTRA_TRIVIAL_COPY_HPP__

namespace ga {

    // An exception of this type is thrown when a ga::checked_trivial_copy() fails.
    class bad_checked_copy_exception : public std::exception {
    public:

        virtual const char* what() const GA_NOEXCEPT {
            return "bad checked copy";
        }
    };

    namespace detail {

        //TODO The compatibility among PossibleGrades could be improved.

        // Implementation of ga::trivial_copy() and ga::checked_trivial_copy() procedures.
        template<bool RuntimeCheck, typename InputExpression, typename ResultExpression, typename Enabled = void>
        struct _trivial_copy {
            static_assert(RuntimeCheck && std::is_same_v<InputExpression, std::nullptr_t>, "Non-trivial ga:checked_trivial_copy() operation.");
            static_assert(!RuntimeCheck && std::is_same_v<InputExpression, std::nullptr_t>, "Non-trivial ga:trivial_copy() operation.");
        };

        template<bool RuntimeCheck, typename InputExpression, typename ResultExpression>
        struct _trivial_assign_and_advance_both;

        template<bool RuntimeCheck, typename InputExpression, typename ResultExpression>
        struct _trivial_set_zero_and_advance_result;

        template<typename InputExpression, typename ResultExpression>
        struct _trivial_check_zero_and_advance_input;

        template<typename InputComponent, typename ResultComponent>
        struct _trivial_assign;

        template<typename ResultComponent>
        struct _trivial_set_zero;

        template<typename InputComponent>
        struct _trivial_check_zero;

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
        struct _trivial_copy<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...>,
            std::enable_if_t<eq_v<InputBasisBlade, ResultBasisBlade> > > :
            _trivial_assign_and_advance_both<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_copy<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade>,
            std::enable_if_t<eq_v<InputBasisBlade, ResultBasisBlade> > > :
            _trivial_assign_and_advance_both<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
        struct _trivial_copy<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...>,
            std::enable_if_t<eq_v<InputBasisBlade, ResultBasisBlade> > > :
            _trivial_assign_and_advance_both<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_copy<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade>,
            std::enable_if_t<eq_v<InputBasisBlade, ResultBasisBlade> > > :
            _trivial_assign_and_advance_both<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
        struct _trivial_copy<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...>,
            std::enable_if_t<lt_v<ResultBasisBlade, InputBasisBlade> > > :
            _trivial_set_zero_and_advance_result<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_copy<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade>,
            std::enable_if_t<lt_v<ResultBasisBlade, InputBasisBlade> && !std::is_same_v<ResultCoefficient, constant_value<0> > > > :
            _trivial_set_zero_and_advance_result<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_copy<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade>,
            std::enable_if_t<lt_v<ResultBasisBlade, InputBasisBlade> && std::is_same_v<ResultCoefficient, constant_value<0> > && RuntimeCheck> > :
            _trivial_check_zero_and_advance_input<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
        struct _trivial_copy<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...>,
            std::enable_if_t<lt_v<ResultBasisBlade, InputBasisBlade> > > :
            _trivial_set_zero_and_advance_result<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_copy<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade>,
            std::enable_if_t<lt_v<ResultBasisBlade, InputBasisBlade> && !std::is_same_v<ResultCoefficient, constant_value<0> > > > :
            _trivial_set_zero_and_advance_result<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_copy<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade>,
            std::enable_if_t<lt_v<ResultBasisBlade, InputBasisBlade> && std::is_same_v<ResultCoefficient, constant_value<0> > && RuntimeCheck> > :
            _trivial_check_zero_and_advance_input<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
        struct _trivial_copy<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...>,
            std::enable_if_t<lt_v<InputBasisBlade, ResultBasisBlade> && RuntimeCheck> > :
            _trivial_check_zero_and_advance_input<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_copy<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade>,
            std::enable_if_t<lt_v<InputBasisBlade, ResultBasisBlade> && RuntimeCheck> > :
            _trivial_check_zero_and_advance_input<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
        struct _trivial_copy<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...>,
            std::enable_if_t<lt_v<InputBasisBlade, ResultBasisBlade> && !std::is_same_v<InputCoefficient, constant_value<0> > && RuntimeCheck> > :
            _trivial_check_zero_and_advance_input<component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
        struct _trivial_copy<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...>,
            std::enable_if_t<lt_v<InputBasisBlade, ResultBasisBlade> && std::is_same_v<InputCoefficient, constant_value<0> > > > :
            _trivial_set_zero_and_advance_result<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_copy<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade>,
            std::enable_if_t<lt_v<InputBasisBlade, ResultBasisBlade> && !std::is_same_v<InputCoefficient, constant_value<0> > && RuntimeCheck> > :
            _trivial_check_zero_and_advance_input<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_copy<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade>,
            std::enable_if_t<lt_v<InputBasisBlade, ResultBasisBlade> && std::is_same_v<InputCoefficient, constant_value<0> > > > :
            _trivial_set_zero_and_advance_result<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> > {
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
        struct _trivial_assign_and_advance_both<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr, typename ToleranceType>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr, ToleranceType const &tol) {
                _trivial_assign<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
                _trivial_copy<RuntimeCheck, add_t<NextInputArguments...>, add_t<NextResultArguments...> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr, tol);
            }
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_assign_and_advance_both<RuntimeCheck, add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade> > {
            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr, typename ToleranceType>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr, ToleranceType const &tol) {
                _trivial_assign<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
                _trivial_copy<RuntimeCheck, add_t<NextInputArguments...>, component<constant_value<0>, constant_basis_blade<bitset_t(0)> > >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr, tol);
            }
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
        struct _trivial_assign_and_advance_both<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr, typename ToleranceType>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr, ToleranceType const &tol) {
                _trivial_assign<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
                _trivial_copy<RuntimeCheck, component<constant_value<0>, constant_basis_blade<bitset_t(0)> >, add_t<NextResultArguments...> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr, tol);
            }
        };

        template<bool RuntimeCheck, typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_assign_and_advance_both<RuntimeCheck, component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> > {
            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr, typename ToleranceType>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr, ToleranceType const &) {
                _trivial_assign<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
            }
        };
        
        template<bool RuntimeCheck, typename InputExpression, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
        struct _trivial_set_zero_and_advance_result<RuntimeCheck, InputExpression, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr, typename ToleranceType>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr, ToleranceType const &tol) {
                _trivial_set_zero<component<ResultCoefficient, ResultBasisBlade> >::run(result_value_itr, result_bitset_itr, result_map_itr);
                _trivial_copy<RuntimeCheck, InputExpression, add_t<NextResultArguments...> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr, tol);
            }
        };

        template<bool RuntimeCheck, typename InputExpression, typename ResultCoefficient, typename ResultBasisBlade>
        struct _trivial_set_zero_and_advance_result<RuntimeCheck, InputExpression, component<ResultCoefficient, ResultBasisBlade> > {
            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr, typename ToleranceType>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr, ToleranceType const &tol) {
                _trivial_set_zero<component<ResultCoefficient, ResultBasisBlade> >::run(result_value_itr, result_bitset_itr, result_map_itr);
                _trivial_copy<RuntimeCheck, InputExpression, component<constant_value<0>, constant_basis_blade<bitset_t(0)> > >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr, tol);
            }
        };

        template<typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultExpression>
        struct _trivial_check_zero_and_advance_input<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, ResultExpression> {
            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr, typename ToleranceType>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr, ToleranceType const &tol) {
                _trivial_check_zero<component<InputCoefficient, InputBasisBlade> >::run(input_value_itr, input_bitset_itr, input_map_itr, tol);
                _trivial_copy<true, add_t<NextInputArguments...>, ResultExpression>::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr, tol);
            }
        };

        template<typename InputCoefficient, typename InputBasisBlade, typename ResultExpression>
        struct _trivial_check_zero_and_advance_input<component<InputCoefficient, InputBasisBlade>, ResultExpression> {
            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr, typename ToleranceType>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr, ToleranceType const &tol) {
                _trivial_check_zero<component<InputCoefficient, InputBasisBlade> >::run(input_value_itr, input_bitset_itr, input_map_itr, tol);
                _trivial_copy<true, component<constant_value<0>, constant_basis_blade<bitset_t(0)> >, ResultExpression>::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr, tol);
            }
        };

        template<typename CommonConstantCoefficient, bitset_t CommonBasisVectors>
        struct _trivial_assign<component<CommonConstantCoefficient, constant_basis_blade<CommonBasisVectors> >, component<CommonConstantCoefficient, constant_basis_blade<CommonBasisVectors> > > {
            static_assert(is_constant_expression_v<CommonConstantCoefficient>, "Common constant expression expected.");

            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr const &, InputBitsetCItr const &, InputMapCItr const &, ResultValueItr const &, ResultBitsetItr const &, ResultMapItr const &) GA_NOEXCEPT {
                // end of recursion
            }
        };

        template<typename InputConstantCoefficient, bitset_t CommonBasisVectors>
        struct _trivial_assign<component<InputConstantCoefficient, constant_basis_blade<CommonBasisVectors> >, component<stored_value, constant_basis_blade<CommonBasisVectors> > > {
            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr const &, InputBitsetCItr const &, InputMapCItr const &, ResultValueItr &result_value_itr, ResultBitsetItr const &, ResultMapItr const &) {
                *result_value_itr = InputConstantCoefficient::template eval<0, 0>(std::make_tuple());
                std::advance(result_value_itr, 1);
            }
        };

        template<bitset_t CommonBasisVectors>
        struct _trivial_assign<component<stored_value, constant_basis_blade<CommonBasisVectors> >, component<stored_value, constant_basis_blade<CommonBasisVectors> > > {
            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr const &, InputMapCItr const &, ResultValueItr &result_value_itr, ResultBitsetItr const &, ResultMapItr const &) {
                *result_value_itr = *input_value_itr;
                std::advance(input_value_itr, 1);
                std::advance(result_value_itr, 1);
            }
        };

        template<typename CommonConstantCoefficient, bitset_t InputPossibleGrades, bitset_t ResultPossibleGrades>
        struct _trivial_assign<component<CommonConstantCoefficient, dynamic_basis_blade<InputPossibleGrades, stored_bitset> >, component<CommonConstantCoefficient, dynamic_basis_blade<ResultPossibleGrades, stored_bitset> > > {
            static_assert(is_constant_expression_v<CommonConstantCoefficient>, "Common constant expression expected.");
            static_assert((InputPossibleGrades & ResultPossibleGrades) == InputPossibleGrades, "The possible grades of the input basis blade must be included in the set of possible brades of the resulting basis blade.");

            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr const &, InputBitsetCItr &input_bitset_itr, InputMapCItr const &, ResultValueItr const &, ResultBitsetItr &result_bitset_itr, ResultMapItr const &) {
                *result_bitset_itr = *input_bitset_itr;
                std::advance(input_bitset_itr, 1);
                std::advance(result_bitset_itr, 1);
            }
        };

        template<typename InputConstantCoefficient, bitset_t InputPossibleGrades, bitset_t ResultPossibleGrades>
        struct _trivial_assign<component<InputConstantCoefficient, dynamic_basis_blade<InputPossibleGrades, stored_bitset> >, component<stored_value, dynamic_basis_blade<ResultPossibleGrades, stored_bitset> > > {
            static_assert((InputPossibleGrades & ResultPossibleGrades) == InputPossibleGrades, "The possible grades of the input basis blade must be included in the set of possible brades of the resulting basis blade.");

            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr const &, InputBitsetCItr &input_bitset_itr, InputMapCItr const &, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr const &) {
                *result_value_itr = InputConstantCoefficient::template eval<0, 0>(std::make_tuple());
                std::advance(result_value_itr, 1);

                *result_bitset_itr = *input_bitset_itr;
                std::advance(input_bitset_itr, 1);
                std::advance(result_bitset_itr, 1);
            }
        };

        template<bitset_t InputPossibleGrades, bitset_t ResultPossibleGrades>
        struct _trivial_assign<component<stored_value, dynamic_basis_blade<InputPossibleGrades, stored_bitset> >, component<stored_value, dynamic_basis_blade<ResultPossibleGrades, stored_bitset> > > {
            static_assert((InputPossibleGrades & ResultPossibleGrades) == InputPossibleGrades, "The possible grades of the input basis blade must be included in the set of possible brades of the resulting basis blade.");

            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr const &, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr const &) {
                *result_value_itr = *input_value_itr;
                std::advance(input_value_itr, 1);
                std::advance(result_value_itr, 1);

                *result_bitset_itr = *input_bitset_itr;
                std::advance(input_bitset_itr, 1);
                std::advance(result_bitset_itr, 1);
            }
        };

        template<typename InputConstantCoefficient, bitset_t InputPossibleGrades, bitset_t ResultPossibleGrades>
        struct _trivial_assign<component<InputConstantCoefficient, dynamic_basis_blade<InputPossibleGrades, stored_bitset> >, component<stored_map_values, dynamic_basis_blade<ResultPossibleGrades, stored_map_bitsets> > > {
            static_assert((InputPossibleGrades & ResultPossibleGrades) == InputPossibleGrades, "The possible grades of the input basis blade must be included in the set of possible brades of the resulting basis blade.");

            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr const &, InputBitsetCItr &input_bitset_itr, InputMapCItr const &, ResultValueItr const &, ResultBitsetItr const &, ResultMapItr &result_map_itr) {
                result_map_itr->clear();
                result_map_itr->emplace(*input_bitset_itr, InputConstantCoefficient::template eval<0, 0>(std::make_tuple()));
                std::advance(input_bitset_itr, 1);
                std::advance(result_map_itr, 1);
            }
        };

        template<bitset_t InputPossibleGrades, bitset_t ResultPossibleGrades>
        struct _trivial_assign<component<stored_value, dynamic_basis_blade<InputPossibleGrades, stored_bitset> >, component<stored_map_values, dynamic_basis_blade<ResultPossibleGrades, stored_map_bitsets> > > {
            static_assert((InputPossibleGrades & ResultPossibleGrades) == InputPossibleGrades, "The possible grades of the input basis blade must be included in the set of possible brades of the resulting basis blade.");

            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr const &, ResultValueItr const &, ResultBitsetItr const &, ResultMapItr &result_map_itr) {
                result_map_itr->clear();
                result_map_itr->emplace(*input_bitset_itr, *input_value_itr);
                std::advance(input_bitset_itr, 1);
                std::advance(result_map_itr, 1);
            }
        };

        template<bitset_t InputPossibleGrades, bitset_t ResultPossibleGrades>
        struct _trivial_assign<component<stored_map_values, dynamic_basis_blade<InputPossibleGrades, stored_map_bitsets> >, component<stored_map_values, dynamic_basis_blade<ResultPossibleGrades, stored_map_bitsets> > > {
            static_assert((InputPossibleGrades & ResultPossibleGrades) == InputPossibleGrades, "The possible grades of the input basis blade must be included in the set of possible brades of the resulting basis blade.");

            template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(InputValueCItr const &, InputBitsetCItr const &, InputMapCItr &input_map_itr, ResultValueItr const &, ResultBitsetItr const &, ResultMapItr &result_map_itr) {
                *result_map_itr = *input_map_itr;
                std::advance(input_map_itr, 1);
                std::advance(result_map_itr, 1);
            }
        };

        template<bitset_t BasisVectors>
        struct _trivial_set_zero<component<stored_value, constant_basis_blade<BasisVectors> > > {
            template<typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(ResultValueItr &result_value_itr, ResultBitsetItr const &, ResultMapItr const &) {
                *result_value_itr = 0;
                std::advance(result_value_itr, 1);
            }
        };

        template<bitset_t PossibleGrades>
        struct _trivial_set_zero<component<stored_value, dynamic_basis_blade<PossibleGrades, stored_bitset> > > {
            template<typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr const &) {
                *result_value_itr = 0;
                std::advance(result_value_itr, 1);

                *result_bitset_itr = bitset_t(0);
                std::advance(result_bitset_itr, 1);
            }
        };

        template<bitset_t PossibleGrades>
        struct _trivial_set_zero<component<stored_map_values, dynamic_basis_blade<PossibleGrades, stored_map_bitsets> > > {
            template<typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
            GA_ALWAYS_INLINE constexpr static void run(ResultValueItr const &, ResultBitsetItr const &, ResultMapItr &result_map_itr) {
                result_map_itr->clear();
                std::advance(result_map_itr, 1);
            }
        };

        template<bitset_t BasisVectors>
        struct _trivial_check_zero<component<stored_value, constant_basis_blade<BasisVectors> > > {
            template<typename InputValueItr, typename InputBitsetItr, typename InputMapItr, typename ToleranceType>
            GA_ALWAYS_INLINE constexpr static void run(InputValueItr &input_value_itr, InputBitsetItr const &, InputMapItr const &, ToleranceType const &tol) {
                if (std::abs(*input_value_itr) > (typename std::iterator_traits<InputValueItr>::value_type)tol) {
                    throw bad_checked_copy_exception();
                }
                std::advance(input_value_itr, 1);
            }
        };

        template<bitset_t PossibleGrades>
        struct _trivial_check_zero<component<stored_value, dynamic_basis_blade<PossibleGrades, stored_bitset> > > {
            template<typename InputValueItr, typename InputBitsetItr, typename InputMapItr, typename ToleranceType>
            GA_ALWAYS_INLINE constexpr static void run(InputValueItr &input_value_itr, InputBitsetItr &input_bitset_itr, InputMapItr const &, ToleranceType const &tol) {
                if (std::abs(*input_value_itr) > (typename std::iterator_traits<InputValueItr>::value_type)tol) {
                    throw bad_checked_copy_exception();
                }
                std::advance(input_value_itr, 1);
                std::advance(input_bitset_itr, 1);
            }
        };

        template<bitset_t PossibleGrades>
        struct _trivial_check_zero<component<stored_map_values, dynamic_basis_blade<PossibleGrades, stored_map_bitsets> > > {
            template<typename InputValueItr, typename InputBitsetItr, typename InputMapItr, typename ToleranceType>
            GA_ALWAYS_INLINE constexpr static void run(InputValueItr const &, InputBitsetItr const &, InputMapItr &input_map_itr, ToleranceType const &tol) {
                for (auto const &pair : *input_map_itr) {
                    if (std::abs(pair.second) > (typename std::iterator_traits<InputValueItr>::value_type)tol) {
                        throw bad_checked_copy_exception();
                    }
                }
                std::advance(input_map_itr, 1);
            }
        };

    }

    // Copies the coefficients of the left-hand side Clifford expression into the right-hand side ga::clifford_expression<...> when it is possible to perform a runtime-checked trivial copy.
    template<typename InputCoefficientType, typename InputExpression, typename ResultCoefficientType, typename ResultExpression, typename ToleranceType>
    constexpr void checked_trivial_copy(clifford_expression<InputCoefficientType, InputExpression> const &input, clifford_expression<ResultCoefficientType, ResultExpression> &result, ToleranceType const &tol) {
        auto input_value_itr = input.values().cbegin();
        auto input_bitset_itr = input.bitsets().cbegin();
        auto input_map_itr = input.maps().cbegin();

        auto result_value_itr = result.values().begin();
        auto result_bitset_itr = result.bitsets().begin();
        auto result_map_itr = result.maps().begin();

        detail::_trivial_copy<true, InputExpression, ResultExpression>::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr, scalar(tol));
    }

    template<typename InputCoefficientType, typename InputExpression, typename ResultCoefficientType, typename ResultExpression>
    constexpr void checked_trivial_copy(clifford_expression<InputCoefficientType, InputExpression> const &input, clifford_expression<ResultCoefficientType, ResultExpression> &result) {
        checked_trivial_copy(input, result, default_tolerance<InputCoefficientType>());
    }

    template<typename CoefficientType, typename Expression, typename ToleranceType>
    constexpr void checked_trivial_copy(clifford_expression<CoefficientType, Expression> const &input, clifford_expression<CoefficientType, Expression> &result, ToleranceType const &tol) GA_NOEXCEPT {
        result = input;
    }

    template<typename CoefficientType, typename Expression>
    constexpr void checked_trivial_copy(clifford_expression<CoefficientType, Expression> const &input, clifford_expression<CoefficientType, Expression> &result) GA_NOEXCEPT {
        result = input;
    }

    template<typename InputType, typename ResultCoefficientType, typename ResultExpression, typename ToleranceType>
    constexpr void checked_trivial_copy(InputType const &input, clifford_expression<ResultCoefficientType, ResultExpression> &result, ToleranceType const &tol) {
        checked_trivial_copy(scalar(input), result, tol);
    }

    template<typename InputType, typename ResultCoefficientType, typename ResultExpression>
    constexpr void checked_trivial_copy(InputType const &input, clifford_expression<ResultCoefficientType, ResultExpression> &result) {
        checked_trivial_copy(scalar(input), result, default_tolerance<InputType>());
    }

    // Copies the coefficients of the left-hand side Clifford expression into the right-hand side ga::clifford_expression<...> when it is possible to perform a trivial copy.
    template<typename InputCoefficientType, typename InputExpression, typename ResultCoefficientType, typename ResultExpression>
    constexpr void trivial_copy(clifford_expression<InputCoefficientType, InputExpression> const &input, clifford_expression<ResultCoefficientType, ResultExpression> &result) {
        auto input_value_itr = input.values().cbegin();
        auto input_bitset_itr = input.bitsets().cbegin();
        auto input_map_itr = input.maps().cbegin();

        auto result_value_itr = result.values().begin();
        auto result_bitset_itr = result.bitsets().begin();
        auto result_map_itr = result.maps().begin();

        detail::_trivial_copy<false, InputExpression, ResultExpression>::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr, 0);
    }

    template<typename CoefficientType, typename Expression>
    constexpr void trivial_copy(clifford_expression<CoefficientType, Expression> const &input, clifford_expression<CoefficientType, Expression> &result) GA_NOEXCEPT {
        result = input;
    }

    template<typename InputType, typename ResultCoefficientType, typename ResultExpression>
    constexpr void trivial_copy(InputType const &input, clifford_expression<ResultCoefficientType, ResultExpression> &result) {
        trivial_copy(scalar(input), result);
    }

}

#endif // __GA_EXTRA_TRIVIAL_COPY_HPP__
