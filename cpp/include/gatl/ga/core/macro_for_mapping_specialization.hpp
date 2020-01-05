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

#ifndef __GA_CORE_MACRO_FOR_MAPPING_SPECIALIZATION_HPP__
#define __GA_CORE_MACRO_FOR_MAPPING_SPECIALIZATION_HPP__

#define _GA_EXTERIOR_PRODUCT_MAPPING_SPECIALIZATION(VECTOR_SPACE_DIMENSIONS, LEFT_BITSET, RIGHT_BITSET, RESULT_COEFFICIENT, RESULT_BITSET) \
    namespace ga { \
        namespace detail { \
            template<> \
            template<> \
            struct exterior_product_mapping<VECTOR_SPACE_DIMENSIONS>::multiply<constant_basis_blade<(LEFT_BITSET)>, constant_basis_blade<(RIGHT_BITSET)> > { \
                using type = component_t<constant_value<(RESULT_COEFFICIENT)>, constant_basis_blade<(RESULT_BITSET)> >; \
            }; \
        } \
    }

#define _GA_GENERAL_METRIC_MAPPING_SPECIALIZATION(GENERAL_METRIC_SPACE_TYPE, GRADED_PRODUCT_TYPE, LEFT_BITSET, RIGHT_BITSET, RESULT_COEFFICIENT, RESULT_BITSET) \
    namespace ga { \
        namespace detail { \
            template<> \
            template<> \
            struct general_metric_mapping<GENERAL_METRIC_SPACE_TYPE, GRADED_PRODUCT_TYPE>::multiply<constant_basis_blade<(LEFT_BITSET)>, constant_basis_blade<(RIGHT_BITSET)> > { \
                using type = component_t<constant_value<(RESULT_COEFFICIENT)>, constant_basis_blade<(RESULT_BITSET)> >; \
            }; \
        } \
    }

#define _GA_ORTHOGONAL_METRIC_MAPPING_SPECIALIZATION(ORTHOGONAL_METRIC_SPACE_TYPE, GRADED_PRODUCT_TYPE, LEFT_BITSET, RIGHT_BITSET, RESULT_COEFFICIENT, RESULT_BITSET) \
    namespace ga { \
        namespace detail { \
            template<> \
            template<> \
            struct orthogonal_metric_mapping<ORTHOGONAL_METRIC_SPACE_TYPE, GRADED_PRODUCT_TYPE>::multiply<constant_basis_blade<(LEFT_BITSET)>, constant_basis_blade<(RIGHT_BITSET)> > { \
                using type = component_t<constant_value<(RESULT_COEFFICIENT)>, constant_basis_blade<(RESULT_BITSET)> >; \
            }; \
        } \
    }

#define _GA_REGRESSIVE_PRODUCT_MAPPING_SPECIALIZATION(VECTOR_SPACE_DIMENSIONS, LEFT_BITSET, RIGHT_BITSET, RESULT_COEFFICIENT, RESULT_BITSET) \
    namespace ga { \
        namespace detail { \
            template<> \
            template<> \
            struct regressive_product_mapping<VECTOR_SPACE_DIMENSIONS>::multiply<constant_basis_blade<(LEFT_BITSET)>, constant_basis_blade<(RIGHT_BITSET)> > { \
                using type = component_t<constant_value<(RESULT_COEFFICIENT)>, constant_basis_blade<(RESULT_BITSET)> >; \
            }; \
        } \
    }

#endif // __GA_CORE_MACRO_FOR_MAPPING_SPECIALIZATION_HPP__
