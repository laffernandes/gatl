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

#ifndef __GA_CORE_EXPRESSION_HPP__
#define __GA_CORE_EXPRESSION_HPP__

namespace ga {

    namespace detail {

        // Helper for real-valued expression mappings (it is used with the product of values).
        struct value_mapping {
        };

        // The name of implemented functions.
        enum class name_t : std::uint8_t {
            reordering_sign,    //  0
            count_one_bits,     //  1

            bitwise_left_shift, //  2
            bitwise_uminus,     //  3
            bitwise_dec,        //  4
            bitwise_and,        //  5
            bitwise_or,         //  6
            bitwise_xor,        //  7

            equal,              //  8
            less_or_equal,      //  9

            logical_and,        // 10
            logical_or,         // 11

            if_else,            // 12

            absolute,           // 13

            exponential,        // 14
            logarithm,          // 15

            cosine,             // 16
            sine,               // 17
            tangent,            // 18

            hyperbolic_cosine,  // 19
            hyperbolic_sine,    // 20
            hyperbolic_tangent, // 21

            power,              // 22
            mul,                // 23
            add                 // 24
        };

        // Returns whether the given expression has stored entries.
        template<typename Expression>
        struct has_stored_entries;

        template<typename Expression>
        constexpr bool has_stored_entries_v = has_stored_entries<Expression>::value;

        // Returns whether the given expression is compile-time defined.
        template<typename Expression>
        struct is_constant_expression;

        template<typename Expression>
        constexpr bool is_constant_expression_v = is_constant_expression<Expression>::value;

        // Returns whether the given expression is a function with the given name.
        template<name_t Name, typename Expression>
        struct is_function;

        template<name_t Name, typename Expression>
        constexpr bool is_function_v = is_function<Name, Expression>::value;

        // Returns whether the given expression is non-negative for sure.
        template<typename Expression>
        struct is_non_negative;

        template<typename Expression>
        constexpr bool is_non_negative_v = is_non_negative<Expression>::value;

        // Returns the possible grades of a given basis blade.
        template<typename BasisBlade>
        struct possible_grades;

        template<typename BasisBlade>
        constexpr bitset_t possible_grades_v = possible_grades<BasisBlade>::value;

        // Product operation.
        template<typename LeftExpression, typename RightExpression, typename Mapping>
        struct _product;

        template<typename LeftExpression, typename RightExpression, typename Mapping>
        using product_t = typename _product<LeftExpression, RightExpression, Mapping>::type;

        // Addition operation.
        template<typename LeftExpression, typename RightExpression>
        struct _addition;

        template<typename LeftExpression, typename RightExpression>
        using addition_t = typename _addition<LeftExpression, RightExpression>::type;

    }

    namespace detail {

        // Tag of variables/arguments.
        using tag_t = std::uint16_t;

        // Integral value defined in compilation time.
        template<default_integral_t Value>
        struct constant_value {
            using type = constant_value;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static default_integral_t eval(std::tuple<InputTypes...> const &) GA_NOEXCEPT {
                return Value;
            }
        };

        // Lazy getter for stored values.
        template<tag_t Tag, std::size_t Index>
        struct get_value {
            using type = get_value;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                static_assert(LowerTag <= Tag && Tag <= UpperTag, "Tag out of bounds.");
                return *std::next(std::get<Tag - LowerTag>(args).values().cbegin(), Index);
            }
        };

        // Lazy getter for values stored in a map.
        template<tag_t Tag, std::size_t Index>
        struct get_map_values {
            using type = get_map_values;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &) {
                static_assert(LowerTag <= Tag && Tag <= UpperTag, "Tag out of bounds.");
                //TODO Not supported yet (map)
                throw not_implemented_error("Sorry! The use of ga::clifford_expresion<CoefficientType, Expression> with ga::associative_container_t<ValueType> is not supported yet.");
            }
        };

        // A value stored by the current clifford_expression<...>.
        struct stored_value {
            using type = stored_value;
        };

        // A collection of values stored in a map by the current clifford_expression<...>.
        struct stored_map_values {
            using type = stored_map_values;
        };

        // Bitset defined in compilation time.
        template<bitset_t Bitset>
        struct constant_bitset {
            using type = constant_bitset;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static bitset_t eval(std::tuple<InputTypes...> const &) GA_NOEXCEPT {
                return Bitset;
            }
        };

        // Lazy getter for stored bitsets.
        template<tag_t Tag, std::size_t Index>
        struct get_bitset {
            using type = get_bitset;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static bitset_t eval(std::tuple<InputTypes...> const &args) {
                static_assert(LowerTag <= Tag && Tag <= UpperTag, "Tag out of bounds.");
                return *std::next(std::get<Tag - LowerTag>(args).bitsets().cbegin(), Index);
            }
        };

        // Lazy getter for bisets stored in a map.
        template<tag_t Tag, std::size_t Index>
        struct get_map_bitsets {
            using type = get_map_bitsets;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &) {
                static_assert(LowerTag <= Tag && Tag <= UpperTag, "Tag out of bounds.");
                //TODO Not supported yet (map)
                throw not_implemented_error("Sorry! The use of ga::clifford_expresion<CoefficientType, Expression> with ga::associative_container_t<ValueType> is not supported yet.");
            }
        };

        // A bitset stored by the current clifford_expression<...>.
        struct stored_bitset {
            using type = stored_value;
        };

        // A collection of bitsets stored in a map by the current clifford_expression<...>.
        struct stored_map_bitsets {
            using type = stored_map_bitsets;
        };

        // Basis blade defined in compilation time.
        template<bitset_t BasisVectors>
        struct constant_basis_blade {
            using type = constant_basis_blade;
        };

        // Basis blade defined in runtime.
        template<bitset_t PossibleGrades, typename Bitset>
        struct dynamic_basis_blade {
            using type = dynamic_basis_blade; // default
        };

        template<typename Bitset>
        struct dynamic_basis_blade<bitset_t(1), Bitset> {
            using type = constant_basis_blade<bitset_t(0)>; // scalar for sure
        };

        template<>
        struct dynamic_basis_blade<bitset_t(1), constant_bitset<bitset_t(0)> > {
            using type = constant_basis_blade<bitset_t(0)>; // scalar for sure
        };

        template<bitset_t PossibleGrades, bitset_t Bitset>
        struct dynamic_basis_blade<PossibleGrades, constant_bitset<Bitset> > {
            using type = constant_basis_blade<Bitset>; // it is not dynamic

            static_assert(PossibleGrades == possible_grades_v<type>, "The possible grades are inconsistent.");
        };

        template<bitset_t PossibleGrades, typename Bitset>
        using dynamic_basis_blade_t = typename dynamic_basis_blade<PossibleGrades, Bitset>::type;

        // A set of basis blades multiplied by some real-valued expression (the coefficient).
        template<typename Coefficient, typename BasisBlade>
        struct component {
        private:

            constexpr static bitset_t possible_grades = possible_grades_v<BasisBlade>;

            using coefficient = std::conditional_t<
                possible_grades == bitset_t(0),
                constant_value<0>, // impossible basis blade
                Coefficient
            >;
            
            using basis_blade = std::conditional_t<
                std::is_same_v<Coefficient, constant_value<0> > || possible_grades == bitset_t(0),
                constant_basis_blade<bitset_t(0)>,  // impossible basis blade or zero
                BasisBlade
            >;

        public:
            
            using type = component<coefficient, basis_blade>;
        };

        template<typename Coefficient, typename BasisBlade>
        using component_t = typename component<Coefficient, BasisBlade>::type;

        // A real-valued function of a bitset function.
        template<name_t Name, typename... Arguments>
        struct function;

        // Lazy computation of the sign induced by the canonical reordering of basis vectors in bilinear products.
        template<typename LeftBitset, typename RightBitset>
        using reordering_sign = function<name_t::reordering_sign, LeftBitset, RightBitset>;

        template<typename LeftBitset, typename RightBitset>
        using reordering_sign_t = typename reordering_sign<LeftBitset, RightBitset>::type;

        // Lazy computation of the number of 1 bits in the given lazy bitset.
        template<typename Bitset>
        using count_one_bits = function<name_t::count_one_bits, Bitset>;

        template<typename Bitset>
        using count_one_bits_t = typename count_one_bits<Bitset>::type;

        // Lazy bitwise LEFT SHIFT operations.
        template<typename LeftBitset, typename RightValue>
        using bitwise_left_shift = function<name_t::bitwise_left_shift, LeftBitset, RightValue>;

        template<typename LeftBitset, typename RightValue>
        using bitwise_left_shift_t = typename bitwise_left_shift<LeftBitset, RightValue>::type;

        // Lazy bitwise UNARY MINUS operations.
        template<typename Bitset>
        using bitwise_uminus = function<name_t::bitwise_uminus, Bitset>;

        template<typename Bitset>
        using bitwise_uminus_t = typename bitwise_uminus<Bitset>::type;

        // Lazy bitwise DECREMENT operations.
        template<typename Bitset>
        using bitwise_dec = function<name_t::bitwise_dec, Bitset>;

        template<typename Bitset>
        using bitwise_dec_t = typename bitwise_dec<Bitset>::type;

        // Lazy bitwise AND operations.
        template<typename LeftType, typename RightType>
        using bitwise_and = function<name_t::bitwise_and, LeftType, RightType>;

        template<typename LeftType, typename RightType>
        using bitwise_and_t = typename bitwise_and<LeftType, RightType>::type;

        // Lazy bitwise OR operations.
        template<typename LeftType, typename RightType>
        using bitwise_or = function<name_t::bitwise_or, LeftType, RightType>;

        template<typename LeftType, typename RightType>
        using bitwise_or_t = typename bitwise_or<LeftType, RightType>::type;

        // Lazy bitwise XOR operations.
        template<typename LeftType, typename RightType>
        using bitwise_xor = function<name_t::bitwise_xor, LeftType, RightType>;

        template<typename LeftType, typename RightType>
        using bitwise_xor_t = typename bitwise_xor<LeftType, RightType>::type;

        // Lazy relational EQUAL TO operation.
        template<typename LeftType, typename RightType>
        using equal = function<name_t::equal, LeftType, RightType>;

        template<typename LeftType, typename RightType>
        using equal_t = typename equal<LeftType, RightType>::type;

        // Lazy relational LESS THAN OR EQUAL TO operation.
        template<typename LeftType, typename RightType>
        using less_or_equal = function<name_t::less_or_equal, LeftType, RightType>;

        template<typename LeftType, typename RightType>
        using less_or_equal_t = typename less_or_equal<LeftType, RightType>::type;

        // Lazy logical AND operation.
        template<typename LeftType, typename RightType>
        using logical_and = function<name_t::logical_and, LeftType, RightType>;

        template<typename LeftType, typename RightType>
        using logical_and_t = typename logical_and<LeftType, RightType>::type;

        // Lazy logical OR operation.
        template<typename LeftType, typename RightType>
        using logical_or = function<name_t::logical_or, LeftType, RightType>;

        template<typename LeftType, typename RightType>
        using logical_or_t = typename logical_or<LeftType, RightType>::type;

        // Lazy ternary conditional operation.
        template<typename Test, typename TrueValue, typename FalseValue>
        using if_else = function<name_t::if_else, Test, TrueValue, FalseValue>;

        template<typename Test, typename TrueValue, typename FalseValue>
        using if_else_t = typename if_else<Test, TrueValue, FalseValue>::type;

        // Absolute value of scalar-valued expressions.
        template<typename Value>
        using absolute = function<name_t::absolute, Value>;

        template<typename Value>
        using absolute_t = typename absolute<Value>::type;

        // The base-e exponential function of scalar-valued expressions.
        template<typename Value>
        using exponential = function<name_t::exponential, Value>;

        template<typename Value>
        using exponential_t = typename exponential<Value>::type;

        // The natural logarithm of scalar-valued expressions.
        template<typename Value>
        using logarithm = function<name_t::logarithm, Value>;

        template<typename Value>
        using logarithm_t = typename logarithm<Value>::type;

        // Cosine of scalar-valued expressions.
        template<typename Value>
        using cosine = function<name_t::cosine, Value>;

        template<typename Value>
        using cosine_t = typename cosine<Value>::type;

        // Sine of scalar-valued expressions.
        template<typename Value>
        using sine = function<name_t::sine, Value>;

        template<typename Value>
        using sine_t = typename sine<Value>::type;

        // Tangent of scalar-valued expressions.
        template<typename Value>
        using tangent = function<name_t::tangent, Value>;

        template<typename Value>
        using tangent_t = typename tangent<Value>::type;

        // Hyperbolic cosine of scalar-valued expressions.
        template<typename Value>
        using hyperbolic_cosine = function<name_t::hyperbolic_cosine, Value>;

        template<typename Value>
        using hyperbolic_cosine_t = typename hyperbolic_cosine<Value>::type;

        // Hyperbolic sine of scalar-valued expressions.
        template<typename Value>
        using hyperbolic_sine = function<name_t::hyperbolic_sine, Value>;

        template<typename Value>
        using hyperbolic_sine_t = typename hyperbolic_sine<Value>::type;

        // Hyperbolic tangent of scalar-valued expressions.
        template<typename Value>
        using hyperbolic_tangent = function<name_t::hyperbolic_tangent, Value>;

        template<typename Value>
        using hyperbolic_tangent_t = typename hyperbolic_tangent<Value>::type;

        // Exponentiation of real-valued expressions.
        template<typename LeftArgument, typename RightArgument>
        using power = function<name_t::power, LeftArgument, RightArgument>;

        template<typename LeftArgument, typename RightArgument>
        struct _power;

        template<typename LeftArgument, typename RightArgument>
        using power_t = typename _power<LeftArgument, RightArgument>::type;

        // Multiplication of real-valued expressions.
        template<typename... Arguments>
        using mul = function<name_t::mul, Arguments...>;

        template<typename... Arguments>
        using mul_t = typename function<name_t::mul, Arguments...>::type;
        
        // Addition of real-valued expressions and/or multivector entries.
        template<typename... Arguments>
        using add = function<name_t::add, Arguments...>;

        template<typename... Arguments>
        using add_t = typename function<name_t::add, Arguments...>::type;

        // Specializations of reordering_sign<LeftBitset, RightBitset>.
        template<typename LeftBitset, typename RightBitset>
        struct function<name_t::reordering_sign, LeftBitset, RightBitset> {
            using type = std::conditional_t<
                std::is_same_v<LeftBitset, constant_bitset<bitset_t(0)> > || std::is_same_v<RightBitset, constant_bitset<bitset_t(0)> >,
                constant_value<1>, // simplify
                function // default
            >;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static default_integral_t eval(std::tuple<InputTypes...> const &args) {
                bitset_t lhs = LeftBitset::template eval<LowerTag, UpperTag>(args);
                bitset_t const rhs = RightBitset::template eval<LowerTag, UpperTag>(args);
                lhs >>= 1;
                int changes = 0;
                while (lhs != bitset_t(0)) {
                    changes += ones(lhs & rhs);
                    lhs >>= 1;
                }
                return static_cast<default_integral_t>((changes & 1) == 0 ? 1 : -1);
            }
        };

        template<bitset_t LeftBitset, bitset_t RightBitset>
        struct function<name_t::reordering_sign, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
            using type = constant_value<((swaps_count((LeftBitset >> 1), RightBitset) & 1) != 0) ? -1 : 1>; // simplify
        };

        // Specializations of count_one_bits<Bitset>.
        template<typename Bitset>
        struct function<name_t::count_one_bits, Bitset> {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static default_integral_t eval(std::tuple<InputTypes...> const &args) {
                return ones(Bitset::template eval<LowerTag, UpperTag>(args));
            }
        };

        template<bitset_t Bitset>
        struct function<name_t::count_one_bits, constant_bitset<Bitset> > {
            using type = constant_value<ones(Bitset)>; // simplify
        };

        // Specializations of bitwise_left_shift<LeftBitset, RightValue>.
        template<typename LeftBitset, typename RightValue>
        struct function<name_t::bitwise_left_shift, LeftBitset, RightValue> {
            using type = std::conditional_t<
                std::is_same_v<LeftBitset, constant_bitset<bitset_t(0)> > || std::is_same_v<RightValue, constant_value<0> >,
                LeftBitset, // simplify
                function // default
            >;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return LeftBitset::template eval<LowerTag, UpperTag>(args) << RightValue::template eval<LowerTag, UpperTag>(args);
            }
        };

        template<bitset_t LeftBitset, default_integral_t RightValue>
        struct function<name_t::bitwise_left_shift, constant_bitset<LeftBitset>, constant_value<RightValue> > {
            using type = constant_bitset<(LeftBitset << RightValue)>; // simplify
        };

        // Specializations of bitwise_uminus<Bitset>.
        template<typename Bitset>
        struct function<name_t::bitwise_uminus, Bitset> {
            using type = function;
                
            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static bitset_t eval(std::tuple<InputTypes...> const &args) {
                return -Bitset::template eval<LowerTag, UpperTag>(args);
            }
        };

        template<typename Bitset>
        struct function<name_t::bitwise_uminus, bitwise_uminus<Bitset> > {
            using type = Bitset; // simplify
        };

        template<bitset_t Bitset>
        struct function<name_t::bitwise_uminus, constant_bitset<Bitset> > {
            using type = constant_bitset<-std::make_signed_t<bitset_t>(Bitset)>; // simplify
        };

        // Specializations of bitwise_dec<Bitset>.
        template<typename Bitset>
        struct function<name_t::bitwise_dec, Bitset> {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static bitset_t eval(std::tuple<InputTypes...> const &args) {
                return Bitset::template eval<LowerTag, UpperTag>(args) - bitset_t(1);
            }
        };

        template<bitset_t Bitset>
        struct function<name_t::bitwise_dec, constant_bitset<Bitset> > {
            using type = constant_bitset<Bitset - bitset_t(1)>; // simplify
        };

        // Specializations of bitwise_and<LeftType, RightType>.
        template<typename LeftType, typename RightType>
        struct function<name_t::bitwise_and, LeftType, RightType> {
            using type = std::conditional_t<
                std::is_same_v<LeftType, constant_value<0> > || std::is_same_v<RightType, constant_value<0> >,
                constant_value<0>, // simplify
                std::conditional_t<
                    std::is_same_v<LeftType, constant_bitset<bitset_t(0)> > || std::is_same_v<RightType, constant_bitset<bitset_t(0)> >,
                    constant_bitset<bitset_t(0)>, // simplify
                    function // default
                >
            >;
                
            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return LeftType::template eval<LowerTag, UpperTag>(args) & RightType::template eval<LowerTag, UpperTag>(args);
            }
        };

        template<default_integral_t LeftValue, default_integral_t RightValue>
        struct function<name_t::bitwise_and, constant_value<LeftValue>, constant_value<RightValue> > {
            using type = constant_value<LeftValue & RightValue>; // simplify
        };

        template<bitset_t LeftBitset, bitset_t RightBitset>
        struct function<name_t::bitwise_and, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
            using type = constant_bitset<LeftBitset & RightBitset>; // simplify
        };

        // Specializations of bitwise_or<LeftType, RightType>.
        template<typename LeftType, typename RightType>
        struct function<name_t::bitwise_or, LeftType, RightType> {
            using type = std::conditional_t<
                std::is_same_v<LeftType, constant_value<0> > || std::is_same_v<LeftType, constant_bitset<bitset_t(0)> >,
                RightType, // simplify
                std::conditional_t<
                    std::is_same_v<RightType, constant_value<0> > || std::is_same_v<RightType, constant_bitset<bitset_t(0)> >,
                    LeftType, // simplify
                    function // default
                >
            >;
                
            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return LeftType::template eval<LowerTag, UpperTag>(args) | RightType::template eval<LowerTag, UpperTag>(args);
            }
        };

        template<default_integral_t LeftValue, default_integral_t RightValue>
        struct function<name_t::bitwise_or, constant_value<LeftValue>, constant_value<RightValue> > {
            using type = constant_value<LeftValue | RightValue>; // simplify
        };

        template<bitset_t LeftBitset, bitset_t RightBitset>
        struct function<name_t::bitwise_or, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
            using type = constant_bitset<LeftBitset | RightBitset>; // simplify
        };

        // Specialization bitwise_xor<LeftType, RightType>.
        template<typename LeftType, typename RightType>
        struct function<name_t::bitwise_xor, LeftType, RightType> {
            using type = std::conditional_t<
                std::is_same_v<LeftType, constant_value<0> > || std::is_same_v<LeftType, constant_bitset<bitset_t(0)> >,
                RightType, // simplify
                std::conditional_t<
                    std::is_same_v<RightType, constant_value<0> > || std::is_same_v<RightType, constant_bitset<bitset_t(0)> >,
                    LeftType, // simplify
                    function // default
                >
            >;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return LeftType::template eval<LowerTag, UpperTag>(args) ^ RightType::template eval<LowerTag, UpperTag>(args);
            }
        };

        template<default_integral_t LeftValue, default_integral_t RightValue>
        struct function<name_t::bitwise_xor, constant_value<LeftValue>, constant_value<RightValue> > {
            using type = constant_value<LeftValue ^ RightValue>; // simplify
        };

        template<bitset_t LeftBitset, bitset_t RightBitset>
        struct function<name_t::bitwise_xor, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
            using type = constant_bitset<LeftBitset ^ RightBitset>; // simplify
        };

        // Specializations of equal<LeftType, RightType>.
        template<typename LeftType, typename RightType>
        struct function<name_t::equal, LeftType, RightType> {
            using type = std::conditional_t<
                std::is_same_v<LeftType, RightType> && !has_stored_entries_v<LeftType>,
                std::true_type, // simplify
                std::conditional_t<
                    !std::is_same_v<LeftType, RightType> && is_constant_expression_v<LeftType> && is_constant_expression_v<RightType>,
                    std::false_type, // simplify
                    function // default
                >
            >;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static bool eval(std::tuple<InputTypes...> const &args) {
                return LeftType::template eval<LowerTag, UpperTag>(args) == RightType::template eval<LowerTag, UpperTag>(args);
            }
        };

        // Specializations of less_or_equal<LeftType, RightType>.
        template<typename LeftType, typename RightType>
        struct function<name_t::less_or_equal, LeftType, RightType> {
            using type = std::conditional_t<
                std::is_same_v<LeftType, RightType> && !has_stored_entries_v<LeftType>,
                std::true_type, // simplify
                function // default
            >;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static bool eval(std::tuple<InputTypes...> const &args) {
                return LeftType::template eval<LowerTag, UpperTag>(args) <= RightType::template eval<LowerTag, UpperTag>(args);
            }
        };

        template<default_integral_t LeftValue, default_integral_t RightValue>
        struct function<name_t::less_or_equal, constant_value<LeftValue>, constant_value<RightValue> > :
            std::bool_constant<(LeftValue <= RightValue)> { // simplify
        };

        template<bitset_t LeftBitset, bitset_t RightBitset>
        struct function<name_t::less_or_equal, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > :
            std::bool_constant<(LeftBitset <= RightBitset)> { // simplify
        };

        // Specializations of logical_and<LeftType, RightType>.
        template<typename LeftType, typename RightType>
        struct function<name_t::logical_and, LeftType, RightType> {
            using type = std::conditional_t<
                std::is_same_v<LeftType, RightType> && !has_stored_entries_v<LeftType>,
                LeftType, // simplify
                function // default
            >;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static bool eval(std::tuple<InputTypes...> const &args) {
                return LeftType::template eval<LowerTag, UpperTag>(args) && RightType::template eval<LowerTag, UpperTag>(args);
            }
        };

        template<typename LeftType>
        struct function<name_t::logical_and, LeftType, std::true_type> {
            using type = LeftType; // simplify
        };

        template<typename RightType>
        struct function<name_t::logical_and, std::true_type, RightType> {
            using type = RightType; // simplify
        };

        template<typename LeftType>
        struct function<name_t::logical_and, LeftType, std::false_type> :
            std::false_type { // simplify
        };

        template<typename RightType>
        struct function<name_t::logical_and, std::false_type, RightType> :
            std::false_type { // simplify
        };
        
        template<>
        struct function<name_t::logical_and, std::true_type, std::true_type> :
            std::true_type { // simplify
        };

        template<>
        struct function<name_t::logical_and, std::false_type, std::true_type> :
            std::false_type { // simplify
        };

        template<>
        struct function<name_t::logical_and, std::true_type, std::false_type> :
            std::false_type { // simplify
        };

        template<>
        struct function<name_t::logical_and, std::false_type, std::false_type> :
            std::false_type { // simplify
        };

        // Specializations of logical_or<LeftType, RightType>.
        template<typename LeftType, typename RightType>
        struct function<name_t::logical_or, LeftType, RightType> {
            using type = function; // default

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static bool eval(std::tuple<InputTypes...> const &args) {
                return LeftType::template eval<LowerTag, UpperTag>(args) || RightType::template eval<LowerTag, UpperTag>(args);
            }
        };

        template<typename LeftType>
        struct function<name_t::logical_or, LeftType, std::false_type> {
            using type = LeftType; // simplify
        };

        template<typename RightType>
        struct function<name_t::logical_or, std::false_type, RightType> {
            using type = RightType; // simplify
        };

        template<typename LeftType>
        struct function<name_t::logical_or, LeftType, std::true_type> :
            std::true_type { // simplify
        };

        template<typename RightType>
        struct function<name_t::logical_or, std::true_type, RightType> :
            std::true_type { // simplify
        };

        template<>
        struct function<name_t::logical_or, std::true_type, std::true_type> :
            std::true_type { // simplify
        };

        template<>
        struct function<name_t::logical_or, std::false_type, std::true_type> :
            std::true_type { // simplify
        };

        template<>
        struct function<name_t::logical_or, std::true_type, std::false_type> :
            std::true_type { // simplify
        };

        template<>
        struct function<name_t::logical_or, std::false_type, std::false_type> :
            std::false_type { // simplify
        };

        // Specializations of if_else<Test, TrueValue, FalseValue>.
        template<typename Test, typename TrueValue, typename FalseValue>
        struct function<name_t::if_else, Test, TrueValue, FalseValue> {
            using type = std::conditional_t<
                std::is_same_v<TrueValue, FalseValue> && !has_stored_entries_v<TrueValue>,
                TrueValue, // simplify
                function
            >;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return Test::template eval<LowerTag, UpperTag>(args) ? TrueValue::template eval<LowerTag, UpperTag>(args) : FalseValue::template eval<LowerTag, UpperTag>(args);
            }
        };

        template<typename TrueValue, typename FalseValue>
        struct function<name_t::if_else, std::true_type, TrueValue, FalseValue> {
            using type = TrueValue; // simplify
        };

        template<typename TrueValue, typename FalseValue>
        struct function<name_t::if_else, std::false_type, TrueValue, FalseValue> {
            using type = FalseValue; // simplify
        };

        // Specializations of absolute<Value>.
        template<typename Value>
        struct function<name_t::absolute, Value> {
            using type = std::conditional_t<
                is_non_negative_v<Value>,
                Value,
                std::conditional_t<
                    is_constant_expression_v<Value> && !(is_function_v<name_t::add, Value> || is_function_v<name_t::if_else, Value>),
                    product_t<constant_value<-1>, Value, value_mapping>,
                    function
                >
            >;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return abs(Value::template eval<LowerTag, UpperTag>(args));
            }
        };

        // Specializations of exponential<Value>.
        template<typename Value>
        struct function<name_t::exponential, Value> {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return exp(Value::template eval<LowerTag, UpperTag>(args));
            }
        };

        template<typename Value>
        struct function<name_t::exponential, logarithm<Value> > {
            using type = Value;
        };

        // Specializations of logarithm<Value>.
        template<typename Value>
        struct function<name_t::logarithm, Value> {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return log(Value::template eval<LowerTag, UpperTag>(args));
            }
        };

        template<typename Value>
        struct function<name_t::logarithm, exponential<Value> > {
            using type = Value;
        };

        // Specializations of cosine<Value>.
        template<typename Value>
        struct function<name_t::cosine, Value> {
            using type = function; //TODO Not supported yet (simplifications)

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return cos(Value::template eval<LowerTag, UpperTag>(args));
            }
        };

        // Specializations of sine<Value>.
        template<typename Value>
        struct function<name_t::sine, Value> {
            using type = function; //TODO Not supported yet (simplifications)

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return sin(Value::template eval<LowerTag, UpperTag>(args));
            }
        };

        // Specializations of tangent<Value>.
        template<typename Value>
        struct function<name_t::tangent, Value> {
            using type = function; //TODO Not supported yet (simplifications)

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return tan(Value::template eval<LowerTag, UpperTag>(args));
            }
        };

        // Specializations of hyperbolic_cosine<Value>.
        template<typename Value>
        struct function<name_t::hyperbolic_cosine, Value> {
            using type = function; //TODO Not supported yet (simplifications)

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return cosh(Value::template eval<LowerTag, UpperTag>(args));
            }
        };

        // Specializations of hyperbolic_sine<Value>.
        template<typename Value>
        struct function<name_t::hyperbolic_sine, Value> {
            using type = function; //TODO Not supported yet (simplifications)

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return sinh(Value::template eval<LowerTag, UpperTag>(args));
            }
        };

        // Specializations of hyperbolic_tangent<Value>.
        template<typename Value>
        struct function<name_t::hyperbolic_tangent, Value> {
            using type = function; //TODO Not supported yet (simplifications)

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return tanh(Value::template eval<LowerTag, UpperTag>(args));
            }
        };

        // Specializations of power<LeftArgument, RightArgument>.
        template<typename LeftArgument, typename RightArgument>
        struct function<name_t::power, LeftArgument, RightArgument> {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return pow(LeftArgument::template eval<LowerTag, UpperTag>(args), RightArgument::template eval<LowerTag, UpperTag>(args));
            }

            static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
            static_assert(!std::is_same_v<RightArgument, constant_value<0> >, "The right-hand side argument cannot be ga::detail::constant_value<0>.");
            static_assert(!std::is_same_v<RightArgument, constant_value<1> >, "The right-hand side argument cannot be ga::detail::constant_value<1>.");
        };

        template<typename LeftArgument>
        struct function<name_t::power, LeftArgument, constant_value<-1> > {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return 1 / cast_to_floating_point(LeftArgument::template eval<LowerTag, UpperTag>(args));
            }

            static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
        };

        template<typename LeftArgument>
        struct function<name_t::power, LeftArgument, constant_value<2> > {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return square(LeftArgument::template eval<LowerTag, UpperTag>(args));
            }

            static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
        };

        template<typename LeftArgument>
        struct function<name_t::power, LeftArgument, constant_value<3> > {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return cube(LeftArgument::template eval<LowerTag, UpperTag>(args));
            }

            static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
        };

        template<typename LeftArgument>
        struct function<name_t::power, LeftArgument, constant_value<4> > {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return square(square(LeftArgument::template eval<LowerTag, UpperTag>(args)));
            }

            static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
        };

        template<typename LeftArgument>
        struct function<name_t::power, LeftArgument, power<constant_value<2>, constant_value<-1> > > {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return sqrt(LeftArgument::template eval<LowerTag, UpperTag>(args));
            }

            static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
        };

        template<typename LeftArgument>
        struct function<name_t::power, LeftArgument, power<constant_value<3>, constant_value<-1> > > {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return cbrt(LeftArgument::template eval<LowerTag, UpperTag>(args));
            }

            static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
        };

        // Specializations of mul<Arguments...>.
        template<typename Argument, typename... NextArguments>
        struct function<name_t::mul, Argument, NextArguments...> {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return Argument::template eval<LowerTag, UpperTag>(args) * mul_t<NextArguments...>::template eval<LowerTag, UpperTag>(args);
            }

            static_assert(!is_any_v<constant_value<0>, Argument, NextArguments...>, "The argument ga::detail::constant_value<0> is invalid.");
            static_assert(!is_any_v<constant_value<1>, Argument, NextArguments...>, "The argument ga::detail::constant_value<1> is invalid.");
        };

        template<typename... NextArguments>
        struct function<name_t::mul, constant_value<-1>, NextArguments...> {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return -mul_t<NextArguments...>::template eval<LowerTag, UpperTag>(args);
            }

            static_assert(!is_any_v<constant_value<0>, NextArguments...>, "The argument ga::detail::constant_value<0> is invalid.");
            static_assert(!is_any_v<constant_value<1>, NextArguments...>, "The argument ga::detail::constant_value<1> is invalid.");
        };

        template<typename LeftArgument, typename RightArgument>
        struct function<name_t::mul, LeftArgument, power<RightArgument, constant_value<-1> > > {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return LeftArgument::template eval<LowerTag, UpperTag>(args) / RightArgument::template eval<LowerTag, UpperTag>(args);
            }

            static_assert(!is_any_v<constant_value<0>, LeftArgument>, "The argument ga::detail::constant_value<0> is invalid.");
            static_assert(!is_any_v<constant_value<1>, LeftArgument>, "The argument ga::detail::constant_value<1> is invalid.");
        };

        template<typename RightArgument>
        struct function<name_t::mul, constant_value<-1>, power<RightArgument, constant_value<-1> > > {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return -power<RightArgument, constant_value<-1> >::template eval<LowerTag, UpperTag>(args);
            }
        };

        template<typename Argument>
        struct function<name_t::mul, Argument> {
            using type = Argument; // simplify
        };

        template<>
        struct function<name_t::mul> {
            using type = constant_value<0>; // simplify
        };

        // Specializations of add<Arguments...>.
        template<typename Argument, typename... NextArguments>
        struct function<name_t::add, Argument, NextArguments...> {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return Argument::template eval<LowerTag, UpperTag>(args) + add_t<NextArguments...>::template eval<LowerTag, UpperTag>(args);
            }

            static_assert(!is_any_v<constant_value<0>, Argument, NextArguments...>, "The argument ga::detail::constant_value<0> is invalid.");
        };

        template<typename LeftArgument, typename... RightArguments>
        struct function<name_t::add, LeftArgument, mul<constant_value<-1>, RightArguments...> > {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return LeftArgument::template eval<LowerTag, UpperTag>(args) - mul_t<RightArguments...>::template eval<LowerTag, UpperTag>(args);
            }

            static_assert(!is_any_v<constant_value<0>, LeftArgument>, "The argument ga::detail::constant_value<0> is invalid.");
        };

        template<typename... LeftArguments, typename RightArgument, typename... RightNextArguments>
        struct function<name_t::add, mul<constant_value<-1>, LeftArguments...>, RightArgument, RightNextArguments...> {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return add_t<RightArgument, RightNextArguments...>::template eval<LowerTag, UpperTag>(args) - mul_t<LeftArguments...>::template eval<LowerTag, UpperTag>(args);
            }
        };

        template<typename... LeftArguments, typename... RightArguments>
        struct function<name_t::add, mul<constant_value<-1>, LeftArguments...>, mul<constant_value<-1>, RightArguments...> > {
            using type = function;

            template<tag_t LowerTag, tag_t UpperTag, typename... InputTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
                return -(mul_t<LeftArguments...>::template eval<LowerTag, UpperTag>(args) + mul_t<RightArguments...>::template eval<LowerTag, UpperTag>(args));
            }
        };

        template<typename Argument>
        struct function<name_t::add, Argument> {
            using type = Argument; // simplify
        };

        template<>
        struct function<name_t::add> {
            using type = constant_value<0>; // simplify
        };

    }

}

#endif // __GA_CORE_EXPRESSION_HPP__
