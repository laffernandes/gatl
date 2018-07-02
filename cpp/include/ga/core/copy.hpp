/**
Copyright (C) 2018 Leandro Augusto Frata Fernandes

author     : Fernandes, Leandro A. F.
e-mail     : laffernandes@ic.uff.br
home page  : http://www.ic.uff.br/~laffernandes
repository : https://github.com/laffernandes/gatl.git

This file is part of The Geometric Algebra Template Library (GATL).

GATL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GATL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GATL. If not, see <https://www.gnu.org/licenses/>.
/**/

#ifndef __GA_CORE_COPY_HPP__
#define __GA_CORE_COPY_HPP__

namespace ga {

	namespace detail {

		//TODO Não está adequado para PossibleGrades da entrada ser subconjunto de PossibleGrades do resultado

		// Executes the copy of clifford_expressions<...> types.
		template<typename InputExpression, typename ResultExpression, typename Enabled = void>
		struct copy {
			static_assert(std::is_same_v<InputExpression, nullptr_t>, "Non-trivial copy operation."); // Always raises a compile-time error.
		};

		template<typename InputComponent, typename ResultComponent>
		struct _copy_assign; //TODO Not supported yet (map)

		template<typename ResultComponent>
		struct _copy_zero; //TODO Not supported yet (map)

		template<typename InputExpression, typename ResultExpression>
		struct _copy_assign_and_advance_both;

		template<typename InputExpression, typename ResultExpression>
		struct _copy_zero_and_advance_result;

		template<typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
		struct copy<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...>, std::enable_if_t<eq_v<InputBasisBlade, ResultBasisBlade> > > :
			_copy_assign_and_advance_both<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
		};

		template<typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade>
		struct copy<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade>, std::enable_if_t<eq_v<InputBasisBlade, ResultBasisBlade> > > :
			_copy_assign_and_advance_both<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade> > {
		};

		template<typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
		struct copy<component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...>, std::enable_if_t<!std::is_same_v<InputCoefficient, constant_value<0> > && eq_v<InputBasisBlade, ResultBasisBlade> > > :
			_copy_assign_and_advance_both<component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
		};

		template<typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade>
		struct copy<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade>, std::enable_if_t<!std::is_same_v<InputCoefficient, constant_value<0> > && eq_v<InputBasisBlade, ResultBasisBlade> > > :
			_copy_assign_and_advance_both<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> > {
		};

		template<typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
		struct copy<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...>, std::enable_if_t<lt_v<ResultBasisBlade, InputBasisBlade> > > :
			_copy_zero_and_advance_result<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
		};

		template<typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade>
		struct copy<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade>, std::enable_if_t<lt_v<ResultBasisBlade, InputBasisBlade> > > :
			_copy_zero_and_advance_result<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade> > {
		};

		template<typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
		struct copy<component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...>, std::enable_if_t<std::is_same_v<InputCoefficient, constant_value<0> > || lt_v<ResultBasisBlade, InputBasisBlade> > > :
			_copy_zero_and_advance_result<component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
		};

		template<typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade>
		struct copy<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade>, std::enable_if_t<std::is_same_v<InputCoefficient, constant_value<0> > || lt_v<ResultBasisBlade, InputBasisBlade> > > :
			_copy_zero_and_advance_result<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> > {
		};

		template<typename InputCoefficient, default_bitset_t BasisVectors>
		struct _copy_assign<component<InputCoefficient, constant_basis_blade<BasisVectors> >, component<stored_value, constant_basis_blade<BasisVectors> > > {
			template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(InputValueCItr const &, InputBitsetCItr const &, InputMapCItr const &, ResultValueItr &result_value_itr, ResultBitsetItr const &, ResultMapItr const &) {
				*result_value_itr = InputCoefficient::eval<0, 0>(std::make_tuple());
				std::advance(result_value_itr, 1);
			}
		};

		template<default_bitset_t BasisVectors>
		struct _copy_assign<component<stored_value, constant_basis_blade<BasisVectors> >, component<stored_value, constant_basis_blade<BasisVectors> > > {
			template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr const &, InputMapCItr const &, ResultValueItr &result_value_itr, ResultBitsetItr const &, ResultMapItr const &) {
				*result_value_itr = *input_value_itr;
				std::advance(input_value_itr, 1);
				std::advance(result_value_itr, 1);
			}
		};

		template<typename InputCoefficient, default_bitset_t InputBasisVectors, default_bitset_t ResultPossibleGrades>
		struct _copy_assign<component<InputCoefficient, constant_basis_blade<InputBasisVectors> >, component<stored_value, dynamic_basis_blade<ResultPossibleGrades, stored_bitset> > > {
			static_assert((possible_grades_v<constant_basis_blade<InputBasisVectors> > & ResultPossibleGrades) == possible_grades_v<constant_basis_blade<InputBasisVectors> >, "The possible grades of the input basis blade must be included in the set of possible brades of the resulting basis blade.");

			template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(InputValueCItr const &, InputBitsetCItr const &, InputMapCItr const &, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr const &) {
				*result_value_itr = InputCoefficient::eval<0, 0>(std::make_tuple());
				std::advance(result_value_itr, 1);

				*result_bitset_itr = InputBasisVectors;
				std::advance(result_bitset_itr, 1);
			}
		};

		template<default_bitset_t InputBasisVectors, default_bitset_t ResultPossibleGrades>
		struct _copy_assign<component<stored_value, constant_basis_blade<InputBasisVectors> >, component<stored_value, dynamic_basis_blade<ResultPossibleGrades, stored_bitset> > > {
			static_assert((possible_grades_v<constant_basis_blade<InputBasisVectors> > & ResultPossibleGrades) == possible_grades_v<constant_basis_blade<InputBasisVectors> >, "The possible grades of the input basis blade must be included in the set of possible brades of the resulting basis blade.");

			template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr const &, InputMapCItr const &, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr const &) {
				*result_value_itr = *input_value_itr;
				std::advance(input_value_itr, 1);
				std::advance(result_value_itr, 1);

				*result_bitset_itr = InputBasisVectors;
				std::advance(result_bitset_itr, 1);
			}
		};

		template<typename InputCoefficient, default_bitset_t InputPossibleGrades, default_bitset_t ResultPossibleGrades>
		struct _copy_assign<component<InputCoefficient, dynamic_basis_blade<InputPossibleGrades, stored_bitset> >, component<stored_value, dynamic_basis_blade<ResultPossibleGrades, stored_bitset> > > {
			static_assert((InputPossibleGrades & ResultPossibleGrades) == InputPossibleGrades, "The possible grades of the input basis blade must be included in the set of possible brades of the resulting basis blade.");

			template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(InputValueCItr const &, InputBitsetCItr &input_bitset_itr, InputMapCItr const &, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr const &) {
				*result_value_itr = InputCoefficient::eval<0, 0>(std::make_tuple());
				std::advance(result_value_itr, 1);

				*result_bitset_itr = *input_bitset_itr;
				std::advance(input_bitset_itr, 1);
				std::advance(result_bitset_itr, 1);
			}
		};

		template<default_bitset_t InputPossibleGrades, default_bitset_t ResultPossibleGrades>
		struct _copy_assign<component<stored_value, dynamic_basis_blade<InputPossibleGrades, stored_bitset> >, component<stored_value, dynamic_basis_blade<ResultPossibleGrades, stored_bitset> > > {
			static_assert((InputPossibleGrades & ResultPossibleGrades) == InputPossibleGrades, "The possible grades of the input basis blade must be included in the set of possible brades of the resulting basis blade.");

			template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr const &, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr const &) {
				*result_value_itr = *input_value_itr;
				std::advance(input_value_itr, 1);
				std::advance(result_value_itr, 1);

				*result_bitset_itr = *input_bitset_itr;
				std::advance(input_bitset_itr, 1);
				std::advance(result_bitset_itr, 1);
			}
		};

		template<default_bitset_t BasisVectors>
		struct _copy_zero<component<stored_value, constant_basis_blade<BasisVectors> > > {
			template<typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(ResultValueItr &result_value_itr, ResultBitsetItr const &, ResultMapItr const &) {
				*result_value_itr = 0;
				std::advance(result_value_itr, 1);
			}
		};

		template<default_bitset_t PossibleGrades>
		struct _copy_zero<component<stored_value, dynamic_basis_blade<PossibleGrades, stored_bitset> > > {
			template<typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr const &) {
				*result_value_itr = 0;
				std::advance(result_value_itr, 1);

				*result_bitset_itr = default_bitset_t(0);
				std::advance(result_bitset_itr, 1);
			}
		};

		template<typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
		struct _copy_assign_and_advance_both<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
			template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr) {
				_copy_assign<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
				copy<add_t<NextInputArguments...>, add_t<NextResultArguments...> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
			}
		};

		template<typename InputCoefficient, typename InputBasisBlade, typename... NextInputArguments, typename ResultCoefficient, typename ResultBasisBlade>
		struct _copy_assign_and_advance_both<add<component<InputCoefficient, InputBasisBlade>, NextInputArguments...>, component<ResultCoefficient, ResultBasisBlade> > {
			template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr) {
				_copy_assign<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
				copy<add_t<NextInputArguments...>, component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
			}
		};

		template<typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
		struct _copy_assign_and_advance_both<component<InputCoefficient, InputBasisBlade>, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
			template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr) {
				_copy_assign<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
				copy<component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> >, add_t<NextResultArguments...> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
			}
		};

		template<typename InputCoefficient, typename InputBasisBlade, typename ResultCoefficient, typename ResultBasisBlade>
		struct _copy_assign_and_advance_both<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> > :
			_copy_assign<component<InputCoefficient, InputBasisBlade>, component<ResultCoefficient, ResultBasisBlade> > {
		};
		
		template<typename InputExpression, typename ResultCoefficient, typename ResultBasisBlade, typename... NextResultArguments>
		struct _copy_zero_and_advance_result<InputExpression, add<component<ResultCoefficient, ResultBasisBlade>, NextResultArguments...> > {
			template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr) {
				_copy_zero<component<ResultCoefficient, ResultBasisBlade> >::run(result_value_itr, result_bitset_itr, result_map_itr);
				copy<InputExpression, add_t<NextResultArguments...> >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
			}
		};

		template<typename InputExpression, typename ResultCoefficient, typename ResultBasisBlade>
		struct _copy_zero_and_advance_result<InputExpression, component<ResultCoefficient, ResultBasisBlade> > {
			template<typename InputValueCItr, typename InputBitsetCItr, typename InputMapCItr, typename ResultValueItr, typename ResultBitsetItr, typename ResultMapItr>
			constexpr static void run(InputValueCItr &input_value_itr, InputBitsetCItr &input_bitset_itr, InputMapCItr &input_map_itr, ResultValueItr &result_value_itr, ResultBitsetItr &result_bitset_itr, ResultMapItr &result_map_itr) {
				_copy_zero<component<ResultCoefficient, ResultBasisBlade> >::run(result_value_itr, result_bitset_itr, result_map_itr);
				copy<InputExpression, component<constant_value<0>, constant_basis_blade<default_bitset_t(0)> > >::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
			}
		};

	}

	// Copies the coefficients of the left-hand side Clifford expression into the right-hand side Clifford expression.
	template<typename InputCoefficientType, typename InputExpression, typename ResultCoefficientType, typename ResultExpression>
	constexpr void copy(clifford_expression<InputCoefficientType, InputExpression> const &input, clifford_expression<ResultCoefficientType, ResultExpression> &result) {
		auto input_value_itr = input.values().cbegin();
		auto input_bitset_itr = input.bitsets().cbegin();
		auto input_map_itr = input.maps().cbegin();

		auto result_value_itr = result.values().begin();
		auto result_bitset_itr = result.bitsets().begin();
		auto result_map_itr = result.maps().begin();

		detail::copy<InputExpression, ResultExpression>::run(input_value_itr, input_bitset_itr, input_map_itr, result_value_itr, result_bitset_itr, result_map_itr);
	}

	template<typename CoefficientType, typename Expression>
	constexpr void copy(clifford_expression<CoefficientType, Expression> const &input, clifford_expression<CoefficientType, Expression> &result) {
		result = input;
	}

	template<typename InputType, typename ResultCoefficientType, typename ResultExpression>
	constexpr void copy(InputType const &input, clifford_expression<ResultCoefficientType, ResultExpression> &result) {
		copy(scalar(input), result);
	}

}

#endif // __GA_CORE_COPY_HPP__
