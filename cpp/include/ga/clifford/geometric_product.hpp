#ifndef __GA_CLIFFORD_GEOMETRIC_PRODUCT_HPP__
#define __GA_CLIFFORD_GEOMETRIC_PRODUCT_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			class gp_func final {
			private:

				struct _iterate_end {
					constexpr static default_bitset_t value = default_bitset_t(0);
				};

				template<grade_t LeftGrade, default_bitset_t RightPossibleGrades, grade_t RightGrade>
				struct _iterate_right {
				private:

					constexpr static default_bitset_t pattern = (default_bitset_t)0x5555555555555555ull;

					constexpr static grade_t min_grade = LeftGrade <= RightGrade ? (RightGrade - LeftGrade) : (LeftGrade - RightGrade);
					constexpr static grade_t max_grade = (LeftGrade + RightGrade) < std::numeric_limits<default_bitset_t>::digits ? (LeftGrade + RightGrade) : (std::numeric_limits<default_bitset_t>::digits - 1);

				public:

					constexpr static default_bitset_t value = _iterate_right<
							LeftGrade,
							(RightPossibleGrades >> 1),
							RightGrade + 1
						>::value | ((RightPossibleGrades & default_bitset_t(1)) != default_bitset_t(0) ? ((((default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - max_grade - 1)) >> min_grade) & pattern) << min_grade) : default_bitset_t(0));
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
					return true;
				}

				template<grade_t LeftGrade, grade_t RightGrade, grade_t ResultGrade>
				struct eval {
					constexpr static bool value = true;
				};

				template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimension>
				struct possible_grades {
					constexpr static default_bitset_t value = _iterate_left<LeftPossibleGrades, 0, RightPossibleGrades>::value & (default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (VectorSpaceDimension + 1)));
				};
			};

		}

		template<class LeftType, class RightType, class MetricSpaceType>
		constexpr decltype(auto) gp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &mtr) {
			return detail::graded_product(detail::begin(lhs), detail::begin(rhs), mtr, detail::gp_func());
		}

		using lazy::operator*;

		template<class LeftExpressionType, class RightExpressionType, typename std::enable_if<detail::may_cast_to_native<LeftExpressionType>::value || detail::may_cast_to_native<RightExpressionType>::value, int>::type = 0>
		constexpr decltype(auto) operator*(clifford_expression<LeftExpressionType> const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return gp(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator*(clifford_expression<LeftExpressionType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return gp(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

		template<class LeftExpressionType, class RightExpressionType>
		constexpr decltype(auto) operator*(lazy_expression<LeftExpressionType> const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return gp(lhs, rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

		template<class LeftExpressionType, class RightType, typename std::enable_if<!(is_lazy_expression<RightType>::value || is_clifford_expression<RightType>::value), int>::type = 0>
		constexpr decltype(auto) operator*(clifford_expression<LeftExpressionType> const &lhs, RightType const &rhs) {
			return gp(lhs, value<RightType>(rhs), euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}
		
		template<class LeftType, class RightExpressionType, typename std::enable_if<!(is_lazy_expression<LeftType>::value || is_clifford_expression<LeftType>::value), int>::type = 0>
		constexpr decltype(auto) operator*(LeftType const &lhs, clifford_expression<RightExpressionType> const &rhs) {
			return gp(value<LeftType>(lhs), rhs, euclidean_metric_space<GA_MAX_BASIS_VECTOR_INDEX>());
		}

	}

}

#endif // __GA_CLIFFORD_GEOMETRIC_PRODUCT_HPP__
