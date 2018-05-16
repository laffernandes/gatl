#ifndef __FUTURE_GA_CLIFFORD_EXPRESSION_HPP__
#define __FUTURE_GA_CLIFFORD_EXPRESSION_HPP__

namespace ga {

	namespace detail {

		// Returns the number of values stored by the given expression.
		template<class... Expressions>
		struct count_stored_values;

		template<class... Expressions>
		constexpr std::size_t count_stored_values_v = count_stored_values<Expressions...>::value;

		template<class Expression, class... NextExpressions>
		struct count_stored_values<Expression, NextExpressions...> {
			constexpr static std::size_t value = count_stored_values_v<Expression> + count_stored_values_v<NextExpressions...>; // recursion
		};

		template<>
		struct count_stored_values<> {
			constexpr static std::size_t value = 0; // end of recursion
		};

		template<class Expression>
		struct count_stored_values<Expression> {
			constexpr static std::size_t value = 0; // default
		};

		template<>
		struct count_stored_values<stored_value> {
			constexpr static std::size_t value = 1;
		};

		template<default_bitset_t PossibleGrades, class LazyBitset>
		struct count_stored_values<dynamic_basis_blade<PossibleGrades, LazyBitset> > {
			constexpr static std::size_t value = count_stored_values_v<LazyBitset>;
		};

		template<class Coefficient, class BasisBlade>
		struct count_stored_values<component<Coefficient, BasisBlade> > {
			constexpr static std::size_t value = count_stored_values_v<Coefficient> + count_stored_values_v<BasisBlade>;
		};

		template<name_t Name, class... Arguments>
		struct count_stored_values<function<Name, Arguments...> > {
			constexpr static std::size_t value = count_stored_values_v<Arguments...>;
		};

		// Returns the number of bitsets stored by the given expression.
		template<class... Expressions>
		struct count_stored_bitsets;

		template<class... Expressions>
		constexpr std::size_t count_stored_bitsets_v = count_stored_bitsets<Expressions...>::value;

		template<class Expression, class... NextExpressions>
		struct count_stored_bitsets<Expression, NextExpressions...> {
			constexpr static std::size_t value = count_stored_bitsets_v<Expression> + count_stored_bitsets_v<NextExpressions...>; // recursion
		};

		template<>
		struct count_stored_bitsets<> {
			constexpr static std::size_t value = 0; // end of recursion
		};

		template<class Expression>
		struct count_stored_bitsets<Expression> {
			constexpr static std::size_t value = 0; // default
		};

		template<>
		struct count_stored_bitsets<stored_bitset> {
			constexpr static std::size_t value = 1;
		};

		template<default_bitset_t PossibleGrades, class LazyBitset>
		struct count_stored_bitsets<dynamic_basis_blade<PossibleGrades, LazyBitset> > {
			constexpr static std::size_t value = count_stored_bitsets_v<LazyBitset>;
		};

		template<class Coefficient, class BasisBlade>
		struct count_stored_bitsets<component<Coefficient, BasisBlade> > {
			constexpr static std::size_t value = count_stored_bitsets_v<Coefficient> + count_stored_bitsets_v<BasisBlade>;
		};

		template<name_t Name, class... Arguments>
		struct count_stored_bitsets<function<Name, Arguments...> > {
			constexpr static std::size_t value = count_stored_bitsets_v<Arguments...>;
		};

		// Sequential collection of stored data entries.
		template<class EntryType, std::size_t Size>
		class sequential_storage {
		public:

			typedef EntryType entry_type;

			constexpr sequential_storage() = default;
			constexpr sequential_storage(sequential_storage const &) = default;
			constexpr sequential_storage(sequential_storage &&) = default;

			template<class... Args>
			constexpr sequential_storage(Args &&... args) :
				data_{ std::move(args)... } {
				static_assert(sizeof...(args) == Size, "The number of arguments must be equal to the number of stored data entries.");
			}

			constexpr sequential_storage & operator=(sequential_storage const &) = default;
			constexpr sequential_storage & operator=(sequential_storage &&) = default;

		private:

			std::array<entry_type, Size> data_;
		};

		// Superclass for ga::clifford_expression<CoefficientType, Expression>.
		template<class CoefficientType, class Expression, std::size_t StoredValues = count_stored_values_v<Expression>, std::size_t StoredBitsets = count_stored_bitsets_v<Expression>, std::size_t StoredMaps = 0 /*TODO Not supported yet (associative storage).*/>
		class _super_clifford_expression;

		template<class CoefficientType, class Expression>
		class _super_clifford_expression<CoefficientType, Expression, 0, 0, 0> {
		public:

			typedef CoefficientType coefficient_type;
			typedef default_bitset_t bitset_type;

			typedef sequential_storage<coefficient_type, 0> value_storage_type;
			typedef sequential_storage<bitset_type, 0> bitset_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;
		};

		template<class CoefficientType, class Expression, std::size_t StoredValues>
		class _super_clifford_expression<CoefficientType, Expression, StoredValues, 0, 0> {
		public:

			typedef CoefficientType coefficient_type;
			typedef default_bitset_t bitset_type;

			typedef sequential_storage<coefficient_type, StoredValues> value_storage_type;
			typedef sequential_storage<bitset_type, 0> bitset_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(value_storage_type &&values) :
				values_(std::move(values)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

		protected:

			value_storage_type values_;
		};

		template<class CoefficientType, class Expression, std::size_t StoredBitsets>
		class _super_clifford_expression<CoefficientType, Expression, 0, StoredBitsets, 0> {
		public:

			typedef CoefficientType coefficient_type;
			typedef default_bitset_t bitset_type;

			typedef sequential_storage<coefficient_type, 0> value_storage_type;
			typedef sequential_storage<bitset_type, StoredBitsets> bitset_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(bitset_storage_type &&bitsets) :
				bitsets_(std::move(bitsets)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

		protected:

			bitset_storage_type bitsets_;
		};

		template<class CoefficientType, class Expression, std::size_t StoredValues, std::size_t StoredBitsets>
		class _super_clifford_expression<CoefficientType, Expression, StoredValues, StoredBitsets, 0> {
		public:

			typedef CoefficientType coefficient_type;
			typedef default_bitset_t bitset_type;

			typedef sequential_storage<coefficient_type, StoredValues> value_storage_type;
			typedef sequential_storage<bitset_type, StoredBitsets> bitset_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(value_storage_type &&values, bitset_storage_type &&bitsets) :
				values_(std::move(values)),
				bitsets_(std::move(bitsets)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

		protected:

			value_storage_type values_;
			bitset_storage_type bitsets_;
		};

	}

	// Clifford expression.
	template<class CoefficientType, class Expression>
	class clifford_expression final : private detail::_super_clifford_expression<CoefficientType, Expression> {
	private:

		typedef detail::_super_clifford_expression<CoefficientType, Expression> super;

	public:

		using typename super::coefficient_type;
		using typename super::bitset_type;

		using typename super::value_storage_type;
		using typename super::bitset_storage_type;

		typedef Expression expression_type;

		constexpr clifford_expression() = default;
		constexpr clifford_expression(clifford_expression const &) = default;
		constexpr clifford_expression(clifford_expression &&) = default;

		template<class OtherCoefficientType, class OtherExpression>
		constexpr clifford_expression(clifford_expression<OtherCoefficientType, OtherExpression> const &) = delete; //TODO Not supported yet (copy)

		template<class... StorageType>
		constexpr clifford_expression(StorageType &&... args) :
			super(std::move(args)...) {
		}

		constexpr clifford_expression & operator=(clifford_expression const &) = default;
		constexpr clifford_expression & operator=(clifford_expression &&) = default;

		template<class = std::enable_if_t<detail::is_scalar_expression_v<clifford_expression> > >
		constexpr operator coefficient_type() const = delete; //TODO Not supported yet (native scalar casting)
	};

	// Returns whether the given type is a clifford expression.
	template<class Type>
	struct is_clifford_expression {
		constexpr static bool value = false;
	};

	template<class CoefficientType, class Expression>
	struct is_clifford_expression<clifford_expression<CoefficientType, Expression> > {
		constexpr static bool value = true;
	};

	template<class Type>
	constexpr bool is_clifford_expression_v = is_clifford_expression<Type>::value;

	// Helper function to build a sequential storage of values or basis blades.
	template<class... Args>
	constexpr decltype(auto) make_sequential_storage(Args &&... args) {
		return detail::sequential_storage<std::common_type_t<Args...>, sizeof...(args)>(std::move(args)...);
	}

}

#endif // __FUTURE_GA_CLIFFORD_EXPRESSION_HPP__
