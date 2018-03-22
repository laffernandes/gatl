#ifndef __GA_DYNAMIC_BASIS_BLADE_HPP__
#define __GA_DYNAMIC_BASIS_BLADE_HPP__

namespace ga {

	namespace detail {

		template<default_bitset_t PossibleGrades>
		class dbasis_blade {
		public:

			typedef default_bitset_t value_type;

			constexpr dbasis_blade() : 
				basis_blade_(0) {
			}

			constexpr dbasis_blade(dbasis_blade const &) = default;
			constexpr dbasis_blade(dbasis_blade &&) = default;

			constexpr dbasis_blade(value_type const &basis_blade) :
				basis_blade_(basis_blade) {
			}

			constexpr dbasis_blade& operator=(dbasis_blade const &) = default;
			constexpr dbasis_blade& operator=(dbasis_blade &&) = default;

			constexpr operator value_type() const {
				return basis_blade_;
			}

			constexpr static default_bitset_t possible_grades() {
				return PossibleGrades;
			}

			constexpr value_type value() const {
				return basis_blade_;
			}

			constexpr static bool compile_time_defined() {
				return false;
			}

		private:

			value_type basis_blade_;
		};

	}

}

#endif // __GA_DYNAMIC_BASIS_BLADE_HPP__
