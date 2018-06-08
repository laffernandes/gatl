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
				component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >
			> type;
		};

		template<class Coefficient, default_bitset_t PossibleGrades, class Bitset, default_integral_t GradeValue>
		struct keep_grade<component<Coefficient, dynamic_basis_blade<PossibleGrades, Bitset> >, component<constant_value<GradeValue>, constant_basis_blade<default_bitset_t(0)> > > {
			typedef std::conditional_t<
				0 <= GradeValue && GradeValue <= GA_MAX_BASIS_VECTOR_INDEX && (PossibleGrades & (default_bitset_t(1) << GradeValue)) != default_bitset_t(0),
				component_t<
					if_else_t<
						equal_t<count_one_bits_t<Bitset>, constant_value<GradeValue> >,
						Coefficient,
						constant_value<0>
					>,
					dynamic_basis_blade_t<(default_bitset_t(1) << GradeValue), Bitset>
				>,
				component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >
			> type;
		};

		template<class Coefficient, class BasisBlade, class Grade>
		struct keep_grade<component<Coefficient, BasisBlade>, component<Grade, constant_basis_blade<default_bitset_t(0)> > > {
			typedef component_t<
				if_else_t<
					equal_t<count_one_bits_t<basis_vectors_t<BasisBlade> >, Grade>,
					Coefficient,
					constant_value<0>
				>,
				BasisBlade
			> type;
		};

	}

	template<class CoefficientType, class Expression, class GradeType, default_integral_t K, class = std::enable_if_t<std::is_constructible_v<grade_t, GradeType> > >
	constexpr decltype(auto) take_grade(clifford_expression<CoefficientType, Expression> const &arg, constant<GradeType, K> const &k) {
		auto lazy = make_lazy_context(arg, k);
		return lazy.eval(clifford_expression<default_integral_t, detail::keep_grade_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1> > >());
	}

	template<class Type, class GradeType, default_integral_t K, class = std::enable_if_t<std::is_constructible_v<grade_t, GradeType> > >
	constexpr decltype(auto) take_grade(Type const &arg, constant<GradeType, K> const &k) {
		return take_grade(scalar(arg), k);
	}

	template<class CoefficientType, class Expression>
	constexpr decltype(auto) take_grade(clifford_expression<CoefficientType, Expression> const &arg, grade_t const k) {
		auto lazy = make_lazy_context(arg, scalar(k));
		return lazy.eval(clifford_expression<default_integral_t, detail::keep_grade_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1> > >());
	}

	template<class Type>
	constexpr decltype(auto) take_grade(Type const &arg, grade_t const k) {
		return take_grade(scalar(arg), k);
	}

}

#endif // __FUTURE_GA_TAKE_GRADE_HPP__
