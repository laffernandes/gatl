#ifndef __GA_VALUE_MUL_HPP__
#define __GA_VALUE_MUL_HPP__

namespace ga {

	namespace detail {

		template<default_integral_t LeftValue, default_integral_t RightValue>
		constexpr cvalue<LeftValue * RightValue> mul(cvalue<LeftValue> const &, cvalue<RightValue> const &) {
			return cvalue<LeftValue * RightValue>();
		}

		template<default_integral_t LeftValue>
		constexpr cvalue<0> mul(cvalue<LeftValue> const &, cvalue<0> const &) {
			return cvalue<0>();
		}

		template<default_integral_t LeftValue>
		constexpr cvalue<LeftValue> mul(cvalue<LeftValue> const &, cvalue<1> const &) {
			return cvalue<LeftValue>();
		}

		template<default_integral_t LeftValue, class RightValueType>
		constexpr decltype(auto) mul(cvalue<LeftValue> const &, RightValueType const &rhs) {
			return (LeftValue * rhs); //TODO lazy
		}

		template<default_integral_t RightValue>
		constexpr cvalue<0> mul(cvalue<0> const &, cvalue<RightValue> const &) {
			return cvalue<0>();
		}

		constexpr cvalue<0> mul(cvalue<0> const &, cvalue<0> const &) {
			return cvalue<0>();
		}

		constexpr cvalue<0> mul(cvalue<0> const &, cvalue<1> const &) {
			return cvalue<0>();
		}

		template<class RightValueType>
		constexpr cvalue<0> mul(cvalue<0> const &, RightValueType const &) {
			return cvalue<0>();
		}

		template<default_integral_t RightValue>
		constexpr cvalue<RightValue> mul(cvalue<1> const &, cvalue<RightValue> const &) {
			return cvalue<RightValue>();
		}

		constexpr cvalue<0> mul(cvalue<1> const &, cvalue<0> const &) {
			return cvalue<0>();
		}

		constexpr cvalue<1> mul(cvalue<1> const &, cvalue<1> const &) {
			return cvalue<1>();
		}

		template<class RightValueType>
		constexpr RightValueType mul(cvalue<1> const &, RightValueType const &rhs) {
			return rhs;
		}

		template<class LeftValueType, default_integral_t RightValue>
		constexpr decltype(auto) mul(LeftValueType const &lhs, cvalue<RightValue> const &) {
			return (lhs * RightValue); //TODO lazy
		}

		template<class LeftValueType>
		constexpr LeftValueType mul(LeftValueType const &lhs, cvalue<1> const &) {
			return lhs;
		}

		template<class LeftValueType>
		constexpr cvalue<0> mul(LeftValueType const &, cvalue<0> const &) {
			return cvalue<0>();
		}

		template<class LeftValueType, class RightValueType>
		constexpr decltype(auto) mul(LeftValueType const &lhs, RightValueType const &rhs) {
			return (lhs * rhs); //TODO lazy
		}

	}

}

#endif // __GA_VALUE_MUL_HPP__
