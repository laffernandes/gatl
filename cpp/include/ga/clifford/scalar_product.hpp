#ifndef __GA_CLIFFORD_SCALAR_PRODUCT_HPP__
#define __GA_CLIFFORD_SCALAR_PRODUCT_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			class scp_func final {
			public:

				constexpr bool operator()(grade_t const lhs_grade, grade_t const rhs_grade, grade_t const result_grade) const {
					return result_grade == 0;
				}

				template<grade_t LeftGrade, grade_t RightGrade, grade_t ResultGrade>
				struct eval {
					constexpr static bool value = ResultGrade == 0;
				};

				template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimension>
				struct possible_grades {
					constexpr static default_bitset_t value = (LeftPossibleGrades & RightPossibleGrades) != default_bitset_t(0) ? default_bitset_t(1) : default_bitset_t(0);
				};
			};

		}

		template<class LeftType, class RightType, class MetricSpaceType>
		constexpr decltype(auto) scp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &mtr) {
			return detail::graded_product(detail::begin(lhs), detail::begin(rhs), mtr, detail::scp_func());
		}

	}

}

#endif // __GA_CLIFFORD_SCALAR_PRODUCT_HPP__