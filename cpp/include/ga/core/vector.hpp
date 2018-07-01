#ifndef __GA_CORE_VECTOR_HPP__
#define __GA_CORE_VECTOR_HPP__

namespace ga {

	namespace detail {

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

	// Makes a vector with the given set of coordinates.
	template<typename MetricSpaceType, typename... CoordinatesTypes>
	constexpr decltype(auto) vector(metric_space<MetricSpaceType> const &, CoordinatesTypes const &&... coords) {
		static_assert(MetricSpaceType::vector_space_dimensions == sizeof...(CoordinatesTypes), "The number of coordinates must be equal to the number of dimensions of the vector space.");
		return detail::make_vector<detail::deduce_vector_t<MetricSpaceType::vector_space_dimensions, std::remove_reference_t<CoordinatesTypes>...> >::run(std::move(coords)...);
	}

}

#endif // __GA_CORE_VECTOR_HPP__
