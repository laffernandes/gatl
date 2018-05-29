#ifndef __FUTURE_GA_EXPRESSION_HPP__
#define __FUTURE_GA_EXPRESSION_HPP__

namespace ga {

	namespace detail {

		// Returns whether the given expression has stored entries.
		template<class... Expressions>
		struct has_stored_entries;

		template<class... Expressions>
		constexpr bool has_stored_entries_v = has_stored_entries<Expressions...>::value;

		// Returns whether the given expressions are compile-time defined.
		template<class... Expressions>
		struct is_constant_expression;

		template<class... Expressions>
		constexpr bool is_constant_expression_v = is_constant_expression<Expressions...>::value;

		// Returns the possible grades of a given basis blade.
		template<class BasisBlade>
		struct possible_grades;

		template<class BasisBlade>
		constexpr default_bitset_t possible_grades_v = possible_grades<BasisBlade>::value;

	}

	namespace detail {

		// Tag of variables/arguments.
		typedef std::uint16_t tag_t;

		// The name of implemented functions.
		enum class name_t : std::uint8_t {
			reordering_sign,    // 0
			count_one_bits,     // 1
			
			power,              // 2
			mul,                // 3
			add,                // 4

			bitwise_left_shift, // 5
			bitwise_and,        // 6
			bitwise_xor,        // 7

			equal,              // 8

			if_else             // 9
		};

		// Integral value defined in compilation time.
		template<default_integral_t Value>
		struct constant_value {
			typedef constant_value type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static default_integral_t eval(std::tuple<InputTypes...> const &) {
				return Value;
			}
		};

		// Lazy getter for stored values.
		template<tag_t Tag, std::size_t Index>
		struct get_value {
			typedef get_value type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				static_assert(LowerTag <= Tag && Tag <= UpperTag, "Tag out of bounds.");
				return *std::next(std::get<Tag - LowerTag>(args).values().cbegin(), Index);
			}
		};

		// Lazy getter for values stored in a map.
		template<tag_t Tag, std::size_t Index>
		struct get_map_values {
			typedef get_map_values type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &) {
				static_assert(LowerTag <= Tag && Tag <= UpperTag, "Tag out of bounds.");
				return nullptr; //TODO Not supported yet (map)
			}
		};

		// A value stored by the current clifford_expression<...>.
		struct stored_value {
			typedef stored_value type;
		};

		// A collection of values stored in a map by the current clifford_expression<...>.
		struct stored_map_values {
			typedef stored_map_values type;
		};

		// Bitset defined in compilation time.
		template<default_bitset_t Bitset>
		struct constant_bitset {
			typedef constant_bitset type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static default_bitset_t eval(std::tuple<InputTypes...> const &) {
				return Bitset;
			}
		};

		// Lazy getter for stored bitsets.
		template<tag_t Tag, std::size_t Index>
		struct get_bitset {
			typedef get_bitset type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static default_bitset_t eval(std::tuple<InputTypes...> const &args) {
				static_assert(LowerTag <= Tag && Tag <= UpperTag, "Tag out of bounds.");
				return *std::next(std::get<Tag - LowerTag>(args).bitsets().cbegin(), Index);
			}
		};

		// Lazy getter for bisets stored in a map.
		template<tag_t Tag, std::size_t Index>
		struct get_map_bitsets {
			typedef get_map_bitsets type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &) {
				static_assert(LowerTag <= Tag && Tag <= UpperTag, "Tag out of bounds.");
				return nullptr; //TODO Not supported yet (map)
			}
		};

		// A bitset stored by the current clifford_expression<...>.
		struct stored_bitset {
			typedef stored_value type;
		};

		// A collection of bitsets stored in a map by the current clifford_expression<...>.
		struct stored_map_bitsets {
			typedef stored_map_bitsets type;
		};

		// Basis blade defined in compilation time.
		template<default_bitset_t BasisVectors>
		struct constant_basis_blade {
			typedef constant_basis_blade type;
		};

		// Basis blade defined in runtime.
		template<default_bitset_t PossibleGrades, class Bitset>
		struct dynamic_basis_blade {
			typedef dynamic_basis_blade type; // default
		};

		template<class Bitset>
		struct dynamic_basis_blade<default_bitset_t(1), Bitset> {
			typedef constant_basis_blade<default_bitset_t(0)> type; // scalar for sure
		};

		template<>
		struct dynamic_basis_blade<default_bitset_t(1), constant_bitset<default_bitset_t(0)> > {
			typedef constant_basis_blade<default_bitset_t(0)> type; // scalar for sure
		};

		template<default_bitset_t PossibleGrades, default_bitset_t Bitset>
		struct dynamic_basis_blade<PossibleGrades, constant_bitset<Bitset> > {
			typedef constant_basis_blade<Bitset> type; // it is not dynamic

			static_assert(PossibleGrades == possible_grades_v<type>, "The possible grades are inconsistent.");
		};

		template<default_bitset_t PossibleGrades, class Bitset>
		using dynamic_basis_blade_t = typename dynamic_basis_blade<PossibleGrades, Bitset>::type;

		// A set of basis blades multiplied by some real-valued expression (the coefficient).
		template<class Coefficient, class BasisBlade>
		struct component {
		private:

			constexpr static default_bitset_t possible_grades = possible_grades_v<BasisBlade>;

			typedef std::conditional_t<
				possible_grades == default_bitset_t(0),
				constant_value<0>, // impossible basis blade
				Coefficient
			> coefficient;
			
			typedef std::conditional_t<
				std::is_same_v<Coefficient, constant_value<0> > || possible_grades == default_bitset_t(0),
				constant_basis_blade<default_bitset_t(0)>,  // impossible basis blade or zero
				BasisBlade
			> basis_blade;

		public:
			
			typedef component<coefficient, basis_blade> type;
		};

		template<class Coefficient, class BasisBlade>
		using component_t = typename component<Coefficient, BasisBlade>::type;

		// A real-valued function of a bitset function.
		template<name_t Name, class... Arguments>
		struct function;

		// Addition of real-valued expressions and/or multivector entries.
		template<class... Arguments>
		struct function<name_t::add, Arguments...>;
		
		template<class... Arguments>
		using add = function<name_t::add, Arguments...>;

		template<class... Arguments>
		using add_t = typename function<name_t::add, Arguments...>::type;

		template<class Argument, class... NextArguments>
		struct function<name_t::add, Argument, NextArguments...> {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return Argument::eval<LowerTag, UpperTag>(args) + add_t<NextArguments...>::eval<LowerTag, UpperTag>(args);
			}

			static_assert(!is_any_v<constant_value<0>, Argument, NextArguments...>, "The argument ga::detail::constant_value<0> is invalid.");
		};

		template<class Argument>
		struct function<name_t::add, Argument> {
			typedef Argument type; // simplify
		};

		template<>
		struct function<name_t::add> {
			typedef constant_value<0> type; // simplify
		};

		// Multiplication of real-valued expressions.
		template<class... Arguments>
		struct function<name_t::mul, Arguments...>;
		
		template<class... Arguments>
		using mul = function<name_t::mul, Arguments...>;

		template<class... Arguments>
		using mul_t = typename function<name_t::mul, Arguments...>::type;

		template<class Argument, class... NextArguments>
		struct function<name_t::mul, Argument, NextArguments...> {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return Argument::eval<LowerTag, UpperTag>(args) * mul_t<NextArguments...>::eval<LowerTag, UpperTag>(args);
			}

			static_assert(!is_any_v<constant_value<0>, Argument, NextArguments...>, "The argument ga::detail::constant_value<0> is invalid.");
			static_assert(!is_any_v<constant_value<1>, Argument, NextArguments...>, "The argument ga::detail::constant_value<1> is invalid.");
		};

		template<class Argument>
		struct function<name_t::mul, Argument> {
			typedef Argument type; // simplify
		};

		template<>
		struct function<name_t::mul> {
			typedef constant_value<0> type; // simplify
		};

		// Exponentiation of real-valued expressions.
		template<class LeftArgument, class RightArgument>
		struct function<name_t::power, LeftArgument, RightArgument> {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return pow(LeftArgument::eval<LowerTag, UpperTag>(args), RightArgument::eval<LowerTag, UpperTag>(args)); //TODO Aplicar padrões para otimização
			}

			static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
			static_assert(!std::is_same_v<RightArgument, constant_value<0> >, "The right-hand side argument cannot be ga::detail::constant_value<0>.");
			static_assert(!std::is_same_v<RightArgument, constant_value<1> >, "The right-hand side argument cannot be ga::detail::constant_value<1>.");
		};

		template<class LeftArgument, class RightArgument>
		using power = function<name_t::power, LeftArgument, RightArgument>;

		template<class LeftArgument, class RightArgument>
		struct _power;

		template<class LeftArgument, class RightArgument>
		using power_t = typename _power<LeftArgument, RightArgument>::type;

		// Lazy computation of the sign induced by the canonical reordering of basis vectors in bilinear products.
		template<class LeftBitset, class RightBitset>
		struct function<name_t::reordering_sign, LeftBitset, RightBitset> {
			typedef std::conditional_t<
				std::is_same_v<LeftBitset, constant_bitset<default_bitset_t(0)> > || std::is_same_v<RightBitset, constant_bitset<default_bitset_t(0)> >,
				constant_value<1>, // simplify
				function // default
			> type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static default_integral_t eval(std::tuple<InputTypes...> const &args) {
				default_bitset_t lhs = LeftBitset::eval<LowerTag, UpperTag>(args);
				default_bitset_t const rhs = RightBitset::eval<LowerTag, UpperTag>(args);
				lhs >>= 1;
				int changes = 0;
				while (lhs != default_bitset_t(0)) {
					changes += ones(lhs & rhs);
					lhs >>= 1;
				}
				return static_cast<default_integral_t>((changes & 1) == 0 ? 1 : -1);
			}
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::reordering_sign, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
			typedef constant_value<((swaps_count((LeftBitset >> 1), RightBitset) & 1) != 0) ? -1 : 1> type; // simplify
		};

		template<class LeftBitset, class RightBitset>
		using reordering_sign = function<name_t::reordering_sign, LeftBitset, RightBitset>;

		template<class LeftBitset, class RightBitset>
		using reordering_sign_t = typename reordering_sign<LeftBitset, RightBitset>::type;

		// Lazy computation of the number of 1 bits in the given lazy bitset.
		template<class Bitset>
		struct function<name_t::count_one_bits, Bitset> {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static default_integral_t eval(std::tuple<InputTypes...> const &args) {
				return ones(Bitset::eval<LowerTag, UpperTag>(args));
			}
		};

		template<default_bitset_t Bitset>
		struct function<name_t::count_one_bits, constant_bitset<Bitset> > {
			typedef constant_value<ones(Bitset)> type; // simplify
		};

		template<class Bitset>
		using count_one_bits = function<name_t::count_one_bits, Bitset>;

		template<class Bitset>
		using count_one_bits_t = typename count_one_bits<Bitset>::type;

		// Lazy bitwise LEFT SHIFT operations.
		template<class LeftType, class RightValue>
		struct function<name_t::bitwise_left_shift, LeftType, RightValue> {
			typedef std::conditional_t<
				std::is_same_v<LeftType, constant_value<0> > || std::is_same_v<LeftType, constant_bitset<default_bitset_t(0)> > || std::is_same_v<RightValue, constant_value<0> >,
				LeftType, // simplify
				function // default
			> type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return LeftType::eval<LowerTag, UpperTag>(args) << RightValue::eval<LowerTag, UpperTag>(args);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::bitwise_left_shift, constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<(LeftValue << RightValue)> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_integral_t RightValue>
		struct function<name_t::bitwise_left_shift, constant_bitset<LeftBitset>, constant_value<RightValue> > {
			typedef constant_bitset<(LeftBitset << RightValue)> type; // simplify
		};

		template<class LeftType, class RightValue>
		using bitwise_left_shift = function<name_t::bitwise_left_shift, LeftType, RightValue>;

		template<class LeftType, class RightValue>
		using bitwise_left_shift_t = typename bitwise_left_shift<LeftType, RightValue>::type;

		// Lazy bitwise AND operations.
		template<class LeftType, class RightType>
		struct function<name_t::bitwise_and, LeftType, RightType> {
			typedef std::conditional_t<
				std::is_same_v<LeftType, constant_value<0> > || std::is_same_v<RightType, constant_value<0> >,
				constant_value<0>, // simplify
				std::conditional_t<
					std::is_same_v<LeftType, constant_bitset<default_bitset_t(0)> > || std::is_same_v<RightType, constant_bitset<default_bitset_t(0)> >,
					constant_bitset<default_bitset_t(0)>, // simplify
					function // degault
				>
			> type;
				
			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return LeftType::eval<LowerTag, UpperTag>(args) & RightType::eval<LowerTag, UpperTag>(args);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::bitwise_and, constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<LeftValue & RightValue> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::bitwise_and, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
			typedef constant_bitset<LeftBitset & RightBitset> type; // simplify
		};

		template<class LeftType, class RightType>
		using bitwise_and = function<name_t::bitwise_and, LeftType, RightType>;

		template<class LeftType, class RightType>
		using bitwise_and_t = typename bitwise_and<LeftType, RightType>::type;

		// Lazy bitwise XOR operations.
		template<class LeftType, class RightType>
		struct function<name_t::bitwise_xor, LeftType, RightType> {
			typedef std::conditional_t<
				std::is_same_v<LeftType, constant_value<0> > || std::is_same_v<LeftType, constant_bitset<default_bitset_t(0)> >,
				RightType, // simplify
				std::conditional_t<
					std::is_same_v<RightType, constant_value<0> > || std::is_same_v<RightType, constant_bitset<default_bitset_t(0)> >,
					LeftType, // simplify
					function // default
				>
			> type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return LeftType::eval<LowerTag, UpperTag>(args) ^ RightType::eval<LowerTag, UpperTag>(args);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::bitwise_xor, constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<LeftValue ^ RightValue> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::bitwise_xor, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
			typedef constant_bitset<LeftBitset ^ RightBitset> type; // simplify
		};

		template<class LeftType, class RightType>
		using bitwise_xor = function<name_t::bitwise_xor, LeftType, RightType>;

		template<class LeftType, class RightType>
		using bitwise_xor_t = typename bitwise_xor<LeftType, RightType>::type;

		// Lazy bitwise EQUAL operation.
		template<class LeftType, class RightType>
		struct function<name_t::equal, LeftType, RightType> {
			typedef std::conditional_t<
				std::is_same_v<LeftType, RightType> && !has_stored_entries_v<LeftType>,
				std::true_type, // simplify
				std::conditional_t<
					!std::is_same_v<LeftType, RightType> && is_constant_expression_v<LeftType, RightType>,
					std::false_type, // simplify
					function // default
				>
			> type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static bool eval(std::tuple<InputTypes...> const &args) {
				return LeftType::eval<LowerTag, UpperTag>(args) == RightType::eval<LowerTag, UpperTag>(args);
			}
		};

		template<class LeftType, class RightType>
		using equal = function<name_t::equal, LeftType, RightType>;

		template<class LeftType, class RightType>
		using equal_t = typename equal<LeftType, RightType>::type;

		// Lazy ternary conditional operation.
		template<class Test, class TrueValue, class FalseValue>
		struct function<name_t::if_else, Test, TrueValue, FalseValue> {
			typedef std::conditional_t<
				std::is_same_v<TrueValue, FalseValue> && !has_stored_entries_v<TrueValue>,
				TrueValue, // simplify
				function
			> type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return Test::eval<LowerTag, UpperTag>(args) ? TrueValue::eval<LowerTag, UpperTag>(args) : FalseValue::eval<LowerTag, UpperTag>(args);
			}
		};

		template<class TrueValue, class FalseValue>
		struct function<name_t::if_else, std::true_type, TrueValue, FalseValue> {
			typedef TrueValue type; // simplify
		};

		template<class TrueValue, class FalseValue>
		struct function<name_t::if_else, std::false_type, TrueValue, FalseValue> {
			typedef FalseValue type; // simplify
		};

		template<class Test, class TrueValue, class FalseValue>
		using if_else = function<name_t::if_else, Test, TrueValue, FalseValue>;

		template<class Test, class TrueValue, class FalseValue>
		using if_else_t = typename if_else<Test, TrueValue, FalseValue>::type;

	}

}

#endif // __FUTURE_GA_EXPRESSION_HPP__
