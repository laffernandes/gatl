#ifndef __FUTURE_GA_LAZY_CONTEXT_HPP__
#define __FUTURE_GA_LAZY_CONTEXT_HPP__

namespace ga {

	//TODO Como lidar com a avaliação parcial da lazy expression?

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
		struct greater_id<get_map_values<Id, Index> > {
			constexpr static id_t value = Id;
		};

		template<id_t Id, std::size_t Index>
		struct greater_id<get_bitset<Id, Index> > {
			constexpr static id_t value = Id;
		};

		template<id_t Id, std::size_t Index>
		struct greater_id<get_map_bitsets<Id, Index> > {
			constexpr static id_t value = Id;
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct greater_id<dynamic_basis_blade<PossibleGrades, Bitset> > {
			constexpr static id_t value = greater_id_v<Bitset>;
		};

		template<class Coefficient, class BasisBlade>
		struct greater_id<component<Coefficient, BasisBlade> > {
			constexpr static id_t value = greater(greater_id_v<Coefficient>, greater_id_v<BasisBlade>);
		};

		template<name_t Name, class... Arguments>
		struct greater_id<function<Name, Arguments...> > {
			constexpr static id_t value = greater_id_v<Arguments...>;
		};

		// Produces an expression where stored_value, stored_bitset, and stored_components_map<PossibleGrades> change to get_value<Id, Index>, get_bitset<Id, Index>, and component<get_map_values<Id, Index>, dynamic_basis_blade<PossibleGrades, get_map_bitsets<Id, Index> > >, respectively.
		template<class Expression, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables;

		template<class Expression, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		using tag_variables_t = typename tag_variables<Expression, Id, BaseValueIndex, BaseBitsetIndex, BaseMapIndex>::type;

		template<class Expression, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables {
			typedef Expression type; // default
		};

		template<id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<stored_value, Id, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
			typedef get_value<Id, BaseValueIndex> type;
		};

		template<id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<stored_bitset, Id, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
			typedef get_bitset<Id, BaseBitsetIndex> type;
		};

		template<default_bitset_t PossibleGrades, class Bitset, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<dynamic_basis_blade<PossibleGrades, Bitset>, Id, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
			typedef dynamic_basis_blade_t<PossibleGrades, tag_variables_t<Bitset, Id, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> > type;
		};

		template<class Coefficient, class BasisBlade, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<component<Coefficient, BasisBlade>, Id, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
			typedef component<tag_variables_t<Coefficient, Id, BaseValueIndex, BaseBitsetIndex, BaseMapIndex>, tag_variables_t<BasisBlade, Id, BaseValueIndex + count_stored_values_v<Coefficient>, BaseBitsetIndex + count_stored_bitsets_v<Coefficient>, BaseMapIndex + count_stored_maps_v<Coefficient> > > type;
		};

		template<default_bitset_t PossibleGrades, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<stored_components_map<PossibleGrades>, Id, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
			typedef component<get_map_values<Id, BaseMapIndex>, dynamic_basis_blade_t<PossibleGrades, get_map_bitsets<Id, BaseMapIndex> > > type;
		};

		template<name_t Name, class... Arguments, id_t Id, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<function<Name, Arguments...>, Id, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
		private:

			constexpr static std::size_t stored_values_count = count_stored_values_v<Arguments...>;
			constexpr static std::size_t stored_bitsets_count = count_stored_bitsets_v<Arguments...>;
			constexpr static std::size_t stored_maps_count = count_stored_maps_v<Arguments...>;

		public:

			//TODO Isso não funcionará
			typedef function<Name, tag_variables_t<Arguments, Id, BaseValueIndex + (stored_values_count - count_stored_values_v<Arguments>), BaseBitsetIndex + (stored_bitsets_count - count_stored_bitsets_v<Arguments>), BaseMapIndex + (stored_maps_count - count_stored_maps_v<Arguments>)>...> type;
		};

	}

	// Helper structure to define expressions for arguments.
	template<class... InputTypes>
	class lazy_context;

	template<class... InputCoefficientTypes, class... InputExpressions>
	class lazy_context<clifford_expression<InputCoefficientTypes, InputExpressions>...> final {
	private:

		typedef detail::greater_id<InputExpressions...> base_id;

		typedef std::tuple<clifford_expression<InputCoefficientTypes, InputExpressions> const &...> input_tuple_type;
		
		template<std::size_t Index>
		struct _input {
			typedef std::remove_const_t<std::remove_reference_t<std::tuple_element_t<Index, input_tuple_type> > > type;
		};
		
		template<std::size_t Index>
		using input_t = typename _input<Index>::type;

		template<std::size_t Index>
		struct _argument {
			typedef clifford_expression<typename input_t<Index>::coefficient_type, detail::tag_variables_t<typename input_t<Index>::expression_type, detail::id_t(base_id::value + Index + 1), 0, 0, 0> > type;
		};

	public:

		template<std::size_t Index>
		using argument_t = typename _argument<Index>::type;

		template<std::size_t Index>
		using argument_expression_t = typename _argument<Index>::type::expression_type;

		constexpr lazy_context(lazy_context const &) = default;
		constexpr lazy_context(lazy_context &&) = default;

		constexpr lazy_context(clifford_expression<InputCoefficientTypes, InputExpressions> const &... inputs) :
			input_tuple_(inputs...) {
		}

		constexpr lazy_context & operator=(lazy_context const &) = delete;
		constexpr lazy_context & operator=(lazy_context &&) = delete;

		template<std::size_t Index>
		constexpr static decltype(auto) argument() {
			return argument_t<Index>();
		}

		template<class CoefficientType, class ExpressionType>
		constexpr decltype(auto) eval(clifford_expression<CoefficientType, ExpressionType> const &arg) const {
			return clifford_expression<CoefficientType, ExpressionType>(); //TODO Parei aqui!
		}

	private:

		input_tuple_type const input_tuple_;
	};

	template<class... InputTypes>
	constexpr decltype(auto) make_lazy_context(InputTypes const &... inputs) {
		return lazy_context<InputTypes...>(inputs...);
	}

}

#endif // __FUTURE_GA_LAZY_CONTEXT_HPP__
