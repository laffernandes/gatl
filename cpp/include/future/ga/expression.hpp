#ifndef __FUTURE_GA_EXPRESSION_HPP__
#define __FUTURE_GA_EXPRESSION_HPP__

namespace ga {

	namespace detail {

		// Index of variables/arguments.
		typedef std::uint16_t id_t;

		// The name of implemented functions.
		enum class name_t : std::int8_t {
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
		template<id_t Id, std::size_t Index>
		struct get_value {
			typedef get_value type;

			template<class... Arguments>
			inline decltype(auto) operator()(Arguments const &... args) const {
				return 0; //TODO Implementar
			}
		};

		// A value stored by the current clifford_expression<...>.
		struct stored_value {
			typedef stored_value type;
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
		template<id_t Id, std::size_t Index>
		struct get_bitset {
			typedef get_bitset type;

			template<class... Arguments>
			inline default_bitset_t operator()(Arguments const &... args) const {
				return 0; //TODO Implementar
			}
		};

		// A bitset stored by the current clifford_expression<...>.
		struct stored_bitset {
			typedef stored_value type;
		};

		// Basis blade defined in compilation time.
		template<default_bitset_t BasisVectors>
		struct constant_basis_blade {
		};

		// Basis blade defined in runtime.
		template<default_bitset_t PossibleGrades, class Bitset>
		struct dynamic_basis_blade {
		};

		// A basis blade multiplied by some real-valued expression (the coefficient).
		template<class Coefficient, class BasisBlade>
		struct component {
		};

		template<class Coefficient, class BasisBlade, class Enable = void>
		struct _component_t {
			typedef component<Coefficient, BasisBlade> type;
		};

		template<class Coefficient, class BasisBlade>
		struct _component_t<Coefficient, BasisBlade, std::enable_if_t<possible_grades_v<BasisBlade> == default_bitset_t(0)> > {
			typedef component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > type; // A * 0 = 0 (simplify)
		};

		template<class BasisBlade>
		struct _component_t<constant_value<0>, BasisBlade, std::enable_if_t<possible_grades_v<BasisBlade> != default_bitset_t(0)> > {
			typedef component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > type; // 0 * Ei = 0 (simplify)
		};

		template<class Coefficient, class BasisBlade>
		struct _component_t<Coefficient, BasisBlade, std::enable_if_t<possible_grades_v<BasisBlade> == default_bitset_t(1) && !std::is_same_v<Coefficient, constant_value<0> > > > {
			typedef component<Coefficient, constant_basis_blade<default_bitset_t(0)> > type; // A * 1 = A (simplify)
		};

		template<class Coefficient, class BasisBlade>
		using component_t = typename _component_t<Coefficient, BasisBlade>::type;

		//TODO Simplificar para pseudoscalar

		// A real-valued function of a bitset function.
		template<name_t Name, class... Arguments>
		struct function;

		// Addition of real-valued expressions and/or multivector components.
		template<class... Arguments>
		struct function<name_t::add, Arguments...> {
			typedef function type;

			static_assert(!is_any_v<constant_value<0>, Arguments...>, "The argument ga::detail::constant_value<0> is invalid.");
			//TODO static_assert(!is_lazy_add_v<left_type>, "The left-hand side argument cannot be a ga::lazy::add<...> expression.");
			//TODO static_assert(le_v<left_type, typename right_type::left_type>, "The arguments do not respect the expected ordering for lazy expressions.");
		};

		template<class... Arguments>
		using add = function<name_t::add, Arguments...>;

		template<class... Arguments>
		using add_t = typename function<name_t::add, Arguments...>::type;

		template<class Argument>
		struct function<name_t::add, Argument> {
			typedef Argument type; // simplify
		};

		template<>
		struct function<name_t::add> {
			typedef constant_value<0> type; // simplify
		};

		template<class LeftArgument>
		struct function<name_t::add, LeftArgument, constant_value<0> > {
			typedef LeftArgument type; // simplify
		};

		template<class... RightArguments>
		struct function<name_t::add, constant_value<0>, RightArguments...> {
			typedef add_t<RightArguments...> type; // simplify
		};

		template<>
		struct function<name_t::add, constant_value<0>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		// Multiplication of real-valued expressions.
		template<class... Arguments>
		struct function<name_t::mul, Arguments...> {
			typedef function type;

			static_assert(!is_any_v<constant_value<0>, Arguments...>, "The argument ga::detail::constant_value<0> is invalid.");
			static_assert(!is_any_v<constant_value<1>, Arguments...>, "The argument ga::detail::constant_value<1> is invalid.");
			//TODO static_assert(!is_lazy_mul_v<left_type>, "The left-hand side argument cannot be a ga::lazy::mul<...> expression.");
			//TODO static_assert(le_v<left_type, typename right_type::left_type>, "The arguments do not respect the expected ordering for lazy expressions.");
		};

		template<class... Arguments>
		using mul = function<name_t::mul, Arguments...>;

		template<class... Arguments>
		using mul_t = typename function<name_t::mul, Arguments...>::type;

		template<class Argument>
		struct function<name_t::mul, Argument> {
			typedef Argument type; // simplify
		};

		template<>
		struct function<name_t::mul> {
			typedef constant_value<0> type; // simplify
		};

		template<class LeftArgument>
		struct function<name_t::mul, LeftArgument, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<class... RightArguments>
		struct function<name_t::mul, constant_value<0>, RightArguments...> {
			typedef constant_value<0> type; // simplify
		};

		template<>
		struct function<name_t::mul, constant_value<0>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<class LeftArgument>
		struct function<name_t::mul, LeftArgument, constant_value<1> > {
			typedef LeftArgument type; // simplify
		};

		template<class... RightArguments>
		struct function<name_t::mul, constant_value<1>, RightArguments...> {
			typedef mul_t<RightArguments...> type; // simplify
		};

		template<>
		struct function<name_t::mul, constant_value<1>, constant_value<1> > {
			typedef constant_value<1> type; // simplify
		};

		template<>
		struct function<name_t::mul, constant_value<0>, constant_value<1> > {
			typedef constant_value<0> type; // simplify
		};

		template<>
		struct function<name_t::mul, constant_value<1>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

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
		using power_t = typename function<name_t::power, LeftArgument, RightArgument>::type;

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
		struct _reordering_sign_t {
			typedef function<name_t::reordering_sign, LeftBitset, RightBitset> type;
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct _reordering_sign_t<constant_bitset<LeftBitset>, constant_bitset<RightBitset>, std::enable_if_t<LeftBitset != 0 && RightBitset != 0> > {
			typedef constant_value<((swaps_count((LeftBitset >> 1), RightBitset) & 1) != 0) ? -1 : 1> type; // simplify
		};

		template<class LeftBitset>
		struct _reordering_sign_t<LeftBitset, constant_bitset<default_bitset_t(0)> > {
			typedef constant_value<1> type; // simplify
		};

		template<class RightBitset>
		struct _reordering_sign_t<constant_bitset<default_bitset_t(0)>, RightBitset> {
			typedef constant_value<1> type; // simplify
		};

		template<>
		struct _reordering_sign_t<constant_bitset<default_bitset_t(0)>, constant_bitset<default_bitset_t(0)> > {
			typedef constant_value<1> type; // simplify
		};

		template<class LeftBitset, class RightBitset>
		using reordering_sign_t = typename _reordering_sign_t<LeftBitset, RightBitset>::type;

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
		using count_one_bits_t = typename function<name_t::count_one_bits, Bitset>::type;

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
		struct _bitwise_left_shift_t {
			typedef function<name_t::bitwise_left_shift, LeftType, RightType> type;
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _bitwise_left_shift_t<constant_value<LeftValue>, constant_value<RightValue>, std::enable_if_t<LeftValue != 0 && RightValue != 0> > {
			typedef constant_value<(LeftValue << RightValue)> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_integral_t RightValue>
		struct _bitwise_left_shift_t<constant_bitset<LeftBitset>, constant_value<RightValue>, std::enable_if_t<LeftBitset != default_bitset_t(0) && RightValue != 0> > {
			typedef constant_bitset<(LeftBitset << RightValue)> type; // simplify
		};

		template<class RightType>
		struct _bitwise_left_shift_t<constant_value<0>, RightType> {
			typedef constant_value<0> type; // simplify
		};

		template<class RightType>
		struct _bitwise_left_shift_t<constant_bitset<default_bitset_t(0)>, RightType> {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<>
		struct _bitwise_left_shift_t<constant_value<0>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<>
		struct _bitwise_left_shift_t<constant_bitset<default_bitset_t(0)>, constant_value<0> > {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<class LeftType>
		struct _bitwise_left_shift_t<LeftType, constant_value<0> > {
			typedef LeftType type; // simplify
		};

		template<class LeftType, class RightType>
		using bitwise_left_shift_t = typename _bitwise_left_shift_t<LeftType, RightType>::type;

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
		struct _bitwise_and_t {
			typedef function<name_t::bitwise_and, LeftType, RightType> type;
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _bitwise_and_t<constant_value<LeftValue>, constant_value<RightValue>, std::enable_if_t<LeftValue != 0 && RightValue != 0> > {
			typedef constant_value<LeftValue & RightValue> type; // simplify
		};

		template<class LeftType>
		struct _bitwise_and_t<LeftType, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<class RightType>
		struct _bitwise_and_t<constant_value<0>, RightType> {
			typedef constant_value<0> type; // simplify
		};

		template<>
		struct _bitwise_and_t<constant_value<0>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct _bitwise_and_t<constant_bitset<LeftBitset>, constant_bitset<RightBitset>, std::enable_if_t<LeftBitset != default_bitset_t(0) && RightBitset != default_bitset_t(0)> > {
			typedef constant_bitset<LeftBitset & RightBitset> type; // simplify
		};

		template<class LeftType>
		struct _bitwise_and_t<LeftType, constant_bitset<default_bitset_t(0)> > {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<class RightType>
		struct _bitwise_and_t<constant_bitset<default_bitset_t(0)>, RightType> {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<>
		struct _bitwise_and_t<constant_bitset<default_bitset_t(0)>, constant_bitset<default_bitset_t(0)> > {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<class LeftType, class RightType>
		using bitwise_and_t = typename _bitwise_and_t<LeftType, RightType>::type;

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
		struct _bitwise_xor_t {
			typedef function<name_t::bitwise_xor, LeftType, RightType> type;
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _bitwise_xor_t<constant_value<LeftValue>, constant_value<RightValue>, std::enable_if_t<LeftValue != 0 && RightValue != 0> > {
			typedef constant_value<LeftValue ^ RightValue> type; // simplify
		};

		template<class LeftType>
		struct _bitwise_xor_t<LeftType, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<class RightType>
		struct _bitwise_xor_t<constant_value<0>, RightType> {
			typedef constant_value<0> type; // simplify
		};

		template<>
		struct _bitwise_xor_t<constant_value<0>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct _bitwise_xor_t<constant_bitset<LeftBitset>, constant_bitset<RightBitset>, std::enable_if_t<LeftBitset != default_bitset_t(0) && RightBitset != default_bitset_t(0)> > {
			typedef constant_bitset<LeftBitset ^ RightBitset> type; // simplify
		};

		template<class LeftType>
		struct _bitwise_xor_t<LeftType, constant_bitset<default_bitset_t(0)> > {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<class RightType>
		struct _bitwise_xor_t<constant_bitset<default_bitset_t(0)>, RightType> {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<>
		struct _bitwise_xor_t<constant_bitset<default_bitset_t(0)>, constant_bitset<default_bitset_t(0)> > {
			typedef constant_bitset<default_bitset_t(0)> type; // simplify
		};

		template<class LeftType, class RightType>
		using bitwise_xor_t = typename _bitwise_xor_t<LeftType, RightType>::type;

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
		struct _equal_t {
			typedef function<name_t::equal, LeftType, RightType> type;
		};

		template<class CommonType>
		struct _equal_t<CommonType, CommonType> {
			typedef std::true_type type; // simplify
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _equal_t<constant_value<LeftValue>, constant_value<RightValue>, std::enable_if_t<LeftValue != RightValue> > {
			typedef std::false_type type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct _equal_t<constant_bitset<LeftBitset>, constant_bitset<RightBitset>, std::enable_if_t<LeftBitset != RightBitset> > {
			typedef std::false_type type; // simplify
		};

		template<class LeftType, class RightType>
		using equal_t = typename _equal_t<LeftType, RightType>::type;

		// Lazy ternary conditional operation.
		template<class Test, class TrueResult, class FalseResult>
		struct function<name_t::if_else, Test, TrueResult, FalseResult> {
			typedef function type;

			template<class... Arguments>
			constexpr default_bitset_t operator()(Arguments const &... args) const {
				return Test(args...) ? TrueResult(args...) : FalseResult(args...);
			}
		};

		template<class Test, class TrueResult, class FalseResult, class Enable = void>
		struct _if_else_t {
			typedef function<name_t::if_else, Test, TrueResult, FalseResult> type;
		};

		template<class Test, class CommonResult>
		struct _if_else_t<Test, CommonResult, CommonResult> {
			typedef CommonResult type; // simplify
		};


		template<class TrueResult, class FalseResult>
		struct _if_else_t<std::true_type, TrueResult, FalseResult, std::enable_if_t<!std::is_same_v<TrueResult, FalseResult> > > {
			typedef TrueResult type; // simplify
		};

		template<class TrueResult, class FalseResult>
		struct _if_else_t<std::false_type, TrueResult, FalseResult, std::enable_if_t<!std::is_same_v<TrueResult, FalseResult> > > {
			typedef FalseResult type; // simplify
		};

		template<class Test, class TrueResult, class FalseResult>
		using if_else_t = typename _if_else_t<Test, TrueResult, FalseResult>::type;

	}

}

#endif // __FUTURE_GA_EXPRESSION_HPP__
