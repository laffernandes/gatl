#ifndef __GA_VALUE_MATH_HPP__
#define __GA_VALUE_MATH_HPP__

namespace ga {

	namespace detail {

		using std::abs;

		template<default_integral_t Value>
		constexpr decltype(auto) abs(cvalue<Value> const &) {
			return cvalue<(Value < 0 ? -Value : Value)>();
		}

		using std::exp;

		template<default_integral_t Value>
		constexpr decltype(auto) exp(cvalue<Value> const &arg) {
			return exp(static_cast<default_floating_point_t>(arg)); //TODO Lazy
		}

		constexpr decltype(auto) exp(cvalue<0> const &arg) {
			return cvalue<1>();
		}

		using std::sqrt;

		constexpr std::uint64_t isqrt_impl(std::uint64_t sq, std::uint64_t dlt, std::uint64_t value) {
			return sq <= value ? isqrt_impl(sq + dlt, dlt + 2, value) : (dlt >> 1) - 1;
		}

		constexpr std::uint64_t isqrt(std::uint64_t value) {
			return isqrt_impl(1, 3, value);
		}

		template<default_integral_t Value>
		struct _sqrt_value {
		private:

			constexpr static default_integral_t result = static_cast<default_integral_t>(isqrt(Value));

			struct _return_cvalue {
				constexpr static decltype(auto) bind() {
					return cvalue<result>();
				}
			};

			struct _return_floating_point {
				static decltype(auto) bind() {
					return sqrt(static_cast<default_floating_point_t>(Value)); // lazy
				}
			};

		public:

			constexpr static decltype(auto) bind() {
				return std::conditional<(result * result) == Value, _return_cvalue, _return_floating_point>::type::bind();
			}
		};

		template<default_integral_t Value>
		constexpr decltype(auto) sqrt(cvalue<Value> const &) {
			return _sqrt_value<Value>::bind();
		}

		using std::cos;

		template<default_integral_t Value>
		constexpr decltype(auto) cos(cvalue<Value> const &) {
			return cos(static_cast<default_floating_point_t>(Value)); // lazy
		}

		constexpr decltype(auto) cos(cvalue<0> const &) {
			return cvalue<1>();
		}

		using std::sin;

		template<default_integral_t Value>
		constexpr decltype(auto) sin(cvalue<Value> const &) {
			return sin(static_cast<default_floating_point_t>(Value)); // lazy
		}

		constexpr decltype(auto) sin(cvalue<0> const &) {
			return cvalue<0>();
		}

		using std::tan;

		template<default_integral_t Value>
		constexpr decltype(auto) tan(cvalue<Value> const &) {
			return tan(static_cast<default_floating_point_t>(Value)); // lazy
		}

		constexpr decltype(auto) tan(cvalue<0> const &) {
			return cvalue<0>();
		}

		using std::cosh;

		template<default_integral_t Value>
		constexpr decltype(auto) cosh(cvalue<Value> const &) {
			return cosh(static_cast<default_floating_point_t>(Value)); // lazy
		}

		constexpr decltype(auto) cosh(cvalue<0> const &) {
			return cvalue<1>();
		}

		using std::sinh;

		template<default_integral_t Value>
		constexpr decltype(auto) sinh(cvalue<Value> const &) {
			return sinh(static_cast<default_floating_point_t>(Value)); // lazy
		}

		constexpr decltype(auto) sinh(cvalue<0> const &) {
			return cvalue<0>();
		}

		using std::tanh;

		template<default_integral_t Value>
		constexpr decltype(auto) tanh(cvalue<Value> const &) {
			return tanh(static_cast<default_floating_point_t>(Value)); // lazy
		}

		constexpr decltype(auto) tanh(cvalue<0> const &) {
			return cvalue<0>();
		}

	}

}

#endif // __GA_VALUE_MATH_HPP__
