#ifndef __FUTURE_GA_EXPRESSION_GRADED_UNARY_MINUS_HPP__
#define __FUTURE_GA_EXPRESSION_GRADED_UNARY_MINUS_HPP__

namespace ga {

	namespace detail {

		// Graded-based unary minus operation.
		template<class Expression, default_bitset_t SignChangePattern>
		struct graded_unary_minus;

		template<class Expression, default_bitset_t SignChangePattern>
		using graded_unary_minus_t = typename graded_unary_minus<Expression, SignChangePattern>::type;

		template<class Argument, class... NextArguments, default_bitset_t SignChangePattern>
		struct graded_unary_minus<add<Argument, NextArguments...>, SignChangePattern> {
			typedef addition_t<
				graded_unary_minus_t<Argument, SignChangePattern>,
				graded_unary_minus_t<add_t<NextArguments...>, SignChangePattern>
			> type;
		};

		template<class Coefficient, default_bitset_t BasisVectors, default_bitset_t SignChangePattern>
		struct graded_unary_minus<component<Coefficient, constant_basis_blade<BasisVectors> >, SignChangePattern> {
			typedef std::conditional_t<
				(SignChangePattern & (default_bitset_t(1) << ones(BasisVectors))) == default_bitset_t(0),
				component<Coefficient, constant_basis_blade<BasisVectors> >,
				component_t<product_t<constant_value<-1>, Coefficient, real_mapping>, constant_basis_blade<BasisVectors> >
			> type;
		};

		template<class Coefficient, default_bitset_t PossibleGrades, class Bitset, default_bitset_t SignChangePattern>
		struct graded_unary_minus<component<Coefficient, dynamic_basis_blade<PossibleGrades, Bitset> >, SignChangePattern> {
			typedef std::conditional_t<
				(PossibleGrades & SignChangePattern) == default_bitset_t(0),
				component<Coefficient, dynamic_basis_blade<PossibleGrades, Bitset> >,
				if_else_t<
					equal_t<bitwise_and_t<constant_bitset<SignChangePattern>, bitwise_left_shift_t<constant_bitset<default_bitset_t(1)>, count_one_bits_t<Bitset> > >, constant_bitset<default_bitset_t(0)> >,
					component<Coefficient, dynamic_basis_blade<PossibleGrades, Bitset> >,
					component_t<product_t<constant_value<-1>, Coefficient, real_mapping>, dynamic_basis_blade<PossibleGrades, Bitset> >
				>
			> type;
		};

	}

}

#endif // __FUTURE_GA_EXPRESSION_GRADED_UNARY_MINUS_HPP__
