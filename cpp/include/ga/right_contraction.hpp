#ifndef __GA_RIGHT_CONTRACTION_HPP__
#define __GA_RIGHT_CONTRACTION_HPP__

namespace ga {

	namespace detail {

		class rcont_func {
		public:

			constexpr bool operator()(grade_t const lhs_grade, grade_t const rhs_grade, grade_t const result_grade) const {
				return (lhs_grade - rhs_grade) == result_grade;
			}

			template<grade_t LeftGrade, grade_t RightGrade, grade_t ResultGrade>
			struct eval {
				constexpr static bool value = (LeftGrade - RightGrade) == ResultGrade;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct maybe_eval {
				constexpr static bool value = true; //TODO Parei aqui!
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct possible_grades {
				constexpr static default_bitset_t value = ~default_bitset_t(0); //TODO Parei aqui!
			};
		};

	}

	template<class LeftType, class RightType, class MetricType>
	constexpr decltype(auto) rcont(LeftType const &lhs, RightType const &rhs, metric<MetricType> const &mtr) {
		return detail::graded_product(detail::begin(lhs), detail::begin(rhs), mtr, detail::rcont_func());
	}

}

#endif // __GA_RIGHT_CONTRACTION_HPP__
