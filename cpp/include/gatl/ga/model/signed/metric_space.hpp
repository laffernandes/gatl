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

#ifndef __GA_MODEL_SIGNED_METRIC_SPACE_HPP__
#define __GA_MODEL_SIGNED_METRIC_SPACE_HPP__

namespace ga {

    // Orthogonal metric space with signature (P,Q,R).
    template<ndims_t P, ndims_t Q, ndims_t R>
    class signed_metric_space : public metric_space<signed_metric_space<P, Q, R> > {
    public:

        using metric_space_type = signed_metric_space;

        constexpr static bitset_t basis_vectors = detail::safe_rshift(bitset_t(~0), std::numeric_limits<bitset_t>::digits - (P + Q + R));
        constexpr static ndims_t vector_space_dimensions = P + Q + R;

    private:

        constexpr static bitset_t negative = (Q != 0) ? detail::safe_rshift(bitset_t(~0), std::numeric_limits<bitset_t>::digits - Q) << P : bitset_t(0);
        constexpr static bitset_t zero = (R != 0) ? detail::safe_rshift(bitset_t(~0), std::numeric_limits<bitset_t>::digits - R) << (P + Q) : bitset_t(0);

    public:

        template<typename BasisVectorsBitset>
        struct metric_factor {
            using type = detail::if_else_t<
                    detail::equal_t<
                        detail::bitwise_and_t<BasisVectorsBitset, detail::constant_bitset<zero> >,
                        detail::constant_bitset<bitset_t(0)>
                    >,
                    detail::if_else_t<
                        detail::equal_t<
                            detail::bitwise_and_t<
                                detail::count_one_bits_t<detail::bitwise_and_t<BasisVectorsBitset, detail::constant_bitset<negative> > >,
                                detail::constant_value<1>
                            >,
                            detail::constant_value<0>
                        >,
                        detail::constant_value<1>,
                        detail::constant_value<-1>
                    >,
                    detail::constant_value<0>
                >;
        };

        static_assert((P + Q + R) <= GA_MAX_BASIS_VECTOR_INDEX, "ga::signed_metric_space<P, Q, R> is ill-defined. It is expectated (P + Q + R) <= GA_MAX_BASIS_VECTOR_INDEX.");
    };

    // Specialization of is_orthogonal_metric_space<MetricSpaceType>.
    template<ndims_t P, ndims_t Q, ndims_t R>
    struct is_orthogonal_metric_space<signed_metric_space<P, Q, R> > :
        std::true_type {
    };

}

#endif // __GA_MODEL_SIGNED_METRIC_SPACE_HPP__
