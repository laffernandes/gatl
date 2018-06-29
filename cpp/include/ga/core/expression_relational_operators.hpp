#ifndef __GA_CORE_RELATIONAL_OPERATORS_HPP__
#define __GA_CORE_RELATIONAL_OPERATORS_HPP__

namespace ga {

	namespace detail {

		// Relational operators.
		template<class LeftType, class RightType>
		struct lt :
			std::false_type {
		};

		template<class LeftType, class RightType>
		using lt_t = typename lt<LeftType, RightType>::type;

		template<class LeftType, class RightType>
		constexpr bool lt_v = lt<LeftType, RightType>::value;

		template<class LeftType, class RightType>
		using le_t = std::bool_constant<lt_v<LeftType, RightType> || !lt_v<RightType, LeftType> >;

		template<class LeftType, class RightType>
		constexpr bool le_v = le_t<LeftType, RightType>::value;

		template<class LeftType, class RightType>
		using eq_t = std::bool_constant<!lt_v<LeftType, RightType> && !lt_v<RightType, LeftType> >;

		template<class LeftType, class RightType>
		constexpr bool eq_v = eq_t<LeftType, RightType>::value;

		template<class LeftType, class RightType>
		using ne_t = std::bool_constant<lt_v<LeftType, RightType> || lt_v<RightType, LeftType> >;

		template<class LeftType, class RightType>
		constexpr bool ne_v = ne_t<LeftType, RightType>::value;

		template<class LeftType, class RightType>
		using gt_t = std::bool_constant<!lt_v<LeftType, RightType> && lt_v<RightType, LeftType> >;

		template<class LeftType, class RightType>
		constexpr bool gt_v = gt_t<LeftType, RightType>::value;

		template<class LeftType, class RightType>
		using ge_t = std::bool_constant<!lt_v<LeftType, RightType> >;

		template<class LeftType, class RightType>
		constexpr bool ge_v = ge_t<LeftType, RightType>::value;

		// Specializations of lt<LeftType, RightType> with values.
		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct lt<constant_value<LeftValue>, constant_value<RightValue> > :
			std::bool_constant<(LeftValue < RightValue)> {
		};

		template<default_integral_t LeftValue, tag_t RightTag, std::size_t RightIndex>
		struct lt<constant_value<LeftValue>, get_value<RightTag, RightIndex> > :
			std::true_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, default_integral_t RightValue>
		struct lt<get_value<LeftTag, LeftIndex>, constant_value<RightValue> > :
			std::false_type {
		};

		template<default_integral_t LeftValue, tag_t RightTag, std::size_t RightIndex>
		struct lt<constant_value<LeftValue>, get_map_values<RightTag, RightIndex> > :
			std::true_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, default_integral_t RightValue>
		struct lt<get_map_values<LeftTag, LeftIndex>, constant_value<RightValue> > :
			std::false_type {
		};

		template<default_integral_t LeftValue>
		struct lt<constant_value<LeftValue>, stored_value> :
			std::true_type {
		};

		template<default_integral_t RightValue>
		struct lt<stored_value, constant_value<RightValue> > :
			std::false_type {
		};

		template<default_integral_t LeftValue>
		struct lt<constant_value<LeftValue>, stored_map_values> :
			std::true_type {
		};

		template<default_integral_t RightValue>
		struct lt<stored_map_values, constant_value<RightValue> > :
			std::false_type {
		};

		template<default_integral_t LeftValue, name_t RightName, class... RightArguments>
		struct lt<constant_value<LeftValue>, function<RightName, RightArguments...> > :
			std::true_type {
		};

		template<name_t LeftName, class... LeftArguments, default_integral_t RightValue>
		struct lt<function<LeftName, LeftArguments...>, constant_value<RightValue> > :
			std::false_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
		struct lt<get_value<LeftTag, LeftIndex>, get_value<RightTag, RightIndex> > :
			std::bool_constant<(LeftTag < RightTag || (LeftTag == RightTag && LeftIndex < RightIndex))> {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
		struct lt<get_value<LeftTag, LeftIndex>, get_map_values<RightTag, RightIndex> > :
			std::bool_constant<(LeftTag <= RightTag)> {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
		struct lt<get_map_values<LeftTag, LeftIndex>, get_value<RightTag, RightIndex> > :
			std::bool_constant<(LeftTag < RightTag)> {
		};

		template<tag_t LeftTag, std::size_t LeftIndex>
		struct lt<get_value<LeftTag, LeftIndex>, stored_value> :
			std::true_type {
		};

		template<tag_t RightTag, std::size_t RightIndex>
		struct lt<stored_value, get_value<RightTag, RightIndex> > :
			std::false_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex>
		struct lt<get_value<LeftTag, LeftIndex>, stored_map_values> :
			std::true_type {
		};

		template<tag_t RightTag, std::size_t RightIndex>
		struct lt<stored_map_values, get_value<RightTag, RightIndex> > :
			std::false_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, name_t RightName, class RightArgument, class... RightNextArguments>
		struct lt<get_value<LeftTag, LeftIndex>, function<RightName, RightArgument, RightNextArguments...> > :
			le_t<get_value<LeftTag, LeftIndex>, RightArgument> {
		};

		template<name_t LeftName, class LeftArgument, class... LeftNextArguments, tag_t RightTag, std::size_t RightIndex>
		struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, get_value<RightTag, RightIndex> > :
			lt_t<LeftArgument, get_value<RightTag, RightIndex> > {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
		struct lt<get_map_values<LeftTag, LeftIndex>, get_map_values<RightTag, RightIndex> > :
			std::bool_constant<(LeftTag < RightTag || (LeftTag == RightTag && LeftIndex < RightIndex))> {
		};

		template<tag_t LeftTag, std::size_t LeftIndex>
		struct lt<get_map_values<LeftTag, LeftIndex>, stored_value> :
			std::true_type {
		};

		template<tag_t RightTag, std::size_t RightIndex>
		struct lt<stored_value, get_map_values<RightTag, RightIndex> > :
			std::false_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex>
		struct lt<get_map_values<LeftTag, LeftIndex>, stored_map_values> :
			std::true_type {
		};

		template<tag_t RightTag, std::size_t RightIndex>
		struct lt<stored_map_values, get_map_values<RightTag, RightIndex> > :
			std::false_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, name_t RightName, class RightArgument, class... RightNextArguments>
		struct lt<get_map_values<LeftTag, LeftIndex>, function<RightName, RightArgument, RightNextArguments...> > :
			le_t<get_map_values<LeftTag, LeftIndex>, RightArgument> {
		};

		template<name_t LeftName, class LeftArgument, class... LeftNextArguments, tag_t RightTag, std::size_t RightIndex>
		struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, get_map_values<RightTag, RightIndex> > :
			lt_t<LeftArgument, get_map_values<RightTag, RightIndex> > {
		};

		template<>
		struct lt<stored_value, stored_value> :
			std::false_type {
		};

		template<>
		struct lt<stored_value, stored_map_values> :
			std::true_type {
		};

		template<>
		struct lt<stored_map_values, stored_value> :
			std::false_type {
		};

		template<name_t RightName, class RightArgument, class... RightNextArguments>
		struct lt<stored_value, function<RightName, RightArgument, RightNextArguments...> > :
			le_t<stored_value, RightArgument> {
		};

		template<name_t LeftName, class LeftArgument, class... LeftNextArguments>
		struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, stored_value> :
			lt_t<LeftArgument, stored_value> {
		};

		template<>
		struct lt<stored_map_values, stored_map_values> :
			std::false_type {
		};

		template<name_t RightName, class RightArgument, class... RightNextArguments>
		struct lt<stored_map_values, function<RightName, RightArgument, RightNextArguments...> > :
			le_t<stored_map_values, RightArgument> {
		};

		template<name_t LeftName, class LeftArgument, class... LeftNextArguments>
		struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, stored_map_values> :
			lt_t<LeftArgument, stored_map_values> {
		};

		// Specializations of lt<LeftType, RightType> with bitsets.
		template<default_bitset_t LeftBitset, default_bitset_t RightBitset>
		struct lt<constant_bitset<LeftBitset>, constant_bitset<RightBitset> > :
			std::bool_constant<(LeftBitset < RightBitset)> {
		};

		template<default_bitset_t LeftBitset, tag_t RightTag, std::size_t RightIndex>
		struct lt<constant_bitset<LeftBitset>, get_bitset<RightTag, RightIndex> > :
			std::true_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, default_bitset_t RightBitset>
		struct lt<get_bitset<LeftTag, LeftIndex>, constant_bitset<RightBitset> > :
			std::false_type {
		};

		template<default_bitset_t LeftBitset, tag_t RightTag, std::size_t RightIndex>
		struct lt<constant_bitset<LeftBitset>, get_map_bitsets<RightTag, RightIndex> > :
			std::true_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, default_bitset_t RightBitset>
		struct lt<get_map_bitsets<LeftTag, LeftIndex>, constant_bitset<RightBitset> > :
			std::false_type {
		};

		template<default_bitset_t LeftBitset>
		struct lt<constant_bitset<LeftBitset>, stored_bitset> :
			std::true_type {
		};

		template<default_bitset_t RightBitset>
		struct lt<stored_bitset, constant_bitset<RightBitset> > :
			std::false_type {
		};

		template<default_bitset_t LeftBitset>
		struct lt<constant_bitset<LeftBitset>, stored_map_bitsets> :
			std::true_type {
		};

		template<default_bitset_t RightBitset>
		struct lt<stored_map_bitsets, constant_bitset<RightBitset> > :
			std::false_type {
		};

		template<default_bitset_t LeftBitset, name_t RightName, class... RightArguments>
		struct lt<constant_bitset<LeftBitset>, function<RightName, RightArguments...> > :
			std::true_type {
		};

		template<name_t LeftName, class... LeftArguments, default_bitset_t RightBitset>
		struct lt<function<LeftName, LeftArguments...>, constant_bitset<RightBitset> > :
			std::false_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
		struct lt<get_bitset<LeftTag, LeftIndex>, get_bitset<RightTag, RightIndex> > :
			std::bool_constant<(LeftTag < RightTag || (LeftTag == RightTag && LeftIndex < RightIndex))> {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
		struct lt<get_bitset<LeftTag, LeftIndex>, get_map_bitsets<RightTag, RightIndex> > :
			std::bool_constant<(LeftTag <= RightTag)> {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
		struct lt<get_map_bitsets<LeftTag, LeftIndex>, get_bitset<RightTag, RightIndex> > :
			std::bool_constant<(LeftTag < RightTag)> {
		};

		template<tag_t LeftTag, std::size_t LeftIndex>
		struct lt<get_bitset<LeftTag, LeftIndex>, stored_bitset> :
			std::true_type {
		};

		template<tag_t RightTag, std::size_t RightIndex>
		struct lt<stored_bitset, get_bitset<RightTag, RightIndex> > :
			std::false_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex>
		struct lt<get_bitset<LeftTag, LeftIndex>, stored_map_bitsets> :
			std::true_type {
		};

		template<tag_t RightTag, std::size_t RightIndex>
		struct lt<stored_map_bitsets, get_bitset<RightTag, RightIndex> > :
			std::false_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, name_t RightName, class RightArgument, class... RightNextArguments>
		struct lt<get_bitset<LeftTag, LeftIndex>, function<RightName, RightArgument, RightNextArguments...> > :
			le_t<get_bitset<LeftTag, LeftIndex>, RightArgument> {
		};

		template<name_t LeftName, class LeftArgument, class... LeftNextArguments, tag_t RightTag, std::size_t RightIndex>
		struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, get_bitset<RightTag, RightIndex> > :
			lt_t<LeftArgument, get_bitset<RightTag, RightIndex> > {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, tag_t RightTag, std::size_t RightIndex>
		struct lt<get_map_bitsets<LeftTag, LeftIndex>, get_map_bitsets<RightTag, RightIndex> > :
			std::bool_constant<(LeftTag < RightTag || (LeftTag == RightTag && LeftIndex < RightIndex))> {
		};

		template<tag_t LeftTag, std::size_t LeftIndex>
		struct lt<get_map_bitsets<LeftTag, LeftIndex>, stored_bitset> :
			std::true_type {
		};

		template<tag_t RightTag, std::size_t RightIndex>
		struct lt<stored_bitset, get_map_bitsets<RightTag, RightIndex> > :
			std::false_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex>
		struct lt<get_map_bitsets<LeftTag, LeftIndex>, stored_map_bitsets> :
			std::true_type {
		};

		template<tag_t RightTag, std::size_t RightIndex>
		struct lt<stored_map_bitsets, get_map_bitsets<RightTag, RightIndex> > :
			std::false_type {
		};

		template<tag_t LeftTag, std::size_t LeftIndex, name_t RightName, class RightArgument, class... RightNextArguments>
		struct lt<get_map_bitsets<LeftTag, LeftIndex>, function<RightName, RightArgument, RightNextArguments...> > :
			le_t<get_map_bitsets<LeftTag, LeftIndex>, RightArgument> {
		};

		template<name_t LeftName, class LeftArgument, class... LeftNextArguments, tag_t RightTag, std::size_t RightIndex>
		struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, get_map_bitsets<RightTag, RightIndex> > :
			lt_t<LeftArgument, get_map_bitsets<RightTag, RightIndex> > {
		};

		template<>
		struct lt<stored_bitset, stored_bitset> :
			std::false_type {
		};

		template<>
		struct lt<stored_bitset, stored_map_bitsets> :
			std::true_type {
		};

		template<>
		struct lt<stored_map_bitsets, stored_bitset> :
			std::false_type {
		};

		template<name_t RightName, class RightArgument, class... RightNextArguments>
		struct lt<stored_bitset, function<RightName, RightArgument, RightNextArguments...> > :
			le_t<stored_bitset, RightArgument> {
		};

		template<name_t LeftName, class LeftArgument, class... LeftNextArguments>
		struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, stored_bitset> :
			lt_t<LeftArgument, stored_bitset> {
		};
		template<>
		struct lt<stored_map_bitsets, stored_map_bitsets> :
			std::false_type {
		};

		template<name_t RightName, class RightArgument, class... RightNextArguments>
		struct lt<stored_map_bitsets, function<RightName, RightArgument, RightNextArguments...> > :
			le_t<stored_map_bitsets, RightArgument> {
		};

		template<name_t LeftName, class LeftArgument, class... LeftNextArguments>
		struct lt<function<LeftName, LeftArgument, LeftNextArguments...>, stored_map_bitsets> :
			lt_t<LeftArgument, stored_map_bitsets> {
		};

		// Specializations of lt<LeftType, RightType> with basis blades.
		template<default_bitset_t LeftBasisVectors, default_bitset_t RightBasisVectors>
		struct lt<constant_basis_blade<LeftBasisVectors>, constant_basis_blade<RightBasisVectors> > :
			std::bool_constant<(possible_grades_v<constant_basis_blade<LeftBasisVectors> > < possible_grades_v<constant_basis_blade<RightBasisVectors> > || (possible_grades_v<constant_basis_blade<LeftBasisVectors> > == possible_grades_v<constant_basis_blade<RightBasisVectors> > && LeftBasisVectors < RightBasisVectors))> {
		};

		template<default_bitset_t LeftBasisVectors, default_bitset_t RightPossibleGrades, class RightBitset>
		struct lt<constant_basis_blade<LeftBasisVectors>, dynamic_basis_blade<RightPossibleGrades, RightBitset> > :
			std::bool_constant<(possible_grades_v<constant_basis_blade<LeftBasisVectors> > <= RightPossibleGrades)> {
		};

		template<default_bitset_t LeftPossibleGrades, class LeftBitset, default_bitset_t RightBasisVectors>
		struct lt<dynamic_basis_blade<LeftPossibleGrades, LeftBitset>, constant_basis_blade<RightBasisVectors> > :
			std::bool_constant<(LeftPossibleGrades < possible_grades_v<constant_basis_blade<RightBasisVectors> >)> {
		};

		template<default_bitset_t LeftPossibleGrades, class LeftBitset, default_bitset_t RightPossibleGrades, class RightBitset>
		struct lt<dynamic_basis_blade<LeftPossibleGrades, LeftBitset>, dynamic_basis_blade<RightPossibleGrades, RightBitset> > :
			std::bool_constant<(LeftPossibleGrades < RightPossibleGrades || (LeftPossibleGrades == RightPossibleGrades && lt_v<LeftBitset, RightBitset>))> {
		};

		// Specializations of lt<LeftType, RightType> with components.
		template<class LeftCoefficient, class LeftBasisBlade, class RightCoefficient, class RightBasisBlade>
		struct lt<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > :
			std::bool_constant<(lt_v<LeftBasisBlade, RightBasisBlade> || (eq_v<LeftBasisBlade, RightBasisBlade> && lt_v<LeftCoefficient, RightCoefficient>))> {
		};

		// Specializations of lt<LeftType, RightType> with functions.
		template<class... Arguments>
		struct _lt_arguments_list {
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct lt<_lt_arguments_list<LeftArgument, LeftNextArguments...>, _lt_arguments_list<RightArgument, RightNextArguments...> > :
			std::bool_constant<(lt_v<LeftArgument, RightArgument> || (eq_v<LeftArgument, RightArgument> && lt_v<_lt_arguments_list<LeftNextArguments...>, _lt_arguments_list<RightNextArguments...> >))> {
		};

		template<class LeftArgument, class RightArgument, class... RightNextArguments>
		struct lt<_lt_arguments_list<LeftArgument>, _lt_arguments_list<RightArgument, RightNextArguments...> > :
			le_t<LeftArgument, RightArgument> {
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument>
		struct lt<_lt_arguments_list<LeftArgument, LeftNextArguments...>, _lt_arguments_list<RightArgument> > :
			lt_t<LeftArgument, RightArgument> {
		};

		template<class LeftArgument, class RightArgument>
		struct lt<_lt_arguments_list<LeftArgument>, _lt_arguments_list<RightArgument> > :
			lt_t<LeftArgument, RightArgument> {
		};

		template<name_t LeftName, class... LeftArguments, name_t RightName, class... RightArguments>
		struct lt<function<LeftName, LeftArguments...>, function<RightName, RightArguments...> > :
			std::bool_constant<(LeftName < RightName || (LeftName == RightName && lt_v<_lt_arguments_list<LeftArguments...>, _lt_arguments_list<RightArguments...> >))> {
		};

	}

}

#endif // __GA_CORE_RELATIONAL_OPERATORS_HPP__
