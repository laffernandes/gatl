#ifndef __GA_VALUE_SQRT_HPP__
#define __GA_VALUE_SQRT_HPP__

namespace ga {

	namespace detail {

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
					return sqrt(static_cast<default_floating_point_t>(Value));
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

	}

}

#endif // __GA_VALUE_SQRT_HPP__
