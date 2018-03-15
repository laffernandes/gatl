#ifndef __GA_BASIS_BLADE_GRADE_HPP__
#define __GA_BASIS_BLADE_GRADE_HPP__

namespace ga {

	namespace detail {

		template<class BitsetType, int digits>
		struct _ones;

		template<std::uint32_t Bitset>
		struct _ones32 {
		private:

			constexpr static auto a = (Bitset & 0x55555555u) + ((Bitset >> 1) & 0x55555555u);
			constexpr static auto b = (a & 0x33333333u) + ((a >> 2) & 0x33333333u);
			constexpr static auto c = (b + (b >> 4)) & 0x0F0F0F0Fu;

		public:

			constexpr static auto value = ((c * 0x01010101u) >> 24);
		};

		inline decltype(auto) ones(std::uint32_t const bitset) {
			const auto a = (bitset & 0x55555555u) + ((bitset >> 1) & 0x55555555u);
			const auto b = (a & 0x33333333u) + ((a >> 2) & 0x33333333u);
			const auto c = (b + (b >> 4)) & 0x0F0F0F0Fu;
			return ((c * 0x01010101u) >> 24);
		}

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
		struct _basis_blade_grade<cbasis_blade<BasisBlade> > : std::conditional<
			std::numeric_limits<default_bitset_t>::digits == 32,
			_ones32<BasisBlade>,
			typename std::conditional<std::numeric_limits<default_bitset_t>::digits == 64,
				_ones64<BasisBlade>,
				std::nullptr_t
			>::type
		>::type {};

		template<default_bitset_t BasisBlade>
		constexpr grade_t basis_blade_grade(cbasis_blade<BasisBlade> const &) {
			return _basis_blade_grade<cbasis_blade<BasisBlade> >::value;
		}

		template<default_bitset_t PossibleGrades>
		constexpr grade_t basis_blade_grade(dbasis_blade<PossibleGrades> const &arg) {
			return ones(arg.value());
		}

	}

}

#endif // __GA_BASIS_BLADE_GRADE_HPP__
