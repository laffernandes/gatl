#ifndef __FUTURE_GA_EXPRESSION_HPP__
#define __FUTURE_GA_EXPRESSION_HPP__

namespace ga {

	namespace detail {

		// Tag of variables/arguments.
		typedef std::uint16_t tag_t;

		// The name of implemented functions.
		enum class name_t : std::uint8_t {
			reordering_sign,
			count_one_bits,
			
			power,
			mul,
			add,

			bitwise_left_shift,
			bitwise_and,
			bitwise_xor,

			equal,

			if_else
		};

		// Integral value defined in compilation time.
		template<default_integral_t Value>
		struct constant_value {
			typedef constant_value type;

			template<class... Arguments>
			constexpr default_integral_t operator()(Arguments const &... args) const {
				return Value;
			}
		};

		// Lazy getter for stored values.
		template<tag_t Tag, std::size_t Index>
		struct get_value {
			typedef get_value type;

			template<class... Arguments>
			inline decltype(auto) operator()(Arguments const &... args) const {
				return 0; //TODO Implementar
			}
		};

		// Lazy getter for values stored in a map.
		template<tag_t Tag, std::size_t Index>
		struct get_map_values {
			typedef get_map_values type;

			template<class... Arguments>
			inline decltype(auto) operator()(Arguments const &... args) const {
				return 0; //TODO Implementar
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

			template<class... Arguments>
			constexpr default_bitset_t operator()(Arguments const &... args) const {
				return Bitset;
			}
		};

		// Lazy getter for stored bitsets.
		template<tag_t Tag, std::size_t Index>
		struct get_bitset {
			typedef get_bitset type;

			template<class... Arguments>
			inline default_bitset_t operator()(Arguments const &... args) const {
				return 0; //TODO Implementar
			}
		};

		// Lazy getter for bisets stored in a map.
		template<tag_t Tag, std::size_t Index>
		struct get_map_bitsets {
			typedef get_map_bitsets type;

			template<class... Arguments>
			inline default_bitset_t operator()(Arguments const &... args) const {
				return 0; //TODO Implementar
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
		};

		// Basis blade defined in runtime.
		template<default_bitset_t PossibleGrades, class Bitset>
		struct dynamic_basis_blade;

		template<default_bitset_t PossibleGrades, class Bitset>
		using dynamic_basis_blade_t = typename dynamic_basis_blade<PossibleGrades, Bitset>::type;

		// A set of basis blades multiplied by some real-valued expression (the coefficient).
		template<class Coefficient, class BasisBlade>
		struct component;

		template<class Coefficient, class BasisBlade>
		using component_t = typename component<Coefficient, BasisBlade>::type;

		// A real-valued function of a bitset function.
		template<name_t Name, class... Arguments>
		struct function;

		// Addition of real-valued expressions and/or multivector entries.
		template<class... Arguments>
		struct function<name_t::add, Arguments...> {
			typedef function type;

			static_assert(!is_any_v<constant_value<0>, Arguments...>, "The argument ga::detail::constant_value<0> is invalid.");
		};

		template<class Argument>
		struct function<name_t::add, Argument> {
			typedef Argument type; // simplify
		};

		template<>
		struct function<name_t::add> {
			typedef constant_value<0> type; // simplify
		};

		template<class... Arguments>
		using add = function<name_t::add, Arguments...>;

		template<class... Arguments>
		using add_t = typename function<name_t::add, Arguments...>::type;

		// Multiplication of real-valued expressions.
		template<class... Arguments>
		struct function<name_t::mul, Arguments...> {
			typedef function type;

			static_assert(!is_any_v<constant_value<0>, Arguments...>, "The argument ga::detail::constant_value<0> is invalid.");
			static_assert(!is_any_v<constant_value<1>, Arguments...>, "The argument ga::detail::constant_value<1> is invalid.");
		};

		template<class Argument>
		struct function<name_t::mul, Argument> {
			typedef Argument type; // simplify
		};

		template<>
		struct function<name_t::mul> {
			typedef constant_value<0> type; // simplify
		};

		template<class... Arguments>
		using mul = function<name_t::mul, Arguments...>;

		template<class... Arguments>
		using mul_t = typename function<name_t::mul, Arguments...>::type;

		// Exponentiation of real-valued expressions.
		template<class LeftArgument, class RightArgument>
		struct function<name_t::power, LeftArgument, RightArgument> {
			typedef function type;

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
			typedef function type;

			template<class... Arguments>
			inline default_integral_t operator()(Arguments const &... args) const {
				default_bitset_t lhs = LeftBitset(args...);
				default_bitset_t const rhs = RightBitset(args...);
				lhs >>= 1;
				int changes = 0;
				while (lhs != default_bitset_t(0)) {
					changes += ones(lhs & rhs);
					lhs >>= 1;
				}
				return static_cast<default_integral_t>((changes & 1) == 0 ? 1 : -1);
			}
		};

		template<class LeftBitset, class RightBitset, class Enable = void>
		struct _reordering_sign { //TODO Como remover?
			typedef function<name_t::reordering_sign, LeftBitset, RightBitset> type;
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct _reordering_sign<constant_bitset<LeftBitset>, constant_bitset<RightBitset>, std::enable_if_t<LeftBitset != 0 && RightBitset != 0> > {
			typedef constant_value<((swaps_count((LeftBitset >> 1), RightBitset) & 1) != 0) ? -1 : 1> type; // simplify
		};

		template<class LeftBitset>
		struct _reordering_sign<LeftBitset, constant_bitset<default_bitset_t(0)> > {
			typedef constant_value<1> type; // simplify
		};

		template<class RightBitset>
		struct _reordering_sign<constant_bitset<default_bitset_t(0)>, RightBitset> {
			typedef constant_value<1> type; // simplify
		};

		template<>
		struct _reordering_sign<constant_bitset<default_bitset_t(0)>, constant_bitset<default_bitset_t(0)> > {
			typedef constant_value<1> type; // simplify
		};

		template<class LeftBitset, class RightBitset>
		using reordering_sign = function<name_t::reordering_sign, LeftBitset, RightBitset>;

		template<class LeftBitset, class RightBitset>
		using reordering_sign_t = typename _reordering_sign<LeftBitset, RightBitset>::type;

		// Lazy computation of the number of 1 bits in the given lazy bitset.
		template<class Bitset>
		struct function<name_t::count_one_bits, Bitset> {
			typedef function type;

			template<class... Arguments>
			inline default_integral_t operator()(Arguments const &... args) const {
				return ones(Bitset(args...));
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
		template<class LeftType, class RightType>
		struct function<name_t::bitwise_left_shift, LeftType, RightType> {
			typedef function type;

			template<class... Arguments>
			constexpr decltype(auto) operator()(Arguments const &... args) const {
				return LeftType(args...) << RightType(args...);
			}
		};

		template<class LeftType, class RightType, class Enable = void>
		struct _bitwise_left_shift { //TODO Como remover?
			typedef function<name_t::bitwise_left_shift, LeftType, RightType> type;
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _bitwise_left_shift<constant_value<LeftValue>, constant_value<RightValue>, std::enable_if_t<LeftValue != 0 && RightValue != 0> > {
			typedef constant_value<(LeftValue << RightValue)> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_integral_t RightValue>
		struct _bitwise_left_shift<constant_bitset<LeftBitset>, constant_value<RightValue>, std::enable_if_t<LeftBitset != default_bitset_t(0) && RightValue != 0> > {
			typedef constant_bitset<(LeftBitset << RightValue)> type; // simplify
		};

		template<class RightType>
		struct _bitwise_left_shift<constant_value<0>, RightType> {
			typedef constant_value<0> type; // simplify
		};

		template<class RightType>
		struct _bitwise_left_shift<constant_bitset<default_bitset_t(0)>, RightType> {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<>
		struct _bitwise_left_shift<constant_value<0>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<>
		struct _bitwise_left_shift<constant_bitset<default_bitset_t(0)>, constant_value<0> > {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<class LeftType>
		struct _bitwise_left_shift<LeftType, constant_value<0> > {
			typedef LeftType type; // simplify
		};

		template<class LeftType, class RightType>
		using bitwise_left_shift = function<name_t::bitwise_left_shift, LeftType, RightType>;

		template<class LeftType, class RightType>
		using bitwise_left_shift_t = typename _bitwise_left_shift<LeftType, RightType>::type;

		// Lazy bitwise AND operations.
		template<class LeftType, class RightType>
		struct function<name_t::bitwise_and, LeftType, RightType> {
			typedef function type;

			template<class... Arguments>
			constexpr decltype(auto) operator()(Arguments const &... args) const {
				return LeftType(args...) & RightType(args...);
			}
		};

		template<class LeftType, class RightType, class Enable = void>
		struct _bitwise_and { //TODO Como remover?
			typedef function<name_t::bitwise_and, LeftType, RightType> type;
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _bitwise_and<constant_value<LeftValue>, constant_value<RightValue>, std::enable_if_t<LeftValue != 0 && RightValue != 0> > {
			typedef constant_value<LeftValue & RightValue> type; // simplify
		};

		template<class LeftType>
		struct _bitwise_and<LeftType, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<class RightType>
		struct _bitwise_and<constant_value<0>, RightType> {
			typedef constant_value<0> type; // simplify
		};

		template<>
		struct _bitwise_and<constant_value<0>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct _bitwise_and<constant_bitset<LeftBitset>, constant_bitset<RightBitset>, std::enable_if_t<LeftBitset != default_bitset_t(0) && RightBitset != default_bitset_t(0)> > {
			typedef constant_bitset<LeftBitset & RightBitset> type; // simplify
		};

		template<class LeftType>
		struct _bitwise_and<LeftType, constant_bitset<default_bitset_t(0)> > {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<class RightType>
		struct _bitwise_and<constant_bitset<default_bitset_t(0)>, RightType> {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<>
		struct _bitwise_and<constant_bitset<default_bitset_t(0)>, constant_bitset<default_bitset_t(0)> > {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<class LeftType, class RightType>
		using bitwise_and = function<name_t::bitwise_and, LeftType, RightType>;

		template<class LeftType, class RightType>
		using bitwise_and_t = typename _bitwise_and<LeftType, RightType>::type;

		// Lazy bitwise XOR operations.
		template<class LeftType, class RightType>
		struct function<name_t::bitwise_xor, LeftType, RightType> {
			typedef function type;

			template<class... Arguments>
			constexpr decltype(auto) operator()(Arguments const &... args) const {
				return LeftType(args...) ^ RightType(args...);
			}
		};

		template<class LeftType, class RightType, class Enable = void>
		struct _bitwise_xor { //TODO Como remover?
			typedef function<name_t::bitwise_xor, LeftType, RightType> type;
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _bitwise_xor<constant_value<LeftValue>, constant_value<RightValue>, std::enable_if_t<LeftValue != 0 && RightValue != 0> > {
			typedef constant_value<LeftValue ^ RightValue> type; // simplify
		};

		template<class LeftType>
		struct _bitwise_xor<LeftType, constant_value<0> > {
			typedef LeftType type; // simplify
		};

		template<class RightType>
		struct _bitwise_xor<constant_value<0>, RightType> {
			typedef RightType type; // simplify
		};

		template<>
		struct _bitwise_xor<constant_value<0>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct _bitwise_xor<constant_bitset<LeftBitset>, constant_bitset<RightBitset>, std::enable_if_t<LeftBitset != default_bitset_t(0) && RightBitset != default_bitset_t(0)> > {
			typedef constant_bitset<LeftBitset ^ RightBitset> type; // simplify
		};

		template<class LeftType>
		struct _bitwise_xor<LeftType, constant_bitset<default_bitset_t(0)> > {
			typedef LeftType type; // simplify
		};

		template<class RightType>
		struct _bitwise_xor<constant_bitset<default_bitset_t(0)>, RightType> {
			typedef RightType type; // simplify
		};

		template<>
		struct _bitwise_xor<constant_bitset<default_bitset_t(0)>, constant_bitset<default_bitset_t(0)> > {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<class LeftType, class RightType>
		using bitwise_xor = function<name_t::bitwise_xor, LeftType, RightType>;

		template<class LeftType, class RightType>
		using bitwise_xor_t = typename _bitwise_xor<LeftType, RightType>::type;

		// Lazy bitwise EQUAL operation.
		template<class LeftType, class RightType>
		struct function<name_t::equal, LeftType, RightType> {
			typedef function type;

			template<class... Arguments>
			constexpr bool operator()(Arguments const &... args) const {
				return LeftType(args...) == RightType(args...);
			}
		};

		template<class LeftType, class RightType, class Enable = void>
		struct _equal { //TODO Como remover?
			typedef function<name_t::equal, LeftType, RightType> type;
		};

		template<class CommonType>
		struct _equal<CommonType, CommonType> {
			typedef std::true_type type; // simplify
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _equal<constant_value<LeftValue>, constant_value<RightValue>, std::enable_if_t<LeftValue != RightValue> > {
			typedef std::false_type type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct _equal<constant_bitset<LeftBitset>, constant_bitset<RightBitset>, std::enable_if_t<LeftBitset != RightBitset> > {
			typedef std::false_type type; // simplify
		};

		template<class LeftType, class RightType>
		using equal = function<name_t::equal, LeftType, RightType>;

		template<class LeftType, class RightType>
		using equal_t = typename _equal<LeftType, RightType>::type;

		// Lazy ternary conditional operation.
		template<class Test, class TrueResult, class FalseResult>
		struct function<name_t::if_else, Test, TrueResult, FalseResult> {
			typedef function type;

			template<class... Arguments>
			constexpr default_bitset_t operator()(Arguments const &... args) const {
				return Test(args...) ? TrueResult(args...) : FalseResult(args...);
			}
		};

		//TODO Deve simplificar apenas se não houver nada armazenado no resultado
		/*
		template<class Test, class CommonResult>
		struct _if_else<Test, CommonResult, CommonResult, std::enable_if_t<!has_stored_entries_v<CommonResult> > > {
			typedef CommonResult type; // simplify
		};
		*/

		template<class TrueResult, class FalseResult>
		struct function<name_t::if_else, std::true_type, TrueResult, FalseResult > {
			typedef TrueResult type; // simplify
		};

		template<class TrueResult, class FalseResult>
		struct function<name_t::if_else, std::false_type, TrueResult, FalseResult > {
			typedef FalseResult type; // simplify
		};

		template<class Test, class TrueResult, class FalseResult>
		using if_else = function<name_t::if_else, Test, TrueResult, FalseResult>;

		template<class Test, class TrueResult, class FalseResult>
		using if_else_t = typename if_else<Test, TrueResult, FalseResult>::type;

	}

}

#endif // __FUTURE_GA_EXPRESSION_HPP__
