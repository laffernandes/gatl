#ifndef __GA_DYNAMIC_BASIS_BLADE_HPP__
#define __GA_DYNAMIC_BASIS_BLADE_HPP__

namespace ga {

	namespace detail {

		template<default_bitset_t PossibleGrades>
		class dbasis_blade {
		public:

			typedef default_bitset_t value_type;

			constexpr dbasis_blade(value_type const &basis_blade) :
				basis_blade_(basis_blade) {
			}

			constexpr operator value_type() const {
				return basis_blade_;
			}

			constexpr static default_bitset_t possible_grades() {
				return PossibleGrades;
			}

			constexpr value_type value() const {
				return basis_blade_;
			}

		private:

			value_type const basis_blade_;
		};

	}

}

#endif // __GA_DYNAMIC_BASIS_BLADE_HPP__
