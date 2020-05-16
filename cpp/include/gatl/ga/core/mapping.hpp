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

#ifndef __GA_CORE_MAPPING_HPP__
#define __GA_CORE_MAPPING_HPP__

namespace ga {

    namespace detail {

        // Mapping for non-metric products.
        template<ndims_t VectorSpaceDimensions>
        struct exterior_product_mapping;

        // Mapping for non-metric products.
        template<ndims_t VectorSpaceDimensions>
        struct regressive_product_mapping;

        // Mapping for products assuming spaces with orthogonal metric.
        template<typename OrthogonalMetricSpace, typename GradedProduct>
        struct orthogonal_metric_mapping;

        // Mapping for productes assuming spaces with general (non-orthogonal) metric.
        template<typename GeneralMetricSpace, typename GradedProduct>
        struct general_metric_mapping;

        // Returns the metric space mapping that fits the given arguments.
        template<typename MetricSpaceType, typename GradedProduct>
        struct _metric_space_mapping {
            using type = std::conditional_t<
                is_orthogonal_metric_space_v<MetricSpaceType>,
                orthogonal_metric_mapping<MetricSpaceType, GradedProduct>,
                std::conditional_t<
                    is_general_metric_space_v<MetricSpaceType>,
                    general_metric_mapping<MetricSpaceType, GradedProduct>,
                    std::nullptr_t // should be impossible
                >
            >;
        };
        
        template<typename MetricSpaceType, typename GradedProduct>
        using metric_space_mapping_t = typename _metric_space_mapping<MetricSpaceType, GradedProduct>::type;

    }

}

#endif // __GA_CORE_MAPPING_HPP__
