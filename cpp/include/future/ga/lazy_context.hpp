#ifndef __FUTURE_GA_LAZY_CONTEXT_HPP__
#define __FUTURE_GA_LAZY_CONTEXT_HPP__

namespace ga {

	//TODO Como lidar com a avaliação parcial da lazy expression?

	namespace detail {
	
		// Returns the greater ID found in the given expressions.
		template<class... Expressions>
		struct greater_id;

		template<class... Expressions>
		constexpr tag_t greater_id_v = greater_id<Expressions...>::value;

		template<class Expression, class... NextExpressions>
		struct greater_id<Expression, NextExpressions...> {
			constexpr static tag_t value = greater(greater_id_v<Expression>, greater_id_v<NextExpressions...>); // recursion
		};

		template<>
		struct greater_id<> {
			constexpr static tag_t value = 0; // end of recursion
		};

		template<class Expression>
		struct greater_id<Expression> {
			constexpr static tag_t value = 0; // default
		};

		template<tag_t Tag, std::size_t Index>
		struct greater_id<get_value<Tag, Index> > {
			constexpr static tag_t value = Tag;
		};

		template<tag_t Tag, std::size_t Index>
		struct greater_id<get_map_values<Tag, Index> > {
			constexpr static tag_t value = Tag;
		};

		template<tag_t Tag, std::size_t Index>
		struct greater_id<get_bitset<Tag, Index> > {
			constexpr static tag_t value = Tag;
		};

		template<tag_t Tag, std::size_t Index>
		struct greater_id<get_map_bitsets<Tag, Index> > {
			constexpr static tag_t value = Tag;
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		struct greater_id<dynamic_basis_blade<PossibleGrades, Bitset> > {
			constexpr static tag_t value = greater_id_v<Bitset>;
		};

		template<class Coefficient, class BasisBlade>
		struct greater_id<component<Coefficient, BasisBlade> > {
			constexpr static tag_t value = greater(greater_id_v<Coefficient>, greater_id_v<BasisBlade>);
		};

		template<name_t Name, class... Arguments>
		struct greater_id<function<Name, Arguments...> > {
			constexpr static tag_t value = greater_id_v<Arguments...>;
		};

		// Produces an expression where stored_value, stored_map_values, stored_bitset, and stored_map_bitsets change to get_value<Tag, Index>, get_map_values<Tag, Index>, get_bitset<Tag, Index>, and get_map_bitsets<Tag, Index>, respectively.
		template<class Expression, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables;

		template<class Expression, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		using tag_variables_t = typename tag_variables<Expression, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex>::type;

		template<class Expression, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables {
			typedef Expression type; // default
		};

		template<tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<stored_value, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
			typedef get_value<Tag, BaseValueIndex> type;
		};

		template<tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<stored_map_values, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
			typedef get_map_values<Tag, BaseMapIndex> type; //TODO Esse índice não é consistente
		};

		template<tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<stored_bitset, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
			typedef get_bitset<Tag, BaseBitsetIndex> type; //TODO Esse índice não é consistente
		};

		template<tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<stored_map_bitsets, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
			typedef get_map_bitsets<Tag, BaseMapIndex> type;
		};

		template<default_bitset_t PossibleGrades, class Bitset, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<dynamic_basis_blade<PossibleGrades, Bitset>, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
			typedef dynamic_basis_blade_t<PossibleGrades, tag_variables_t<Bitset, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> > type;
		};

		template<class Coefficient, class BasisBlade, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<component<Coefficient, BasisBlade>, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
			typedef component_t<tag_variables_t<Coefficient, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex>, tag_variables_t<BasisBlade, Tag, BaseValueIndex + count_stored_values_v<Coefficient>, BaseBitsetIndex + count_stored_bitsets_v<Coefficient>, BaseMapIndex + count_stored_maps_v<Coefficient> > > type;
		};

		template<name_t Name, class... Arguments, tag_t Tag, std::size_t BaseValueIndex, std::size_t BaseBitsetIndex, std::size_t BaseMapIndex>
		struct tag_variables<function<Name, Arguments...>, Tag, BaseValueIndex, BaseBitsetIndex, BaseMapIndex> {
		private:

			constexpr static std::size_t stored_values_count = count_stored_values_v<Arguments...>;
			constexpr static std::size_t stored_bitsets_count = count_stored_bitsets_v<Arguments...>;
			constexpr static std::size_t stored_maps_count = count_stored_maps_v<Arguments...>;

		public:

			//TODO Isso não funcionará
			typedef function<Name, tag_variables_t<Arguments, Tag, BaseValueIndex + (stored_values_count - count_stored_values_v<Arguments>), BaseBitsetIndex + (stored_bitsets_count - count_stored_bitsets_v<Arguments>), BaseMapIndex + (stored_maps_count - count_stored_maps_v<Arguments>)>...> type;
		};

		// Evaluates the given clifford_expression<...>.
		template<tag_t LowerTag, tag_t UpperTag, class Expression>
		struct eval_expression;

		template<tag_t LowerTag, tag_t UpperTag, class Expression>
		using eval_expression_t = typename eval_expression<LowerTag, UpperTag, Expression>::type;

		template<tag_t LowerTag, tag_t UpperTag, default_integral_t Value>
		struct eval_expression<LowerTag, UpperTag, constant_value<Value> > {
			typedef constant_value<Value> type;
		};

		template<tag_t LowerTag, tag_t UpperTag, tag_t Tag, std::size_t Index>
		struct eval_expression<LowerTag, UpperTag, get_value<Tag, Index> > {
			typedef std::conditional_t<(LowerTag <= Tag && Tag <= UpperTag), stored_value, get_value<Tag, Index> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, tag_t Tag, std::size_t Index>
		struct eval_expression<LowerTag, UpperTag, get_map_values<Tag, Index> > {
			typedef std::conditional_t<(LowerTag <= Tag && Tag <= UpperTag), stored_map_values, get_map_values<Tag, Index> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag>
		struct eval_expression<LowerTag, UpperTag, stored_value> {
			typedef stored_value type;
		};

		template<tag_t LowerTag, tag_t UpperTag>
		struct eval_expression<LowerTag, UpperTag, stored_map_values> {
			typedef stored_map_values type;
		};

		template<tag_t LowerTag, tag_t UpperTag, default_bitset_t Bitset>
		struct eval_expression<LowerTag, UpperTag, constant_bitset<Bitset> > {
			typedef constant_bitset<Bitset> type;
		};

		template<tag_t LowerTag, tag_t UpperTag, tag_t Tag, std::size_t Index>
		struct eval_expression<LowerTag, UpperTag, get_bitset<Tag, Index> > {
			typedef std::conditional_t<(LowerTag <= Tag && Tag <= UpperTag), stored_bitset, get_bitset<Tag, Index> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, tag_t Tag, std::size_t Index>
		struct eval_expression<LowerTag, UpperTag, get_map_bitsets<Tag, Index> > {
			typedef std::conditional_t<(LowerTag <= Tag && Tag <= UpperTag), stored_map_bitsets, get_map_bitsets<Tag, Index> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag>
		struct eval_expression<LowerTag, UpperTag, stored_bitset> {
			typedef stored_bitset type;
		};

		template<tag_t LowerTag, tag_t UpperTag>
		struct eval_expression<LowerTag, UpperTag, stored_map_bitsets> {
			typedef stored_map_bitsets type;
		};

		template<tag_t LowerTag, tag_t UpperTag, default_bitset_t BasisVectors>
		struct eval_expression<LowerTag, UpperTag, constant_basis_blade<BasisVectors> > {
			typedef constant_basis_blade<BasisVectors> type;
		};

		template<tag_t LowerTag, tag_t UpperTag, default_bitset_t PossibleGrades, class Bitset>
		struct eval_expression<LowerTag, UpperTag, dynamic_basis_blade<PossibleGrades, Bitset> > {
			typedef dynamic_basis_blade_t<PossibleGrades, eval_expression_t<LowerTag, UpperTag, Bitset> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, class Coefficient, class BasisBlade>
		struct eval_expression<LowerTag, UpperTag, component<Coefficient, BasisBlade> > {
			typedef component_t<eval_expression_t<LowerTag, UpperTag, Coefficient>, eval_expression_t<LowerTag, UpperTag, BasisBlade> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, class Argument, class... NextArguments>
		struct eval_expression<LowerTag, UpperTag, add<Argument, NextArguments...> > {
			typedef addition_t<eval_expression_t<LowerTag, UpperTag, Argument>, eval_expression_t<LowerTag, UpperTag, add_t<NextArguments...> > > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, class Argument, class... NextArguments>
		struct eval_expression<LowerTag, UpperTag, mul<Argument, NextArguments...> > {
			typedef product_t<eval_expression_t<LowerTag, UpperTag, Argument>, eval_expression_t<LowerTag, UpperTag, add_t<NextArguments...> >, real_mapping> type;
		};

		template<tag_t LowerTag, tag_t UpperTag, class LeftArgument, class RightArgument>
		struct eval_expression<LowerTag, UpperTag, power<LeftArgument, RightArgument> > {
			typedef power_t<eval_expression_t<LowerTag, UpperTag, LeftArgument>, eval_expression_t<LowerTag, UpperTag, RightArgument> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, class LeftBitset, class RightBitset>
		struct eval_expression<LowerTag, UpperTag, reordering_sign<LeftBitset, RightBitset> > {
			typedef reordering_sign_t<eval_expression_t<LowerTag, UpperTag, LeftBitset>, eval_expression_t<LowerTag, UpperTag, RightBitset> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, class Bitset>
		struct eval_expression<LowerTag, UpperTag, count_one_bits<Bitset> > {
			typedef count_one_bits_t<eval_expression_t<LowerTag, UpperTag, Bitset> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, class LeftType, class RightType>
		struct eval_expression<LowerTag, UpperTag, bitwise_left_shift<LeftType, RightType> > {
			typedef bitwise_left_shift_t<eval_expression_t<LowerTag, UpperTag, LeftType>, eval_expression_t<LowerTag, UpperTag, RightType> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, class LeftType, class RightType>
		struct eval_expression<LowerTag, UpperTag, bitwise_and<LeftType, RightType> > {
			typedef bitwise_and_t<eval_expression_t<LowerTag, UpperTag, LeftType>, eval_expression_t<LowerTag, UpperTag, RightType> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, class LeftType, class RightType>
		struct eval_expression<LowerTag, UpperTag, bitwise_xor<LeftType, RightType> > {
			typedef bitwise_xor_t<eval_expression_t<LowerTag, UpperTag, LeftType>, eval_expression_t<LowerTag, UpperTag, RightType> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, class LeftType, class RightType>
		struct eval_expression<LowerTag, UpperTag, equal<LeftType, RightType> > {
			typedef equal_t<eval_expression_t<LowerTag, UpperTag, LeftType>, eval_expression_t<LowerTag, UpperTag, RightType> > type;
		};

		template<tag_t LowerTag, tag_t UpperTag, class Test, class TrueResult, class FalseResult>
		struct eval_expression<LowerTag, UpperTag, if_else<Test, TrueResult, FalseResult> > {
			typedef if_else_t<eval_expression_t<LowerTag, UpperTag, Test>, eval_expression_t<LowerTag, UpperTag, TrueResult>, eval_expression_t<LowerTag, UpperTag, FalseResult> > type;
		};
		
		template<tag_t LowerTag, tag_t UpperTag, class CoefficientType, class Expression, class... InputTypes>
		constexpr static decltype(auto) eval(clifford_expression<CoefficientType, Expression> const &expression, std::tuple<InputTypes...> const &args) {
			typedef clifford_expression<CoefficientType, eval_expression_t<LowerTag, UpperTag, Expression> > result_type;
			return result_type(); //TODO Parei aqui!
		}

		// Superclass for ga::lazy_context<InputTypes...>.
		template<tag_t BaseTag, class... InputTypes>
		class _super_lazy_context;

		template<size_t ReverseIndex, class InputCoefficientType, class InputExpression, bool StoredReference = has_stored_entries_v<InputExpression> >
		class _super_lazy_context_input {
		public:

			typedef clifford_expression<InputCoefficientType, InputExpression> input_type;

			constexpr _super_lazy_context_input(_super_lazy_context_input const &) = default;
			constexpr _super_lazy_context_input(_super_lazy_context_input &&) = default;

			constexpr _super_lazy_context_input(input_type const &input) :
				input_(input) {
			}

			constexpr _super_lazy_context_input & operator=(_super_lazy_context_input const &) = delete;
			constexpr _super_lazy_context_input & operator=(_super_lazy_context_input &&) = delete;

			constexpr decltype(auto) get_as_tuple() const {
				return std::tie(input_);
			}

			constexpr static bool is_stored() {
				return true;
			}

		private:

			input_type const &input_;
		};

		template<std::size_t ReverseIndex, class InputCoefficientType, class InputExpression>
		class _super_lazy_context_input<ReverseIndex, InputCoefficientType, InputExpression, false> {
		public:

			typedef clifford_expression<InputCoefficientType, InputExpression> input_type;

			constexpr _super_lazy_context_input(_super_lazy_context_input const &) = default;
			constexpr _super_lazy_context_input(_super_lazy_context_input &&) = default;

			constexpr _super_lazy_context_input(clifford_expression<InputCoefficientType, InputExpression> const &) {
			}

			constexpr _super_lazy_context_input & operator=(_super_lazy_context_input const &) = delete;
			constexpr _super_lazy_context_input & operator=(_super_lazy_context_input &&) = delete;

			constexpr decltype(auto) get_as_tuple() const {
				return std::make_tuple();
			}

			constexpr static bool is_stored() {
				return false;
			}
		};

		template<tag_t BaseTag, class InputCoefficientType, class InputExpression, class... OtherInputCoefficientTypes, class... OtherInputExpressions>
		class _super_lazy_context<BaseTag, clifford_expression<InputCoefficientType, InputExpression>, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions>...> :
			private _super_lazy_context_input<sizeof...(OtherInputExpressions), InputCoefficientType, InputExpression>,
			private _super_lazy_context<_super_lazy_context_input<sizeof...(OtherInputExpressions), InputCoefficientType, InputExpression>::is_stored() ? BaseTag + 1 : BaseTag, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions>...> {
		private:

			typedef _super_lazy_context_input<sizeof...(OtherInputExpressions), InputCoefficientType, InputExpression> super_input;
			typedef _super_lazy_context<super_input::is_stored() ? BaseTag + 1 : BaseTag, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions>...> super_recursive;

		public:

			template<std::size_t Index>
			struct argument {
				typedef typename super_recursive::template argument<Index - 1>::type type;
			};

			template<>
			struct argument<0> {
				typedef std::conditional_t<
					super_input::is_stored(),
					clifford_expression<InputCoefficientType, tag_variables_t<InputExpression, BaseTag + 1, 0, 0, 0> >,
					typename super_input::input_type
				> type;
			};

			constexpr _super_lazy_context(_super_lazy_context const &) = default;
			constexpr _super_lazy_context(_super_lazy_context &&) = default;

			constexpr _super_lazy_context(clifford_expression<InputCoefficientType, InputExpression> const &input, clifford_expression<OtherInputCoefficientTypes, OtherInputExpressions> const &... other_inputs) :
				super_input(input),
				super_recursive(other_inputs...) {
			}

			constexpr _super_lazy_context & operator=(_super_lazy_context const &) = delete;
			constexpr _super_lazy_context & operator=(_super_lazy_context &&) = delete;

			constexpr decltype(auto) stored_inputs_tuple() const {
				return std::tuple_cat(super_input::get_as_tuple(), super_recursive::stored_inputs_tuple());
			}

			constexpr static std::size_t stored_inputs_count() {
				return (super_input::is_stored() ? 1 : 0) + super_recursive::stored_inputs_count();
			}
		};

		template<tag_t BaseTag>
		class _super_lazy_context<BaseTag> {
		public:

			constexpr _super_lazy_context() = default;
			constexpr _super_lazy_context(_super_lazy_context const &) = default;
			constexpr _super_lazy_context(_super_lazy_context &&) = default;

			constexpr _super_lazy_context & operator=(_super_lazy_context const &) = delete;
			constexpr _super_lazy_context & operator=(_super_lazy_context &&) = delete;

			constexpr decltype(auto) stored_inputs_tuple() const {
				return std::make_tuple();
			}

			constexpr static std::size_t stored_inputs_count() {
				return 0;
			}
		};

	};

	// Helper structure to define lazy arguments for lazy evaluation of expressions.
	template<class... InputTypes>
	class lazy_context;

	template<class... InputCoefficientTypes, class... InputExpressions>
	class lazy_context<clifford_expression<InputCoefficientTypes, InputExpressions>...> final :
		private detail::_super_lazy_context<detail::greater_id_v<InputExpressions...>, clifford_expression<InputCoefficientTypes, InputExpressions>...> {
	private:

		constexpr static detail::tag_t base_id = detail::greater_id_v<InputExpressions...>;
		
		typedef detail::_super_lazy_context<base_id, clifford_expression<InputCoefficientTypes, InputExpressions>...> super;

	public:

		template<std::size_t Index>
		using argument_t = typename super::template argument<Index>::type;

		template<std::size_t Index>
		using argument_coefficient_t = typename super::template argument<Index>::type::coefficient_type;

		template<std::size_t Index>
		using argument_expression_t = typename super::template argument<Index>::type::expression_type;

		constexpr lazy_context(lazy_context const &) = default;
		constexpr lazy_context(lazy_context &&) = default;

		constexpr lazy_context(clifford_expression<InputCoefficientTypes, InputExpressions> const &... inputs) :
			super(inputs...) {
		}

		constexpr lazy_context & operator=(lazy_context const &) = delete;
		constexpr lazy_context & operator=(lazy_context &&) = delete;

		template<std::size_t Index>
		constexpr static decltype(auto) argument() {
			return argument_t<Index>();
		}

		template<class CoefficientType, class Expression, class = std::enable_if_t<super::stored_inputs_count() != 0> >
		constexpr decltype(auto) eval(clifford_expression<CoefficientType, Expression> const &expression) const {
			return detail::eval<base_id + 1, base_id + (detail::tag_t)super::stored_inputs_count()>(expression, super::stored_inputs_tuple());
		}

		template<class CoefficientType, class Expression, class = std::enable_if_t<super::stored_inputs_count() == 0> >
		constexpr decltype(auto) eval(clifford_expression<CoefficientType, Expression> &&expression) const {
			return std::move(expression);
		}
	};

	template<class... InputTypes>
	constexpr decltype(auto) make_lazy_context(InputTypes const &... inputs) {
		return lazy_context<InputTypes...>(inputs...);
	}

}

#endif // __FUTURE_GA_LAZY_CONTEXT_HPP__
