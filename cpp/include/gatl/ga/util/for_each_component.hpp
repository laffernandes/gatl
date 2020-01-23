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

#ifndef __GA_UTIL_FOR_EACH_COMPONENT_HPP__
#define __GA_UTIL_FOR_EACH_COMPONENT_HPP__

namespace ga {

    // Sources of data (values and bitsets) defining of a given ga::clifford_expression<...>.
    enum entry_source_t { COMPILE_TIME_DEFINED_ENTRY = 0, STORED_RUNTIME_DEFINED_ENTRY, MAPPED_RUNTIME_DEFINED_ENTRY };

    namespace detail {

        // Implementation of the for_each_component() function.
        template<typename ValueType, typename Expression>
        struct _for_each_component_impl;

        template<typename ValueType, typename Coefficient, typename BasisBlade>
        struct _for_each_component_impl_inner_iteration;

        template<typename ValueType, typename Coefficient, typename BasisBlade, typename... NextComponents>
        struct _for_each_component_impl<ValueType, add<component<Coefficient, BasisBlade>, NextComponents...> > {
            template<typename ValueCItr, typename BitsetCItr, typename MapCIts, typename Function>
            GA_ALWAYS_INLINE constexpr static bool run(ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts &map_citr, Function f) GA_NOEXCEPT(GA_NOEXCEPT(f)) {
                return _for_each_component_impl_inner_iteration<ValueType, Coefficient, BasisBlade>::run(value_citr, bitset_citr, map_citr, f)
                    && _for_each_component_impl<ValueType, add_t<NextComponents...> >::run(value_citr, bitset_citr, map_citr, f);
            }
        };

        template<typename ValueType, typename Coefficient, typename BasisBlade>
        struct _for_each_component_impl<ValueType, component<Coefficient, BasisBlade> > :
            _for_each_component_impl_inner_iteration<ValueType, Coefficient, BasisBlade> {
        };

        template<typename ValueType, typename Coefficient, bitset_t BasisVectors>
        struct _for_each_component_impl_inner_iteration<ValueType, Coefficient, constant_basis_blade<BasisVectors> > {
            static_assert(can_be_stored_v<Coefficient>, "The ga::for_each_component() function does not allow lazy evaluation with arguments from a lazy context.");

            template<typename ValueCItr, typename BitsetCItr, typename MapCIts, typename Function>
            GA_ALWAYS_INLINE constexpr static bool run(ValueCItr const &, BitsetCItr const &, MapCIts const &, Function f) GA_NOEXCEPT(GA_NOEXCEPT(f)) {
                bool keep_going = true;
                f(BasisVectors, static_cast<ValueType>(Coefficient::template eval<0, 0>(std::make_tuple())), entry_source_t::COMPILE_TIME_DEFINED_ENTRY, entry_source_t::COMPILE_TIME_DEFINED_ENTRY, keep_going);
                return keep_going;
            }
        };

        template<typename ValueType, bitset_t BasisVectors>
        struct _for_each_component_impl_inner_iteration<ValueType, stored_value, constant_basis_blade<BasisVectors> > {
            template<typename ValueCItr, typename BitsetCItr, typename MapCIts, typename Function>
            GA_ALWAYS_INLINE constexpr static bool run(ValueCItr &value_citr, BitsetCItr const &, MapCIts const &, Function f) GA_NOEXCEPT(GA_NOEXCEPT(f)) {
                bool keep_going = true;
                f(BasisVectors, *value_citr, entry_source_t::COMPILE_TIME_DEFINED_ENTRY, entry_source_t::STORED_RUNTIME_DEFINED_ENTRY, keep_going);
                ++value_citr;
                return keep_going;
            }
        };

        template<typename ValueType, typename Coefficient, bitset_t PossibleGrades>
        struct _for_each_component_impl_inner_iteration<ValueType, Coefficient, dynamic_basis_blade<PossibleGrades, stored_bitset> > {
            static_assert(can_be_stored_v<Coefficient>, "The ga::for_each_component() function does not allow lazy evaluation with arguments from a lazy context.");

            template<typename ValueCItr, typename BitsetCItr, typename MapCIts, typename Function>
            GA_ALWAYS_INLINE constexpr static bool run(ValueCItr const &, BitsetCItr &bitset_citr, MapCIts const &, Function f) GA_NOEXCEPT(GA_NOEXCEPT(f)) {
                bool keep_going = true;
                f(*bitset_citr, static_cast<ValueType>(Coefficient::template eval<0, 0>(std::make_tuple())), entry_source_t::STORED_RUNTIME_DEFINED_ENTRY, entry_source_t::COMPILE_TIME_DEFINED_ENTRY, keep_going);
                ++bitset_citr;
                return keep_going;
            }
        };

        template<typename ValueType, bitset_t PossibleGrades>
        struct _for_each_component_impl_inner_iteration<ValueType, stored_value, dynamic_basis_blade<PossibleGrades, stored_bitset> > {
            template<typename ValueCItr, typename BitsetCItr, typename MapCIts, typename Function>
            GA_ALWAYS_INLINE constexpr static bool run(ValueCItr &value_citr, BitsetCItr &bitset_citr, MapCIts const &, Function f) GA_NOEXCEPT(GA_NOEXCEPT(f)) {
                bool keep_going = true;
                f(*bitset_citr, *value_citr, entry_source_t::STORED_RUNTIME_DEFINED_ENTRY, entry_source_t::STORED_RUNTIME_DEFINED_ENTRY, keep_going);
                ++value_citr;
                ++bitset_citr;
                return keep_going;
            }
        };

        template<typename ValueType, bitset_t PossibleGrades>
        struct _for_each_component_impl_inner_iteration<ValueType, stored_map_values, dynamic_basis_blade<PossibleGrades, stored_map_bitsets> > {
            template<typename ValueCItr, typename BitsetCItr, typename MapCIts, typename Function>
            GA_ALWAYS_INLINE constexpr static bool run(ValueCItr const &, BitsetCItr const &, MapCIts &map_citr, Function f) GA_NOEXCEPT(GA_NOEXCEPT(f)) {
                bool keep_going = true;
                for (auto const &pair : *map_citr) {
                    f(pair.first, pair.second, entry_source_t::MAPPED_RUNTIME_DEFINED_ENTRY, entry_source_t::MAPPED_RUNTIME_DEFINED_ENTRY, keep_going);
                    if (!keep_going) {
                        break;
                    }
                }
                ++map_citr;
                return keep_going;
            }
        };

    }

    // Applies the given function object f to the result of dereferencing every component in the given instance of ga::clifford_expression<CoefficientType, Expression>. The list of parameters of the function is: bitset_t const basis_vectors, CoefficientType const &value, ga::entry_source_t const basis_vectors_source, ga::entry_source_t const value_source, bool &keep_going. The keep_going parameter is always initialized to true. This function does not allow lazy evaluation with arguments from a lazy context.
    template<typename CoefficientType, typename Expression, typename Function>
    inline bool for_each_component(clifford_expression<CoefficientType, Expression> const &arg, Function f) GA_NOEXCEPT(GA_NOEXCEPT(f)) {
        static_assert(detail::can_be_stored_v<Expression>, "This function does not expect lazy expressions.");
        auto value_citr = arg.values().cbegin();
        auto bitset_citr = arg.bitsets().cbegin();
        auto map_citr = arg.maps().cbegin();
        return detail::_for_each_component_impl<CoefficientType, Expression>::run(value_citr, bitset_citr, map_citr, f);
    }

}

#endif // __GA_UTIL_FOR_EACH_COMPONENT_HPP__
