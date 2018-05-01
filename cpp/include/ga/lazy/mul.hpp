#ifndef __GA_LAZY_MUL_HPP__
#define __GA_LAZY_MUL_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class LeftExpressionType, class RightExpressionType>
			class mul final :
				public lazy_expression<mul<LeftExpressionType, RightExpressionType> >,
				private binary_lazy_expression<LeftExpressionType, RightExpressionType> {
			private:

				typedef binary_lazy_expression<LeftExpressionType, RightExpressionType> _super_for_arguments;

			public:

				typedef mul expression_type;

				using left_type = typename _super_for_arguments::left_type;
				using right_type = typename _super_for_arguments::right_type;

				constexpr mul() = default;
				constexpr mul(mul const &) = default;
				constexpr mul(mul &&) = default;

				constexpr mul(left_type const &lhs, right_type const &rhs) :
					_super_for_arguments(lhs, rhs) {
				}

				constexpr mul & operator=(mul const &) = default;
				constexpr mul & operator=(mul &&) = default;

				using _super_for_arguments::left;
				using _super_for_arguments::right;
				using _super_for_arguments::compile_time_defined;

				static_assert(!std::is_same<left_type, constant<0> >::value, "The left-hand side argument cannot be a ga::lazy::constant<0> expression.");
				static_assert(!std::is_same<left_type, constant<1> >::value, "The left-hand side argument cannot be a ga::lazy::constant<1> expression.");
				static_assert(!std::is_same<right_type, constant<0> >::value, "The right-hand side argument cannot be a ga::lazy::constant<0> expression.");
				static_assert(!std::is_same<right_type, constant<1> >::value, "The right-hand side argument cannot be a ga::lazy::constant<1> expression.");
				static_assert(le<left_type, right_type>::value, "The arguments do not respect the expected ordering for lazy expressions.");
			};

			template<class LeftExpressionType, class RightExpressionType>
			constexpr mul<LeftExpressionType, RightExpressionType> make_mul(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return mul<LeftExpressionType, RightExpressionType>(lhs, rhs);
			}

		}

	}

	namespace common {

		template<class LeftExpressionType, class RightExpressionType>
		struct is_lazy_expression<lazy::detail::mul<LeftExpressionType, RightExpressionType> > {
			constexpr static bool value = true;
		};

		template<class LeftExpressionType, class RightExpressionType>
		struct is_lazy_constant<lazy::detail::mul<LeftExpressionType, RightExpressionType> > {
			constexpr static bool value = is_lazy_constant<LeftExpressionType>::value && is_lazy_constant<RightExpressionType>::value;
		};

		template<class LeftExpressionType, class RightExpressionType>
		struct allows_lazy_simplification<lazy::detail::mul<LeftExpressionType, RightExpressionType> > {
			constexpr static bool value = allows_lazy_simplification<LeftExpressionType>::value; // By sorting, we do not to check the right-hand side argument.
		};

	}

}

#endif // __GA_LAZY_MUL_HPP__
