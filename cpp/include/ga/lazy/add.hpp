#ifndef __GA_LAZY_ADD_HPP__
#define __GA_LAZY_ADD_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class LeftExpressionType, class RightExpressionType>
			class add final :
				public lazy_expression<add<LeftExpressionType, RightExpressionType> >,
				private binary_lazy_expression<LeftExpressionType, RightExpressionType> {
			private:

				typedef binary_lazy_expression<LeftExpressionType, RightExpressionType> _super_for_arguments;

			public:

				typedef add expression_type;

				using left_type = typename _super_for_arguments::left_type;
				using right_type = typename _super_for_arguments::right_type;

				typedef decltype(typename left_type::value_type() + typename right_type::value_type()) value_type;

				constexpr add() = default;
				constexpr add(add const &) = default;
				constexpr add(add &&) = default;

				constexpr add(left_type const &lhs, right_type const &rhs) :
					_super_for_arguments(lhs, rhs) {
				}

				constexpr add & operator=(add const &) = default;
				constexpr add & operator=(add &&) = default;

				using _super_for_arguments::left;
				using _super_for_arguments::right;
				using _super_for_arguments::compile_time_defined;

				static_assert(!std::is_same<left_type, constant<0> >::value, "The left-hand side argument cannot be a ga::lazy::constant<0> expression.");
				static_assert(!std::is_same<right_type, constant<0> >::value, "The right-hand side argument cannot be a ga::lazy::constant<0> expression.");
				static_assert(le<left_type, right_type>::value, "The arguments do not respect the expected ordering for lazy expressions.");
			};

			template<class LeftExpressionType, class RightExpressionType>
			constexpr add<LeftExpressionType, RightExpressionType> make_add(LeftExpressionType const &lhs, RightExpressionType const &rhs) {
				return add<LeftExpressionType, RightExpressionType>(lhs, rhs);
			}

			template<class LeftExpressionType, class RightExpressionType>
			struct is_lazy_expression<detail::add<LeftExpressionType, RightExpressionType> > {
				constexpr static bool value = true;
			};

			template<class LeftExpressionType, class RightExpressionType>
			struct is_value<detail::add<LeftExpressionType, RightExpressionType> > {
				constexpr static bool value = is_value<LeftExpressionType>::value && is_value<RightExpressionType>::value;
			};

			template<class LeftExpressionType, class RightExpressionType>
			struct is_variable<detail::add<LeftExpressionType, RightExpressionType> > {
				constexpr static bool value = is_variable<LeftExpressionType>::value && is_variable<RightExpressionType>::value;
			};

		}

	}

}

#endif // __GA_LAZY_ADD_HPP__
