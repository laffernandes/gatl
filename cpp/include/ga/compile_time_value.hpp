#ifndef __GA_COMPILE_TIME_VALUE_HPP__
#define __GA_COMPILE_TIME_VALUE_HPP__

//TODO Armazenar uma fração

namespace ga {

	namespace detail {

		template<default_integral_t Value>
		class cvalue {
		public:

			typedef default_integral_t value_type;

			constexpr operator value_type() const {
				return Value;
			}

			constexpr static value_type value() {
				return Value;
			}
		};

	}

	template<default_integral_t Value>
	constexpr auto c = detail::cvalue<Value>();

}

namespace std {

	template<ga::default_integral_t LeftValue, class RightType>
	struct common_type<ga::detail::cvalue<LeftValue>, RightType> : std::common_type<ga::default_integral_t, RightType> {
	};

	template<class LeftType, ga::default_integral_t RightValue>
	struct common_type<LeftType, ga::detail::cvalue<RightValue> > : std::common_type<LeftType, ga::default_integral_t> {
	};

	template<ga::default_integral_t LeftValue, ga::default_integral_t RightValue>
	struct common_type<ga::detail::cvalue<LeftValue>, ga::detail::cvalue<RightValue> > {
		typedef ga::default_integral_t type;
	};

	template<ga::default_integral_t Value>
	struct common_type<ga::detail::cvalue<Value>, ga::detail::cvalue<Value> > {
		typedef ga::detail::cvalue<Value> type;
	};
}

#endif // __GA_COMPILE_TIME_VALUE_HPP__
