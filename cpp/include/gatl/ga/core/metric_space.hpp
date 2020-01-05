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

#ifndef __GA_CORE_METRIC_SPACE_HPP__
#define __GA_CORE_METRIC_SPACE_HPP__

namespace ga {

    // Base metric space typename.
    template<typename MetricSpaceType>
    class metric_space {

        using metric_space_type = MetricSpaceType;

    protected:

        constexpr metric_space() = default;
        constexpr metric_space(metric_space const &) = default;
        constexpr metric_space(metric_space &&) = default;

        constexpr metric_space & operator=(metric_space const &) = default;
        constexpr metric_space & operator=(metric_space &&) = default;
    };

    // Returns whether the given metric space is orthogonal.
    template<typename MetricSpaceType>
    struct is_orthogonal_metric_space :
        std::false_type {
    };

    template<typename MetricSpaceType>
    constexpr bool is_orthogonal_metric_space_v = is_orthogonal_metric_space<MetricSpaceType>::value;

    template<typename MetricSpaceType>
    struct is_orthogonal_metric_space<metric_space<MetricSpaceType> > :
        std::bool_constant<is_orthogonal_metric_space_v<MetricSpaceType> > {
    };

    // Returns whether the given metric space is general.
    template<typename MetricSpaceType>
    struct is_general_metric_space :
        std::false_type {
    };

    template<typename MetricSpaceType>
    constexpr bool is_general_metric_space_v = is_general_metric_space<MetricSpaceType>::value;

    template<typename MetricSpaceType>
    struct is_general_metric_space<metric_space<MetricSpaceType> > :
        std::bool_constant<is_general_metric_space_v<MetricSpaceType> > {
    };

    // Returns whether the given type is a metric space type.
    template<typename Type>
    struct is_metric_space :
        std::bool_constant<is_orthogonal_metric_space_v<Type> || is_general_metric_space_v<Type> > {
    };

    template<typename Type>
    constexpr bool is_metric_space_v = is_metric_space<Type>::value;

}

#endif // __GA_CORE_METRIC_SPACE_HPP__
