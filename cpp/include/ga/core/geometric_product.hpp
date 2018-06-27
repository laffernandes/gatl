#ifndef __GA_CORE_GEOMETRIC_PRODUCT_HPP__
#define __GA_CORE_GEOMETRIC_PRODUCT_HPP__

namespace ga {

	namespace detail {

		//TODO É possível melhorar?

		struct gp_mapping {
		private:

			template<grade_t LeftGrade, grade_t RightGrade>
			struct resulting_bitset {
			private:

				constexpr static default_bitset_t pattern = (default_bitset_t)0x5555555555555555ull;

				constexpr static grade_t min_grade = LeftGrade <= RightGrade ? (RightGrade - LeftGrade) : (LeftGrade - RightGrade);
				constexpr static grade_t max_grade = (LeftGrade + RightGrade) < std::numeric_limits<default_bitset_t>::digits ? (LeftGrade + RightGrade) : (std::numeric_limits<default_bitset_t>::digits - 1);

			public:

				constexpr static default_bitset_t value = (((default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - max_grade - 1)) >> min_grade) & pattern) << min_grade;
			};

			template<grade_t LeftGrade, default_bitset_t RightPossibleGrades>
			struct iterate_right {
			private:

				constexpr static default_bitset_t right_grade_bitset = rightmost_set_bit(RightPossibleGrades);

			public:

				constexpr static default_bitset_t value = iterate_right<LeftGrade, RightPossibleGrades ^ right_grade_bitset>::value | resulting_bitset<LeftGrade, set_bit_index(right_grade_bitset)>::value;
			};

			template<grade_t LeftGrade>
			struct iterate_right<LeftGrade, default_bitset_t(0)> {
				constexpr static default_bitset_t value = default_bitset_t(0);
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct iterate_left {
			private:

				constexpr static default_bitset_t left_grade_bitset = rightmost_set_bit(LeftPossibleGrades);

			public:

				constexpr static default_bitset_t value = iterate_left<LeftPossibleGrades ^ left_grade_bitset, RightPossibleGrades>::value | iterate_right<set_bit_index(left_grade_bitset), RightPossibleGrades>::value;
			};

			template<default_bitset_t RightPossibleGrades>
			struct iterate_left<default_bitset_t(0), RightPossibleGrades> {
				constexpr static default_bitset_t value = default_bitset_t(0);
			};

		public:

			template<class LeftGrade, class RightGrade, class ResultGrade>
			struct are_valid_grades {
				typedef std::true_type type;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimensions>
			struct possible_grades_result {
				constexpr static default_bitset_t value = iterate_left<LeftPossibleGrades, RightPossibleGrades>::value & (default_bitset_t(~0) >> (std::numeric_limits<default_bitset_t>::digits - (VectorSpaceDimensions + 1)));
			};
		};

	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class MetricSpaceType>
	constexpr decltype(auto) gp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
		auto lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(clifford_expression<default_integral_t, detail::product_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1>, detail::metric_space_mapping_t<MetricSpaceType, detail::gp_mapping> > >());
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) gp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return gp(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) gp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return gp(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) gp(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return gp(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) gp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return gp(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) gp(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return gp(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) gp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) {
		return gp(scalar(lhs), rhs, detail::real_metric_space());
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) gp(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return gp(scalar(lhs), rhs, detail::real_metric_space());
	}

	template<class LeftType, class RightType, class MetricSpaceType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) gp(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return gp(scalar(lhs), scalar(rhs), detail::real_metric_space());
	}

	template<class LeftType, class RightType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) gp(LeftType const &lhs, RightType const &rhs) {
		return gp(scalar(lhs), scalar(rhs), detail::real_metric_space());
	}

}

#endif // __GA_CORE_GEOMETRIC_PRODUCT_HPP__
