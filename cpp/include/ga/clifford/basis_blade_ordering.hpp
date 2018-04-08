#ifndef __GA_CLIFFORD_BASIS_BLADE_ORDERING_HPP__
#define __GA_CLIFFORD_BASIS_BLADE_ORDERING_HPP__

namespace ga {

	namespace common {

		namespace detail {

			template<default_bitset_t LeftBasisBlade, default_bitset_t RightBasisBlade>
			struct lt<clifford::detail::cbasis_blade<LeftBasisBlade>, clifford::detail::cbasis_blade<RightBasisBlade> > {
				constexpr static bool value = (clifford::detail::cbasis_blade<LeftBasisBlade>::possible_grades() < clifford::detail::cbasis_blade<RightBasisBlade>::possible_grades()) || (clifford::detail::cbasis_blade<LeftBasisBlade>::possible_grades() == clifford::detail::cbasis_blade<RightBasisBlade>::possible_grades() && LeftBasisBlade < RightBasisBlade);
			};

			template<default_bitset_t LeftBasisBlade, default_bitset_t RightPossibleGrades>
			struct lt<clifford::detail::cbasis_blade<LeftBasisBlade>, clifford::detail::dbasis_blade<RightPossibleGrades> > {
				constexpr static bool value = clifford::detail::cbasis_blade<LeftBasisBlade>::possible_grades() <= RightPossibleGrades;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightBasisBlade>
			struct lt<clifford::detail::dbasis_blade<LeftPossibleGrades>, clifford::detail::cbasis_blade<RightBasisBlade> > {
				constexpr static bool value = LeftPossibleGrades < clifford::detail::cbasis_blade<RightBasisBlade>::possible_grades();
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct lt<clifford::detail::dbasis_blade<LeftPossibleGrades>, clifford::detail::dbasis_blade<RightPossibleGrades> > {
				constexpr static bool value = LeftPossibleGrades < RightPossibleGrades;
			};

		}

	}

}

#endif // __GA_CLIFFORD_BASIS_BLADE_ORDERING_HPP__
