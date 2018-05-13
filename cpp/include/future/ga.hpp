#ifndef __FUTURE_GA_HPP__
#define __FUTURE_GA_HPP__

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

namespace future {

	namespace ga {

		static_assert(std::is_integral_v<decltype((GA_MAX_BASIS_VECTOR_INDEX))> && 1 <= (GA_MAX_BASIS_VECTOR_INDEX) && (GA_MAX_BASIS_VECTOR_INDEX) <= 63, "GA_MAX_BASIS_VECTOR_INDEX must be an integer value between 1 and 63, inclusive.");

		typedef std::int32_t default_integral_t;
		typedef std::int32_t id_t;

		typedef std::conditional_t<(GA_MAX_BASIS_VECTOR_INDEX) < 8, std::uint8_t, std::conditional_t<(GA_MAX_BASIS_VECTOR_INDEX) < 16, std::uint16_t, std::conditional_t<(GA_MAX_BASIS_VECTOR_INDEX) < 32, std::uint32_t, std::uint64_t> > > default_bitset_t;

		typedef std::int32_t grade_t;

		typedef std::uint32_t index_t;
		typedef std::uint32_t ndims_t;

	}

	#include "ga/type_traits_extension.hpp"
	
	#include "ga/constexpr.hpp"

	#include "ga/declarations.hpp"

	#include "ga/expression.hpp"
	#include "ga/expression_traits.hpp"

	#include "ga/metric_space.hpp"
	#include "ga/signed_metric_space.hpp"

	#include "ga/mapping.hpp"
	#include "ga/orthogonal_metric_mapping.hpp"
	#include "ga/general_metric_mapping.hpp"

	#include "ga/make_component.hpp"
	#include "ga/relational_operators.hpp"
	#include "ga/addition.hpp"
	#include "ga/product.hpp"
	#include "ga/exponentiation.hpp"

	#include "ga/clifford_expression.hpp"

	#include "ga/lazy_arguments.hpp"
	#include "ga/eval.hpp"
	#include "ga/lazy_context.hpp"

	#include "ga/constant.hpp"
	#include "ga/scalar.hpp"
	#include "ga/basis_vector.hpp"
	#include "ga/pseudoscalar.hpp"

	#include "ga/geometric_product.hpp"
	#include "ga/left_contraction.hpp"
	#include "ga/outer_product.hpp"
	#include "ga/right_contraction.hpp"
	#include "ga/scalar_product.hpp"

	#include "ga/reverse_norm.hpp"
	#include "ga/inverse_geometric_product.hpp"
	#include "ga/dualization.hpp"

	#include "ga/arithmetic_operators.hpp"

}

//TODO take_grade
//TODO simplificar pseudoscalar
//TODO math
//TODO reversion
//TODO involution
//TODO conjugation
//TODO grade
//TODO conformal_metric_space
//TODO exp
//TODO eval
//TODO Lidar com components<>

#endif // __FUTURE_GA_HPP__
