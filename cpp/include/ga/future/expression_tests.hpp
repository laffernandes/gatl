#ifndef __GA_FUTURE_EXPRESSION_TESTS_HPP__
#define __GA_FUTURE_EXPRESSION_TESTS_HPP__

namespace future {

	namespace detail {

		// Definition of is_constant_expression<Type>.
		template<class Type>
		struct is_constant_expression {
			constexpr static bool value = false;
		};

		// Specializations of is_constant_expression<Type>.
		template<default_integral_t Value>
		struct is_constant_expression<constant<Value> > {
			constexpr static bool value = true;
		};

		template<class Argument, class... NextArguments>
		struct is_constant_expression<add<Argument, NextArguments...> > {
			constexpr static bool value = is_constant_expression_v<Argument> && is_constant_expression_v<add<NextArguments...> >;
		};

		template<>
		struct is_constant_expression<add<> > {
			constexpr static bool value = true;
		};

		template<class Argument, class... NextArguments>
		struct is_constant_expression<mul<Argument, NextArguments...> > {
			constexpr static bool value = is_constant_expression_v<Argument> && is_constant_expression_v<mul<NextArguments...> >;
		};

		template<>
		struct is_constant_expression<mul<> > {
			constexpr static bool value = true;
		};

		template<class LeftArgument, class RightArgument>
		struct is_constant_expression<power<LeftArgument, RightArgument> > {
			constexpr static bool value = is_constant_expression_v<LeftArgument> && is_constant_expression_v<RightArgument>;
		};

		template<class Tag, class Arguments>
		struct is_constant_expression<function<Tag, Arguments> > {
			constexpr static bool value = is_constant_expression_v<Arguments>;
		};

		template<class Coefficient, default_bitset_t BasisVectors>
		struct is_constant_expression<component<Coefficient, constant_basis_blade<BasisVectors> > > {
			constexpr static bool value = is_constant_expression_v<Coefficient>;
		};

	}

}

#endif // __GA_FUTURE_EXPRESSION_TESTS_HPP__
