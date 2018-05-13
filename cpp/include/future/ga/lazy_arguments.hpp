#ifndef __FUTURE_GA_LAZY_ARGUMENTS_HPP__
#define __FUTURE_GA_LAZY_ARGUMENTS_HPP__

namespace ga {

	namespace detail {
	
		// Returns the smallest ID found in the given expressions.
		template<class... Expressions>
		struct smallest_base_id;

		template<class... Expressions>
		constexpr id_t smallest_base_id_v = smallest_base_id<Expressions...>::value;

		template<class Expression, class... NextExpressions>
		struct smallest_base_id<Expression, NextExpressions...> {
			constexpr static id_t value = smallest(smallest_base_id_v<Expression>, smallest_base_id_v<NextExpressions...>); // recursion
		};

		template<>
		struct smallest_base_id<> {
			constexpr static id_t value = 0; // end of recursion
		};

		template<default_integral_t Value>
		struct smallest_base_id<constant<Value> > {
			constexpr static id_t value = 0;
		};

		template<class LazyCoefficient>
		struct smallest_base_id<value<LazyCoefficient> > {
			constexpr static id_t value = smallest_base_id_v<LazyCoefficient>;
		};

		template<name_t Name, class... Arguments>
		struct smallest_base_id<function<Name, Arguments...> > {
			constexpr static id_t value = smallest_base_id_v<Arguments...>;
		};

		template<class Coefficient, class BasisBlade>
		struct smallest_base_id<component<Coefficient, BasisBlade> > {
			constexpr static id_t value = smallest(smallest_base_id_v<Coefficient>, smallest_base_id_v<BasisBlade>);
		};

		template<default_bitset_t BasisVectors>
		struct smallest_base_id<constant_basis_blade<BasisVectors> > {
			constexpr static id_t value = 0;
		};

		template<default_bitset_t PossibleGrades, class LazyBasisVectors>
		struct smallest_base_id<dynamic_basis_blade<PossibleGrades, LazyBasisVectors> > {
			constexpr static id_t value = smallest_base_id_v<LazyBasisVectors>;
		};

		template<>
		struct smallest_base_id<stored> {
			constexpr static id_t value = 0;
		};

		template<default_bitset_t Bitset>
		struct smallest_base_id<lazy_constant_bitset<Bitset> > {
			constexpr static id_t value = 0;
		};

		template<id_t Id, std::size_t Index>
		struct smallest_base_id<lazy_get_coefficient<Id, Index> > {
			constexpr static id_t value = Id;
		};

		template<id_t Id, std::size_t Index>
		struct smallest_base_id<lazy_get_basis_vectors<Id, Index> > {
			constexpr static id_t value = Id;
		};

		// Produces an expression where value<stored> and dynamic_basis_blade<PossibleGrades, stored> changes to value<lazy_get_coefficient<Id, Index> > and dynamic_basis_blade<PossibleGrades, lazy_get_basis_vectors<Id, Index> >, respectively.
		template<class Expression, id_t Id, std::size_t BaseCoefficientIndex, std::size_t BaseBasisBladeIndex>
		struct tag_variables;

		template<class Expression, id_t Id, std::size_t BaseCoefficientIndex, std::size_t BaseBasisBladeIndex>
		using tag_variables_t = typename tag_variables<Expression, Id, BaseCoefficientIndex, BaseBasisBladeIndex>::type;

		template<class Expression, id_t Id, std::size_t BaseCoefficientIndex, std::size_t BaseBasisBladeIndex>
		struct tag_variables {
			typedef Expression type; // default
		};

		template<id_t Id, std::size_t BaseCoefficientIndex, std::size_t BaseBasisBladeIndex>
		struct tag_variables<value<stored>, Id, BaseCoefficientIndex, BaseBasisBladeIndex> {
			typedef value<lazy_get_coefficient<Id, BaseCoefficientIndex> > type;
		};

		template<default_bitset_t PossibleGrades, id_t Id, std::size_t BaseCoefficientIndex, std::size_t BaseBasisBladeIndex>
		struct tag_variables<dynamic_basis_blade<PossibleGrades, stored>, Id, BaseCoefficientIndex, BaseBasisBladeIndex> {
			typedef dynamic_basis_blade<PossibleGrades, lazy_get_basis_vectors<Id, BaseBasisBladeIndex> > type;
		};

		template<name_t Name, class... Arguments, id_t Id, std::size_t BaseCoefficientIndex, std::size_t BaseBasisBladeIndex>
		struct tag_variables<function<Name, Arguments...>, Id, BaseCoefficientIndex, BaseBasisBladeIndex> {
		private:

			constexpr static std::size_t stored_coefficients_count = count_stored_coefficients_v<Arguments...>;
			constexpr static std::size_t stored_basis_blades_count = count_stored_basis_blades_v<Arguments...>;

		public:

			typedef function<Name, tag_variables_t<Arguments, Id, BaseCoefficientIndex + (stored_coefficients_count - count_stored_coefficients_v<Arguments>), BaseBasisBladeIndex + (stored_basis_blades_count - count_stored_basis_blades<Arguments>)>...> type;
		};

		template<class Coefficient, class BasisBlade, id_t Id, std::size_t BaseCoefficientIndex, std::size_t BaseBasisBladeIndex>
		struct tag_variables<component<Coefficient, BasisBlade>, Id, BaseCoefficientIndex, BaseBasisBladeIndex> {
			typedef component<tag_variables_t<Coefficient, Id, BaseCoefficientIndex, 0>, tag_variables_t<BasisBlade, Id, 0, BaseBasisBladeIndex> > type;
		};

		// Produces an expression where value<Id, lazy_get_coefficient<Id, Index> > and dynamic_basis_blade<PossibleGrades, lazy_get_basis_vectors<Id, Index> > changes to, respectively, value<stored> and dynamic_basis_blade<PossibleGrades, stored> for a given Id.
		template<class Expression, id_t Id>
		struct untag_variables;

		template<class Expression, id_t Id>
		using untag_variables_t = typename untag_variables<Expression, Id>::type;

		template<class Expression, id_t Id>
		struct untag_variables {
			typedef Expression type; // default
		};

		template<id_t Id, std::size_t Index>
		struct untag_variables<value<lazy_get_coefficient<Id, Index> >, Id> {
			typedef value<stored> type;
		};

		template<default_bitset_t PossibleGrades, id_t Id, std::size_t Index>
		struct untag_variables<dynamic_basis_blade<PossibleGrades, lazy_get_basis_vectors<Id, Index> >, Id> {
			typedef dynamic_basis_blade<PossibleGrades, stored> type;
		};

		template<name_t Name, class... Arguments, id_t Id>
		struct untag_variables<function<Name, Arguments...>, Id> {
			typedef function<Name, untag_variables_t<Arguments, Id>...> type;
		};

		template<class Coefficient, class BasisBlade, id_t Id>
		struct untag_variables<component<Coefficient, BasisBlade>, Id> {
			typedef make_component_t<untag_variables_t<Coefficient, Id>, untag_variables_t<BasisBlade, Id> > type;
		};

		// Helper structure to define expressions for arguments.
		template<class FirstInputExpression, class... OtherInputExpressions>
		struct lazy_arguments {
		private:

			typedef smallest_base_id<FirstInputExpression, OtherInputExpressions...> base_id;

			template<std::size_t Index, class Expression, class... NextExpressions>
			struct argument_expression {
				typedef typename argument_expression<Index - 1, NextExpressions...>::type type;
			};

			template<class Expression, class... NextExpressions>
			struct argument_expression<0, Expression, NextExpressions...> {
				typedef tag_variables_t<Expression, base_id::value - id_t(sizeof...(NextExpressions) + 1), 0, 0> type;
			};

			template<class LazyExpression, class Expression, class... NextExpressions>
			struct result_expression {
				typedef untag_variables_t<typename result_expression<LazyExpression, NextExpressions...>::type, base_id::value - id_t(sizeof...(NextExpressions) + 1)> type;
			};

			template<class LazyExpression, class Expression>
			struct result_expression<LazyExpression, Expression> {
				typedef untag_variables_t<LazyExpression, base_id::value - 1> type;
			};

		public:

			template<std::size_t Index>
			using argument_expression_t = typename argument_expression<Index, FirstInputExpression, OtherInputExpressions...>::type;

			template<class LazyExpression>
			using result_expression_t = typename result_expression<LazyExpression, FirstInputExpression, OtherInputExpressions...>::type;
		};

	}

}

#endif // __FUTURE_GA_LAZY_ARGUMENTS_HPP__
