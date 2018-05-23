#ifndef __FUTURE_GA_EXPRESSION_DYNAMIC_BASIS_BLADE_HPP__
#define __FUTURE_GA_EXPRESSION_DYNAMIC_BASIS_BLADE_HPP__

namespace ga {

	namespace detail {

		// Specializations of _dynamic_basis_blade<PossibleGrades, Bitset>.
		template<default_bitset_t PossibleGrades, class Bitset>
		struct _dynamic_basis_blade {
			typedef dynamic_basis_blade<PossibleGrades, Bitset> type; // default
		};

		template<class Bitset>
		struct _dynamic_basis_blade<default_bitset_t(1), Bitset> {
			typedef constant_basis_blade<default_bitset_t(0)> type; // scalar for sure
		};

		template<>
		struct _dynamic_basis_blade<default_bitset_t(1), constant_bitset<default_bitset_t(0)> > {
			typedef constant_basis_blade<default_bitset_t(0)> type; // scalar for sure
		};

		template<default_bitset_t PossibleGrades, default_bitset_t Bitset>
		struct _dynamic_basis_blade<PossibleGrades, constant_bitset<Bitset> > {
			typedef constant_basis_blade<Bitset> type; // it is not dynamic

			static_assert(PossibleGrades == possible_grades_v<type>, "The possible grades are inconsistent.");
		};

	}

}

#endif // __FUTURE_GA_EXPRESSION_DYNAMIC_BASIS_BLADE_HPP__
