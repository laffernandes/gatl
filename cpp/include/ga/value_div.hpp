#ifndef __GA_VALUE_DIV_HPP__
#define __GA_VALUE_DIV_HPP__

namespace ga {

	namespace detail {

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _div_return_cvalue {
			constexpr static decltype(auto) bind() {
				return cvalue<LeftValue / RightValue>();
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _div_return_floating_point {
			constexpr static decltype(auto) bind() {
				return static_cast<default_floating_point_t>(LeftValue) / RightValue;
			}
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		constexpr decltype(auto) div(cvalue<LeftValue> const &, cvalue<RightValue> const &) {
			return std::conditional<(LeftValue % RightValue) == 0, _div_return_cvalue<LeftValue, RightValue>, _div_return_floating_point<LeftValue, RightValue> >::type::bind();
		}

		template<default_integral_t LeftValue>
		cvalue<0> div(cvalue<LeftValue> const &, cvalue<0> const &) = delete;

		template<default_integral_t LeftValue>
		constexpr cvalue<LeftValue> div(cvalue<LeftValue> const &, cvalue<1> const &) {
			return cvalue<LeftValue>();
		}

		template<default_integral_t LeftValue, class RightValueType>
		constexpr decltype(auto) div(cvalue<LeftValue> const &, RightValueType const &rhs) {
			return (static_cast<default_floating_point_t>(LeftValue) / rhs); //TODO lazy
		}

		template<default_integral_t RightValue>
		constexpr cvalue<0> div(cvalue<0> const &, cvalue<RightValue> const &) {
			return cvalue<0>();
		}

		constexpr cvalue<0> div(cvalue<0> const &, cvalue<1> const &) {
			return cvalue<0>();
		}

		template<class RightValueType>
		constexpr cvalue<0> div(cvalue<0> const &, RightValueType const &) {
			return cvalue<0>();
		}

		template<default_integral_t RightValue>
		constexpr decltype(auto) div(cvalue<1> const &, cvalue<RightValue> const &) {
			return static_cast<default_floating_point_t>(1) / RightValue; //TODO lazy
		}

		constexpr cvalue<1> div(cvalue<1> const &, cvalue<1> const &) {
			return cvalue<1>();
		}

		template<class RightValueType>
		constexpr decltype(auto) div(cvalue<1> const &, RightValueType const &rhs) {
			return (static_cast<default_floating_point_t>(1) / rhs); //TODO lazy
		}

		template<class LeftValueType, default_integral_t RightValue>
		constexpr decltype(auto) div(LeftValueType const &lhs, cvalue<RightValue> const &) {
			return (lhs / static_cast<default_floating_point_t>(RightValue)); //TODO lazy
		}

		template<class LeftValueType>
		constexpr LeftValueType div(LeftValueType const &lhs, cvalue<1> const &) {
			return lhs;
		}

		template<class LeftValueType>
		cvalue<0> div(LeftValueType const &, cvalue<0> const &) = delete;

		template<class LeftValueType, class RightValueType>
		constexpr decltype(auto) div(LeftValueType const &lhs, RightValueType const &rhs) {
			return (lhs / rhs); //TODO lazy
		}

	}

}

#endif // __GA_VALUE_DIV_HPP__
