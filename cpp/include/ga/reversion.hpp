#ifndef __GA_REVERSION_HPP__
#define __GA_REVERSION_HPP__

namespace ga {

	namespace detail {

		class reversion_func {
		private:

			template<class DefaultBitsetType>
			struct pattern;

			template<>
			struct pattern<std::uint32_t> {
				constexpr static std::uint32_t value = 0xCCCCCCCCu;
			};

			template<>
			struct pattern<std::uint64_t> {
				constexpr static std::uint64_t value = 0xCCCCCCCCCCCCCCCCull;
			};

		public:

			constexpr bool operator()(grade_t const arg_grade) const {
				return (pattern<default_bitset_t>::value & (default_bitset_t(1) << arg_grade)) != default_bitset_t(0);;
			}

			template<grade_t ArgGrade>
			struct eval {
				constexpr static bool value = (pattern<default_bitset_t>::value & (default_bitset_t(1) << ArgGrade)) != default_bitset_t(0);
			};

			template<default_bitset_t PossibleGrades>
			struct maybe_eval {
				constexpr static bool value = (pattern<default_bitset_t>::value & PossibleGrades) != default_bitset_t(0);
			};
		};

	}

	template<class Type>
	constexpr decltype(auto) reversion(Type const &arg) {
		return detail::graded_unary_minus(detail::begin(arg), detail::reversion_func());
	}

}

#endif // __GA_REVERSION_HPP__
