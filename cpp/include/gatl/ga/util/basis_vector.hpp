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

#ifndef __GA_UTIL_BASIS_VECTOR_HPP__
#define __GA_UTIL_BASIS_VECTOR_HPP__

namespace ga {

    // Helper for defining a scaled runtime defined basis vector type.
    template<typename CoefficientType>
    using scaled_basis_vector_t = clifford_expression<CoefficientType, detail::component_t<detail::stored_value, detail::dynamic_basis_blade_t<bitset_t(2), detail::stored_bitset> > >;

    // Helper for defining a scaled compile-time defined basis vector type.
    template<typename CoefficientType, index_t Index>
    using scaled_constant_basis_vector_t = clifford_expression<CoefficientType, detail::component_t<detail::stored_value, detail::constant_basis_blade<(bitset_t(1) << (Index - 1))> > >;

    // Helper for defining an unit runtime defined basis vector type.
    using unit_basis_vector_t = clifford_expression<default_integral_t, detail::component_t<detail::constant_value<1>, detail::dynamic_basis_blade_t<bitset_t(2), detail::stored_bitset> > >;

    // Helper for defining an unit compile-time defined basis vector type.
    template<index_t Index>
    using unit_constant_basis_vector_t = clifford_expression<default_integral_t, detail::component_t<detail::constant_value<1>, detail::constant_basis_blade<(bitset_t(1) << (Index - 1))> > >;

    // Returns a runtime defined unit basis vector.
    constexpr unit_basis_vector_t e(index_t const index) GA_NOEXCEPT {
        assert(index > 0);
        return unit_basis_vector_t(make_sequential_storage(bitset_t(1) << (index - 1)));
    }

    // Returns a compile-time defined unit basis vector.
    template<typename IndexType, default_integral_t Index, std::enable_if_t<std::is_constructible_v<index_t, IndexType>, int> = 0>
    constexpr unit_constant_basis_vector_t<Index> e(constant<IndexType, Index> const &) GA_NOEXCEPT {
        static_assert(Index > 0, "Basis vector index out of bounds. It is expected a positive value.");
        return unit_constant_basis_vector_t<Index>();
    }

}

#endif // __GA_UTIL_BASIS_VECTOR_HPP__
