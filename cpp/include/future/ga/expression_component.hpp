#ifndef __FUTURE_GA_EXPRESSION_COMPONENT_HPP__
#define __FUTURE_GA_EXPRESSION_COMPONENT_HPP__

namespace ga {

	namespace detail {

		// Specializations of component<Coefficient, BasisBlade>.
		template<class Coefficient, class BasisBlade>
		struct component {
		private:

			constexpr static default_bitset_t possible_grades = possible_grades_v<BasisBlade>;

			typedef std::conditional_t<
				possible_grades == default_bitset_t(0),
				constant_value<0>, // impossible basis blade
				Coefficient
			> coefficient;
			
			typedef std::conditional_t<
				std::is_same_v<Coefficient, constant_value<0> > || possible_grades == default_bitset_t(0),
				constant_basis_blade<default_bitset_t(0)>,  // impossible basis blade or zero
				BasisBlade
			> basis_blade;

		public:
			
			typedef component<coefficient, basis_blade> type;
		};

	}

}

#endif // __FUTURE_GA_EXPRESSION_COMPONENT_HPP__
