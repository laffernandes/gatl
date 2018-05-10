#ifndef __GA_FUTURE_POSSIBLE_GRADES_HPP__
#define __GA_FUTURE_POSSIBLE_GRADES_HPP__

namespace future {

	namespace detail {

		// Specializations of possible_grades<Component>.
		template<class Coefficient, default_bitset_t BasisVectors>
		struct possible_grades<component<Coefficient, constant_basis_blade<BasisVectors> > > {
			constexpr static default_bitset_t value = default_bitset_t(1) << ones_v<BasisVectors>;
		};

		template<class Coefficient, default_bitset_t PossibleGrades, id_t... Ids>
		struct possible_grades<component<Coefficient, dynamic_basis_blade<PossibleGrades, Ids...> > > {
			constexpr static default_bitset_t value = PossibleGrades;
		};

		template<class Coefficient, default_bitset_t PossibleGrades, id_t... Ids>
		struct possible_grades<component<Coefficient, dynamic_basis_blades<PossibleGrades, Ids...> > > {
			constexpr static default_bitset_t value = PossibleGrades;
		};

	}

}

#endif // __GA_FUTURE_POSSIBLE_GRADES_HPP__
