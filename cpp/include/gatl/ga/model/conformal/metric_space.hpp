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

#ifndef __GA_MODEL_CONFORMAL_METRIC_SPACE_HPP__
#define __GA_MODEL_CONFORMAL_METRIC_SPACE_HPP__

namespace ga {

    // Conformal metric space.
    template<ndims_t D>
    class conformal_metric_space : public metric_space<conformal_metric_space<D> > {
    public:

        using metric_space_type = conformal_metric_space;

        constexpr static bitset_t basis_vectors = detail::safe_rshift(bitset_t(~0), std::numeric_limits<bitset_t>::digits - (D + 2));
        constexpr static ndims_t vector_space_dimensions = D + 2;

        template<typename RowIndex, typename ColIndex>
        struct entry {
            using type = detail::if_else_t<
                detail::equal_t<RowIndex, ColIndex>,
                detail::if_else_t<detail::less_or_equal_t<RowIndex, detail::constant_value<D> >, detail::constant_value<1>, detail::constant_value<0> >,
                detail::if_else_t<detail::logical_or_t<detail::less_or_equal_t<RowIndex, detail::constant_value<D> >, detail::less_or_equal_t<ColIndex, detail::constant_value<D> > >, detail::constant_value<0>, detail::constant_value<-1> >
            >;
        };
    };

    // Specialization of is_general_metric_space<MetricSpaceType>.
    template<ndims_t D>
    struct is_general_metric_space<conformal_metric_space<D> > :
        std::true_type {
    };

}

#endif // __GA_MODEL_CONFORMAL_METRIC_SPACE_HPP__
