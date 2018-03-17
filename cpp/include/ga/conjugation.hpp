#ifndef __GA_CONJUGATION_HPP__
#define __GA_CONJUGATION_HPP__

namespace ga {

	namespace detail {

		class conjugation_func {
		private:

			constexpr static default_bitset_t pattern = (default_bitset_t)0x6666666666666666ull;

		public:

			constexpr bool operator()(grade_t const arg_grade) const {
				return (pattern & (default_bitset_t(1) << arg_grade)) != default_bitset_t(0);;
			}

			template<grade_t ArgGrade>
			struct eval {
				constexpr static bool value = (pattern & (default_bitset_t(1) << ArgGrade)) != default_bitset_t(0);
			};

			template<default_bitset_t PossibleGrades>
			struct maybe_eval {
				constexpr static bool value = (pattern & PossibleGrades) != default_bitset_t(0);
			};
		};

	}

	template<class Type>
	constexpr decltype(auto) conjugation(Type const &arg) {
		return detail::graded_unary_minus(detail::begin(arg), detail::conjugation_func());
	}

}

#endif // __GA_CONJUGATION_HPP__
