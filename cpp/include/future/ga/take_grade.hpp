#ifndef __FUTURE_GA_TAKE_GRADE_HPP__
#define __FUTURE_GA_TAKE_GRADE_HPP__

namespace ga {

	namespace detail {

		template<class Expression, class GradeExpression>
		struct keep_grade;

		template<class Expression, class GradeExpression>
		using keep_grade_t = typename keep_grade<Expression, GradeExpression>::type;

		template<class Argument, class... NextArguments, class GradeExpression>
		struct keep_grade<add<Argument, NextArguments...>, GradeExpression> {
			typedef addition_t<
				keep_grade_t<Argument, GradeExpression>,
				keep_grade_t<add_t<NextArguments...>, GradeExpression>
			> type;
		};

		template<class Coefficient, default_bitset_t BasisVectors, default_integral_t GradeValue>
		struct keep_grade<component<Coefficient, constant_basis_blade<BasisVectors> >, component<constant_value<GradeValue>, constant_basis_blade<default_bitset_t(0)> > > {
			typedef std::conditional_t<
				ones(BasisVectors) == GradeValue,
				component<Coefficient, constant_basis_blade<BasisVectors> >,
				component_t<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >
			> type;
		};

		template<class Coefficient, default_bitset_t PossibleGrades, class Bitset, default_integral_t GradeValue>
		struct keep_grade<component<Coefficient, dynamic_basis_blade<PossibleGrades, Bitset> >, component<constant_value<GradeValue>, constant_basis_blade<default_bitset_t(0)> > > {
			typedef std::conditional_t<
				0 <= GradeValue && GradeValue <= GA_MAX_BASIS_VECTOR_INDEX && (PossibleGrades & (default_bitset_t(1) << GradeValue)) != default_bitset_t(0),
				if_else_t<
					equal_t<count_one_bits_t<Bitset>, constant_value<GradeValue> >,
					component<Coefficient, dynamic_basis_blade<(default_bitset_t(1) << GradeValue), Bitset> >,
					component_t<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >
				>,
				component_t<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >
			> type;
		};

		template<class Coefficient, class BasisBlade, class Grade>
		struct keep_grade<component<Coefficient, BasisBlade>, component<Grade, constant_basis_blade<default_bitset_t(0)> > > {
			typedef if_else_t<
				equal_t<count_one_bits_t<basis_vectors_t<BasisBlade> >, Grade>,
				component<Coefficient, BasisBlade>,
				component_t<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >
			> type;
		};

	}

	template<class CoefficientType, class Expression, grade_t K>
	constexpr decltype(auto) take_grade(clifford_expression<CoefficientType, Expression> const &arg, constant<K> const &k) {
		typedef detail::lazy_arguments<Expression, typename constant<K>::expression_type> lazy;
		return detail::eval<detail::keep_grade_t<lazy::argument_expression_t<0>, lazy::argument_expression_t<1> > >(arg, k);
	}

	template<class Type, grade_t K>
	constexpr decltype(auto) take_grade(Type const &arg, constant<K> const &k) {
		return take_grade(scalar(arg), k);
	}

	template<class CoefficientType, class Expression>
	constexpr decltype(auto) take_grade(clifford_expression<CoefficientType, Expression> const &arg, grade_t const k) {
		typedef detail::lazy_arguments<Expression, typename decltype(scalar(grade_t()))::expression_type> lazy;
		return detail::eval<detail::keep_grade_t<lazy::argument_expression_t<0>, lazy::argument_expression_t<1> > >(arg, scalar(k));
	}

	template<class Type>
	constexpr decltype(auto) take_grade(Type const &arg, grade_t const k) {
		return take_grade(scalar(arg), k);
	}

}

#endif // __FUTURE_GA_TAKE_GRADE_HPP__