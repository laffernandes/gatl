#ifndef __GA_CLIFFORD_SIGNED_METRIC_SPACE_HPP__
#define __GA_CLIFFORD_SIGNED_METRIC_SPACE_HPP__

namespace ga {
	
	namespace clifford {

		template<ndims_t P, ndims_t Q>
		class signed_metric_space : public orthogonal_metric_space<signed_metric_space<P, Q> > {
		public:

			typedef typename detail::metric_space_traits<signed_metric_space>::entry_type entry_type;

			template<default_bitset_t BasisBlade>
			struct cincludes_basis_blade : detail::space_traits<signed_metric_space>::template cincludes_basis_blade<BasisBlade> {
			};

			template<default_bitset_t PossibleGrades>
			struct cincludes_grades : detail::space_traits<signed_metric_space>::template cincludes_grades<PossibleGrades> {
			};

			template<index_t Row, index_t Col>
			struct cmetric_entry : detail::metric_space_traits<signed_metric_space>::template cmetric_entry<Row, Col> {
			};

			template<default_bitset_t BasisBlade>
			struct cmetric_factor : detail::metric_space_traits<signed_metric_space>::template cmetric_factor<BasisBlade> {
			};

			constexpr static decltype(auto) basis_vectors() {
				return detail::cbasis_blade<detail::space_traits<signed_metric_space>::basis_vectors>();
			}

			constexpr static ndims_t vector_space_dimension() {
				return P + Q;
			}

			constexpr static bool includes_basis_blade(default_bitset_t const arg) {
				return (arg & ~detail::space_traits<signed_metric_space>::basis_vectors) == 0;
			}

			constexpr static entry_type metric_entry(index_t const row, index_t const col) {
				assert(0 < row && row <= (P + Q) && 0 < col && col <= (P + Q));
				return static_cast<entry_type>(row == col ? (row <= P ? 1 : -1) : 0);
			}

			constexpr static entry_type metric_factor(default_bitset_t const arg) {
				assert(includes_basis_blade(arg));
				return static_cast<entry_type>((detail::ones(arg & detail::metric_space_traits<signed_metric_space>::negative) & 1) == 0 ? 1 : -1);
			}

			static_assert((P + Q) <= GA_MAX_BASIS_VECTOR_INDEX, "ga::clifford::signed_metric_space<P, Q> is ill-defined. It is expectated (P + Q) <= GA_MAX_BASIS_VECTOR_INDEX.");
		};

		template<ndims_t P>
		class signed_metric_space<P, 0> : public orthogonal_metric_space<signed_metric_space<P, 0> > {
		public:

			typedef typename detail::metric_space_traits<signed_metric_space>::entry_type entry_type;

			template<default_bitset_t BasisBlade>
			struct cincludes_basis_blade : detail::space_traits<signed_metric_space>::template cincludes_basis_blade<BasisBlade> {
			};

			template<default_bitset_t PossibleGrades>
			struct cincludes_grades : detail::space_traits<signed_metric_space>::template cincludes_grades<PossibleGrades> {
			};

			template<index_t Row, index_t Col>
			struct cmetric_entry : detail::metric_space_traits<signed_metric_space>::template cmetric_entry<Row, Col> {
			};

			template<default_bitset_t BasisBlade>
			struct cmetric_factor : detail::metric_space_traits<signed_metric_space>::template cmetric_factor<BasisBlade> {
			};

			constexpr static decltype(auto) basis_vectors() {
				return detail::cbasis_blade<detail::space_traits<signed_metric_space>::basis_vectors>();
			}

			constexpr static ndims_t vector_space_dimension() {
				return P;
			}

			constexpr static bool includes_basis_blade(default_bitset_t const arg) {
				return (arg & ~detail::space_traits<signed_metric_space>::basis_vectors) == 0;
			}

			constexpr static entry_type metric_entry(index_t const row, index_t const col) {
				assert(0 < row && row <= P && 0 < col && col <= P);
				return static_cast<entry_type>(row == col ? 1 : 0);
			}

			constexpr static constant<1> metric_factor(default_bitset_t const arg) {
				assert(includes_basis_blade(arg));
				return constant<1>();
			}

			static_assert(P <= GA_MAX_BASIS_VECTOR_INDEX, "ga::clifford::signed_metric_space<P, 0> is ill-defined. It is expectated 0 <= P <= GA_MAX_BASIS_VECTOR_INDEX.");
		};

		namespace detail {

			template<ndims_t P, ndims_t Q>
			struct space_traits<signed_metric_space<P, Q> > {

				constexpr static default_bitset_t basis_vectors = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (P + Q)));

				template<default_bitset_t BasisBlade>
				struct cincludes_basis_blade {
					constexpr static bool value = (BasisBlade & ~basis_vectors) == 0;
				};

				template<default_bitset_t PossibleGrades>
				struct cincludes_grades {
					constexpr static bool value = (PossibleGrades & ~(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (P + Q + 1)))) == 0;
				};

				constexpr static decltype(auto) call_basis_vectors(signed_metric_space<P, Q> const *space) {
					return space->basis_vectors();
				}

				constexpr static ndims_t call_vector_space_dimension(signed_metric_space<P, Q> const *space) {
					return space->vector_space_dimension();
				}

				constexpr static bool call_includes_basis_blade(signed_metric_space<P, Q> const *space, default_bitset_t const arg) {
					return space->includes_basis_blade(arg);
				}
			};

			template<ndims_t P, ndims_t Q>
			struct metric_space_traits<signed_metric_space<P, Q> > {
				typedef default_integral_t entry_type;

				constexpr static default_bitset_t positive = default_bitset_t(default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - P));
				constexpr static default_bitset_t negative = space_traits<signed_metric_space<P, Q> >::basis_vectors - positive;

				template<index_t Row, index_t Col>
				struct cmetric_entry {
					static_assert(0 < Row && Row <= (P + Q) && 0 < Col && Col <= (P + Q), "Basis vector index Row or Col is out of bounds. It is expected 0 < Row <= (P + Q) and 0 < Col <= (P + Q).");
					constexpr static auto value = constant<Row == Col ? (Row <= P ? 1 : -1) : 0>();
				};

				template<default_bitset_t BasisBlade>
				struct cmetric_factor {
					static_assert(space_traits<signed_metric_space<P, Q> >::template cincludes_basis_blade<BasisBlade>::value, "Basis vector index Row or Col is out of bounds. It is expected 0 < Row <= (P + Q) and 0 < Col <= (P + Q).");
					constexpr static auto value = constant<(_ones<BasisBlade & negative>::value & 1) == 0 ? 1 : -1>();
				};

				constexpr static decltype(auto) call_metric_entry(signed_metric_space<P, Q> const *metric_space, index_t const row, index_t const col) {
					return metric_space->metric_entry(row, col);
				}

				constexpr static decltype(auto) call_metric_factor(signed_metric_space<P, Q> const *metric_space, default_bitset_t const arg) {
					return metric_space->metric_factor(arg);
				}
			};

		}

	}

}

#endif // __GA_CLIFFORD_SIGNED_METRIC_SPACE_HPP__
