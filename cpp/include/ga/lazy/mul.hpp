#ifndef __GA_LAZY_MUL_HPP__
#define __GA_LAZY_MUL_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class... ArgumentTypes>
			class mul;

			template<class LeftArgumentType, class... RightArgumentTypes>
			class mul<LeftArgumentType, RightArgumentTypes...> final :
				public lazy_expression<mul<LeftArgumentType, RightArgumentTypes...> >,
				private arguments_storage<LeftArgumentType, mul<RightArgumentTypes...> > {
			private:

				typedef arguments_storage<LeftArgumentType, mul<RightArgumentTypes...> > _super_for_arguments;

			public:

				typedef mul expression_type;

				using left_type = typename _super_for_arguments::left_type;
				using right_type = typename _super_for_arguments::right_type;

				constexpr mul() = default;
				constexpr mul(mul const &) = default;
				constexpr mul(mul &&) = default;

				constexpr mul(left_type const &lhs, RightArgumentTypes const &... rhs) :
					_super_for_arguments(lhs, right_type(rhs...)) {
				}

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
				static_assert(!is_lazy_mul<left_type>::value, "The left-hand side argument cannot be a ga::lazy::mul<...> expression.");
				static_assert(le<left_type, typename right_type::left_type>::value, "The arguments do not respect the expected ordering for lazy expressions.");
			};

			template<class LeftArgumentType, class RightArgumentType>
			class mul<LeftArgumentType, RightArgumentType> final :
				public lazy_expression<mul<LeftArgumentType, RightArgumentType> >,
				private arguments_storage<LeftArgumentType, RightArgumentType> {
			private:

				typedef arguments_storage<LeftArgumentType, RightArgumentType> _super_for_arguments;

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
				static_assert(!is_lazy_mul<left_type>::value, "The left-hand side argument cannot be a ga::lazy::mul<...> expression.");
				static_assert(!is_lazy_mul<right_type>::value, "The right-hand side argument cannot be a ga::lazy::mul<...> expression.");
				static_assert(le<left_type, right_type>::value, "The arguments do not respect the expected ordering for lazy expressions.");
			};

		}

	}

	namespace common {

		template<class... ArgumentTypes>
		struct is_lazy_expression<lazy::detail::mul<ArgumentTypes...> > {
			constexpr static bool value = true;
		};

		template<class LeftArgumentType, class... RightArgumentTypes>
		struct is_lazy_constant<lazy::detail::mul<LeftArgumentType, RightArgumentTypes...> > {
			constexpr static bool value = is_lazy_constant<lazy::detail::mul<RightArgumentTypes...> >::value; // By construction, if the right-hand side argument is constant then the left-hand side one is constant, too.
		};

		template<class LeftArgumentType, class RightArgumentType>
		struct is_lazy_constant<lazy::detail::mul<LeftArgumentType, RightArgumentType> > {
			constexpr static bool value = is_lazy_constant<RightArgumentType>::value; // By construction, if the right-hand side argument is constant then the left-hand side one is constant, too.
		};

		template<class LeftArgumentType, class... RightArgumentTypes>
		struct is_lazy_mul<lazy::detail::mul<LeftArgumentType, RightArgumentTypes...> > {
			constexpr static bool value = true;
		};

		template<class LeftArgumentType, class RightArgumentType>
		struct is_lazy_mul<lazy::detail::mul<LeftArgumentType, RightArgumentType> > {
			constexpr static bool value = true;
		};

	}

}

#endif // __GA_LAZY_MUL_HPP__
