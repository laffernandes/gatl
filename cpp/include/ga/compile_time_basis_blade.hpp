#ifndef __GA_COMPILE_TIME_BASIS_BLADE_HPP__
#define __GA_COMPILE_TIME_BASIS_BLADE_HPP__

namespace ga {

	namespace detail {

		template<default_bitset_t BasisBlade>
		class cbasis_blade {
		public:

			typedef default_bitset_t value_type;

			constexpr operator value_type() const {
				return BasisBlade;
			}

			constexpr static default_bitset_t possible_grades() {
				return default_bitset_t(1) << _basis_blade_grade<cbasis_blade>::value;
			}

			constexpr static value_type value() {
				return BasisBlade;
			}
		};

	}

}

#endif // __GA_COMPILE_TIME_BASIS_BLADE_HPP__
