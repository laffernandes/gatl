#ifndef __GA_INVOLUTION_HPP__
#define __GA_INVOLUTION_HPP__

namespace ga {

	namespace detail {

		class involution_func {
		private:

			template<class DefaultBitsetType>
			struct pattern;

			template<>
			struct pattern<std::uint32_t> {
				constexpr static std::uint32_t value = 0xAAAAAAAAu;
			};

			template<>
			struct pattern<std::uint64_t> {
				constexpr static std::uint64_t value = 0xAAAAAAAAAAAAAAAAull;
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
	constexpr decltype(auto) involution(Type const &arg) {
		return detail::graded_unary_minus(detail::begin(arg), detail::involution_func());
	}

}

#endif // __GA_INVOLUTION_HPP__
