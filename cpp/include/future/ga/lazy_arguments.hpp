#ifndef __FUTURE_GA_LAZY_ARGUMENTS_HPP__
#define __FUTURE_GA_LAZY_ARGUMENTS_HPP__

namespace ga {

	namespace detail {
	
		// Returns the greater ID found in the given expressions.
		template<class... Expressions>
		struct greater_id;

		template<class... Expressions>
		constexpr id_t greater_id_v = greater_id<Expressions...>::value;

		template<class Expression, class... NextExpressions>
		struct greater_id<Expression, NextExpressions...> {
			constexpr static id_t value = greater(greater_id_v<Expression>, greater_id_v<NextExpressions...>); // recursion
		};

		template<>
		struct greater_id<> {
			constexpr static id_t value = 0; // end of recursion
		};

		template<class Expression>
		struct greater_id<Expression> {
			constexpr static id_t value = 0; // default
		};

		template<id_t Id, std::size_t Index>
		struct greater_id<get_value<Id, Index> > {
			constexpr static id_t value = Id;
		};

		template<id_t Id, std::size_t Index>
		struct greater_id<get_bitset<Id, Index> > {
			constexpr static id_t value = Id;
		};

		template<default_bitset_t PossibleGrades, class LazyBitset>
		struct greater_id<dynamic_basis_blade<PossibleGrades, LazyBitset> > {
			constexpr static id_t value = greater_id_v<LazyBitset>;
		};

		template<class Coefficient, class BasisBlade>
		struct greater_id<component<Coefficient, BasisBlade> > {
			constexpr static id_t value = greater(greater_id_v<Coefficient>, greater_id_v<BasisBlade>);
		};

		template<name_t Name, class... Arguments>
		struct greater_id<function<Name, Arguments...> > {
			constexpr static id_t value = greater_id_v<Arguments...>;
		};

		// Produces an expression where stored_value and stored_bitset changes to get_value<Id, Index> and get_bitset<Id, Index>, respectively.
		template<class Expression, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex>
		struct tag_variables;

		template<class Expression, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex>
		using tag_variables_t = typename tag_variables<Expression, Id, BaseValueIndex, BaseBitsetIndex>::type;

		template<class Expression, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex>
		struct tag_variables {
			typedef Expression type; // default
		};

		template<id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex>
		struct tag_variables<stored_value, Id, BaseValueIndex, BaseBitsetIndex> {
			typedef get_value<Id, BaseValueIndex> type;
		};

		template<id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex>
		struct tag_variables<stored_bitset, Id, BaseValueIndex, BaseBitsetIndex> {
			typedef get_bitset<Id, BaseBitsetIndex> type;
		};

		template<default_bitset_t PossibleGrades, class LazyBitset, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex>
		struct tag_variables<dynamic_basis_blade<PossibleGrades, LazyBitset>, Id, BaseValueIndex, BaseBitsetIndex> {
			typedef dynamic_basis_blade<PossibleGrades, tag_variables_t<LazyBitset, Id, BaseValueIndex, BaseBitsetIndex> > type;
		};

		template<class Coefficient, class BasisBlade, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex>
		struct tag_variables<component<Coefficient, BasisBlade>, Id, BaseValueIndex, BaseBitsetIndex> {
			typedef component<tag_variables_t<Coefficient, Id, BaseValueIndex, BaseBitsetIndex>, tag_variables_t<BasisBlade, Id, BaseValueIndex + count_stored_values_v<Coefficient>, BaseBitsetIndex + count_stored_bitsets_v<Coefficient> > > type;
		};

		template<name_t Name, class... Arguments, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex>
		struct tag_variables<function<Name, Arguments...>, Id, BaseValueIndex, BaseBitsetIndex> {
		private:

			constexpr static std::size_t stored_values_count = count_stored_values_v<Arguments...>;
			constexpr static std::size_t stored_bitsets_count = count_stored_bitsets_v<Arguments...>;

		public:

			//TODO Isso não funcionará
			typedef function<Name, tag_variables_t<Arguments, Id, BaseValueIndex + (stored_values_count - count_stored_values_v<Arguments>), BaseBitsetIndex + (stored_bitsets_count - count_stored_bitsets<Arguments>)>...> type;
		};

		// Produces an expression where get_value<Id, Index> and get_bitset<Id, Index> changes to, respectively, stored_value and stored for a given Id.
		template<class Expression, id_t Id>
		struct untag_variables;

		template<class Expression, id_t Id>
		using untag_variables_t = typename untag_variables<Expression, Id>::type;

		template<class Expression, id_t Id>
		struct untag_variables {
			typedef Expression type; // default
		};

		template<id_t Id, std::size_t Index>
		struct untag_variables<get_value<Id, Index>, Id> {
			typedef stored_value type;
		};

		template<id_t Id, std::size_t Index>
		struct untag_variables<get_bitset<Id, Index>, Id> {
			typedef stored_bitset type;
		};

		template<default_bitset_t PossibleGrades, class LazyBitset, id_t Id>
		struct untag_variables<dynamic_basis_blade<PossibleGrades, LazyBitset>, Id> {
			typedef dynamic_basis_blade<PossibleGrades, untag_variables_t<LazyBitset, Id> > type;
		};

		template<class Coefficient, class BasisBlade, id_t Id>
		struct untag_variables<component<Coefficient, BasisBlade>, Id> {
			typedef component_t<untag_variables_t<Coefficient, Id>, untag_variables_t<BasisBlade, Id> > type;
		};

		template<name_t Name, class... Arguments, id_t Id>
		struct untag_variables<function<Name, Arguments...>, Id> {
			typedef function<Name, untag_variables_t<Arguments, Id>...> type;
		};

		// Helper structure to define expressions for arguments.
		template<class FirstInputExpression, class... OtherInputExpressions>
		struct lazy_arguments {
		private:

			typedef greater_id<FirstInputExpression, OtherInputExpressions...> base_id;

			template<std::size_t Index, class Expression, class... NextExpressions>
			struct argument_expression {
				typedef typename argument_expression<Index - 1, NextExpressions...>::type type;
			};

			template<class Expression, class... NextExpressions>
			struct argument_expression<0, Expression, NextExpressions...> {
				typedef tag_variables_t<Expression, base_id::value + id_t(sizeof...(OtherInputExpressions) - sizeof...(NextExpressions) + 1), 0, 0> type;
			};

			template<class LazyExpression, class Expression, class... NextExpressions>
			struct result_expression {
				typedef untag_variables_t<typename result_expression<LazyExpression, NextExpressions...>::type, base_id::value + id_t(sizeof...(OtherInputExpressions) - sizeof...(NextExpressions) + 1)> type;
			};

			template<class LazyExpression, class Expression>
			struct result_expression<LazyExpression, Expression> {
				typedef untag_variables_t<LazyExpression, base_id::value + 1> type;
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
