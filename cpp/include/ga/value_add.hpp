#ifndef __GA_VALUE_ADD_HPP__
#define __GA_VALUE_ADD_HPP__

namespace ga {

	namespace detail {

		template<default_integral_t LeftValue, default_integral_t RightValue>
		constexpr cvalue<LeftValue + RightValue> add(cvalue<LeftValue> const &, cvalue<RightValue> const &) {
			return cvalue<LeftValue + RightValue>();
		}

		template<default_integral_t LeftValue>
		constexpr cvalue<LeftValue> add(cvalue<LeftValue> const &, cvalue<0> const &) {
			return cvalue<LeftValue>();
		}

		template<default_integral_t LeftValue, class RightValueType>
		constexpr decltype(auto) add(cvalue<LeftValue> const &, RightValueType const &rhs) {
			return LeftValue + rhs; //TODO lazy
		}

		template<default_integral_t RightValue>
		constexpr cvalue<RightValue> add(cvalue<0> const &, cvalue<RightValue> const &) {
			return cvalue<RightValue>();
		}

		constexpr cvalue<0> add(cvalue<0> const &, cvalue<0> const &) {
			return cvalue<0>();
		}

		template<class RightValueType>
		constexpr RightValueType add(cvalue<0> const &, RightValueType const &rhs) {
			return rhs;
		}

		template<class LeftValueType, default_integral_t RightValue>
		constexpr decltype(auto) add(LeftValueType const &lhs, cvalue<RightValue> const &) {
			return lhs + RightValue; //TODO lazy
		}

		template<class LeftValueType>
		constexpr LeftValueType add(LeftValueType const &lhs, cvalue<0> const &) {
			return lhs;
		}

		template<class LeftValueType, class RightValueType>
		constexpr decltype(auto) add(LeftValueType const &lhs, RightValueType const &rhs) {
			return (lhs + rhs); //TODO lazy
		}

	}

}

#endif // __GA_VALUE_ADD_HPP__
