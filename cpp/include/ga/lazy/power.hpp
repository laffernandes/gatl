#ifndef __GA_LAZY_POWER_HPP__
#define __GA_LAZY_POWER_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class LeftExpressionType, class RightExpressionType>
			class power final :
				public lazy_expression<power<LeftExpressionType, RightExpressionType> >,
				private binary_lazy_expression<LeftExpressionType, RightExpressionType> {
			private:

				typedef binary_lazy_expression<LeftExpressionType, RightExpressionType> _super_for_arguments;

			public:

				typedef power expression_type;

				using left_type = typename _super_for_arguments::left_type;
				using right_type = typename _super_for_arguments::right_type;

				constexpr power() = default;
				constexpr power(power const &) = default;
				constexpr power(power &&) = default;

				constexpr power(left_type const &lhs, right_type const &rhs) :
					_super_for_arguments(lhs, rhs) {
				}

				constexpr power & operator=(power const &) = default;
				constexpr power & operator=(power &&) = default;

				using _super_for_arguments::left;
				using _super_for_arguments::right;
				using _super_for_arguments::compile_time_defined;

				static_assert(!std::is_same<left_type, constant<0> >::value, "The left-hand side argument cannot be a ga::lazy::constant<0> expression.");
				static_assert(!std::is_same<right_type, constant<0> >::value, "The right-hand side argument cannot be a ga::lazy::constant<0> expression.");
				static_assert(!std::is_same<right_type, constant<1> >::value, "The right-hand side argument cannot be a ga::lazy::constant<1> expression.");
			};

			template<class LeftExpressionType, class RightExpressionType>
			constexpr power<LeftExpressionType, RightExpressionType> make_power(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return power<LeftExpressionType, RightExpressionType>(lhs, rhs);
			}

		}

	}

	namespace common {

		template<class LeftExpressionType, class RightExpressionType>
		struct is_lazy_expression<lazy::detail::power<LeftExpressionType, RightExpressionType> > {
			constexpr static bool value = true;
		};

		template<class LeftExpressionType, class RightExpressionType>
		struct is_lazy_constant<lazy::detail::power<LeftExpressionType, RightExpressionType> > {
			constexpr static bool value = is_lazy_constant<LeftExpressionType>::value && is_lazy_constant<RightExpressionType>::value;
		};

		template<class LeftExpressionType, class RightExpressionType>
		struct is_lazy_value<lazy::detail::power<LeftExpressionType, RightExpressionType> > {
			constexpr static bool value = is_lazy_value<LeftExpressionType>::value && is_lazy_value<RightExpressionType>::value;
		};

		template<class LeftExpressionType, class RightExpressionType>
		struct is_lazy_variable<lazy::detail::power<LeftExpressionType, RightExpressionType> > {
			constexpr static bool value = is_lazy_variable<LeftExpressionType>::value && is_lazy_variable<RightExpressionType>::value;
		};

		template<class LeftExpressionType, class RightExpressionType>
		struct allows_lazy_simplification<lazy::detail::power<LeftExpressionType, RightExpressionType> > {
			constexpr static bool value = allows_lazy_simplification<LeftExpressionType>::value && allows_lazy_simplification<RightExpressionType>::value;
		};

	}

}

#endif // __GA_LAZY_POWER_HPP__
