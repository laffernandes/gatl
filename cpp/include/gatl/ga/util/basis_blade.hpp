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

#ifndef __GA_UTIL_BASIS_BLADE_HPP__
#define __GA_UTIL_BASIS_BLADE_HPP__

namespace ga {

    // Helper for defining a scaled runtime defined basis blade type.
    template<typename CoefficientType, grade_t FirstPossibleGrade, grade_t LastPossibleGrade = FirstPossibleGrade>
    using scaled_basis_blade_t = clifford_expression<CoefficientType, detail::component_t<detail::stored_value, detail::dynamic_basis_blade_t<((bitset_t(1) << LastPossibleGrade) | ((bitset_t(1) << LastPossibleGrade) - bitset_t(1))) - ((bitset_t(1) << FirstPossibleGrade) - bitset_t(1)), detail::stored_bitset> > >;

    // Helper for defining a scaled compile-time defined basis blade type.
    template<typename CoefficientType, index_t... Indices>
    using scaled_constant_basis_blade_t = clifford_expression<CoefficientType, detail::component_t<detail::stored_value, detail::constant_basis_blade<((bitset_t(1) << (Indices - 1)) + ... + bitset_t(0))> > >;

    // Helper for defining an unit runtime defined basis blade type.
    template<grade_t FirstPossibleGrade, grade_t LastPossibleGrade = FirstPossibleGrade>
    using unit_basis_blade_t = clifford_expression<default_integral_t, detail::component_t<detail::constant_value<1>, detail::dynamic_basis_blade_t<((bitset_t(1) << LastPossibleGrade) | ((bitset_t(1) << LastPossibleGrade) - bitset_t(1))) - ((bitset_t(1) << FirstPossibleGrade) - bitset_t(1)), detail::stored_bitset> > >;

    // Helper for defining an unit compile-time defined basis blade type.
    template<index_t... Indices>
    using unit_constant_basis_blade_t = clifford_expression<default_integral_t, detail::component_t<detail::constant_value<1>, detail::constant_basis_blade<((bitset_t(1) << (Indices - 1)) + ... + bitset_t(0))> > >;

}

#endif // __GA_UTIL_BASIS_BLADE_HPP__
