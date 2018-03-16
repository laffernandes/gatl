#ifndef __GA_VALUE_EXP_HPP__
#define __GA_VALUE_EXP_HPP__

namespace ga {

	namespace detail {

		template<default_integral_t Value>
		constexpr decltype(auto) exp(cvalue<Value> const &arg) {
			return exp(static_cast<default_floating_point_t>(arg)); //TODO Lazy
		}

	}

}

#endif // __GA_VALUE_EXP_HPP__
