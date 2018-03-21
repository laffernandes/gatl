#ifndef __GA_SPACE_HPP__
#define __GA_SPACE_HPP__

namespace ga {

	namespace detail {

		template<class SpaceType>
		struct space_traits;

	}

	template<class SpaceType>
	class space {
	public:

		template<default_bitset_t BasisBlade>
		struct cincludes_basis_blade : detail::space_traits<SpaceType>::template cincludes_basis_blade<BasisBlade> {
		};

		template<default_bitset_t PossibleGrades>
		struct cincludes_grades : detail::space_traits<SpaceType>::template cincludes_grades<PossibleGrades> {
		};

		constexpr decltype(auto) basis_vectors() const {
			return detail::space_traits<SpaceType>::call_basis_vectors(static_cast<SpaceType const*>(this));
		}

		constexpr static ndims_t vector_space_dimension() {
			return detail::space_traits<SpaceType>::call_vector_space_dimension(static_cast<SpaceType const*>(this));
		}

		constexpr bool includes_basis_blade(default_bitset_t const arg) const {
			return detail::space_traits<SpaceType>::call_includes_basis_blade(static_cast<SpaceType const*>(this), arg);
		}
	};

}

#endif // __GA_SPACE_HPP__
