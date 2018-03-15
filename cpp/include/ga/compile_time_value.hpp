#ifndef __GA_COMPILE_TIME_VALUE_HPP__
#define __GA_COMPILE_TIME_VALUE_HPP__

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

#endif // __GA_COMPILE_TIME_VALUE_HPP__
