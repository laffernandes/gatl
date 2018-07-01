#ifndef __GA_EXTRA_TAKE_GRADE_HPP__
#define __GA_EXTRA_TAKE_GRADE_HPP__

namespace ga {

	namespace detail {

		template<typename Expression, typename GradeExpression>
		struct keep_grade;

		template<typename Expression, typename GradeExpression>
		using keep_grade_t = typename keep_grade<Expression, GradeExpression>::type;

		template<typename Argument, typename... NextArguments, typename GradeExpression>
		struct keep_grade<add<Argument, NextArguments...>, GradeExpression> {
			typedef addition_t<
				keep_grade_t<Argument, GradeExpression>,
				keep_grade_t<add_t<NextArguments...>, GradeExpression>
			> type;
		};

		template<typename Coefficient, default_bitset_t BasisVectors, default_integral_t GradeValue>
		struct keep_grade<component<Coefficient, constant_basis_blade<BasisVectors> >, component<constant_value<GradeValue>, constant_basis_blade<default_bitset_t(0)> > > {
			typedef std::conditional_t<
				ones(BasisVectors) == GradeValue,
				component<Coefficient, constant_basis_blade<BasisVectors> >,
				component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >
			> type;
		};

		template<typename Coefficient, default_bitset_t PossibleGrades, typename Bitset, default_integral_t GradeValue>
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

		template<typename Coefficient, typename BasisBlade, typename Grade>
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

	template<typename CoefficientType, typename Expression, typename GradeType, default_integral_t K, typename = std::enable_if_t<std::is_constructible_v<grade_t, GradeType> > >
	constexpr decltype(auto) take_grade(clifford_expression<CoefficientType, Expression> const &arg, constant<GradeType, K> const &k) {
		auto lazy = make_lazy_context(arg, k);
		return lazy.eval(clifford_expression<default_integral_t, detail::keep_grade_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1> > >());
	}

	template<typename Type, typename GradeType, default_integral_t K, typename = std::enable_if_t<std::is_constructible_v<grade_t, GradeType> > >
	constexpr decltype(auto) take_grade(Type const &arg, constant<GradeType, K> const &k) {
		return take_grade(scalar(arg), k);
	}

	template<typename CoefficientType, typename Expression>
	constexpr decltype(auto) take_grade(clifford_expression<CoefficientType, Expression> const &arg, grade_t const k) {
		auto lazy = make_lazy_context(arg, scalar(k));
		return lazy.eval(clifford_expression<default_integral_t, detail::keep_grade_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1> > >());
	}

	template<typename Type>
	constexpr decltype(auto) take_grade(Type const &arg, grade_t const k) {
		return take_grade(scalar(arg), k);
	}

}

#endif // __GA_EXTRA_TAKE_GRADE_HPP__
