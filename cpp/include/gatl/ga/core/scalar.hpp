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

#ifndef __GA_CORE_SCALAR_HPP__
#define __GA_CORE_SCALAR_HPP__

namespace ga {

    // Helper for defining a scalar value type.
    template<typename CoefficientType>
    using scaled_scalar_t = scalar_clifford_expression<CoefficientType, detail::stored_value>;

    // Helper for defining an unit compile-time defined scalar type.
    using unit_scalar_t = scalar_clifford_expression<default_integral_t, detail::constant_value<1> >;

    // Converts the given native value type to scalar Clifford expression.
    template<typename ValueType, std::enable_if_t<!is_clifford_expression_v<ValueType>, int> = 0>
    constexpr scaled_scalar_t<ValueType> scalar(ValueType const &arg) GA_NOEXCEPT {
        return scaled_scalar_t<ValueType>(make_sequential_storage(arg));
    }

    template<typename ValueType, std::enable_if_t<!is_clifford_expression_v<ValueType>, int> = 0>
    constexpr decltype(auto) scalar(ValueType &&arg) GA_NOEXCEPT {
        return scaled_scalar_t<std::remove_cv_t<std::remove_reference_t<ValueType> > >(make_sequential_storage(std::move(arg)));
    }

    template<typename CoefficientType, typename Coefficient>
    constexpr decltype(auto) scalar(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) GA_NOEXCEPT {
        return arg;
    }

    template<typename CoefficientType, typename Coefficient>
    constexpr decltype(auto) scalar(scalar_clifford_expression<CoefficientType, Coefficient> &&arg) GA_NOEXCEPT {
        return std::move(arg);
    }

}

#endif // __GA_CORE_SCALAR_HPP__
