#ifndef __GA_INVOLUTION_HPP__
#define __GA_INVOLUTION_HPP__

namespace ga {

	namespace detail {

		class involution_func final {
		private:

			constexpr static default_bitset_t pattern = (default_bitset_t)0xAAAAAAAAAAAAAAAAull;

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
	constexpr decltype(auto) involution(Type const &arg) {
		return detail::graded_unary_minus(detail::begin(arg), detail::involution_func());
	}

}

#endif // __GA_INVOLUTION_HPP__
