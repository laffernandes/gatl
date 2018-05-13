#ifndef __FUTURE_GA_MAKE_COMPONENT_HPP__
#define __FUTURE_GA_MAKE_COMPONENT_HPP__

namespace ga {

	namespace detail {

		// Specializations of make_component<Coefficient, BasisBlade>.
		template<class Coefficient, class BasisBlade>
		struct make_component<Coefficient, BasisBlade, std::enable_if_t<possible_grades_v<BasisBlade> != default_bitset_t(0) && possible_grades_v<BasisBlade> != default_bitset_t(1)> > {
			typedef component<Coefficient, BasisBlade> type; // default (bind)
		};

		template<class Coefficient, class BasisBlade>
		struct make_component<Coefficient, BasisBlade, std::enable_if_t<possible_grades_v<BasisBlade> == default_bitset_t(0)> > {
			typedef constant<0> type; // A * 0 = 0 (simplify)
		};

		template<class Coefficient, class BasisBlade>
		struct make_component<Coefficient, BasisBlade, std::enable_if_t<possible_grades_v<BasisBlade> == default_bitset_t(1)> > {
			typedef Coefficient type; // A * 1 = A (simplify)
		};

		template<class BasisBlade>
		struct make_component<constant<0>, BasisBlade> {
			typedef constant<0> type; // 0 * Ei = 0 (simplify)
		};

	}

}

#endif // __FUTURE_GA_MAKE_COMPONENT_HPP__
