#ifndef __FUTURE_GA_EXPRESSION_TESTS_HPP__
#define __FUTURE_GA_EXPRESSION_TESTS_HPP__

namespace ga {

	namespace detail {

		// Specializations of is_constant_expression<Expression>.
		template<default_integral_t Value>
		struct is_constant_expression<constant<Value> > {
			constexpr static bool value = true; // end of recursion
		};

		template<class LazyCoefficient>
		struct is_constant_expression<value<LazyCoefficient> > {
			constexpr static bool value = false; // end of recursion
		};

		template<name_t Name, class... Arguments>
		struct is_constant_expression<function<Name, Arguments...> > {
			constexpr static bool value = is_constant_expression_v<_arguments_list<Arguments...> >; // recursive
		};

		template<class Coefficient, default_bitset_t BasisVectors>
		struct is_constant_expression<component<Coefficient, constant_basis_blade<BasisVectors> > > {
			constexpr static bool value = is_constant_expression_v<Coefficient>; // recursive
		};

		template<class Coefficient, default_bitset_t PossibleGrades, class LazyBasisVectors>
		struct is_constant_expression<component<Coefficient, dynamic_basis_blade<PossibleGrades, LazyBasisVectors> > > {
			constexpr static bool value = false; // end of recursion
		};

		template<class Argument, class... NextArguments>
		struct is_constant_expression<_arguments_list<Argument, NextArguments...> > {
			constexpr static bool value = is_constant_expression_v<Argument> && is_constant_expression_v<_arguments_list<NextArguments...> >; // recursive
		};

		template<>
		struct is_constant_expression<_arguments_list<> > {
			constexpr static bool value = true; // end of recursion
		};

		// Specializations of is_scalar_expression<Expression>.
		template<default_integral_t Value>
		struct is_scalar_expression<constant<Value> > {
			constexpr static bool value = true; // end of recursion
		};

		template<class LazyCoefficient>
		struct is_scalar_expression<value<LazyCoefficient> > {
			constexpr static bool value = true; // end of recursion
		};

		template<name_t Name, class... Arguments>
		struct is_scalar_expression<function<Name, Arguments...> > {
			constexpr static bool value = true; // end of recursion
		};

		template<class Coefficient, class BasisBlade>
		struct is_scalar_expression<component<Coefficient, BasisBlade> > {
			constexpr static bool value = false; // end of recursion
		};

		template<class Argument, class... NextArguments>
		struct is_scalar_expression<_arguments_list<Argument, NextArguments...> > {
			constexpr static bool value = is_scalar_expression_v<Argument> && is_scalar_expression_v<_arguments_list<NextArguments...> >; // recursive
		};

		template<>
		struct is_scalar_expression<_arguments_list<> > {
			constexpr static bool value = true; // end of recursion
		};

		// Specializations of possible_grades<BasisBlade>.
		template<default_bitset_t BasisVectors>
		struct possible_grades<constant_basis_blade<BasisVectors> > {
			constexpr static default_bitset_t value = default_bitset_t(1) << ones(BasisVectors);
		};

		template<default_bitset_t PossibleGrades, class LazyBasisVectors>
		struct possible_grades<dynamic_basis_blade<PossibleGrades, LazyBasisVectors> > {
			constexpr static default_bitset_t value = PossibleGrades;
		};

		// Returns the basis vectors of a given basis blade.
		template<class BasisBlade>
		struct basis_vectors;

		template<default_bitset_t BasisVectors>
		struct basis_vectors<constant_basis_blade<BasisVectors> > {
			typedef lazy_constant_bitset<BasisVectors> type;
		};

		template<default_bitset_t PossibleGrades, class LazyBasisVectors>
		struct basis_vectors<dynamic_basis_blade<PossibleGrades, LazyBasisVectors> > {
			typedef LazyBasisVectors type;
		};

		template<class BasisBlade>
		using basis_vectors_t = typename basis_vectors<BasisBlade>::type;

	}

}

#endif // __FUTURE_GA_EXPRESSION_TESTS_HPP__
