#ifndef __GA_LAZY_ADD_HPP__
#define __GA_LAZY_ADD_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class... ArgumentTypes>
			class add;

			template<class LeftArgumentType, class... RightArgumentTypes>
			class add<LeftArgumentType, RightArgumentTypes...> final :
				public lazy_expression<add<LeftArgumentType, RightArgumentTypes...> >,
				private arguments_storage<LeftArgumentType, add<RightArgumentTypes...> > {
			private:

				typedef arguments_storage<LeftArgumentType, add<RightArgumentTypes...> > _super_for_arguments;

			public:

				typedef add expression_type;

				using left_type = typename _super_for_arguments::left_type;
				using right_type = typename _super_for_arguments::right_type;

				constexpr add() = default;
				constexpr add(add const &) = default;
				constexpr add(add &&) = default;

				constexpr add(left_type const &lhs, RightArgumentTypes const &... rhs) :
					_super_for_arguments(lhs, right_type(rhs...)) {
				}

				constexpr add(left_type const &lhs, right_type const &rhs) :
					_super_for_arguments(lhs, rhs) {
				}

				constexpr add & operator=(add const &) = default;
				constexpr add & operator=(add &&) = default;

				using _super_for_arguments::left;
				using _super_for_arguments::right;

				using _super_for_arguments::compile_time_defined;

				static_assert(!std::is_same<left_type, constant<0> >::value, "The left-hand side argument cannot be a ga::lazy::constant<0> expression.");
				static_assert(!is_lazy_add<left_type>::value, "The left-hand side argument cannot be a ga::lazy::add<...> expression.");
				static_assert(le<left_type, typename right_type::left_type>::value, "The arguments do not respect the expected ordering for lazy expressions.");
			};

			template<class LeftArgumentType, class RightArgumentType>
			class add<LeftArgumentType, RightArgumentType> final :
				public lazy_expression<add<LeftArgumentType, RightArgumentType> >,
				private arguments_storage<LeftArgumentType, RightArgumentType> {
			private:

				typedef arguments_storage<LeftArgumentType, RightArgumentType> _super_for_arguments;

			public:

				typedef add expression_type;

				using left_type = typename _super_for_arguments::left_type;
				using right_type = typename _super_for_arguments::right_type;

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
				static_assert(!is_lazy_add<left_type>::value, "The left-hand side argument cannot be a ga::lazy::add<...> expression.");
				static_assert(!is_lazy_add<right_type>::value, "The right-hand side argument cannot be a ga::lazy::add<...> expression.");
				static_assert(le<left_type, right_type>::value, "The arguments do not respect the expected ordering for lazy expressions.");
			};

		}

		template<id_t Id, id_t... SubIds, class... ArgumentTypes>
		constexpr detail::add<ArgumentTypes...> var(detail::add<ArgumentTypes...> const &arg) {
			return arg;
		}

	}

	namespace common {

		template<class... ArgumentTypes>
		struct is_lazy_expression<lazy::detail::add<ArgumentTypes...> > {
			constexpr static bool value = true;
		};

		template<class LeftArgumentType, class... RightArgumentTypes>
		struct is_lazy_constant<lazy::detail::add<LeftArgumentType, RightArgumentTypes...> > {
			constexpr static bool value = is_lazy_constant<lazy::detail::add<RightArgumentTypes...> >::value; // By construction, if the right-hand side argument is constant then the left-hand side one is constant, too.
		};

		template<class LeftArgumentType, class RightArgumentType>
		struct is_lazy_constant<lazy::detail::add<LeftArgumentType, RightArgumentType> > {
			constexpr static bool value = is_lazy_constant<RightArgumentType>::value; // By construction, if the right-hand side argument is constant then the left-hand side one is constant, too.
		};

		template<class LeftArgumentType, class... RightArgumentTypes>
		struct is_lazy_add<lazy::detail::add<LeftArgumentType, RightArgumentTypes...> > {
			constexpr static bool value = true;
		};

		template<class LeftArgumentType, class RightArgumentType>
		struct is_lazy_add<lazy::detail::add<LeftArgumentType, RightArgumentType> > {
			constexpr static bool value = true;
		};

		template<class LeftArgumentType, class... RightArgumentTypes>
		struct common_value_type<lazy::detail::add<LeftArgumentType, RightArgumentTypes...> > : std::common_type<
			typename common_value_type<LeftArgumentType>::type,
			typename common_value_type<lazy::detail::add<RightArgumentTypes...> >::type
		> {
		};

		template<class LeftArgumentType, class RightArgumentType>
		struct common_value_type<lazy::detail::add<LeftArgumentType, RightArgumentType> > : std::common_type<
			typename common_value_type<LeftArgumentType>::type,
			typename common_value_type<RightArgumentType>::type
		> {
		};

	}

}

#endif // __GA_LAZY_ADD_HPP__
