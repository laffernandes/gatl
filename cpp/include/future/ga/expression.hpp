#ifndef __FUTURE_GA_EXPRESSION_HPP__
#define __FUTURE_GA_EXPRESSION_HPP__

namespace ga {

	namespace detail {

		// Constant integer value defined in compilation time.
		template<default_integral_t Value>
		using constant = std::integral_constant<default_integral_t, Value>;

		// Real value (or variable) defined in runtime.
		template<class LazyCoefficient>
		struct value {
		};

		// A basis blade multiplied by some real-valued expression (the coefficient).
		template<class Coefficient, class BasisBlade>
		struct component {
			static_assert(!std::is_same_v<Coefficient, constant<0> >, "The coefficient cannot be a ga::detail::constant<0> expression.");
			static_assert(possible_grades_v<BasisBlade> != default_bitset_t(0), "The basis blade must have at least one possible grade.");
			static_assert(possible_grades_v<BasisBlade> != default_bitset_t(1), "Grade 0 (zero) is not valid because real values are not representd by ga::detail::component<Coefficient, BasisBlade> types.");
		};

		// The name of implemented functions.
		enum class name_t : std::int8_t { add, mul, power, lazy_reordering_sign, lazy_ones, lazy_if_else, lazy_eq, lazy_plus, lazy_minus, lazy_bitwise_and, lazy_bitwise_xor };

		// A real-valued function of a bitset function.
		template<name_t Name, class... Arguments>
		struct function;

		// Basis blade defined in compilation time.
		template<default_bitset_t BasisVectors>
		struct constant_basis_blade {
		};

		// Basis blade defined in runtime.
		template<default_bitset_t PossibleGrades, class LazyBasisVectors>
		struct dynamic_basis_blade {
		};

		// A flag to indicate that the coefficient or basis blade is stored.
		struct stored {
		};

		// Lazy getter for stored coefficient values.
		template<id_t Id, std::size_t Index>
		struct lazy_get_coefficient {
			typedef lazy_get_coefficient type;

			template<class... Arguments>
			inline decltype(auto) operator()(Arguments const &... args) const {
				return 0; //TODO Implementar
			}
		};

		// Lazy getter for stored basis vectors values.
		template<id_t Id, std::size_t Index>
		struct lazy_get_basis_vectors {
			typedef lazy_get_basis_vectors type;

			template<class... Arguments>
			inline default_bitset_t operator()(Arguments const &... args) const {
				return 0; //TODO Implementar
			}
		};

		// Compile-time definition of a bitset to be used in lazy expressions.
		template<default_bitset_t Bitset>
		struct lazy_constant_bitset {
			typedef lazy_constant_bitset type;

			template<class... Arguments>
			constexpr default_bitset_t operator()(Arguments const &... args) const {
				return Bitset;
			}
		};

		// Addition of real-valued expressions and/or multivector components.
		template<class... Arguments>
		struct function<name_t::add, Arguments...> {
			typedef function<name_t::add, Arguments...> type;

			static_assert(!is_any_v<constant<0>, Arguments...>, "The argument ga::detail::constant<0> is invalid.");
			//TODO static_assert(!is_lazy_add_v<left_type>, "The left-hand side argument cannot be a ga::lazy::add<...> expression.");
			//TODO static_assert(le_v<left_type, typename right_type::left_type>, "The arguments do not respect the expected ordering for lazy expressions.");
		};

		template<class Argument>
		struct function<name_t::add, Argument> {
			typedef Argument type; // simplify
		};

		template<>
		struct function<name_t::add> {
			typedef constant<0> type; // simplify
		};

		template<class... Arguments>
		using add = function<name_t::add, Arguments...>;

		template<class... Arguments>
		using add_t = typename function<name_t::add, Arguments...>::type;

		// Multiplication of real-valued expressions.
		template<class... Arguments>
		struct function<name_t::mul, Arguments...> {
			typedef function<name_t::mul, Arguments...> type;

			static_assert(!is_any_v<constant<0>, Arguments...>, "The argument ga::detail::constant<0> is invalid.");
			static_assert(!is_any_v<constant<1>, Arguments...>, "The argument ga::detail::constant<1> is invalid.");
			//TODO static_assert(!is_lazy_mul_v<left_type>, "The left-hand side argument cannot be a ga::lazy::mul<...> expression.");
			//TODO static_assert(le_v<left_type, typename right_type::left_type>, "The arguments do not respect the expected ordering for lazy expressions.");
		};

		template<class Argument>
		struct function<name_t::mul, Argument> {
			typedef Argument type; // simplify
		};

		template<>
		struct function<name_t::mul> {
			typedef constant<0> type; // simplify
		};

		template<class... Arguments>
		using mul = function<name_t::mul, Arguments...>;

		template<class... Arguments>
		using mul_t = typename function<name_t::mul, Arguments...>::type;

		// Exponentiation of real-valued expressions.
		template<class LeftArgument, class RightArgument>
		struct function<name_t::power, LeftArgument, RightArgument> {
			typedef function<name_t::power, LeftArgument, RightArgument> type;

			static_assert(!std::is_same_v<LeftArgument, constant<0> >, "The left-hand side argument cannot be ga::detail::constant<0>.");
			static_assert(!std::is_same_v<RightArgument, constant<0> >, "The right-hand side argument cannot be ga::detail::constant<0>.");
			static_assert(!std::is_same_v<RightArgument, constant<1> >, "The right-hand side argument cannot be ga::detail::constant<1>.");
		};

		template<class LeftArgument, class RightArgument>
		using power = function<name_t::power, LeftArgument, RightArgument>;

		template<class LeftArgument, class RightArgument>
		using power_t = typename function<name_t::power, LeftArgument, RightArgument>::type;

		// Lazy computation of the sign induced by the canonical reordering of basis vectors in bilinear products.
		template<class LeftLazyBitset, class RightLazyBitset>
		struct function<name_t::lazy_reordering_sign, LeftLazyBitset, RightLazyBitset> {
			typedef function<name_t::lazy_reordering_sign, LeftLazyBitset, RightLazyBitset> type; //TODO Como lidar com a avaliação parcial da lazy expression?

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
		struct function<name_t::lazy_reordering_sign, lazy_constant_bitset<LeftBitset>, lazy_constant_bitset<RightBitset> > {
			typedef constant<((swaps_count((LeftBitset >> 1), RightBitset) & 1) != 0) ? -1 : 1> type; // simplify
		};

		template<class LeftLazyBitset, class RightLazyBitset>
		using lazy_reordering_sign_t = typename function<name_t::lazy_reordering_sign, LeftLazyBitset, RightLazyBitset>::type;

		// Lazy computation of the number of 1 bits in the given lazy bitset.
		template<class LazyBitset>
		struct function<name_t::lazy_ones, LazyBitset> {
			typedef function<name_t::lazy_ones, LazyBitset> type;

			template<class... Arguments>
			inline default_integral_t operator()(Arguments const &... args) const {
				return ones(LazyBitset(args...));
			}
		};

		template<default_bitset_t Bitset>
		struct function<name_t::lazy_ones, lazy_constant_bitset<Bitset> > {
			typedef constant<ones(Bitset)> type; // simplify
		};

		template<class LazyBitset>
		using lazy_ones_t = typename function<name_t::lazy_ones, LazyBitset>::type;

		// Lazy ternary conditional operation.
		template<class LazyTest, class LazyTrueResult, class LazyFalseResult>
		struct function<name_t::lazy_if_else, LazyTest, LazyTrueResult, LazyFalseResult> {
			typedef function<name_t::lazy_if_else, LazyTest, LazyTrueResult, LazyFalseResult> type;
			
			template<class... Arguments>
			constexpr default_bitset_t operator()(Arguments const &... args) const {
				return LazyTest(args...) ? LazyTrueResult(args...) : LazyFalseResult(args...);
			}
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

		// Lazy bitwise EQUAL operation.
		template<class CommonType>
		struct function<name_t::lazy_eq, CommonType, CommonType> {
			typedef std::true_type type; // simplify
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::lazy_eq, constant<LeftValue>, constant<RightValue> > {
			typedef std::bool_constant<LeftValue == RightValue> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::lazy_eq, lazy_constant_bitset<LeftBitset>, lazy_constant_bitset<RightBitset> > {
			typedef std::bool_constant<LeftBitset == RightBitset> type; // simplify
		};

		template<class LeftLazyType, class RightLazyType>
		using lazy_eq_t = typename function<name_t::lazy_eq, LeftLazyType, RightLazyType>::type;

		// Lazy PLUS operations.
		template<class LeftLazyType, class RightLazyType>
		struct function<name_t::lazy_plus, LeftLazyType, RightLazyType> {
			typedef function<name_t::lazy_plus, LeftLazyType, RightLazyType> type;

			template<class... Arguments>
			constexpr decltype(auto) operator()(Arguments const &... args) const {
				return LeftLazyType(args...) + RightLazyType(args...);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::lazy_plus, constant<LeftValue>, constant<RightValue> > {
			typedef constant<LeftValue + RightValue> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::lazy_plus, lazy_constant_bitset<LeftBitset>, lazy_constant_bitset<RightBitset> > {
			typedef lazy_constant_bitset<LeftBitset + RightBitset> type; // simplify
		};

		template<class LeftLazyType, class RightLazyType>
		using lazy_plus_t = typename function<name_t::lazy_plus, LeftLazyType, RightLazyType>::type;

		// Lazy MINUS operations.
		template<class LeftLazyType, class RightLazyType>
		struct function<name_t::lazy_minus, LeftLazyType, RightLazyType> {
			typedef function<name_t::lazy_minus, LeftLazyType, RightLazyType> type;

			template<class... Arguments>
			constexpr decltype(auto) operator()(Arguments const &... args) const {
				return LeftLazyType(args...) - RightLazyType(args...);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::lazy_minus, constant<LeftValue>, constant<RightValue> > {
			typedef constant<LeftValue - RightValue> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::lazy_minus, lazy_constant_bitset<LeftBitset>, lazy_constant_bitset<RightBitset> > {
			typedef lazy_constant_bitset<LeftBitset - RightBitset> type; // simplify
		};

		template<class LeftLazyType, class RightLazyType>
		using lazy_minus_t = typename function<name_t::lazy_minus, LeftLazyType, RightLazyType>::type;

		// Lazy bitwise AND operations.
		template<class LeftLazyType, class RightLazyType>
		struct function<name_t::lazy_bitwise_and, LeftLazyType, RightLazyType> {
			typedef function<name_t::lazy_bitwise_and, LeftLazyType, RightLazyType> type;

			template<class... Arguments>
			constexpr decltype(auto) operator()(Arguments const &... args) const {
				return LeftLazyType(args...) & RightLazyType(args...);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::lazy_bitwise_and, constant<LeftValue>, constant<RightValue> > {
			typedef constant<LeftValue & RightValue> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::lazy_bitwise_and, lazy_constant_bitset<LeftBitset>, lazy_constant_bitset<RightBitset> > {
			typedef lazy_constant_bitset<LeftBitset & RightBitset> type; // simplify
		};

		template<class LeftLazyType, class RightLazyType>
		using lazy_bitwise_and_t = typename function<name_t::lazy_bitwise_and, LeftLazyType, RightLazyType>::type;

		// Lazy bitwise XOR operations.
		template<class LeftLazyType, class RightLazyType>
		struct function<name_t::lazy_bitwise_xor, LeftLazyType, RightLazyType> {
			typedef function<name_t::lazy_bitwise_xor, LeftLazyType, RightLazyType> type;

			template<class... Arguments>
			constexpr decltype(auto) operator()(Arguments const &... args) const {
				return LeftLazyType(args...) ^ RightLazyType(args...);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::lazy_bitwise_xor, constant<LeftValue>, constant<RightValue> > {
			typedef constant<LeftValue ^ RightValue> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::lazy_bitwise_xor, lazy_constant_bitset<LeftBitset>, lazy_constant_bitset<RightBitset> > {
			typedef lazy_constant_bitset<LeftBitset ^ RightBitset> type; // simplify
		};

		template<class LeftLazyType, class RightLazyType>
		using lazy_bitwise_xor_t = typename function<name_t::lazy_bitwise_xor, LeftLazyType, RightLazyType>::type;

		// Helper structure to simplify the implementation of some traits.
		template<class... Arguments>
		struct _arguments_list {
		};

	}

}

#endif // __FUTURE_GA_EXPRESSION_HPP__
