#ifndef __GA_VALUE_NEG_HPP__
#define __GA_VALUE_NEG_HPP__

namespace ga {

	namespace detail {

		template<default_integral_t RightValue>
		constexpr cvalue<-RightValue> neg(cvalue<RightValue> const &) {
			return cvalue<-RightValue>();
		}

		template<class RightValueType>
		constexpr decltype(auto) neg(RightValueType const &rhs) {
			return mul(cvalue<-1>(), rhs);
		}

	}

}

#endif // __GA_VALUE_NEG_HPP__
