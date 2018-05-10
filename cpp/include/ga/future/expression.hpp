#ifndef __GA_FUTURE_EXPRESSION_HPP__
#define __GA_FUTURE_EXPRESSION_HPP__

namespace future {

	namespace detail {

		//TODO Implementar métricas que respondam ao seguinte comando: typename Mapping::template resulting_component<LeftBasisBlade, RightBasisBlade>::type

		// Constant integer value defined in compilation time.
		template<default_integral_t Value>
		struct constant final {
		};

		// Real value (or variable) defined in runtime.
		template<id_t... Id>
		struct value final {
		};

		// Addition of real-valued expressions and/or multivector components.
		template<class... Arguments>
		struct add final {
			static_assert(!is_any_v<constant<0>, Arguments...>, "The argument future::detail::constant<0> is invalid.");
			//TODO static_assert(!is_lazy_add_v<left_type>, "The left-hand side argument cannot be a ga::lazy::add<...> expression.");
			//TODO static_assert(le_v<left_type, typename right_type::left_type>, "The arguments do not respect the expected ordering for lazy expressions.");
		};

		// Multiplication of real-valued expressions.
		template<class... Arguments>
		struct mul final {
			static_assert(!is_any_v<constant<0>, Arguments...>, "The argument future::detail::constant<0> is invalid.");
			static_assert(!is_any_v<constant<1>, Arguments...>, "The argument future::detail::constant<1> is invalid.");
			//TODO static_assert(!is_lazy_mul_v<left_type>, "The left-hand side argument cannot be a ga::lazy::mul<...> expression.");
			//TODO static_assert(le_v<left_type, typename right_type::left_type>, "The arguments do not respect the expected ordering for lazy expressions.");
		};

		// Exponentiation of real-valued expressions.
		template<class LeftArgument, class RightArgument>
		struct power final {
			static_assert(!std::is_same_v<LeftArgument, constant<0> >, "The left-hand side argument cannot be future::detail::constant<0>.");
			static_assert(!std::is_same_v<RightArgument, constant<0> >, "The right-hand side argument cannot be future::detail::constant<0>.");
			static_assert(!std::is_same_v<RightArgument, constant<1> >, "The right-hand side argument cannot be future::detail::constant<1>.");
		};

		// Real-valued function.
		template<class Tag, class Arguments>
		struct function final {
		};

		// A basis blade multiplied by some real-valued expression (the coefficient).
		template<class Coefficient, class BasisBlade>
		struct component final {
			static_assert(!std::is_same_v<Coefficient, constant<0> >, "The coefficient cannot be a future::detail::constant<0> expression.");
			static_assert(possible_grades_v<BasisBlade> != default_bitset_t(0), "The basis blade must have at least one possible grade.");
			static_assert(possible_grades_v<BasisBlade> != default_bitset_t(1), "Grade 0 (zero) is not valid because real values are not representd by future::detail::component<Coefficient, BasisBlade> types.");
		};

		// Basis blade defined in compilation time.
		template<default_bitset_t BasisVectors>
		struct constant_basis_blade final {
		};

		// Basis blade defined in runtime.
		template<default_bitset_t PossibleGrades, id_t... Ids>
		struct dynamic_basis_blade final {
		};

		// Collection of basis blades defined in runtime.
		template<default_bitset_t PossibleGrades, id_t... Ids>
		struct dynamic_basis_blades final {
		};

		// A simple mapping for real-valued expressions.
		struct real_mapping final {
		};

	}

}

#endif // __GA_FUTURE_EXPRESSION_HPP__
