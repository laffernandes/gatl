#ifndef __GA_CORE_EXPRESSION_HPP__
#define __GA_CORE_EXPRESSION_HPP__

namespace ga {

	namespace detail {

		// Helper for real-valued expression mappings (it is used with the product of values).
		struct value_mapping {
		};

		// The name of implemented functions.
		enum class name_t : std::uint8_t {
			reordering_sign,    //  0
			count_one_bits,     //  1

			bitwise_left_shift, //  2
			bitwise_uminus,     //  3
			bitwise_dec,        //  4
			bitwise_and,        //  5
			bitwise_or,         //  6
			bitwise_xor,        //  7

			equal,              //  8
			less_or_equal,      //  9

			logical_and,        // 10
			logical_or,         // 11

			if_else,            // 12

			absolute,           // 13

			exponential,        // 14
			logarithm,          // 15

			cosine,             // 16
			sine,               // 17
			tangent,            // 18

			hyperbolic_cosine,  // 19
			hyperbolic_sine,    // 20
			hyperbolic_tangent, // 21

			power,              // 22
			mul,                // 23
			add                 // 24
		};

		// Returns whether the given expression has stored entries.
		template<class Expression>
		struct has_stored_entries;

		template<class Expression>
		constexpr bool has_stored_entries_v = has_stored_entries<Expression>::value;

		// Returns whether the given expression is compile-time defined.
		template<class Expression>
		struct is_constant_expression;

		template<class Expression>
		constexpr bool is_constant_expression_v = is_constant_expression<Expression>::value;

		// Returns whether the given expression is a function with the given name.
		template<name_t Name, class Expression>
		struct is_function;

		template<name_t Name, class Expression>
		constexpr bool is_function_v = is_function<Name, Expression>::value;

		// Returns whether the given expression is non-negative for sure.
		template<class Expression>
		struct is_non_negative;

		template<class Expression>
		constexpr bool is_non_negative_v = is_non_negative<Expression>::value;

		// Returns the possible grades of a given basis blade.
		template<class BasisBlade>
		struct possible_grades;

		template<class BasisBlade>
		constexpr default_bitset_t possible_grades_v = possible_grades<BasisBlade>::value;

		// Product operation.
		template<class LeftExpression, class RightExpression, class Mapping>
		struct _product;

		template<class LeftExpression, class RightExpression, class Mapping>
		using product_t = typename _product<LeftExpression, RightExpression, Mapping>::type;

		// Addition operation.
		template<class LeftExpression, class RightExpression>
		struct _addition;

		template<class LeftExpression, class RightExpression>
		using addition_t = typename _addition<LeftExpression, RightExpression>::type;

	}

	namespace detail {

		// Tag of variables/arguments.
		typedef std::uint16_t tag_t;

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

		// Lazy computation of the sign induced by the canonical reordering of basis vectors in bilinear products.
		template<class LeftBitset, class RightBitset>
		using reordering_sign = function<name_t::reordering_sign, LeftBitset, RightBitset>;

		template<class LeftBitset, class RightBitset>
		using reordering_sign_t = typename reordering_sign<LeftBitset, RightBitset>::type;

		// Lazy computation of the number of 1 bits in the given lazy bitset.
		template<class Bitset>
		using count_one_bits = function<name_t::count_one_bits, Bitset>;

		template<class Bitset>
		using count_one_bits_t = typename count_one_bits<Bitset>::type;

		// Lazy bitwise LEFT SHIFT operations.
		template<class LeftBitset, class RightValue>
		using bitwise_left_shift = function<name_t::bitwise_left_shift, LeftBitset, RightValue>;

		template<class LeftBitset, class RightValue>
		using bitwise_left_shift_t = typename bitwise_left_shift<LeftBitset, RightValue>::type;

		// Lazy bitwise UNARY MINUS operations.
		template<class Bitset>
		using bitwise_uminus = function<name_t::bitwise_uminus, Bitset>;

		template<class Bitset>
		using bitwise_uminus_t = typename bitwise_uminus<Bitset>::type;

		// Lazy bitwise DECREMENT operations.
		template<class Bitset>
		using bitwise_dec = function<name_t::bitwise_dec, Bitset>;

		template<class Bitset>
		using bitwise_dec_t = typename bitwise_dec<Bitset>::type;

		// Lazy bitwise AND operations.
		template<class LeftType, class RightType>
		using bitwise_and = function<name_t::bitwise_and, LeftType, RightType>;

		template<class LeftType, class RightType>
		using bitwise_and_t = typename bitwise_and<LeftType, RightType>::type;

		// Lazy bitwise OR operations.
		template<class LeftType, class RightType>
		using bitwise_or = function<name_t::bitwise_or, LeftType, RightType>;

		template<class LeftType, class RightType>
		using bitwise_or_t = typename bitwise_or<LeftType, RightType>::type;

		// Lazy bitwise XOR operations.
		template<class LeftType, class RightType>
		using bitwise_xor = function<name_t::bitwise_xor, LeftType, RightType>;

		template<class LeftType, class RightType>
		using bitwise_xor_t = typename bitwise_xor<LeftType, RightType>::type;

		// Lazy relational EQUAL TO operation.
		template<class LeftType, class RightType>
		using equal = function<name_t::equal, LeftType, RightType>;

		template<class LeftType, class RightType>
		using equal_t = typename equal<LeftType, RightType>::type;

		// Lazy relational LESS THAN OR EQUAL TO operation.
		template<class LeftType, class RightType>
		using less_or_equal = function<name_t::less_or_equal, LeftType, RightType>;

		template<class LeftType, class RightType>
		using less_or_equal_t = typename less_or_equal<LeftType, RightType>::type;

		// Lazy logical AND operation.
		template<class LeftType, class RightType>
		using logical_and = function<name_t::logical_and, LeftType, RightType>;

		template<class LeftType, class RightType>
		using logical_and_t = typename logical_and<LeftType, RightType>::type;

		// Lazy logical OR operation.
		template<class LeftType, class RightType>
		using logical_or = function<name_t::logical_or, LeftType, RightType>;

		template<class LeftType, class RightType>
		using logical_or_t = typename logical_or<LeftType, RightType>::type;

		// Lazy ternary conditional operation.
		template<class Test, class TrueValue, class FalseValue>
		using if_else = function<name_t::if_else, Test, TrueValue, FalseValue>;

		template<class Test, class TrueValue, class FalseValue>
		using if_else_t = typename if_else<Test, TrueValue, FalseValue>::type;

		// Absolute value of scalar-valued expressions.
		template<class Value>
		using absolute = function<name_t::absolute, Value>;

		template<class Value>
		using absolute_t = typename absolute<Value>::type;

		// The base-e exponential function of scalar-valued expressions.
		template<class Value>
		using exponential = function<name_t::exponential, Value>;

		template<class Value>
		using exponential_t = typename exponential<Value>::type;

		// The natural logarithm of scalar-valued expressions.
		template<class Value>
		using logarithm = function<name_t::logarithm, Value>;

		template<class Value>
		using logarithm_t = typename logarithm<Value>::type;

		// Cosine of scalar-valued expressions.
		template<class Value>
		using cosine = function<name_t::cosine, Value>;

		template<class Value>
		using cosine_t = typename cosine<Value>::type;

		// Sine of scalar-valued expressions.
		template<class Value>
		using sine = function<name_t::sine, Value>;

		template<class Value>
		using sine_t = typename sine<Value>::type;

		// Tangent of scalar-valued expressions.
		template<class Value>
		using tangent = function<name_t::tangent, Value>;

		template<class Value>
		using tangent_t = typename tangent<Value>::type;

		// Hyperbolic cosine of scalar-valued expressions.
		template<class Value>
		using hyperbolic_cosine = function<name_t::hyperbolic_cosine, Value>;

		template<class Value>
		using hyperbolic_cosine_t = typename hyperbolic_cosine<Value>::type;

		// Hyperbolic sine of scalar-valued expressions.
		template<class Value>
		using hyperbolic_sine = function<name_t::hyperbolic_sine, Value>;

		template<class Value>
		using hyperbolic_sine_t = typename hyperbolic_sine<Value>::type;

		// Hyperbolic tangent of scalar-valued expressions.
		template<class Value>
		using hyperbolic_tangent = function<name_t::hyperbolic_tangent, Value>;

		template<class Value>
		using hyperbolic_tangent_t = typename hyperbolic_tangent<Value>::type;

		// Exponentiation of real-valued expressions.
		template<class LeftArgument, class RightArgument>
		using power = function<name_t::power, LeftArgument, RightArgument>;

		template<class LeftArgument, class RightArgument>
		struct _power; //TODO Is it a problem?

		template<class LeftArgument, class RightArgument>
		using power_t = typename _power<LeftArgument, RightArgument>::type;

		// Multiplication of real-valued expressions.
		template<class... Arguments>
		using mul = function<name_t::mul, Arguments...>;

		template<class... Arguments>
		using mul_t = typename function<name_t::mul, Arguments...>::type;
		
		// Addition of real-valued expressions and/or multivector entries.
		template<class... Arguments>
		using add = function<name_t::add, Arguments...>;

		template<class... Arguments>
		using add_t = typename function<name_t::add, Arguments...>::type;

		// Specializations of reordering_sign<LeftBitset, RightBitset>.
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

		// Specializations of count_one_bits<Bitset>.
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

		// Specializations of bitwise_left_shift<LeftBitset, RightValue>.
		template<class LeftBitset, class RightValue>
		struct function<name_t::bitwise_left_shift, LeftBitset, RightValue> {
			typedef std::conditional_t<
				std::is_same_v<LeftBitset, constant_bitset<default_bitset_t(0)> > || std::is_same_v<RightValue, constant_value<0> >,
				LeftBitset, // simplify
				function // default
			> type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return LeftBitset::eval<LowerTag, UpperTag>(args) << RightValue::eval<LowerTag, UpperTag>(args);
			}
		};

		template<default_bitset_t LeftBitset, default_integral_t RightValue>
		struct function<name_t::bitwise_left_shift, constant_bitset<LeftBitset>, constant_value<RightValue> > {
			typedef constant_bitset<(LeftBitset << RightValue)> type; // simplify
		};

		// Specializations of bitwise_uminus<Bitset>.
		template<class Bitset>
		struct function<name_t::bitwise_uminus, Bitset> {
			typedef function type;
				
			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static default_bitset_t eval(std::tuple<InputTypes...> const &args) {
				return -Bitset::eval<LowerTag, UpperTag>(args);
			}
		};

		template<class Bitset>
		struct function<name_t::bitwise_uminus, bitwise_uminus<Bitset> > {
			typedef Bitset type; // simplify
		};

		template<default_bitset_t Bitset>
		struct function<name_t::bitwise_uminus, constant_bitset<Bitset> > {
			typedef constant_bitset<-std::make_signed_t<default_bitset_t>(Bitset)> type; // simplify
		};

		// Specializations of bitwise_dec<Bitset>.
		template<class Bitset>
		struct function<name_t::bitwise_dec, Bitset> {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static default_bitset_t eval(std::tuple<InputTypes...> const &args) {
				return Bitset::eval<LowerTag, UpperTag>(args) - default_bitset_t(1);
			}
		};

		template<default_bitset_t Bitset>
		struct function<name_t::bitwise_dec, constant_bitset<Bitset> > {
			typedef constant_bitset<Bitset - default_bitset_t(1)> type; // simplify
		};

		// Specializations of bitwise_and<LeftType, RightType>.
		template<class LeftType, class RightType>
		struct function<name_t::bitwise_and, LeftType, RightType> {
			typedef std::conditional_t<
				std::is_same_v<LeftType, constant_value<0> > || std::is_same_v<RightType, constant_value<0> >,
				constant_value<0>, // simplify
				std::conditional_t<
					std::is_same_v<LeftType, constant_bitset<default_bitset_t(0)> > || std::is_same_v<RightType, constant_bitset<default_bitset_t(0)> >,
					constant_bitset<default_bitset_t(0)>, // simplify
					function // default
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

		// Specializations of bitwise_or<LeftType, RightType>.
		template<class LeftType, class RightType>
		struct function<name_t::bitwise_or, LeftType, RightType> {
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
				return LeftType::eval<LowerTag, UpperTag>(args) | RightType::eval<LowerTag, UpperTag>(args);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::bitwise_or, constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<LeftValue | RightValue> type; // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::bitwise_or, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > {
			typedef constant_bitset<LeftBitset | RightBitset> type; // simplify
		};

		// Specialization bitwise_xor<LeftType, RightType>.
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

		// Specializations of equal<LeftType, RightType>.
		template<class LeftType, class RightType>
		struct function<name_t::equal, LeftType, RightType> {
			typedef std::conditional_t<
				std::is_same_v<LeftType, RightType> && !has_stored_entries_v<LeftType>,
				std::true_type, // simplify
				std::conditional_t<
					!std::is_same_v<LeftType, RightType> && is_constant_expression_v<LeftType> && is_constant_expression_v<RightType>,
					std::false_type, // simplify
					function // default
				>
			> type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static bool eval(std::tuple<InputTypes...> const &args) {
				return LeftType::eval<LowerTag, UpperTag>(args) == RightType::eval<LowerTag, UpperTag>(args);
			}
		};

		// Specializations of less_or_equal<LeftType, RightType>.
		template<class LeftType, class RightType>
		struct function<name_t::less_or_equal, LeftType, RightType> {
			typedef std::conditional_t<
				std::is_same_v<LeftType, RightType> && !has_stored_entries_v<LeftType>,
				std::true_type, // simplify
				function // default
			> type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static bool eval(std::tuple<InputTypes...> const &args) {
				return LeftType::eval<LowerTag, UpperTag>(args) <= RightType::eval<LowerTag, UpperTag>(args);
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct function<name_t::less_or_equal, constant_value<LeftValue>, constant_value<RightValue> > :
			std::bool_constant<(LeftValue <= RightValue)> { // simplify
		};

		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct function<name_t::less_or_equal, constant_bitset<LeftBitset>, constant_bitset<RightBitset> > :
			std::bool_constant<(LeftBitset <= RightBitset)> { // simplify
		};

		// Specializations of logical_and<LeftType, RightType>.
		template<class LeftType, class RightType>
		struct function<name_t::logical_and, LeftType, RightType> {
			typedef std::conditional_t<
				std::is_same_v<LeftType, RightType> && !has_stored_entries_v<LeftType>,
				LeftType, // simplify
				function // default
			> type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static bool eval(std::tuple<InputTypes...> const &args) {
				return LeftType::eval<LowerTag, UpperTag>(args) && RightType::eval<LowerTag, UpperTag>(args);
			}
		};

		template<class LeftType>
		struct function<name_t::logical_and, LeftType, std::true_type> {
			typedef LeftType type; // simplify
		};

		template<class RightType>
		struct function<name_t::logical_and, std::true_type, RightType> {
			typedef RightType type; // simplify
		};

		template<class LeftType>
		struct function<name_t::logical_and, LeftType, std::false_type> :
			std::false_type { // simplify
		};

		template<class RightType>
		struct function<name_t::logical_and, std::false_type, RightType> :
			std::false_type { // simplify
		};
		
		template<>
		struct function<name_t::logical_and, std::true_type, std::true_type> :
			std::true_type { // simplify
		};

		template<>
		struct function<name_t::logical_and, std::false_type, std::true_type> :
			std::false_type { // simplify
		};

		template<>
		struct function<name_t::logical_and, std::true_type, std::false_type> :
			std::false_type { // simplify
		};

		template<>
		struct function<name_t::logical_and, std::false_type, std::false_type> :
			std::false_type { // simplify
		};

		// Specializations of logical_or<LeftType, RightType>.
		template<class LeftType, class RightType>
		struct function<name_t::logical_or, LeftType, RightType> {
			typedef function type; // default

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static bool eval(std::tuple<InputTypes...> const &args) {
				return LeftType::eval<LowerTag, UpperTag>(args) || RightType::eval<LowerTag, UpperTag>(args);
			}
		};

		template<class LeftType>
		struct function<name_t::logical_or, LeftType, std::false_type> {
			typedef LeftType type; // simplify
		};

		template<class RightType>
		struct function<name_t::logical_or, std::false_type, RightType> {
			typedef RightType type; // simplify
		};

		template<class LeftType>
		struct function<name_t::logical_or, LeftType, std::true_type> :
			std::true_type { // simplify
		};

		template<class RightType>
		struct function<name_t::logical_or, std::true_type, RightType> :
			std::true_type { // simplify
		};

		template<>
		struct function<name_t::logical_or, std::true_type, std::true_type> :
			std::true_type { // simplify
		};

		template<>
		struct function<name_t::logical_or, std::false_type, std::true_type> :
			std::true_type { // simplify
		};

		template<>
		struct function<name_t::logical_or, std::true_type, std::false_type> :
			std::true_type { // simplify
		};

		template<>
		struct function<name_t::logical_or, std::false_type, std::false_type> :
			std::false_type { // simplify
		};

		// Specializations of if_else<Test, TrueValue, FalseValue>.
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

		// Specializations of absolute<Value>.
		template<class Value>
		struct function<name_t::absolute, Value> {
			typedef std::conditional_t<
				is_non_negative_v<Value>,
				Value,
				std::conditional_t<
					is_constant_expression_v<Value> && !(is_function_v<name_t::add, Value> || is_function_v<name_t::if_else, Value>),
					product_t<constant_value<-1>, Value, value_mapping>,
					function
				>
			> type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return abs(Value::eval<LowerTag, UpperTag>(args));
			}
		};

		// Specializations of exponential<Value>.
		template<class Value>
		struct function<name_t::exponential, Value> {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return exp(Value::eval<LowerTag, UpperTag>(args));
			}
		};

		template<class Value>
		struct function<name_t::exponential, logarithm<Value> > {
			typedef Value type;
		};

		// Specializations of logarithm<Value>.
		template<class Value>
		struct function<name_t::logarithm, Value> {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return log(Value::eval<LowerTag, UpperTag>(args));
			}
		};

		template<class Value>
		struct function<name_t::logarithm, exponential<Value> > {
			typedef Value type;
		};

		// Specializations of cosine<Value>.
		template<class Value>
		struct function<name_t::cosine, Value> {
			typedef function type; //TODO Not supported yet (simplifications)

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return cos(Value::eval<LowerTag, UpperTag>(args));
			}
		};

		// Specializations of sine<Value>.
		template<class Value>
		struct function<name_t::sine, Value> {
			typedef function type; //TODO Not supported yet (simplifications)

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return sin(Value::eval<LowerTag, UpperTag>(args));
			}
		};

		// Specializations of tangent<Value>.
		template<class Value>
		struct function<name_t::tangent, Value> {
			typedef function type; //TODO Not supported yet (simplifications)

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return tan(Value::eval<LowerTag, UpperTag>(args));
			}
		};

		// Specializations of hyperbolic_cosine<Value>.
		template<class Value>
		struct function<name_t::hyperbolic_cosine, Value> {
			typedef function type; //TODO Not supported yet (simplifications)

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return cosh(Value::eval<LowerTag, UpperTag>(args));
			}
		};

		// Specializations of hyperbolic_sine<Value>.
		template<class Value>
		struct function<name_t::hyperbolic_sine, Value> {
			typedef function type; //TODO Not supported yet (simplifications)

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return sinh(Value::eval<LowerTag, UpperTag>(args));
			}
		};

		// Specializations of hyperbolic_tangent<Value>.
		template<class Value>
		struct function<name_t::hyperbolic_tangent, Value> {
			typedef function type; //TODO Not supported yet (simplifications)

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return tanh(Value::eval<LowerTag, UpperTag>(args));
			}
		};

		// Specializations of power<LeftArgument, RightArgument>.
		template<class LeftArgument, class RightArgument>
		struct function<name_t::power, LeftArgument, RightArgument> {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return pow(LeftArgument::eval<LowerTag, UpperTag>(args), RightArgument::eval<LowerTag, UpperTag>(args));
			}

			static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
			static_assert(!std::is_same_v<RightArgument, constant_value<0> >, "The right-hand side argument cannot be ga::detail::constant_value<0>.");
			static_assert(!std::is_same_v<RightArgument, constant_value<1> >, "The right-hand side argument cannot be ga::detail::constant_value<1>.");
		};

		template<class LeftArgument>
		struct function<name_t::power, LeftArgument, constant_value<-1> > {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return 1 / cast_to_floating_point(LeftArgument::eval<LowerTag, UpperTag>(args));
			}

			static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
		};

		template<class LeftArgument>
		struct function<name_t::power, LeftArgument, constant_value<2> > {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return square(LeftArgument::eval<LowerTag, UpperTag>(args));
			}

			static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
		};

		template<class LeftArgument>
		struct function<name_t::power, LeftArgument, power<constant_value<2>, constant_value<-1> > > {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return sqrt(LeftArgument::eval<LowerTag, UpperTag>(args));
			}

			static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
		};

		template<class LeftArgument>
		struct function<name_t::power, LeftArgument, power<constant_value<3>, constant_value<-1> > > {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return cbrt(LeftArgument::eval<LowerTag, UpperTag>(args));
			}

			static_assert(!std::is_same_v<LeftArgument, constant_value<0> >, "The left-hand side argument cannot be ga::detail::constant_value<0>.");
		};

		// Specializations of mul<Arguments...>.
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

		template<class... NextArguments>
		struct function<name_t::mul, constant_value<-1>, NextArguments...> {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return -mul_t<NextArguments...>::eval<LowerTag, UpperTag>(args);
			}

			static_assert(!is_any_v<constant_value<0>, NextArguments...>, "The argument ga::detail::constant_value<0> is invalid.");
			static_assert(!is_any_v<constant_value<1>, NextArguments...>, "The argument ga::detail::constant_value<1> is invalid.");
		};

		template<class LeftArgument, class RightArgument>
		struct function<name_t::mul, LeftArgument, power<RightArgument, constant_value<-1> > > {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return LeftArgument::eval<LowerTag, UpperTag>(args) / RightArgument::eval<LowerTag, UpperTag>(args);
			}

			static_assert(!is_any_v<constant_value<0>, LeftArgument>, "The argument ga::detail::constant_value<0> is invalid.");
			static_assert(!is_any_v<constant_value<1>, LeftArgument>, "The argument ga::detail::constant_value<1> is invalid.");
		};

		template<class RightArgument>
		struct function<name_t::mul, constant_value<-1>, power<RightArgument, constant_value<-1> > > {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return -power<RightArgument, constant_value<-1> >::eval<LowerTag, UpperTag>(args);
			}
		};

		template<class Argument>
		struct function<name_t::mul, Argument> {
			typedef Argument type; // simplify
		};

		template<>
		struct function<name_t::mul> {
			typedef constant_value<0> type; // simplify
		};

		// Specializations of add<Arguments...>.
		template<class Argument, class... NextArguments>
		struct function<name_t::add, Argument, NextArguments...> {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return Argument::eval<LowerTag, UpperTag>(args) + add_t<NextArguments...>::eval<LowerTag, UpperTag>(args);
			}

			static_assert(!is_any_v<constant_value<0>, Argument, NextArguments...>, "The argument ga::detail::constant_value<0> is invalid.");
		};

		template<class LeftArgument, class... RightArguments>
		struct function<name_t::add, LeftArgument, mul<constant_value<-1>, RightArguments...> > {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return LeftArgument::eval<LowerTag, UpperTag>(args) - mul_t<RightArguments...>::eval<LowerTag, UpperTag>(args);
			}

			static_assert(!is_any_v<constant_value<0>, LeftArgument>, "The argument ga::detail::constant_value<0> is invalid.");
		};

		template<class... LeftArguments, class... RightArguments>
		struct function<name_t::add, mul<constant_value<-1>, LeftArguments...>, RightArguments...> {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return add_t<RightArguments...>::eval<LowerTag, UpperTag>(args) - mul_t<LeftArguments...>::eval<LowerTag, UpperTag>(args);
			}
		};

		template<class... LeftArguments, class... RightArguments>
		struct function<name_t::add, mul<constant_value<-1>, LeftArguments...>, mul<constant_value<-1>, RightArguments...> > {
			typedef function type;

			template<tag_t LowerTag, tag_t UpperTag, class... InputTypes>
			constexpr static decltype(auto) eval(std::tuple<InputTypes...> const &args) {
				return -(mul_t<LeftArguments...>::eval<LowerTag, UpperTag>(args) + mul_t<RightArguments...>::eval<LowerTag, UpperTag>(args));
			}
		};

		template<class Argument>
		struct function<name_t::add, Argument> {
			typedef Argument type; // simplify
		};

		template<>
		struct function<name_t::add> {
			typedef constant_value<0> type; // simplify
		};

	}

}

#endif // __GA_CORE_EXPRESSION_HPP__
