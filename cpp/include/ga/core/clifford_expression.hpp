#ifndef __GA_CORE_CLIFFORD_EXPRESSION_HPP__
#define __GA_CORE_CLIFFORD_EXPRESSION_HPP__

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

		template<default_bitset_t PossibleGrades, class Bitset>
		struct count_stored_values<dynamic_basis_blade<PossibleGrades, Bitset> > {
			constexpr static std::size_t value = count_stored_values_v<Bitset>;
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

		template<default_bitset_t PossibleGrades, class Bitset>
		struct count_stored_bitsets<dynamic_basis_blade<PossibleGrades, Bitset> > {
			constexpr static std::size_t value = count_stored_bitsets_v<Bitset>;
		};

		template<class Coefficient, class BasisBlade>
		struct count_stored_bitsets<component<Coefficient, BasisBlade> > {
			constexpr static std::size_t value = count_stored_bitsets_v<Coefficient> + count_stored_bitsets_v<BasisBlade>;
		};

		template<name_t Name, class... Arguments>
		struct count_stored_bitsets<function<Name, Arguments...> > {
			constexpr static std::size_t value = count_stored_bitsets_v<Arguments...>;
		};

		// Returns the number of maps stored by the given expression.
		template<class... Expressions>
		struct count_stored_maps;

		template<class... Expressions>
		constexpr std::size_t count_stored_maps_v = count_stored_maps<Expressions...>::value;

		template<class Expression, class... NextExpressions>
		struct count_stored_maps<Expression, NextExpressions...> {
			constexpr static std::size_t value = count_stored_maps_v<Expression> + count_stored_maps_v<NextExpressions...>; // recursion
		};

		template<>
		struct count_stored_maps<> {
			constexpr static std::size_t value = 0; // end of recursion
		};

		template<class Expression>
		struct count_stored_maps<Expression> {
			constexpr static std::size_t value = 0; // default
		};

		template<default_bitset_t PossibleGrades>
		struct count_stored_values<component<stored_map_values, dynamic_basis_blade<PossibleGrades, stored_map_bitsets> > > {
			constexpr static std::size_t value = 1;
		};

		template<class... Arguments>
		struct count_stored_maps<add<Arguments...> > {
			constexpr static std::size_t value = count_stored_maps_v<Arguments...>;
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
				entries_{ std::move(args)... } {
				static_assert(sizeof...(args) == Size, "The number of arguments must be equal to the number of stored data entries.");
			}

			constexpr sequential_storage & operator=(sequential_storage const &) = default;
			constexpr sequential_storage & operator=(sequential_storage &&) = default;

			constexpr decltype(auto) begin() {
				return entries_.begin();
			}

			constexpr decltype(auto) begin() const {
				return entries_.begin();
			}

			constexpr decltype(auto) end() {
				return entries_.end();
			}

			constexpr decltype(auto) end() const {
				return entries_.end();
			}

			constexpr decltype(auto) cbegin() const {
				return entries_.cbegin();
			}

			constexpr decltype(auto) cend() const {
				return entries_.cend();
			}

		private:

			default_sequence_container_t<entry_type, Size> entries_;
		};

		// Superclass for ga::clifford_expression<ValueType, Expression>.
		template<class ValueType, class Expression, std::size_t StoredValuesCount = count_stored_values_v<Expression>, std::size_t StoredBitsetsCount = count_stored_bitsets_v<Expression>, std::size_t StoredMapsCount = count_stored_maps_v<Expression> >
		class _super_clifford_expression {
		public:

			typedef ValueType value_type;
			typedef default_bitset_t bitset_type;
			typedef default_associative_container_t<value_type> map_type;

			typedef sequential_storage<value_type, StoredValuesCount> value_storage_type;
			typedef sequential_storage<bitset_type, StoredBitsetsCount> bitset_storage_type;
			typedef sequential_storage<map_type, StoredMapsCount> map_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(value_storage_type &&values, bitset_storage_type &&bitsets, map_storage_type &&maps) :
				values_(std::move(values)),
				bitsets_(std::move(bitsets)),
				maps_(std::move(maps)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

			constexpr value_storage_type & values() {
				return values_;
			}

			constexpr value_storage_type const & values() const {
				return values_;
			}

			constexpr bitset_storage_type & bitsets() {
				return bitsets_;
			}

			constexpr bitset_storage_type const & bitsets() const {
				return bitsets_;
			}

			constexpr map_storage_type & maps() {
				return maps_;
			}

			constexpr map_storage_type const & maps() const {
				return maps_;
			}

		private:

			value_storage_type values_;
			bitset_storage_type bitsets_;
			map_storage_type maps_;
		};

		template<class ValueType, class Expression, std::size_t StoredBitsetsCount, std::size_t StoredMapsCount>
		class _super_clifford_expression<ValueType, Expression, 0, StoredBitsetsCount, StoredMapsCount> {
		public:

			typedef ValueType value_type;
			typedef default_bitset_t bitset_type;
			typedef default_associative_container_t<value_type> map_type;

			typedef sequential_storage<value_type, 0> value_storage_type;
			typedef sequential_storage<bitset_type, StoredBitsetsCount> bitset_storage_type;
			typedef sequential_storage<map_type, StoredMapsCount> map_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(value_storage_type &&, bitset_storage_type &&bitsets, map_storage_type &&maps) :
				bitsets_(std::move(bitsets)),
				maps_(std::move(maps)) {
			}
			
			constexpr _super_clifford_expression(bitset_storage_type &&bitsets, map_storage_type &&maps) :
				bitsets_(std::move(bitsets)),
				maps_(std::move(maps)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

			constexpr value_storage_type values() const {
				return value_storage_type();
			}

			constexpr bitset_storage_type & bitsets() {
				return bitsets_;
			}

			constexpr bitset_storage_type const & bitsets() const {
				return bitsets_;
			}

			constexpr map_storage_type & maps() {
				return maps_;
			}

			constexpr map_storage_type const & maps() const {
				return maps_;
			}

		private:

			bitset_storage_type bitsets_;
			map_storage_type maps_;
		};

		template<class ValueType, class Expression, std::size_t StoredValuesCount, std::size_t StoredMapsCount>
		class _super_clifford_expression<ValueType, Expression, StoredValuesCount, 0, StoredMapsCount> {
		public:

			typedef ValueType value_type;
			typedef default_bitset_t bitset_type;
			typedef default_associative_container_t<value_type> map_type;

			typedef sequential_storage<value_type, StoredValuesCount> value_storage_type;
			typedef sequential_storage<bitset_type, 0> bitset_storage_type;
			typedef sequential_storage<map_type, StoredMapsCount> map_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(value_storage_type &&values, bitset_storage_type &&, map_storage_type &&maps) :
				values_(std::move(values)),
				maps_(std::move(maps)) {
			}

			constexpr _super_clifford_expression(value_storage_type &&values, map_storage_type &&maps) :
				values_(std::move(values)),
				maps_(std::move(maps)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

			constexpr value_storage_type & values() {
				return values_;
			}

			constexpr value_storage_type const & values() const {
				return values_;
			}

			constexpr bitset_storage_type bitsets() const {
				return bitset_storage_type();
			}

			constexpr map_storage_type & maps() {
				return maps_;
			}

			constexpr map_storage_type const & maps() const {
				return maps_;
			}

		private:

			value_storage_type values_;
			map_storage_type maps_;
		};

		template<class ValueType, class Expression, std::size_t StoredMapsCount>
		class _super_clifford_expression<ValueType, Expression, 0, 0, StoredMapsCount> {
		public:

			typedef ValueType value_type;
			typedef default_bitset_t bitset_type;
			typedef default_associative_container_t<value_type> map_type;

			typedef sequential_storage<value_type, 0> value_storage_type;
			typedef sequential_storage<bitset_type, 0> bitset_storage_type;
			typedef sequential_storage<map_type, StoredMapsCount> map_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(value_storage_type &&, bitset_storage_type &&, map_storage_type &&maps) :
				maps_(std::move(maps)) {
			}

			constexpr _super_clifford_expression(map_storage_type &&maps) :
				maps_(std::move(maps)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

			constexpr value_storage_type values() const {
				return value_storage_type();
			}

			constexpr bitset_storage_type bitsets() const {
				return bitset_storage_type();
			}

			constexpr map_storage_type & maps() {
				return maps_;
			}

			constexpr map_storage_type const & maps() const {
				return maps_;
			}

		private:

			map_storage_type maps_;
		};

		template<class ValueType, class Expression, std::size_t StoredValuesCount, std::size_t StoredBitsetsCount>
		class _super_clifford_expression<ValueType, Expression, StoredValuesCount, StoredBitsetsCount, 0> {
		public:

			typedef ValueType value_type;
			typedef default_bitset_t bitset_type;
			typedef default_associative_container_t<value_type> map_type;

			typedef sequential_storage<value_type, StoredValuesCount> value_storage_type;
			typedef sequential_storage<bitset_type, StoredBitsetsCount> bitset_storage_type;
			typedef sequential_storage<map_type, 0> map_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(value_storage_type &&values, bitset_storage_type &&bitsets, map_storage_type &&) :
				values_(std::move(values)),
				bitsets_(std::move(bitsets)) {
			}

			constexpr _super_clifford_expression(value_storage_type &&values, bitset_storage_type &&bitsets) :
				values_(std::move(values)),
				bitsets_(std::move(bitsets)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

			constexpr value_storage_type & values() {
				return values_;
			}

			constexpr value_storage_type const & values() const {
				return values_;
			}

			constexpr bitset_storage_type & bitsets() {
				return bitsets_;
			}

			constexpr bitset_storage_type const & bitsets() const {
				return bitsets_;
			}

			constexpr map_storage_type maps() const {
				return map_storage_type();
			}

		private:

			value_storage_type values_;
			bitset_storage_type bitsets_;
		};

		template<class ValueType, class Expression, std::size_t StoredBitsetsCount>
		class _super_clifford_expression<ValueType, Expression, 0, StoredBitsetsCount, 0> {
		public:

			typedef ValueType value_type;
			typedef default_bitset_t bitset_type;
			typedef default_associative_container_t<value_type> map_type;

			typedef sequential_storage<value_type, 0> value_storage_type;
			typedef sequential_storage<bitset_type, StoredBitsetsCount> bitset_storage_type;
			typedef sequential_storage<map_type, 0> map_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(value_storage_type &&, bitset_storage_type &&bitsets, map_storage_type &&) :
				bitsets_(std::move(bitsets)) {
			}

			constexpr _super_clifford_expression(bitset_storage_type &&bitsets) :
				bitsets_(std::move(bitsets)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

			constexpr value_storage_type values() const {
				return value_storage_type();
			}

			constexpr bitset_storage_type & bitsets() {
				return bitsets_;
			}

			constexpr bitset_storage_type const & bitsets() const {
				return bitsets_;
			}

			constexpr map_storage_type maps() const {
				return map_storage_type();
			}

		private:

			bitset_storage_type bitsets_;
		};

		template<class ValueType, class Expression, std::size_t StoredValuesCount>
		class _super_clifford_expression<ValueType, Expression, StoredValuesCount, 0, 0> {
		public:

			typedef ValueType value_type;
			typedef default_bitset_t bitset_type;
			typedef default_associative_container_t<value_type> map_type;

			typedef sequential_storage<value_type, StoredValuesCount> value_storage_type;
			typedef sequential_storage<bitset_type, 0> bitset_storage_type;
			typedef sequential_storage<map_type, 0> map_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(value_storage_type &&values, bitset_storage_type &&, map_storage_type &&) :
				values_(std::move(values)) {
			}

			constexpr _super_clifford_expression(value_storage_type &&values) :
				values_(std::move(values)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

			constexpr value_storage_type & values() {
				return values_;
			}

			constexpr value_storage_type const & values() const {
				return values_;
			}

			constexpr bitset_storage_type bitsets() const {
				return bitset_storage_type();
			}

			constexpr map_storage_type maps() const {
				return map_storage_type();
			}

		private:

			value_storage_type values_;
		};

		template<class ValueType, class Expression>
		class _super_clifford_expression<ValueType, Expression, 0, 0, 0> {
		public:

			typedef ValueType value_type;
			typedef default_bitset_t bitset_type;
			typedef default_associative_container_t<value_type> map_type;

			typedef sequential_storage<value_type, 0> value_storage_type;
			typedef sequential_storage<bitset_type, 0> bitset_storage_type;
			typedef sequential_storage<map_type, 0> map_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(value_storage_type &&, bitset_storage_type &&, map_storage_type &&) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

			constexpr value_storage_type values() const {
				return value_storage_type();
			}

			constexpr bitset_storage_type bitsets() const {
				return bitset_storage_type();
			}

			constexpr map_storage_type maps() const {
				return map_storage_type();
			}

		};

		// Cast scalar expressions to native value.
		template<class Expression, bool IsConstant = is_constant_expression_v<Expression> >
		struct _clifford_expression_to_native;
		
		template<class Coefficient>
		struct _clifford_expression_to_native<component<Coefficient, constant_basis_blade<default_bitset_t(0)> >, true> {
			template<class ValueCItr>
			constexpr static decltype(auto) eval(ValueCItr const &) {
				return Coefficient::eval<0, 0>(std::tuple<>());
			}
		};

		template<>
		struct _clifford_expression_to_native<component<stored_value, constant_basis_blade<default_bitset_t(0)> >, false> {
			template<class ValueCItr>
			constexpr static decltype(auto) eval(ValueCItr const &value_itr) {
				return *value_itr;
			}
		};

	}

	// Clifford expression.
	template<class CoefficientType, class Expression>
	class clifford_expression final :
		private detail::_super_clifford_expression<CoefficientType, Expression> {
	private:

		typedef detail::_super_clifford_expression<CoefficientType, Expression> super;

	public:

		typedef CoefficientType coefficient_type;
		typedef Expression expression_type;
		
		using typename super::value_type;
		using typename super::bitset_type;
		using typename super::map_type;

		using typename super::value_storage_type;
		using typename super::bitset_storage_type;
		using typename super::map_storage_type;

		using super::values;
		using super::bitsets;
		using super::maps;

		constexpr clifford_expression() = default;
		constexpr clifford_expression(clifford_expression const &) = default;
		constexpr clifford_expression(clifford_expression &&) = default;

		template<class OtherCoefficientType, class OtherExpression>
		constexpr clifford_expression(clifford_expression<OtherCoefficientType, OtherExpression> const &) = delete; //TODO Not supported yet (copy).

		template<class... StorageTypes>
		constexpr clifford_expression(StorageTypes &&... args) :
			super(std::move(args)...) {
		}

		constexpr clifford_expression & operator=(clifford_expression const &) = default;
		constexpr clifford_expression & operator=(clifford_expression &&) = default;

		template<class OtherCoefficientType, class OtherExpression>
		constexpr clifford_expression & operator=(clifford_expression<OtherCoefficientType, OtherExpression> const &) = delete; //TODO Not supported yet (copy).

		template<class Type, class = std::enable_if_t<detail::is_scalar_component_v<Expression> && detail::can_be_stored_v<Expression> > >
		constexpr operator Type() const {
			return detail::_clifford_expression_to_native<Expression>::eval(super::values().cbegin());
		}
	};

	// Returns whether the given type is a clifford expression.
	template<class Type>
	struct is_clifford_expression :
		std::false_type {
	};

	template<class CoefficientType, class Expression>
	struct is_clifford_expression<clifford_expression<CoefficientType, Expression> > :
		std::true_type {
	};

	template<class Type>
	constexpr bool is_clifford_expression_v = is_clifford_expression<Type>::value;

	// Helper function to build a sequential storage of values, bitsets or maps.
	template<class... Args>
	constexpr decltype(auto) make_sequential_storage(Args &&... args) {
		return detail::sequential_storage<std::common_type_t<std::remove_cv_t<std::remove_reference_t<Args> >...>, sizeof...(args)>(std::move(args)...);
	}

}

#endif // __GA_CORE_CLIFFORD_EXPRESSION_HPP__
