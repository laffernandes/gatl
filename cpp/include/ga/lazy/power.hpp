#ifndef __GA_LAZY_POWER_HPP__
#define __GA_LAZY_POWER_HPP__

namespace ga {

	namespace lazy {

		namespace detail {

			template<class LeftArgumentType, class RightArgumentType>
			class power final :
				public lazy_expression<power<LeftArgumentType, RightArgumentType> >,
				private arguments_storage<LeftArgumentType, RightArgumentType> {
			private:

				typedef arguments_storage<LeftArgumentType, RightArgumentType> _super_for_arguments;

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

			template<class LeftArgumentType, class RightArgumentType>
			constexpr power<LeftArgumentType, RightArgumentType> make_power(LeftArgumentType const &lhs, RightArgumentType const &rhs) {
				return power<LeftArgumentType, RightArgumentType>(lhs, rhs);
			}

		}

	}

	namespace common {

		template<class LeftArgumentType, class RightArgumentType>
		struct is_lazy_expression<lazy::detail::power<LeftArgumentType, RightArgumentType> > {
			constexpr static bool value = true;
		};

		template<class LeftArgumentType, class RightArgumentType>
		struct is_lazy_constant<lazy::detail::power<LeftArgumentType, RightArgumentType> > {
			constexpr static bool value = is_lazy_constant<LeftArgumentType>::value && is_lazy_constant<RightArgumentType>::value;
		};

	}

}

#endif // __GA_LAZY_POWER_HPP__
