#ifndef __GA_CLIFFORD_RIGHT_CONTRACTION_HPP__
#define __GA_CLIFFORD_RIGHT_CONTRACTION_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			class rcont_func final {
			private:

				struct _iterate_end {
					constexpr static default_bitset_t value = default_bitset_t(0);
				};

				template<grade_t LeftGrade, default_bitset_t RightPossibleGrades, grade_t RightGrade>
				struct _iterate_right {
					constexpr static default_bitset_t value = _iterate_right<
						LeftGrade,
						(RightGrade < LeftGrade ? (RightPossibleGrades >> 1) : default_bitset_t(0)),
						RightGrade + 1
					>::value | ((RightPossibleGrades & default_bitset_t(1)) != default_bitset_t(0) ? (default_bitset_t(1) << (LeftGrade - RightGrade)) : default_bitset_t(0));
				};

				template<grade_t LeftGrade, grade_t RightGrade>
				struct _iterate_right<LeftGrade, 0, RightGrade> : _iterate_end {
				};

				template<default_bitset_t LeftPossibleGrades, grade_t LeftGrade, default_bitset_t RightPossibleGrades>
				struct _iterate_left {
					constexpr static default_bitset_t value = _iterate_left<(LeftPossibleGrades >> 1), LeftGrade + 1, RightPossibleGrades>::value | std::conditional<(LeftPossibleGrades & default_bitset_t(1)) != default_bitset_t(0), _iterate_right<LeftGrade, RightPossibleGrades, 0>, _iterate_end>::type::value;
				};

				template<grade_t LeftGrade, default_bitset_t RightPossibleGrades>
				struct _iterate_left<0, LeftGrade, RightPossibleGrades> : _iterate_end {
				};

			public:

				constexpr bool operator()(grade_t const lhs_grade, grade_t const rhs_grade, grade_t const result_grade) const {
					return (lhs_grade - rhs_grade) == result_grade;
				}

				template<grade_t LeftGrade, grade_t RightGrade, grade_t ResultGrade>
				struct eval {
					constexpr static bool value = (LeftGrade - RightGrade) == ResultGrade;
				};

				template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimension>
				struct possible_grades : _iterate_left<LeftPossibleGrades, 0, RightPossibleGrades> {
				};
			};

		}

		template<class LeftType, class RightType, class MetricSpaceType>
		constexpr decltype(auto) rcont(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &mtr) {
			return detail::try_cast_to_native(detail::graded_product(detail::begin(lhs), detail::begin(rhs), mtr, detail::rcont_func()));
		}

	}

}

#endif // __GA_CLIFFORD_RIGHT_CONTRACTION_HPP__
