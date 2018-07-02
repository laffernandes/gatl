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

#ifndef __GA_UTIL_K_VECTOR_HPP__
#define __GA_UTIL_K_VECTOR_HPP__

namespace ga {

	namespace detail {

		// Helper structure for defining the expression of a full k-vector type with runtime defined coefficients over an n-dimensional vector space.
		template<default_bitset_t Bitset, default_bitset_t BasisVectors>
		struct make_kvector_expression;

		template<default_bitset_t Bitset, default_bitset_t BasisVectors>
		using make_kvector_expression_t = typename make_kvector_expression<Bitset, BasisVectors>::type;

		template<default_bitset_t Bitset, default_bitset_t BasisVectors>
		struct make_kvector_expression {
			typedef addition_t<component_t<stored_value, constant_basis_blade<Bitset> >, make_kvector_expression_t<next_combination(Bitset, BasisVectors), BasisVectors> > type;
		};

		template<default_bitset_t BasisVectors>
		struct make_kvector_expression<default_bitset_t(0), BasisVectors> {
			typedef component_t<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > type;
		};

		// Deduces the ga::clifford_expression<CoefficientType, Expression> type of the vector having the given set of coordinates.
		template<ndims_t N, typename... CoordinatesTypes>
		struct deduce_vector;

		template<ndims_t N, typename... CoordinatesTypes>
		using deduce_vector_t = typename deduce_vector<N, CoordinatesTypes...>::type;

		template<ndims_t N, typename CoordinateType, typename... NextCoordinateTypes>
		struct deduce_vector<N, CoordinateType, NextCoordinateTypes...> {
		private:

			typedef deduce_vector_t<N, NextCoordinateTypes...> tail;

		public:

			typedef clifford_expression<std::common_type_t<CoordinateType, typename tail::coefficient_type>, addition_t<component_t<stored_value, constant_basis_blade<(default_bitset_t(1) << (N - (sizeof...(NextCoordinateTypes) + 1)))> >, typename tail::expression_type> > type;
		};

		template<ndims_t N, typename CoordinateType>
		struct deduce_vector<N, CoordinateType> {
			typedef clifford_expression<CoordinateType, component_t<stored_value, constant_basis_blade<(default_bitset_t(1) << (N - 1))> > > type;
		};

		template<ndims_t N, typename CoefficientType, typename Coefficient, typename... NextCoordinateTypes>
		struct deduce_vector<N, scalar_clifford_expression<CoefficientType, Coefficient>, NextCoordinateTypes...> {
		private:

			typedef deduce_vector_t<N, NextCoordinateTypes...> tail;

		public:

			typedef clifford_expression<std::common_type_t<CoefficientType, typename tail::coefficient_type>, addition_t<component_t<Coefficient, constant_basis_blade<(default_bitset_t(1) << (N - (sizeof...(NextCoordinateTypes) + 1)))> >, typename tail::expression_type> > type;
		};

		template<ndims_t N, typename CoefficientType, typename Coefficient>
		struct deduce_vector<N, scalar_clifford_expression<CoefficientType, Coefficient> > {
			typedef clifford_expression<CoefficientType, component_t<Coefficient, constant_basis_blade<(default_bitset_t(1) << (N - 1))> > > type;
		};

		template<ndims_t N, typename CoefficientType, typename Expression, typename... NextCoordinateTypes>
		struct deduce_vector<N, clifford_expression<CoefficientType, Expression>, NextCoordinateTypes...> {
			static_assert(is_scalar_component_v<Expression>, "The given coordinate is not defined as a scalar value in compilation time.");
		};

		template<ndims_t N, typename CoefficientType, typename Expression>
		struct deduce_vector<N, clifford_expression<CoefficientType, Expression> > {
			static_assert(is_scalar_component_v<Expression>, "The given coordinate is not defined as a scalar value in compilation time.");
		};

		// Helper structures to build a sequential storage of vector coordinates.
		struct make_vector_sequential_storage_simple {
			template<typename... CoordinatesTypes>
			constexpr static decltype(auto) run(CoordinatesTypes const &&... coords) {
				return make_sequential_storage(std::move(coords)...);
			}
		};

		struct make_vector_sequential_storage_not_simple {
		private:

			template<typename ValueType, std::size_t Size, std::size_t... Indices>
			constexpr static decltype(auto) to_values_tuple(sequential_storage<ValueType, Size> const &&values, indices<Indices...> const) {
				return std::tie(std::get<Indices>(std::move(values))...);
			}

			template<typename ValueType, std::size_t Size>
			constexpr static decltype(auto) to_values_tuple(sequential_storage<ValueType, Size> const &&) {
				return to_values_tuple(std::move(values), build_indices_t<Size>());
			}

			template<typename ValueType>
			constexpr static decltype(auto) to_values_tuple(sequential_storage<ValueType, 0> const &&) {
				return std::make_tuple();
			}

			constexpr static decltype(auto) make_values_tuple() {
				return std::make_tuple();
			}

			template<typename CoordinateType, typename... NextCoordinatesTypes>
			constexpr static decltype(auto) make_values_tuple(CoordinateType const &&coord, NextCoordinatesTypes const &&... next_coords) {
				return std::tuple_cat(std::make_tuple(std::move(coord)), make_values_tuple(std::move(next_coords)...));
			}

			template<typename CoefficientType, typename Expression, typename... NextCoordinatesTypes>
			constexpr static decltype(auto) make_values_tuple(clifford_expression<CoefficientType, Expression> const &&coord, NextCoordinatesTypes const &&... next_coords) {
				return std::tuple_cat(to_values_tuple(coord.values()), make_values_tuple(std::move(next_coords)...));
			}

			template<typename... ValueTypes, std::size_t... Indices>
			constexpr static decltype(auto) to_sequential_storage(std::tuple<ValueTypes...> const &&tuple, indices<Indices...> const) {
				return make_sequential_storage(std::get<Indices>(std::move(tuple))...);
			}

			template<typename... ValueTypes>
			constexpr static decltype(auto) to_sequential_storage(std::tuple<ValueTypes...> const &&tuple) {
				return to_sequential_storage(std::move(tuple), build_indices_t<std::tuple_size_v<std::remove_reference_t<std::tuple<ValueTypes...> > > >());
			}

		public:

			template<typename... CoordinatesTypes>
			constexpr static decltype(auto) run(CoordinatesTypes const &&... coords) {
				return to_sequential_storage(make_values_tuple(std::move(coords)...));
			}
		};

		// Helper structure to build a ga::clifford_expression<CoefficientType, Expression> representing a vector.
		template<typename CliffordExpression, typename Enabled = void>
		struct make_vector {
			template<typename... CoordinatesTypes>
			constexpr static CliffordExpression run(CoordinatesTypes const &&... coords) {
				return CliffordExpression(std::conditional_t<std::disjunction_v<std::bool_constant<is_clifford_expression_v<std::remove_reference_t<CoordinatesTypes> > >...>, detail::make_vector_sequential_storage_not_simple, detail::make_vector_sequential_storage_simple>::run(std::move(coords)...));
			}
		};

		template<typename CliffordExpression>
		struct make_vector<CliffordExpression, std::enable_if_t<count_stored_values_v<typename CliffordExpression::expression_type> == 0> > {
			template<typename... CoordinatesTypes>
			constexpr static CliffordExpression run(CoordinatesTypes const &&...) {
				return CliffordExpression();
			}
		};

	}

	// Helper for defining a full k-vector type with runtime defined coefficients over an n-dimensional vector space.
	template<typename CoefficientType, grade_t K, ndims_t N>
	using full_kvector_t = clifford_expression<CoefficientType, std::conditional_t<K == 0, detail::component_t<detail::stored_value, detail::constant_basis_blade<default_bitset_t(0)> >, detail::make_kvector_expression_t<detail::first_combination(K), detail::first_combination(N)> > >;

	// Helper for defining a full vector type with runtime defined coefficients over an n-dimensional vector space.
	template<typename CoefficientType, ndims_t N>
	using full_vector_t = clifford_expression<CoefficientType, detail::make_kvector_expression_t<default_bitset_t(1), detail::first_combination(N)> >;

	// Makes a vector with the given set of coordinates.
	template<typename MetricSpaceType, typename... CoordinatesTypes>
	constexpr decltype(auto) vector(metric_space<MetricSpaceType> const &, CoordinatesTypes const &&... coords) {
		static_assert(MetricSpaceType::vector_space_dimensions == sizeof...(CoordinatesTypes), "The number of coordinates must be equal to the number of dimensions of the vector space.");
		return detail::make_vector<detail::deduce_vector_t<MetricSpaceType::vector_space_dimensions, std::remove_reference_t<CoordinatesTypes>...> >::run(std::move(coords)...);
	}

}

#endif // __GA_UTIL_K_VECTOR_HPP__
