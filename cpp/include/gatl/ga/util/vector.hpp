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

#ifndef __GA_UTIL_VECTOR_HPP__
#define __GA_UTIL_VECTOR_HPP__

namespace ga {

    namespace detail {

        // Deduces the ga::clifford_expression<CoefficientType, Expression> type of the vector having the given set of coordinates.
        template<ndims_t N, typename... Types>
        struct deduce_vector;

        template<ndims_t N, typename... Types>
        using deduce_vector_t = typename deduce_vector<N, Types...>::type;

        template<ndims_t N, typename CoordinateType, typename... NextCoordinateTypes>
        struct deduce_vector<N, CoordinateType, NextCoordinateTypes...> {
        private:

            using tail = deduce_vector_t<N, NextCoordinateTypes...>;

        public:

            using type = clifford_expression<std::common_type_t<CoordinateType, typename tail::coefficient_type>, addition_t<component_t<stored_value, constant_basis_blade<(bitset_t(1) << (N - (sizeof...(NextCoordinateTypes) + 1)))> >, typename tail::expression_type> >;
        };

        template<ndims_t N, typename CoordinateType>
        struct deduce_vector<N, CoordinateType> {
            using type = clifford_expression<CoordinateType, component_t<stored_value, constant_basis_blade<(bitset_t(1) << (N - 1))> > >;
        };

        template<ndims_t N, typename CoefficientType, typename Coefficient, typename... NextCoordinateTypes>
        struct deduce_vector<N, scalar_clifford_expression<CoefficientType, Coefficient>, NextCoordinateTypes...> {
        private:

            using tail = deduce_vector_t<N, NextCoordinateTypes...>;

        public:

            using type = clifford_expression<std::common_type_t<CoefficientType, typename tail::coefficient_type>, addition_t<component_t<Coefficient, constant_basis_blade<(bitset_t(1) << (N - (sizeof...(NextCoordinateTypes) + 1)))> >, typename tail::expression_type> >;
        };

        template<ndims_t N, typename CoefficientType, typename Coefficient>
        struct deduce_vector<N, scalar_clifford_expression<CoefficientType, Coefficient> > {
            using type = clifford_expression<CoefficientType, component_t<Coefficient, constant_basis_blade<(bitset_t(1) << (N - 1))> > >;
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
            template<typename... Types>
            GA_ALWAYS_INLINE constexpr static decltype(auto) run(Types &&... coords) GA_NOEXCEPT {
                return make_sequential_storage(std::move(coords)...);
            }
        };

        struct make_vector_sequential_storage_not_simple {
        private:

            template<typename ValueType, std::size_t Size, std::size_t... Indices>
            GA_ALWAYS_INLINE constexpr static decltype(auto) to_values_tuple(sequential_storage<ValueType, Size> &&values, std::index_sequence<Indices...> const) GA_NOEXCEPT {
                return std::tie(std::get<Indices>(std::move(values))...);
            }

            template<typename ValueType, std::size_t Size>
            GA_ALWAYS_INLINE constexpr static decltype(auto) to_values_tuple(sequential_storage<ValueType, Size> &&values) GA_NOEXCEPT {
                return to_values_tuple(std::move(values), std::make_index_sequence<Size>{});
            }

            template<typename ValueType>
            GA_ALWAYS_INLINE constexpr static decltype(auto) to_values_tuple(sequential_storage<ValueType, 0> &&) GA_NOEXCEPT {
                return std::make_tuple();
            }

            GA_ALWAYS_INLINE constexpr static decltype(auto) make_values_tuple() GA_NOEXCEPT {
                return std::make_tuple();
            }

            template<typename CoordinateType, typename... NextTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) make_values_tuple(CoordinateType &&coord, NextTypes &&... next_coords) GA_NOEXCEPT {
                return std::tuple_cat(std::make_tuple(std::move(coord)), make_values_tuple(std::move(next_coords)...));
            }

            template<typename CoefficientType, typename Coefficient, typename... NextTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) make_values_tuple(scalar_clifford_expression<CoefficientType, Coefficient> const &&coord, NextTypes &&... next_coords) GA_NOEXCEPT {
                return std::tuple_cat(to_values_tuple(coord.values()), make_values_tuple(std::move(next_coords)...));
            }

            template<typename... ValueTypes, std::size_t... Indices>
            GA_ALWAYS_INLINE constexpr static decltype(auto) to_sequential_storage(std::tuple<ValueTypes...> &&tuple, std::index_sequence<Indices...> const) GA_NOEXCEPT {
                return make_sequential_storage(std::get<Indices>(std::move(tuple))...);
            }

            template<typename... ValueTypes>
            GA_ALWAYS_INLINE constexpr static decltype(auto) to_sequential_storage(std::tuple<ValueTypes...> &&tuple) GA_NOEXCEPT {
                return to_sequential_storage(std::move(tuple), std::make_index_sequence<std::tuple_size_v<std::remove_cv_t<std::remove_reference_t<std::tuple<ValueTypes...> > > > >{});
            }

        public:

            template<typename... Types>
            GA_ALWAYS_INLINE constexpr static decltype(auto) run(Types &&... coords) GA_NOEXCEPT {
                return to_sequential_storage(make_values_tuple(std::move(coords)...));
            }
        };

        // Helper structure to build a ga::clifford_expression<CoefficientType, Expression> representing a vector.
        template<typename CliffordExpression, typename Enabled = void>
        struct make_vector {
            template<typename... Types>
            GA_ALWAYS_INLINE constexpr static CliffordExpression run(Types &&... coords) GA_NOEXCEPT {
                return CliffordExpression(std::conditional_t<std::disjunction_v<std::bool_constant<is_clifford_expression_v<std::remove_cv_t<std::remove_reference_t<Types> > > >...>, detail::make_vector_sequential_storage_not_simple, detail::make_vector_sequential_storage_simple>::run(std::move(coords)...));
            }
        };

        template<typename CliffordExpression>
        struct make_vector<CliffordExpression, std::enable_if_t<count_stored_values_v<typename CliffordExpression::expression_type> == 0> > {
            template<typename... Types>
            GA_ALWAYS_INLINE constexpr static CliffordExpression run(Types &&...) GA_NOEXCEPT {
                return CliffordExpression();
            }
        };

    }

    // Makes a vector with the given set of coordinates.
    template<typename MetricSpaceType, typename... Types, std::enable_if_t<std::disjunction_v<std::bool_constant<!detail::is_iterator_v<Types> >...>, int> = 0>
    constexpr decltype(auto) vector(metric_space<MetricSpaceType> const &, Types &&... coords) GA_NOEXCEPT {
        static_assert(MetricSpaceType::vector_space_dimensions == sizeof...(Types), "The number of coordinates must be equal to the number of dimensions of the vector space.");
        return detail::make_vector<detail::deduce_vector_t<MetricSpaceType::vector_space_dimensions, std::remove_cv_t<std::remove_reference_t<Types> >...> >::run(std::move(coords)...);
    }

    namespace detail {

        // Helper function to adapt one vector() function to another.
        template<typename MetricSpaceType, typename IteratorType, std::size_t... Indices, typename... ExtraTypes>
        GA_ALWAYS_INLINE constexpr decltype(auto) make_vector_using_iterator(metric_space<MetricSpaceType> const &mtr, IteratorType begin, std::index_sequence<Indices...>, ExtraTypes &&... extra_coords) GA_NOEXCEPT {
            return vector(mtr, *(begin + Indices)..., std::move(extra_coords)...);
        };

    }

    // Makes a vector using the given iterator to provide the set of coordinates.
    template<typename MetricSpaceType, typename IteratorType, std::enable_if_t<detail::is_iterator_v<IteratorType>, int> = 0>
    constexpr decltype(auto) vector(metric_space<MetricSpaceType> const &mtr, IteratorType begin, IteratorType end) GA_NOEXCEPT {
        assert(MetricSpaceType::vector_space_dimensions == std::distance(begin, end));
        return detail::make_vector_using_iterator(mtr, begin, std::make_index_sequence<MetricSpaceType::vector_space_dimensions>{});
    }

}

#endif // __GA_UTIL_VECTOR_HPP__
