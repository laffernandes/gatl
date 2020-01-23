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

#ifndef __GA_UTIL_PSEUDOSCALAR_HPP__
#define __GA_UTIL_PSEUDOSCALAR_HPP__

namespace ga {

    // Helper for defining a scaled compile-time defined pseudoscalar type.
    template<typename CoefficientType, ndims_t N>
    using scaled_pseudoscalar_t = clifford_expression<CoefficientType, detail::component_t<detail::stored_value, detail::constant_basis_blade<detail::first_combination(N)> > >;

    // Helper for defining an unit compile-time defined pseudoscalar type.
    template<ndims_t N>
    using unit_pseudoscalar_t = clifford_expression<default_integral_t, detail::component_t<detail::constant_value<1>, detail::constant_basis_blade<detail::first_combination(N)> > >;

    // Returns the compile-time defined unit pseudoscalar of the given space.
    template<typename MetricSpaceType>
    constexpr unit_pseudoscalar_t<MetricSpaceType::vector_space_dimensions> pseudoscalar(metric_space<MetricSpaceType> const &) GA_NOEXCEPT {
        return unit_pseudoscalar_t<MetricSpaceType::vector_space_dimensions>();
    }

}

#endif // __GA_UTIL_PSEUDOSCALAR_HPP__
