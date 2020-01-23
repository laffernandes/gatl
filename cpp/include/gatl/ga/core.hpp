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

#ifndef __GA_CORE_HPP__
#define __GA_CORE_HPP__

#ifdef _MSC_VER
    #pragma inline_recursion(on)
    #pragma inline_depth(255)
#endif

#if defined(__GNUC__)
    #define GA_ALWAYS_INLINE __attribute__((always_inline))
    #define GA_NOEXCEPT noexcept
#elif defined(_MSC_VER) && !defined(__clang__)
    #define GA_ALWAYS_INLINE __forceinline
    #if _MSC_VER >= 1900
        #define GA_NOEXCEPT noexcept
    #else
        #define GA_NOEXCEPT
    #endif
#else
    #define GA_ALWAYS_INLINE
    #define GA_NOEXCEPT
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <type_traits>

#ifndef GA_DEFAULT_FLOATING_POINT_TYPE
    #define GA_DEFAULT_FLOATING_POINT_TYPE std::double_t
#endif // GA_DEFAULT_FLOATING_POINT_TYPE

#ifndef GA_DEFAULT_INTEGRAL_TYPE
    #define GA_DEFAULT_INTEGRAL_TYPE std::int64_t
#endif // GA_DEFAULT_INTEGRAL_TYPE

#ifndef GA_MAX_BASIS_VECTOR_INDEX
    #define GA_MAX_BASIS_VECTOR_INDEX 63
#endif // GA_MAX_BASIS_VECTOR_INDEX

namespace ga {

    static_assert(std::is_integral_v<decltype((GA_MAX_BASIS_VECTOR_INDEX))> && 1 <= (GA_MAX_BASIS_VECTOR_INDEX) && (GA_MAX_BASIS_VECTOR_INDEX) <= 63, "GA_MAX_BASIS_VECTOR_INDEX must be an integer value between 1 and 63, inclusive.");

    using default_floating_point_t = GA_DEFAULT_FLOATING_POINT_TYPE;
    using default_integral_t = GA_DEFAULT_INTEGRAL_TYPE;

    using bitset_t = std::conditional_t<(GA_MAX_BASIS_VECTOR_INDEX) < 8, std::uint8_t, std::conditional_t<(GA_MAX_BASIS_VECTOR_INDEX) < 16, std::uint16_t, std::conditional_t<(GA_MAX_BASIS_VECTOR_INDEX) < 32, std::uint32_t, std::uint64_t> > >;

    using grade_t = default_integral_t;

    using index_t = std::uint64_t;
    using ndims_t = index_t;

    template<typename ValueType>
    using associative_container_t = std::map<bitset_t, ValueType>;

    template<typename EntryType, std::size_t Size>
    using sequence_container_t = std::array<EntryType, Size>;

}

#include "core/exceptions.hpp"
#include "core/type_traits_extension.hpp"

#include "core/constexpr.hpp"

#include "core/expression.hpp"
#include "core/expression_traits.hpp"

#include "core/metric_space.hpp"
#include "core/real_metric_space.hpp"

#include "core/mapping.hpp"

#include "core/expression_relational_operators.hpp"
#include "core/expression_graded_unary_minus.hpp"

#include "core/rules.hpp"
#include "core/expression_simplification_addition_values.hpp"
#include "core/expression_simplification_addition_components.hpp"
#include "core/expression_simplification_product_values.hpp"
#include "core/expression_simplification_product_components.hpp"
#include "core/expression_simplification_power.hpp"

#include "core/clifford_expression.hpp"

#include "core/lazy_context.hpp"

#include "core/constant.hpp"
#include "core/scalar.hpp"

#include "core/conjugation.hpp"
#include "core/involution.hpp"
#include "core/reversion.hpp"

#include "core/exterior_product_mapping.hpp"
#include "core/regressive_product_mapping.hpp"
#include "core/orthogonal_metric_mapping.hpp"
#include "core/general_metric_mapping.hpp"

#include "core/dot_product.hpp"
#include "core/geometric_product.hpp"
#include "core/hestenes_inner_product.hpp"
#include "core/left_contraction.hpp"
#include "core/outer_product.hpp"
#include "core/regressive_product.hpp"
#include "core/right_contraction.hpp"
#include "core/scalar_product.hpp"

#include "core/math.hpp"
#include "core/arithmetic_operators.hpp"

#include "core/macro_for_algebra_overload.hpp"
#include "core/macro_for_mapping_specialization.hpp"

#endif // __GA_CORE_HPP__
