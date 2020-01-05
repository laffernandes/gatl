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

#ifndef __GA_MODEL_GENERAL_METRIC_SPACE_HPP__
#define __GA_MODEL_GENERAL_METRIC_SPACE_HPP__

namespace ga {

    namespace detail {

        template<typename Index, typename... Entries>
        struct metric_matrix_entry;
        //TODO Runtime-defined index is not supported yet.

        template<typename Index, typename... Entries>
        using metric_matrix_entry_t = typename metric_matrix_entry<Index, Entries...>::type;

        template<default_integral_t IndexValue, typename FirstEntry, typename... NextEntries>
        struct metric_matrix_entry<constant_value<IndexValue>, FirstEntry, NextEntries...> :
            metric_matrix_entry<constant_value<IndexValue - 1>, NextEntries...> {
        };

        template<typename FirstEntry, typename... NextEntries>
        struct metric_matrix_entry<constant_value<0>, FirstEntry, NextEntries...> {
            using type = FirstEntry;
        };

        template<typename FirstEntry>
        struct metric_matrix_entry<constant_value<0>, FirstEntry> {
            using type = FirstEntry;
        };

    }

    // General metric space.
    template<typename... MetricMatrixEntries>
    class general_metric_space : public metric_space<general_metric_space<MetricMatrixEntries...> > {
    public:

        using metric_space_type = general_metric_space;

        constexpr static ndims_t vector_space_dimensions = detail::isqrt(sizeof...(MetricMatrixEntries));
        constexpr static bitset_t basis_vectors = detail::safe_rshift(bitset_t(~0), std::numeric_limits<bitset_t>::digits - vector_space_dimensions);

        template<typename RowIndex, typename ColIndex>
        struct entry {
            using type = detail::metric_matrix_entry_t<detail::addition_t<detail::product_t<detail::constant_value<vector_space_dimensions>, detail::addition_t<RowIndex, detail::constant_value<-1> >, detail::value_mapping>, detail::addition_t<ColIndex, detail::constant_value<-1> > >, MetricMatrixEntries...>;
        };
    };

    template<default_integral_t... MetricMatrixValues>
    using constant_general_metric_space_t = general_metric_space<detail::constant_value<MetricMatrixValues>...>;

    // Specialization of is_general_metric_space<MetricSpaceType>.
    template<typename... MetricMatrixEntries>
    struct is_general_metric_space<general_metric_space<MetricMatrixEntries...> > :
        std::true_type {
    };

}

#endif // __GA_MODEL_GENERAL_METRIC_SPACE_HPP__
