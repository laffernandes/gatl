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

#ifndef __GA_UTIL_FOR_EACH_BASIS_VECTOR_HPP__
#define __GA_UTIL_FOR_EACH_BASIS_VECTOR_HPP__

namespace ga {

    // Applies the given function object f to the result of dereferencing every basis vector in the given instance of ga::clifford_expression<CoefficientType, Expression> comprised by a single scaled basis blade or bitset. The list of parameters of the function is: ga::index_t const index, bool &keep_going. The keep_going parameter is always initialized to true.
    template<typename Function>
    inline bool for_each_basis_vector(bitset_t arg, Function f) GA_NOEXCEPT(GA_NOEXCEPT(f)) {
        bool keep_going = true;
        while (arg != bitset_t(0) && keep_going) {
            bitset_t const current_set_bit = detail::rightmost_set_bit(arg);
            f(detail::set_bit_index(current_set_bit) + 1, keep_going);
            arg ^= current_set_bit;
        }
        return keep_going;
    };

    template<typename CoefficientType, typename Coefficient, bitset_t BasisVectors, typename Function>
    inline bool for_each_basis_vector(clifford_expression<CoefficientType, detail::component<Coefficient, detail::constant_basis_blade<BasisVectors> > > const &, Function f) GA_NOEXCEPT(GA_NOEXCEPT(f)) {
        static_assert(detail::can_be_stored_v<Coefficient>, "The ga::for_each_basis_vector() function does not allow lazy evaluation with arguments from a lazy context.");
        return for_each_basis_vector(BasisVectors, f);
    };

    template<typename CoefficientType, typename Coefficient, bitset_t PossibleGrades, typename Function>
    inline bool for_each_basis_vector(clifford_expression<CoefficientType, detail::component<Coefficient, detail::dynamic_basis_blade<PossibleGrades, detail::stored_bitset> > > const &arg, Function f) GA_NOEXCEPT(GA_NOEXCEPT(f)) {
        static_assert(detail::can_be_stored_v<Coefficient>, "The ga::for_each_basis_vector() function does not allow lazy evaluation with arguments from a lazy context.");
        return for_each_basis_vector(*arg.bitsets().cbegin(), f);
    };

}

#endif // __GA_UTIL_FOR_EACH_BASIS_VECTOR_HPP__
