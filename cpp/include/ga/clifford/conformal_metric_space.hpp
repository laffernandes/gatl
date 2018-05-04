#ifndef __GA_CLIFFORD_CONFORMAL_METRIC_SPACE_HPP__
#define __GA_CLIFFORD_CONFORMAL_METRIC_SPACE_HPP__

namespace ga {

	namespace clifford {

		template<ndims_t N>
		class conformal_metric_space final : public general_metric_space<conformal_metric_space<N> > {
		public:

			typedef typename detail::metric_space_traits<conformal_metric_space>::entry_type entry_type;

			template<default_bitset_t BasisBlade>
			struct cincludes_basis_blade : detail::space_traits<conformal_metric_space>::template cincludes_basis_blade<BasisBlade> {
			};

			template<default_bitset_t PossibleGrades>
			struct cincludes_grades : detail::space_traits<conformal_metric_space>::template cincludes_grades<PossibleGrades> {
			};

			template<index_t Row, index_t Col>
			struct cmetric_entry : detail::metric_space_traits<conformal_metric_space>::template cmetric_entry<Row, Col> {
			};

			template<default_bitset_t BasisBlade>
			struct cmetric_factor : detail::metric_space_traits<conformal_metric_space>::template cmetric_factor<BasisBlade> {
			};

			constexpr static decltype(auto) basis_vectors() {
				return detail::cbasis_blade<detail::space_traits<conformal_metric_space>::basis_vectors>();
			}

			constexpr static ndims_t vector_space_dimension() {
				return N + 2;
			}

			constexpr static bool includes_basis_blade(default_bitset_t const arg) {
				return (arg & ~detail::space_traits<conformal_metric_space>::basis_vectors) == 0;
			}

			constexpr static entry_type metric_entry(index_t const row, index_t const col) {
				assert(0 < row && row <= (N + 2) && 0 < col && col <= (N + 2));
				return static_cast<entry_type>(row == col ? (row <= N ? 1 : 0) : (row <= N || col <= N ? 0 : -1));
			}

			constexpr static entry_type metric_factor(default_bitset_t const arg) {
				assert(includes_basis_blade(arg));
				return static_cast<entry_type>(1/*TODO Implementar*/);
			}

			static_assert((N + 2) <= GA_MAX_BASIS_VECTOR_INDEX, "ga::clifford::conformal_metric_space<N> is ill-defined. It is expectated N <= GA_MAX_BASIS_VECTOR_INDEX.");
		};

		namespace detail {

			template<ndims_t N>
			struct space_traits<conformal_metric_space<N> > {

				constexpr static default_bitset_t basis_vectors = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (N + 2)));

				template<default_bitset_t BasisBlade>
				struct cincludes_basis_blade {
					constexpr static bool value = (BasisBlade & ~basis_vectors) == 0;
				};

				template<default_bitset_t PossibleGrades>
				struct cincludes_grades {
					constexpr static bool value = (PossibleGrades & ~(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (N + 2 + 1)))) == 0;
				};

				constexpr static decltype(auto) call_basis_vectors(conformal_metric_space<N> const *space) {
					return space->basis_vectors();
				}

				constexpr static ndims_t call_vector_space_dimension(conformal_metric_space<N> const *space) {
					return space->vector_space_dimension();
				}

				constexpr static bool call_includes_basis_blade(conformal_metric_space<N> const *space, default_bitset_t const arg) {
					return space->includes_basis_blade(arg);
				}
			};

			template<ndims_t N>
			struct metric_space_traits<conformal_metric_space<N> > {
				typedef default_integral_t entry_type;

				template<index_t Row, index_t Col>
				struct cmetric_entry {
					static_assert(0 < Row && Row <= (N + 2) && 0 < Col && Col <= (N + 2), "Basis vector index Row or Col is out of bounds. It is expected 0 < Row <= (N + 2) and 0 < Col <= (N + 2).");
					constexpr static auto value = constant<Row == Col ? (Row <= N ? 1 : 0) : (Row <= N || Col <= N ? 0 : -1)>();
				};

				template<default_bitset_t BasisBlade>
				struct cmetric_factor {
					static_assert(space_traits<conformal_metric_space<N> >::template cincludes_basis_blade<BasisBlade>::value, "Basis vector index Row or Col is out of bounds. It is expected 0 < Row <= (N + 2) and 0 < Col <= (N + 2).");
					constexpr static auto value = constant<1/*TODO Implementar*/>();
				};

				constexpr static decltype(auto) call_metric_entry(conformal_metric_space<N> const *metric_space, index_t const row, index_t const col) {
					return metric_space->metric_entry(row, col);
				}

				constexpr static decltype(auto) call_metric_factor(conformal_metric_space<N> const *metric_space, default_bitset_t const arg) {
					return metric_space->metric_factor(arg);
				}
			};

		}

	}

}

#endif // __GA_CLIFFORD_CONFORMAL_METRIC_SPACE_HPP__
