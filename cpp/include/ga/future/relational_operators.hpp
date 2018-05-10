#ifndef __GA_FUTURE_RELATIONAL_OPERATORS_HPP__
#define __GA_FUTURE_RELATIONAL_OPERATORS_HPP__

namespace future {

	namespace detail {

		//TODO Rever a ordenação de funções

		// Specializations of id_cmp<LeftIds...>::lt<RightIds...>.
		template<id_t LeftId, id_t... LeftSubIds>
		struct id_cmp<LeftId, LeftSubIds...> {
			template<id_t... RightId>
			struct lt;

			template<id_t RightId, id_t... RightSubIds>
			struct lt<RightId, RightSubIds...> {
				constexpr static bool value = LeftId < RightId || (LeftId == RightId && id_cmp<LeftSubIds...>::lt_v<RightSubIds...>);
			};

			template<>
			struct lt<> {
				constexpr static bool value = false;
			};

			template<id_t... RightId>
			constexpr static bool lt_v = lt<RightId...>::value;
		};

		template<>
		struct id_cmp<> {
			template<id_t... RightId>
			struct lt;

			template<id_t RightId, id_t... RightSubIds>
			struct lt<RightId, RightSubIds...> {
				constexpr static bool value = true;
			};

			template<>
			struct lt<> {
				constexpr static bool value = false;
			};

			template<id_t... RightId>
			constexpr static bool lt_v = lt<RightId...>::value;
		};

		// Specializations of lt<LeftType, RightType> with constant.
		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct lt<constant<LeftValue>, constant<RightValue> > {
			constexpr static bool value = LeftValue < RightValue;
		};

		template<default_integral_t LeftValue, id_t... RightId>
		struct lt<constant<LeftValue>, value<RightId...> > {
			constexpr static bool value = true;
		};

		template<id_t... LeftId, default_integral_t RightValue>
		struct lt<value<LeftId...>, constant<RightValue> > {
			constexpr static bool value = false;
		};

		template<default_integral_t LeftValue, class... RightArguments>
		struct lt<constant<LeftValue>, add<RightArguments...> > {
			constexpr static bool value = true;
		};

		template<class... LeftArguments, default_integral_t RightValue>
		struct lt<add<LeftArguments...>, constant<RightValue> > {
			constexpr static bool value = false;
		};

		template<default_integral_t LeftValue, class... RightArguments>
		struct lt<constant<LeftValue>, mul<RightArguments...> > {
			constexpr static bool value = true;
		};

		template<class... LeftArguments, default_integral_t RightValue>
		struct lt<mul<LeftArguments...>, constant<RightValue> > {
			constexpr static bool value = false;
		};

		template<default_integral_t LeftValue, class RightLeftArgument, class RightRightArgument>
		struct lt<constant<LeftValue>, power<RightLeftArgument, RightRightArgument> > {
			constexpr static bool value = true;
		};

		template<class LeftLeftArgument, class LeftRightArgument, default_integral_t RightValue>
		struct lt<power<LeftLeftArgument, LeftRightArgument>, constant<RightValue> > {
			constexpr static bool value = false;
		};

		template<default_integral_t LeftValue, class RightTag, class RightArguments>
		struct lt<constant<LeftValue>, function<RightTag, RightArguments> > {
			constexpr static bool value = true;
		};

		template<class LeftTag, class LeftArguments, default_integral_t RightValue>
		struct lt<function<LeftTag, LeftArguments>, constant<RightValue> > {
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

		// Specializations of lt<LeftType, RightType> with value.
		template<id_t... LeftId, id_t... RightId>
		struct lt<value<LeftId...>, value<RightId...> > {
			constexpr static bool value = id_cmp<LeftId...>::lt_v<RightId...>;
		};

		template<id_t... LeftId, class RightArgument, class... RightNextArguments>
		struct lt<value<LeftId...>, add<RightArgument, RightNextArguments...> > {
			constexpr static bool value = le_v<value<LeftId...>, RightArgument>;
		};

		template<id_t... LeftId>
		struct lt<value<LeftId...>, add<> > {
			constexpr static bool value = false;
		};

		template<class LeftArgument, class... LeftNextArguments, id_t... RightId>
		struct lt<add<LeftArgument, LeftNextArguments...>, value<RightId...> > {
			constexpr static bool value = lt_v<LeftArgument, value<RightId...> >;
		};

		template<id_t... RightId>
		struct lt<add<>, value<RightId...> > {
			constexpr static bool value = true;
		};

		template<id_t... LeftId, class RightArgument, class... RightNextArguments>
		struct lt<value<LeftId...>, mul<RightArgument, RightNextArguments...> > {
			constexpr static bool value = le_v<value<LeftId...>, RightArgument>;
		};

		template<id_t... LeftId>
		struct lt<value<LeftId...>, mul<> > {
			constexpr static bool value = false;
		};

		template<class LeftArgument, class... LeftNextArguments, id_t... RightId>
		struct lt<mul<LeftArgument, LeftNextArguments...>, value<RightId...> > {
			constexpr static bool value = lt_v<LeftArgument, value<RightId...> >;
		};

		template<id_t... RightId>
		struct lt<mul<>, value<RightId...> > {
			constexpr static bool value = true;
		};

		template<id_t... LeftId, class RightLeftArgument, class RightRightArgument>
		struct lt<value<LeftId...>, power<RightLeftArgument, RightRightArgument> > {
			constexpr static bool value = le_v<value<LeftId...>, RightLeftArgument>;
		};

		template<class LeftLeftArgument, class LeftRightArgument, id_t... RightId>
		struct lt<power<LeftLeftArgument, LeftRightArgument>, value<RightId...> > {
			constexpr static bool value = lt_v<LeftLeftArgument, value<RightId...> >;
		};

		template<id_t... LeftId, class RightTag, class RightArguments>
		struct lt<value<LeftId...>, function<RightTag, RightArguments> > {
			constexpr static bool value = true;
		};

		template<class LeftTag, class LeftArguments, id_t... RightId>
		struct lt<function<LeftTag, LeftArguments>, value<RightId...> > {
			constexpr static bool value = false;
		};

		template<id_t... LeftId, class RightCoefficient, class RightBasisBlade>
		struct lt<value<LeftId...>, component<RightCoefficient, RightBasisBlade> > {
			constexpr static bool value = true;
		};

		template<class LeftCoefficient, class LeftBasisBlade, id_t... RightId>
		struct lt<component<LeftCoefficient, LeftBasisBlade>, value<RightId...> > {
			constexpr static bool value = false;
		};

		// Specializations of lt<LeftType, RightType> with add.
		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct lt<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...> > {
			constexpr static bool value = lt_v<LeftArgument, RightArgument> || (eq_v<LeftArgument, RightArgument> && lt_v<add<LeftNextArguments...>, add<RightNextArguments...> >);
		};

		template<class LeftArgument, class... LeftNextArguments>
		struct lt<add<LeftArgument, LeftNextArguments...>, add<> > {
			constexpr static bool value = lt_v<add<LeftArgument, LeftNextArguments...>, constant<0> >;
		};

		template<class RightArgument, class... RightNextArguments>
		struct lt<add<>, add<RightArgument, RightNextArguments...> > {
			constexpr static bool value = lt_v<constant<0>, add<RightArgument, RightNextArguments...> >;
		};

		template<>
		struct lt<add<>, add<> > {
			constexpr static bool value = false;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct lt<add<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...> > {
			constexpr static bool value = lt_v<LeftArgument, mul<RightArgument, RightNextArguments...> >;
		};

		template<class LeftArgument, class... LeftNextArguments>
		struct lt<add<LeftArgument, LeftNextArguments...>, mul<> > {
			constexpr static bool value = lt_v<LeftArgument, constant<1> >;
		};

		template<class RightArgument, class... RightNextArguments>
		struct lt<add<>, mul<RightArgument, RightNextArguments...> > {
			constexpr static bool value = lt_v<constant<0>, mul<RightArgument, RightNextArguments...> >;
		};

		template<>
		struct lt<add<>, mul<> > {
			constexpr static bool value = true;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct lt<mul<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...> > {
			constexpr static bool value = le_v<mul<LeftArgument, LeftNextArguments...>, RightArgument>;
		};

		template<class LeftArgument, class... LeftNextArguments>
		struct lt<mul<LeftArgument, LeftNextArguments...>, add<> > {
			constexpr static bool value = le_v<mul<LeftArgument, LeftNextArguments...>, constant<0> >;
		};

		template<class RightArgument, class... RightNextArguments>
		struct lt<mul<>, add<RightArgument, RightNextArguments...> > {
			constexpr static bool value = le_v<constant<1>, RightArgument>;
		};

		template<>
		struct lt<mul<>, add<> > {
			constexpr static bool value = false;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightLeftArgument, class RightRightArgument>
		struct lt<add<LeftArgument, LeftNextArguments...>, power<RightLeftArgument, RightRightArgument> > {
			constexpr static bool value = lt_v<LeftArgument, power<RightLeftArgument, RightRightArgument> >;
		};

		template<class RightLeftArgument, class RightRightArgument>
		struct lt<add<>, power<RightLeftArgument, RightRightArgument> > {
			constexpr static bool value = lt_v<constant<0>, power<RightLeftArgument, RightRightArgument> >;
		};

		template<class LeftLeftArgument, class LeftRightArgument, class RightArgument, class... RightNextArguments>
		struct lt<power<LeftLeftArgument, LeftRightArgument>, add<RightArgument, RightNextArguments...> > {
			constexpr static bool value = le_v<power<LeftLeftArgument, LeftRightArgument>, RightArgument>;
		};

		template<class LeftLeftArgument, class LeftRightArgument>
		struct lt<power<LeftLeftArgument, LeftRightArgument>, add<> > {
			constexpr static bool value = le_v<power<LeftLeftArgument, LeftRightArgument>, constant<0> >;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightTag, class RightArguments>
		struct lt<add<LeftArgument, LeftNextArguments...>, function<RightTag, RightArguments> > {
			constexpr static bool value = lt_v<LeftArgument, function<RightTag, RightArguments> >;
		};

		template<class RightTag, class RightArguments>
		struct lt<add<>, function<RightTag, RightArguments> > {
			constexpr static bool value = lt_v<constant<0>, function<RightTag, RightArguments> >;
		};

		template<class LeftTag, class LeftArguments, class RightArgument, class... RightNextArguments>
		struct lt<function<LeftTag, LeftArguments>, add<RightArgument, RightNextArguments...> > {
			constexpr static bool value = le_v<function<LeftTag, LeftArguments>, RightArgument>;
		};

		template<class LeftTag, class LeftArguments>
		struct lt<function<LeftTag, LeftArguments>, add<> > {
			constexpr static bool value = le_v<function<LeftTag, LeftArguments>, constant<0> >;
		};

		template<class... LeftArguments, class RightCoefficient, class RightBasisBlade>
		struct lt<add<LeftArguments...>, component<RightCoefficient, RightBasisBlade> > {
			constexpr static bool value = true;
		};

		template<class LeftCoefficient, class LeftBasisBlade, class... RightArguments>
		struct lt<component<LeftCoefficient, LeftBasisBlade>, add<RightArguments...> > {
			constexpr static bool value = false;
		};

		// Specializations of lt<LeftType, RightType> with mul.
		template<class LeftArgument, class... LeftNextArguments, class RightArgument, class... RightNextArguments>
		struct lt<mul<LeftArgument, LeftNextArguments...>, mul<RightArgument, RightNextArguments...> > {
			constexpr static bool value = lt_v<LeftArgument, RightArgument> || (eq_v<LeftArgument, RightArgument> && lt_v<mul<LeftNextArguments...>, mul<RightNextArguments...> >);
		};

		template<class LeftArgument, class... LeftNextArguments>
		struct lt<mul<LeftArgument, LeftNextArguments...>, mul<> > {
			constexpr static bool value = lt_v<mul<LeftArgument, LeftNextArguments...>, constant<1> >;
		};

		template<class RightArgument, class... RightNextArguments>
		struct lt<mul<>, mul<RightArgument, RightNextArguments...> > {
			constexpr static bool value = lt_v<constant<1>, mul<RightArgument, RightNextArguments...> >;
		};

		template<>
		struct lt<mul<>, mul<> > {
			constexpr static bool value = false;
		};
		
		template<class LeftArgument, class... LeftNextArguments, class RightLeftArgument, class RightRightArgument>
		struct lt<mul<LeftArgument, LeftNextArguments...>, power<RightLeftArgument, RightRightArgument> > {
			constexpr static bool value = lt_v<LeftArgument, power<RightLeftArgument, RightRightArgument> >;
		};

		template<class RightLeftArgument, class RightRightArgument>
		struct lt<mul<>, power<RightLeftArgument, RightRightArgument> > {
			constexpr static bool value = lt_v<constant<1>, power<RightLeftArgument, RightRightArgument> >;
		};

		template<class LeftLeftArgument, class LeftRightArgument, class RightArgument, class... RightNextArguments>
		struct lt<power<LeftLeftArgument, LeftRightArgument>, mul<RightArgument, RightNextArguments...> > {
			constexpr static bool value = le_v<power<LeftLeftArgument, LeftRightArgument>, RightArgument>;
		};

		template<class LeftLeftArgument, class LeftRightArgument>
		struct lt<power<LeftLeftArgument, LeftRightArgument>, mul<> > {
			constexpr static bool value = le_v<power<LeftLeftArgument, LeftRightArgument>, constant<1> >;
		};

		template<class LeftArgument, class... LeftNextArguments, class RightTag, class RightArguments>
		struct lt<mul<LeftArgument, LeftNextArguments...>, function<RightTag, RightArguments> > {
			constexpr static bool value = lt_v<LeftArgument, function<RightTag, RightArguments> >;
		};

		template<class RightTag, class RightArguments>
		struct lt<mul<>, function<RightTag, RightArguments> > {
			constexpr static bool value = lt_v<constant<1>, function<RightTag, RightArguments> >;
		};

		template<class LeftTag, class LeftArguments, class RightArgument, class... RightNextArguments>
		struct lt<function<LeftTag, LeftArguments>, mul<RightArgument, RightNextArguments...> > {
			constexpr static bool value = le_v<function<LeftTag, LeftArguments>, RightArgument>;
		};

		template<class LeftTag, class LeftArguments>
		struct lt<function<LeftTag, LeftArguments>, mul<> > {
			constexpr static bool value = le_v<function<LeftTag, LeftArguments>, constant<1> >;
		};

		template<class... LeftArguments, class RightCoefficient, class RightBasisBlade>
		struct lt<mul<LeftArguments...>, component<RightCoefficient, RightBasisBlade> > {
			constexpr static bool value = true;
		};

		template<class LeftCoefficient, class LeftBasisBlade, class... RightArguments>
		struct lt<component<LeftCoefficient, LeftBasisBlade>, mul<RightArguments...> > {
			constexpr static bool value = false;
		};
		
		// Specializations of lt<LeftType, RightType> with power.
		template<class LeftLeftArgument, class LeftRightArgument, class RightLeftArgument, class RightRightArgument>
		struct lt<power<LeftLeftArgument, LeftRightArgument>, power<RightLeftArgument, RightRightArgument> > {
			constexpr static bool value = lt_v<LeftLeftArgument, RightLeftArgument> || (eq_v<LeftLeftArgument, RightLeftArgument> && lt_v<LeftRightArgument, RightRightArgument>);
		};

		template<class LeftLeftArgument, class LeftRightArgument, class RightTag, class RightArguments>
		struct lt<power<LeftLeftArgument, LeftRightArgument>, function<RightTag, RightArguments> > {
			constexpr static bool value = true;
		};

		template<class LeftTag, class LeftArguments, class RightLeftArgument, class RightRightArgument>
		struct lt<function<LeftTag, LeftArguments>, power<RightLeftArgument, RightRightArgument> > {
			constexpr static bool value = false;
		};

		template<class LeftLeftArgument, class LeftRightArgument, class RightCoefficient, class RightBasisBlade>
		struct lt<power<LeftLeftArgument, LeftRightArgument>, component<RightCoefficient, RightBasisBlade> > {
			constexpr static bool value = true;
		};

		template<class LeftCoefficient, class LeftBasisBlade, class RightLeftArgument, class RightRightArgument>
		struct lt<component<LeftCoefficient, LeftBasisBlade>, power<RightLeftArgument, RightRightArgument> > {
			constexpr static bool value = false;
		};

		// Specializations of lt<LeftType, RightType> with function.
		template<class LeftTag, class LeftArguments, class RightTag, class RightArguments>
		struct lt<function<LeftTag, LeftArguments>, function<RightTag, RightArguments> > {
			constexpr static bool value = lt_v<LeftTag, RightTag> || (eq_v<LeftTag, RightTag> && lt_v<LeftArguments, RightArguments>);
		};

		template<class LeftTag, class LeftArguments, class RightCoefficient, class RightBasisBlade>
		struct lt<function<LeftTag, LeftArguments>, component<RightCoefficient, RightBasisBlade> > {
			constexpr static bool value = true;
		};

		template<class LeftCoefficient, class LeftBasisBlade, class RightTag, class RightArguments>
		struct lt<component<LeftCoefficient, LeftBasisBlade>, function<RightTag, RightArguments> > {
			constexpr static bool value = false;
		};

		// Specializations of lt<LeftType, RightType> with component.
		template<class LeftCoefficient, class LeftBasisBlade, class RightCoefficient, class RightBasisBlade>
		struct lt<component<LeftCoefficient, LeftBasisBlade>, component<RightCoefficient, RightBasisBlade> > {
			constexpr static bool value = lt_v<LeftBasisBlade, RightBasisBlade>;
		};

		// Specializations of lt<LeftType, RightType> with basis blades.
		template<default_bitset_t LeftBasisVectors, default_bitset_t RightBasisVectors>
		struct lt<constant_basis_blade<LeftBasisVectors>, constant_basis_blade<RightBasisVectors> > {
			constexpr static bool value = possible_grades_v<constant_basis_blade<LeftBasisVectors> > < possible_grades_v<constant_basis_blade<RightBasisVectors> > || (possible_grades_v<constant_basis_blade<LeftBasisVectors> > == possible_grades_v<constant_basis_blade<RightBasisVectors> > && LeftBasisVectors < RightBasisVectors);
		};

		template<default_bitset_t LeftBasisVectors, default_bitset_t RightPossibleGrades, id_t... RightId>
		struct lt<constant_basis_blade<LeftBasisVectors>, dynamic_basis_blade<RightPossibleGrades, RightId...> > {
			constexpr static bool value = possible_grades_v<constant_basis_blade<LeftBasisVectors> > <= RightPossibleGrades;
		};

		template<default_bitset_t LeftPossibleGrades, id_t... LeftId, default_bitset_t RightBasisVectors>
		struct lt<dynamic_basis_blade<LeftPossibleGrades, LeftId...>, constant_basis_blade<RightBasisVectors> > {
			constexpr static bool value = LeftPossibleGrades < possible_grades_v<constant_basis_blade<RightBasisVectors> >;
		};

		template<default_bitset_t LeftBasisVectors, default_bitset_t RightPossibleGrades, id_t... RightId>
		struct lt<constant_basis_blade<LeftBasisVectors>, dynamic_basis_blades<RightPossibleGrades, RightId...> > {
			constexpr static bool value = possible_grades_v<constant_basis_blade<LeftBasisVectors> > <= RightPossibleGrades;
		};

		template<default_bitset_t LeftPossibleGrades, id_t... LeftId, default_bitset_t RightBasisVectors>
		struct lt<dynamic_basis_blades<LeftPossibleGrades, LeftId...>, constant_basis_blade<RightBasisVectors> > {
			constexpr static bool value = LeftPossibleGrades < possible_grades_v<constant_basis_blade<RightBasisVectors> >;
		};

		template<default_bitset_t LeftPossibleGrades, id_t... LeftId, default_bitset_t RightPossibleGrades, id_t... RightId>
		struct lt<dynamic_basis_blade<LeftPossibleGrades, LeftId...>, dynamic_basis_blade<RightPossibleGrades, RightId...> > {
			constexpr static bool value = LeftPossibleGrades < RightPossibleGrades || (LeftPossibleGrades == RightPossibleGrades && id_cmp<LeftId...>::lt_v<RightId...>);
		};

		template<default_bitset_t LeftPossibleGrades, id_t... LeftId, default_bitset_t RightPossibleGrades, id_t... RightId>
		struct lt<dynamic_basis_blade<LeftPossibleGrades, LeftId...>, dynamic_basis_blades<RightPossibleGrades, RightId...> > {
			constexpr static bool value = LeftPossibleGrades < RightPossibleGrades || (LeftPossibleGrades == RightPossibleGrades && id_cmp<LeftId...>::lt_v<RightId...>);
		};

		template<default_bitset_t LeftPossibleGrades, id_t... LeftId, default_bitset_t RightPossibleGrades, id_t... RightId>
		struct lt<dynamic_basis_blades<LeftPossibleGrades, LeftId...>, dynamic_basis_blade<RightPossibleGrades, RightId...> > {
			constexpr static bool value = LeftPossibleGrades < RightPossibleGrades || (LeftPossibleGrades == RightPossibleGrades && id_cmp<LeftId...>::lt_v<RightId...>);
		};

		template<default_bitset_t LeftPossibleGrades, id_t... LeftId, default_bitset_t RightPossibleGrades, id_t... RightId>
		struct lt<dynamic_basis_blades<LeftPossibleGrades, LeftId...>, dynamic_basis_blades<RightPossibleGrades, RightId...> > {
			constexpr static bool value = LeftPossibleGrades < RightPossibleGrades || (LeftPossibleGrades == RightPossibleGrades && id_cmp<LeftId...>::lt_v<RightId...>);
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

#endif // __GA_FUTURE_RELATIONAL_OPERATORS_HPP__
