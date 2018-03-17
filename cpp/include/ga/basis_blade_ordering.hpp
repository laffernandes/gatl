/**
#ifndef __GA_BASIS_BLADE_ORDERING_HPP__
#define __GA_BASIS_BLADE_ORDERING_HPP__

namespace ga {

	namespace detail {

		template<default_bitset_t LeftBasisBlade, default_bitset_t RightBasisBlade>
		struct lt<cbasis_blade<LeftBasisBlade>, cbasis_blade<RightBasisBlade> > {
			constexpr static bool value = LeftBasisBlade < RightBasisBlade;
		};

		template<default_bitset_t LeftBasisBlade, default_bitset_t RightPossibleGrades>
		struct lt<cbasis_blade<LeftBasisBlade>, dbasis_blade<RightPossibleGrades> > {
			constexpr static bool value = true;
		};

		template<default_bitset_t LeftPossibleGrades, default_bitset_t RightBasisBlade>
		struct lt<dbasis_blade<LeftPossibleGrades>, cbasis_blade<RightBasisBlade> > {
			constexpr static bool value = false;
		};

		template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
		struct lt<dbasis_blade<LeftPossibleGrades>, dbasis_blade<RightPossibleGrades> > {
			constexpr static bool value = LeftPossibleGrades < RightPossibleGrades;
		};

	}

}

#endif // __GA_BASIS_BLADE_ORDERING_HPP__
/*/
#ifndef __GA_BASIS_BLADE_ORDERING_HPP__
#define __GA_BASIS_BLADE_ORDERING_HPP__

namespace ga {

	namespace detail {

		template<default_bitset_t LeftBasisBlade, default_bitset_t RightBasisBlade>
		struct lt<cbasis_blade<LeftBasisBlade>, cbasis_blade<RightBasisBlade> > {
			constexpr static bool value = (cbasis_blade<LeftBasisBlade>::possible_grades() < cbasis_blade<RightBasisBlade>::possible_grades()) || (cbasis_blade<LeftBasisBlade>::possible_grades() == cbasis_blade<RightBasisBlade>::possible_grades() && LeftBasisBlade < RightBasisBlade);
		};

		template<default_bitset_t LeftBasisBlade, default_bitset_t RightPossibleGrades>
		struct lt<cbasis_blade<LeftBasisBlade>, dbasis_blade<RightPossibleGrades> > {
			constexpr static bool value = cbasis_blade<LeftBasisBlade>::possible_grades() <= RightPossibleGrades;
		};

		template<default_bitset_t LeftPossibleGrades, default_bitset_t RightBasisBlade>
		struct lt<dbasis_blade<LeftPossibleGrades>, cbasis_blade<RightBasisBlade> > {
			constexpr static bool value = LeftPossibleGrades < cbasis_blade<RightBasisBlade>::possible_grades();
		};

		template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
		struct lt<dbasis_blade<LeftPossibleGrades>, dbasis_blade<RightPossibleGrades> > {
			constexpr static bool value = LeftPossibleGrades < RightPossibleGrades;
		};

	}

}

#endif // __GA_BASIS_BLADE_ORDERING_HPP__
/**/