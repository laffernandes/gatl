#ifndef __FUTURE_GA_CLIFFORD_EXPRESSION_HPP__
#define __FUTURE_GA_CLIFFORD_EXPRESSION_HPP__

namespace ga {

	namespace detail {

		// Returns the number of coefficients stored for the given expression.
		template<class... Expressions>
		struct count_stored_coefficients;

		template<class... Expressions>
		constexpr std::size_t count_stored_coefficients_v = count_stored_coefficients<Expressions...>::value;

		template<class Expression, class... NextExpressions>
		struct count_stored_coefficients<Expression, NextExpressions...> {
			constexpr static std::size_t value = count_stored_coefficients_v<Expression> + count_stored_coefficients_v<NextExpressions...>; // recursion
		};

		template<>
		struct count_stored_coefficients<> {
			constexpr static std::size_t value = 0; // end of recursion
		};

		template<default_integral_t Value>
		struct count_stored_coefficients<constant<Value> > {
			constexpr static std::size_t value = 0;
		};

		template<class LazyCoefficient>
		struct count_stored_coefficients<value<LazyCoefficient> > {
			constexpr static std::size_t value = 0;
		};

		template<>
		struct count_stored_coefficients<value<stored> > {
			constexpr static std::size_t value = 1;
		};

		template<name_t Name, class... Arguments>
		struct count_stored_coefficients<function<Name, Arguments...> > {
			constexpr static std::size_t value = count_stored_coefficients_v<Arguments...>;
		};

		template<class Coefficient, class BasisBlade>
		struct count_stored_coefficients<component<Coefficient, BasisBlade> > {
			constexpr static std::size_t value = 0;
		};

		template<class Coefficient, default_bitset_t BasisVectors>
		struct count_stored_coefficients<component<Coefficient, constant_basis_blade<BasisVectors> > > {
			constexpr static std::size_t value = count_stored_coefficients_v<Coefficient>;
		};

		template<class Coefficient, default_bitset_t PossibleGrades, class LazyBasisVectors>
		struct count_stored_coefficients<component<Coefficient, dynamic_basis_blade<PossibleGrades, LazyBasisVectors> > > {
			constexpr static std::size_t value = count_stored_coefficients_v<Coefficient>;
		};

		// Returns the number of basis blades stored for the given expression.
		template<class... Expressions>
		struct count_stored_basis_blades;

		template<class... Expressions>
		constexpr std::size_t count_stored_basis_blades_v = count_stored_basis_blades<Expressions...>::value;

		template<class Expression, class... NextExpressions>
		struct count_stored_basis_blades<Expression, NextExpressions...> {
			constexpr static std::size_t value = count_stored_basis_blades_v<Expression> + count_stored_basis_blades_v<NextExpressions...>; // recursion
		};

		template<>
		struct count_stored_basis_blades<> {
			constexpr static std::size_t value = 0; // end of recursion
		};

		template<default_integral_t Value>
		struct count_stored_basis_blades<constant<Value> > {
			constexpr static std::size_t value = 0;
		};

		template<class LazyCoefficient>
		struct count_stored_basis_blades<value<LazyCoefficient> > {
			constexpr static std::size_t value = 0;
		};

		template<name_t Name, class... Arguments>
		struct count_stored_basis_blades<function<Name, Arguments...> > {
			constexpr static std::size_t value = 0;
		};

		template<class Coefficient, class BasisBlade>
		struct count_stored_basis_blades<component<Coefficient, BasisBlade> > {
			constexpr static std::size_t value = 0;
		};

		template<class Coefficient, default_bitset_t PossibleGrades>
		struct count_stored_basis_blades<component<Coefficient, dynamic_basis_blade<PossibleGrades, stored> > > {
			constexpr static std::size_t value = 1;
		};

		// Sequential collection of stored data entries.
		template<class DataEntryType, std::size_t Size>
		class sequential_storage {
		public:

			typedef DataEntryType data_entry_type;

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

			std::array<data_entry_type, Size> data_;
		};

		// Superclass for ga::clifford_expression<CoefficientType, Expression>.
		template<class CoefficientType, class Expression, std::size_t StoredCoefficients = count_stored_coefficients_v<Expression>, std::size_t StoredBasisBlades = count_stored_basis_blades_v<Expression>, bool AssociativeStorageOfComponents = false /*TODO Not supported yet (associative storage).*/>
		class _super_clifford_expression;

		template<class CoefficientType, class Expression>
		class _super_clifford_expression<CoefficientType, Expression, 0, 0, false> {
		public:

			typedef CoefficientType coefficient_type;
			typedef default_bitset_t basis_blade_type;

			typedef sequential_storage<coefficient_type, 0> coefficient_storage_type;
			typedef sequential_storage<basis_blade_type, 0> basis_blade_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;
		};

		template<class CoefficientType, class Expression, std::size_t StoredCoefficients>
		class _super_clifford_expression<CoefficientType, Expression, StoredCoefficients, 0, false> {
		public:

			typedef CoefficientType coefficient_type;
			typedef default_bitset_t basis_blade_type;

			typedef sequential_storage<coefficient_type, StoredCoefficients> coefficient_storage_type;
			typedef sequential_storage<basis_blade_type, 0> basis_blade_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(coefficient_storage_type &&coefficients) :
				coefficients_(std::move(coefficients)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

		protected:

			coefficient_storage_type coefficients_;
		};

		template<class CoefficientType, class Expression, std::size_t StoredBasisBlades>
		class _super_clifford_expression<CoefficientType, Expression, 0, StoredBasisBlades, false> {
		public:

			typedef CoefficientType coefficient_type;
			typedef default_bitset_t basis_blade_type;

			typedef sequential_storage<coefficient_type, 0> coefficient_storage_type;
			typedef sequential_storage<basis_blade_type, StoredBasisBlades> basis_blade_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(basis_blade_storage_type &&basis_blades) :
				basis_blades_(std::move(basis_blades)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

		protected:

			basis_blade_storage_type basis_blades_;
		};

		template<class CoefficientType, class Expression, std::size_t StoredCoefficients, std::size_t StoredBasisBlades>
		class _super_clifford_expression<CoefficientType, Expression, StoredCoefficients, StoredBasisBlades, false> {
		public:

			typedef CoefficientType coefficient_type;
			typedef default_bitset_t basis_blade_type;

			typedef sequential_storage<coefficient_type, StoredCoefficients> coefficient_storage_type;
			typedef sequential_storage<basis_blade_type, StoredBasisBlades> basis_blade_storage_type;

			constexpr _super_clifford_expression() = default;
			constexpr _super_clifford_expression(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression(_super_clifford_expression &&) = default;

			constexpr _super_clifford_expression(coefficient_storage_type &&coefficients, basis_blade_storage_type &&basis_blades) :
				coefficients_(std::move(coefficients)),
				basis_blades_(std::move(basis_blades)) {
			}

			constexpr _super_clifford_expression & operator=(_super_clifford_expression const &) = default;
			constexpr _super_clifford_expression & operator=(_super_clifford_expression &&) = default;

		protected:

			coefficient_storage_type coefficients_;
			basis_blade_storage_type basis_blades_;
		};

	}

	// Clifford expression.
	template<class CoefficientType, class Expression>
	class clifford_expression final : private detail::_super_clifford_expression<CoefficientType, Expression> {
	private:

		typedef detail::_super_clifford_expression<CoefficientType, Expression> super;

	public:

		using typename super::coefficient_type;
		using typename super::basis_blade_type;

		using typename super::coefficient_storage_type;
		using typename super::basis_blade_storage_type;

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

		template<class = std::enable_if_t<std::is_same_v<Expression, detail::value<detail::stored> > > >
		constexpr operator coefficient_type() const {
			return super::coefficients_.front();
		}
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

	// Helper function to build a sequential storage of coefficients or basis blades.
	template<class... Args>
	constexpr decltype(auto) make_sequential_storage(Args &&... args) {
		return detail::sequential_storage<std::common_type_t<Args...>, sizeof...(args)>(std::move(args)...);
	}

}

#endif // __FUTURE_GA_CLIFFORD_EXPRESSION_HPP__
