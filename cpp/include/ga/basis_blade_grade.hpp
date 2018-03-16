#ifndef __GA_BASIS_BLADE_GRADE_HPP__
#define __GA_BASIS_BLADE_GRADE_HPP__

namespace ga {

	namespace detail {

		template<class BitsetType, int digits>
		struct _ones;

		template<std::uint64_t Bitset>
		struct _ones64 {
		private:

			constexpr static auto a = (Bitset & 0x5555555555555555ull) + ((Bitset >> 1) & 0x5555555555555555ull);
			constexpr static auto b = (a & 0x3333333333333333ull) + ((a >> 2) & 0x3333333333333333ull);
			constexpr static auto c = (b & 0x0F0F0F0F0F0F0F0Full) + ((b >> 4) & 0x0F0F0F0F0F0F0F0Full);

		public:

			constexpr static auto value = ((c * 0x0101010101010101ull) >> 56);
		};

		inline decltype(auto) ones(std::uint64_t const bitset) {
			const auto a = (bitset & 0x5555555555555555ull) + ((bitset >> 1) & 0x5555555555555555ull);
			const auto b = (a & 0x3333333333333333ull) + ((a >> 2) & 0x3333333333333333ull);
			const auto c = (b & 0x0F0F0F0F0F0F0F0Full) + ((b >> 4) & 0x0F0F0F0F0F0F0F0Full);
			return ((c * 0x0101010101010101ull) >> 56);
		}

		template <class Type>
		int ones(Type) = delete;

		template<class BitsetType>
		struct _basis_blade_grade;
		
		template<default_bitset_t BasisBlade>
		struct _basis_blade_grade<cbasis_blade<BasisBlade> > : _ones64<BasisBlade> {
			static_assert(std::numeric_limits<default_bitset_t>::digits <= 64, "The ga::default_bitset_t type must have 64 digits or less.");
		};

		template<default_bitset_t BasisBlade>
		constexpr grade_t basis_blade_grade(cbasis_blade<BasisBlade> const &) {
			return _basis_blade_grade<cbasis_blade<BasisBlade> >::value;
		}

		template<default_bitset_t PossibleGrades>
		constexpr grade_t basis_blade_grade(dbasis_blade<PossibleGrades> const &arg) {
			return static_cast<grade_t>(ones(arg.value()));
		}

		constexpr grade_t highest_possible_grade(default_bitset_t possible_grades) {
			return (possible_grades & (default_bitset_t(1) << (std::numeric_limits<default_bitset_t>::digits - 1))) ? (std::numeric_limits<default_bitset_t>::digits - 1) : highest_possible_grade((possible_grades << 1) | default_bitset_t(1)) - 1;
		}
		
	}

}

#endif // __GA_BASIS_BLADE_GRADE_HPP__
