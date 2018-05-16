#ifndef __FUTURE_GA_EXPRESSION_HPP__
#define __FUTURE_GA_EXPRESSION_HPP__

namespace ga {

	namespace detail {

		// Index of variables/arguments.
		typedef std::uint16_t id_t;

		// The name of implemented functions.
		enum class name_t : std::int8_t {
			lazy_reordering_sign,
			lazy_ones,
			
			power,
			mul,
			add,

			lazy_plus,
			lazy_minus,
			lazy_bitwise_and,
			lazy_bitwise_xor,
			lazy_eq,
			lazy_if_else
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
		template<default_bitset_t PossibleGrades, class LazyBitset>
		struct dynamic_basis_blade {
		};

		// A basis blade multiplied by some real-valued expression (the coefficient).
		template<class Coefficient, class BasisBlade>
		struct component {
		};

		template<class Coefficient, class BasisBlade, class Enable = void>
		struct _component_t;

		template<class Coefficient, class BasisBlade>
		struct _component_t<Coefficient, BasisBlade, std::enable_if_t<possible_grades_v<BasisBlade> != default_bitset_t(0) && possible_grades_v<BasisBlade> != default_bitset_t(1)> > {
			typedef component<Coefficient, BasisBlade> type; // default (bind)
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
			//TODO static_assert(!is_lazy_mul_v<left_type>, "The left-hand side argument cannot be a ga::lazy::mul<...> expression.");
			//TODO static_assert(le_v<left_type, typename right_type::left_type>, "The arguments do not respect the expected ordering for lazy expressions.");
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
		using power_t = typename function<name_t::power, LeftArgument, RightArgument>::type;

		// Lazy computation of the sign induced by the canonical reordering of basis vectors in bilinear products.
		template<class LeftLazyBitset, class RightLazyBitset>
		struct function<name_t::lazy_reordering_sign, LeftLazyBitset, RightLazyBitset> {
			typedef function type;

			template<class... Arguments>
			inline default_integral_t operator()(Arguments const &... args) const {
				default_bitset_t lhs = LeftLazyBitset(args...);
				default_bitset_t const rhs = RightLazyBitset(args...);
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
		struct function<name_t::lazy_reordering_sign, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
			typedef constant_value<((swaps_count((LeftBitset >> 1), RightBitset) & 1) != 0) ? -1 : 1> type; // simplify
		};

		template<class LeftLazyBitset>
		struct function<name_t::lazy_reordering_sign, LeftLazyBitset, constant_bitset<0> > {
			typedef constant_value<1> type; // simplify
		};

		template<class RightLazyBitset>
		struct function<name_t::lazy_reordering_sign, constant_bitset<0>, RightLazyBitset> {
			typedef constant_value<1> type; // simplify
		};

		template<>
		struct function<name_t::lazy_reordering_sign, constant_bitset<0>, constant_bitset<0> > {
			typedef constant_value<1> type; // simplify
		};

		template<class LeftLazyBitset, class RightLazyBitset>
		using lazy_reordering_sign_t = typename function<name_t::lazy_reordering_sign, LeftLazyBitset, RightLazyBitset>::type;

		// Lazy computation of the number of 1 bits in the given lazy bitset.
		template<class LazyBitset>
		struct function<name_t::lazy_ones, LazyBitset> {
			typedef function type;

			template<class... Arguments>
			inline default_integral_t operator()(Arguments const &... args) const {
				return ones(LazyBitset(args...));
			}
		};

		template<default_bitset_t Bitset>
		struct function<name_t::lazy_ones, constant_bitset<Bitset> > {
			typedef constant_value<ones(Bitset)> type; // simplify
		};

		template<class LazyBitset>
		using lazy_ones_t = typename function<name_t::lazy_ones, LazyBitset>::type;

		// Lazy PLUS operations.
		template<class LeftLazyType, class RightLazyType>
		struct function<name_t::lazy_plus, LeftLazyType, RightLazyType> {
			typedef function type;

			template<class... Arguments>
			constexpr decltype(auto) operator()(Arguments const &... args) const {
				return LeftLazyType(args...) + RightLazyType(args...);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::lazy_plus, constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<LeftValue + RightValue> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::lazy_plus, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
			typedef constant_bitset<LeftBitset + RightBitset> type; // simplify
		};

		template<class LeftLazyType, class RightLazyType>
		using lazy_plus_t = typename function<name_t::lazy_plus, LeftLazyType, RightLazyType>::type;

		// Lazy MINUS operations.
		template<class LeftLazyType, class RightLazyType>
		struct function<name_t::lazy_minus, LeftLazyType, RightLazyType> {
			typedef function type;

			template<class... Arguments>
			constexpr decltype(auto) operator()(Arguments const &... args) const {
				return LeftLazyType(args...) - RightLazyType(args...);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::lazy_minus, constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<LeftValue - RightValue> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::lazy_minus, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
			typedef constant_bitset<LeftBitset - RightBitset> type; // simplify
		};

		template<class LeftLazyType, class RightLazyType>
		using lazy_minus_t = typename function<name_t::lazy_minus, LeftLazyType, RightLazyType>::type;

		// Lazy bitwise AND operations.
		template<class LeftLazyType, class RightLazyType>
		struct function<name_t::lazy_bitwise_and, LeftLazyType, RightLazyType> {
			typedef function type;

			template<class... Arguments>
			constexpr decltype(auto) operator()(Arguments const &... args) const {
				return LeftLazyType(args...) & RightLazyType(args...);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::lazy_bitwise_and, constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<LeftValue & RightValue> type; // simplify
		};

		template<class LeftLazyType>
		struct function<name_t::lazy_bitwise_and, LeftLazyType, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<class RightLazyType>
		struct function<name_t::lazy_bitwise_and, constant_value<0>, RightLazyType> {
			typedef constant_value<0> type; // simplify
		};

		template<>
		struct function<name_t::lazy_bitwise_and, constant_value<0>, constant_value<0>> {
			typedef constant_value<0> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::lazy_bitwise_and, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
			typedef constant_bitset<LeftBitset & RightBitset> type; // simplify
		};

		template<class LeftLazyType>
		struct function<name_t::lazy_bitwise_and, LeftLazyType, constant_bitset<0> > {
			typedef constant_bitset<0> type; // simplify
		};

		template<class RightLazyType>
		struct function<name_t::lazy_bitwise_and, constant_bitset<0>, RightLazyType> {
			typedef constant_bitset<0> type; // simplify
		};

		template<>
		struct function<name_t::lazy_bitwise_and, constant_bitset<0>, constant_bitset<0> > {
			typedef constant_bitset<0> type; // simplify
		};

		template<class LeftLazyType, class RightLazyType>
		using lazy_bitwise_and_t = typename function<name_t::lazy_bitwise_and, LeftLazyType, RightLazyType>::type;

		// Lazy bitwise XOR operations.
		template<class LeftLazyType, class RightLazyType>
		struct function<name_t::lazy_bitwise_xor, LeftLazyType, RightLazyType> {
			typedef function type;

			template<class... Arguments>
			constexpr decltype(auto) operator()(Arguments const &... args) const {
				return LeftLazyType(args...) ^ RightLazyType(args...);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::lazy_bitwise_xor, constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<LeftValue ^ RightValue> type; // simplify
		};

		template<class LeftLazyType>
		struct function<name_t::lazy_bitwise_xor, LeftLazyType, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		template<class RightLazyType>
		struct function<name_t::lazy_bitwise_xor, constant_value<0>, RightLazyType> {
			typedef constant_value<0> type; // simplify
		};

		template<>
		struct function<name_t::lazy_bitwise_xor, constant_value<0>, constant_value<0>> {
			typedef constant_value<0> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::lazy_bitwise_xor, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
			typedef constant_bitset<LeftBitset ^ RightBitset> type; // simplify
		};

		template<class LeftLazyType>
		struct function<name_t::lazy_bitwise_xor, LeftLazyType, constant_bitset<0> > {
			typedef constant_bitset<0> type; // simplify
		};

		template<class RightLazyType>
		struct function<name_t::lazy_bitwise_xor, constant_bitset<0>, RightLazyType> {
			typedef constant_bitset<0> type; // simplify
		};

		template<>
		struct function<name_t::lazy_bitwise_xor, constant_bitset<0>, constant_bitset<0> > {
			typedef constant_bitset<0> type; // simplify
		};

		template<class LeftLazyType, class RightLazyType>
		using lazy_bitwise_xor_t = typename function<name_t::lazy_bitwise_xor, LeftLazyType, RightLazyType>::type;

		// Lazy bitwise EQUAL operation.
		template<class LeftType, class RightType>
		struct function<name_t::lazy_eq, LeftType, RightType> {
			typedef function type;

			template<class... Arguments>
			constexpr bool operator()(Arguments const &... args) const {
				return LeftType(args...) == RightType(args...);
			}
		};

		template<class CommonType>
		struct function<name_t::lazy_eq, CommonType, CommonType> {
			typedef std::true_type type; // simplify
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::lazy_eq, constant_value<LeftValue>, constant_value<RightValue> > {
			typedef std::bool_constant<LeftValue == RightValue> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::lazy_eq, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
			typedef std::bool_constant<LeftBitset == RightBitset> type; // simplify
		};

		template<class LeftLazyType, class RightLazyType>
		using lazy_eq_t = typename function<name_t::lazy_eq, LeftLazyType, RightLazyType>::type;

		// Lazy ternary conditional operation.
		template<class LazyTest, class LazyTrueResult, class LazyFalseResult>
		struct function<name_t::lazy_if_else, LazyTest, LazyTrueResult, LazyFalseResult> {
			typedef function type;

			template<class... Arguments>
			constexpr default_bitset_t operator()(Arguments const &... args) const {
				return LazyTest(args...) ? LazyTrueResult(args...) : LazyFalseResult(args...);
			}
		};

		template<class LazyTest, class LazyCommonResult>
		struct function<name_t::lazy_if_else, LazyTest, LazyCommonResult, LazyCommonResult> {
			typedef LazyCommonResult type; // simplify
		};


		template<class LazyTrueResult, class LazyFalseResult>
		struct function<name_t::lazy_if_else, std::true_type, LazyTrueResult, LazyFalseResult> {
			typedef LazyTrueResult type; // simplify
		};

		template<class LazyTrueResult, class LazyFalseResult>
		struct function<name_t::lazy_if_else, std::false_type, LazyTrueResult, LazyFalseResult> {
			typedef LazyFalseResult type; // simplify
		};

		template<class LazyTest, class LazyTrueResult, class LazyFalseResult>
		using lazy_if_else_t = typename function<name_t::lazy_if_else, LazyTest, LazyTrueResult, LazyFalseResult>::type;

	}

}

#endif // __FUTURE_GA_EXPRESSION_HPP__
