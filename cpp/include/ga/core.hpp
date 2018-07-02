/**
Copyright (C) 2018 Leandro Augusto Frata Fernandes

author     : Fernandes, Leandro A. F.
e-mail     : laffernandes@ic.uff.br
home page  : http://www.ic.uff.br/~laffernandes
repository : https://github.com/laffernandes/gatl.git

This file is part of The Geometric Algebra Template Library (GATL).

GATL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GATL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GATL. If not, see <https://www.gnu.org/licenses/>.
/**/

#ifndef __GA_CORE_HPP__
#define __GA_CORE_HPP__

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

#ifndef GA_MAX_BASIS_VECTOR_INDEX
	#define GA_MAX_BASIS_VECTOR_INDEX 63
#endif // GA_MAX_BASIS_VECTOR_INDEX

namespace ga {

	static_assert(std::is_integral_v<decltype((GA_MAX_BASIS_VECTOR_INDEX))> && 1 <= (GA_MAX_BASIS_VECTOR_INDEX) && (GA_MAX_BASIS_VECTOR_INDEX) <= 63, "GA_MAX_BASIS_VECTOR_INDEX must be an integer value between 1 and 63, inclusive.");

	typedef std::int32_t default_integral_t;
	typedef std::double_t default_floating_point_t;
	typedef std::conditional_t<(GA_MAX_BASIS_VECTOR_INDEX) < 8, std::uint8_t, std::conditional_t<(GA_MAX_BASIS_VECTOR_INDEX) < 16, std::uint16_t, std::conditional_t<(GA_MAX_BASIS_VECTOR_INDEX) < 32, std::uint32_t, std::uint64_t> > > default_bitset_t;

	template<typename EntryType, std::size_t Size>
	using default_sequence_container_t = std::array<EntryType, Size>;
		
	template<typename ValueType>
	using default_associative_container_t = std::map<default_bitset_t, ValueType>;

	typedef default_integral_t grade_t;

	typedef std::uint32_t index_t;
	typedef std::uint32_t ndims_t;

}

#include "ga/core/type_traits_extension.hpp"
	
#include "ga/core/constexpr.hpp"

#include "ga/core/expression.hpp"
#include "ga/core/expression_traits.hpp"

#include "ga/core/metric_space.hpp"
#include "ga/core/real_metric_space.hpp"

#include "ga/core/mapping.hpp"

#include "ga/core/expression_relational_operators.hpp"
#include "ga/core/expression_addition.hpp"
#include "ga/core/expression_product.hpp"
#include "ga/core/expression_power.hpp"
#include "ga/core/expression_graded_unary_minus.hpp"

#include "ga/core/clifford_expression.hpp"

#include "ga/core/lazy_context.hpp"

#include "ga/core/constant.hpp"
#include "ga/core/scalar.hpp"

#include "ga/core/copy.hpp"

#include "ga/core/conjugation.hpp"
#include "ga/core/involution.hpp"
#include "ga/core/reversion.hpp"

#include "ga/core/exterior_product_mapping.hpp"
#include "ga/core/regressive_product_mapping.hpp"
#include "ga/core/orthogonal_metric_mapping.hpp"
#include "ga/core/general_metric_mapping.hpp"

#include "ga/core/dot_product.hpp"
#include "ga/core/geometric_product.hpp"
#include "ga/core/hestenes_inner_product.hpp"
#include "ga/core/left_contraction.hpp"
#include "ga/core/outer_product.hpp"
#include "ga/core/regressive_product.hpp"
#include "ga/core/right_contraction.hpp"
#include "ga/core/scalar_product.hpp"

#include "ga/core/math.hpp"
#include "ga/core/arithmetic_operators.hpp"

#include "ga/core/macro_for_algebra_overload.hpp"

#endif // __GA_CORE_HPP__
