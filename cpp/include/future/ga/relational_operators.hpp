#ifndef __FUTURE_GA_RELATIONAL_OPERATORS_HPP__
#define __FUTURE_GA_RELATIONAL_OPERATORS_HPP__

namespace ga {

	namespace detail {

		// Specializations of lt<LeftType, RightType> with constant.
		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct lt<constant<LeftValue>, constant<RightValue> > {
			constexpr static bool value = LeftValue < RightValue;
		};

		template<default_integral_t LeftValue, class RightLazyCoefficient>
		struct lt<constant<LeftValue>, value<RightLazyCoefficient> > {
			constexpr static bool value = true;
		};

		template<class LeftLazyCoefficient, default_integral_t RightValue>
		struct lt<value<LeftLazyCoefficient>, constant<RightValue> > {
			constexpr static bool value = false;
		};

		template<default_integral_t LeftValue, class RightCoefficient, class RightBasisBlade>
		struct lt<constant<LeftValue>, component<RightCoefficient, RightBasisBlade> > {
			constexpr static bool value = true;
		};

		template<class LeftCoefficient, class LeftBasisBlade, default_integral_t RightValue>
		struct lt<component<LeftCoefficient, LeftBasisBlade>, constant<RightValue> > {
			constexpr static bool value = false;
		};

		template<default_integral_t LeftValue, name_t RightName, class... RightArguments>
		struct lt<constant<LeftValue>, function<RightName, RightArguments...> > {
			constexpr static bool value = true;
		};

		template<name_t LeftName, class... LeftArguments, default_integral_t RightValue>
		struct lt<function<LeftName, LeftArguments...>, constant<RightValue> > {
			constexpr static bool value = false;
		};

		// Specializations of lt<LeftType, RightType> with value.
		template<class LeftLazyCoefficient, class RightLazyCoefficient>
		struct lt<value<LeftLazyCoefficient>, value<RightLazyCoefficient> > {
			constexpr static bool value = lt_v<LeftLazyCoefficient, RightLazyCoefficient>;
		};

		template<class LeftLazyCoefficient, class RightCoefficient, class RightBasisBlade>
		struct lt<value<LeftLazyCoefficient>, component<RightCoefficient, RightBasisBlade> > {
			constexpr static bool value = true;
		};

		template<class LeftCoefficient, class LeftBasisBlade, class RightLazyCoefficient>
		struct lt<component<LeftCoefficient, LeftBasisBlade>, value<RightLazyCoefficient> > {
			constexpr static bool value = false;
		};

		template<class LeftLazyCoefficient, name_t RightName, class RightArgument, class... RightNextArguments>
		struct lt<value<LeftLazyCoefficient>, function<RightName, RightArgument, RightNextArguments...> > {
			constexpr static bool value = le_v<value<LeftLazyCoefficient>, RightArgument>;
		};

		template<name_t LeftName, class LeftArgument, class... LeftNextArguments, class RightLazyCoefficient>
		struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, value<RightLazyCoefficient> > {
			constexpr static bool value = lt_v<LeftArgument, value<RightLazyCoefficient> >;
		};

		// Specializations of lt<LeftType, RightType> with function.
		template<name_t LeftName, class... LeftArguments, name_t RightName, class... RightArguments>
		struct lt<function<LeftName, LeftArguments...>, function<RightName, RightArguments...> > {
			constexpr static bool value = LeftName < RightName || (LeftName == RighName && lt_v<_arguments_list<LeftArguments...>, _arguments_list<RightArguments...> >);
		};

		template<name_t LeftName, class... LeftArguments, class RightCoefficient, class RightBasisBlade>
		struct lt<function<LeftName, LeftArguments...>, component<RightCoefficient, RightBasisBlade> > {
			constexpr static bool value = true;
		};

		template<class LeftCoefficient, class LeftBasisBlade, name_t RightName, class... RightArguments>
		struct lt<component<LeftCoefficient, LeftBasisBlade>, function<RightName, RightArguments...> > {
			constexpr static bool value = false;
		};

		// Specializations of lt<LeftType, RightType> with component.
		template<class LeftCoefficient, class LeftBasisBlade, class RightCoefficient, class RightBasisBlade>
		struct lt<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > {
			constexpr static bool value = lt_v<LeftBasisBlade, RightBasisBlade> || (eq_v<LeftBasisBlade, RightBasisBlade> && lt_v<LeftCoefficient, RightCoefficient>);
		};

		// Specializations of lt<LeftType, RightType> with basis blades.
		template<default_bitset_t LeftBasisVectors, default_bitset_t RightBasisVectors>
		struct lt<constant_basis_blade<LeftBasisVectors>, constant_basis_blade<RightBasisVectors> > {
			constexpr static bool value = possible_grades_v<constant_basis_blade<LeftBasisVectors> > < possible_grades_v<constant_basis_blade<RightBasisVectors> > || (possible_grades_v<constant_basis_blade<LeftBasisVectors> > == possible_grades_v<constant_basis_blade<RightBasisVectors> > && LeftBasisVectors < RightBasisVectors);
		};

		template<default_bitset_t LeftBasisVectors, default_bitset_t RightPossibleGrades, class RightLazyBasisVectors>
		struct lt<constant_basis_blade<LeftBasisVectors>, dynamic_basis_blade<RightPossibleGrades, RightLazyBasisVectors> > {
			constexpr static bool value = possible_grades_v<constant_basis_blade<LeftBasisVectors> > <= RightPossibleGrades;
		};

		template<default_bitset_t LeftPossibleGrades, class LeftLazyBasisVectors, default_bitset_t RightBasisVectors>
		struct lt<dynamic_basis_blade<LeftPossibleGrades, LeftLazyBasisVectors>, constant_basis_blade<RightBasisVectors> > {
			constexpr static bool value = LeftPossibleGrades < possible_grades_v<constant_basis_blade<RightBasisVectors> >;
		};

		template<default_bitset_t LeftPossibleGrades, class LeftLazyBasisVectors, default_bitset_t RightPossibleGrades, class RightLazyBasisVectors>
		struct lt<dynamic_basis_blade<LeftPossibleGrades, LeftLazyBasisVectors>, dynamic_basis_blade<RightPossibleGrades, RightLazyBasisVectors> > {
			constexpr static bool value = LeftPossibleGrades < RightPossibleGrades || (LeftPossibleGrades == RightPossibleGrades && lt_v<LeftLazyBasisVectors, RightLazyBasisVectors>);
		};

		// Specialization of other relational operators.
		template<class LeftType, class RightType>
		struct le {
			constexpr static bool value = lt<LeftType, RightType>::value || !lt<RightType, LeftType>::value;
		};

		template<class LeftType, class RightType>
		struct eq {
			constexpr static bool value = !lt<LeftType, RightType>::value && !lt<RightType, LeftType>::value;
		};

		template<class LeftType, class RightType>
		struct ne {
			constexpr static bool value = lt<LeftType, RightType>::value || lt<RightType, LeftType>::value;
		};

		template<class LeftType, class RightType>
		struct gt {
			constexpr static bool value = !lt<LeftType, RightType>::value && lt<RightType, LeftType>::value;
		};

		template<class LeftType, class RightType>
		struct ge {
			constexpr static bool value = !lt<LeftType, RightType>::value;
		};

	}

}

#endif // __FUTURE_GA_RELATIONAL_OPERATORS_HPP__
