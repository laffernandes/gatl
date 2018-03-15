#ifndef __GA_DEFAULT_TOLERANCE_HPP__
#define __GA_DEFAULT_TOLERANCE_HPP__

namespace ga {

	template<class IntegralType>
	constexpr IntegralType default_tolerance() {
		static_assert(std::is_integral<IntegralType>::value, "An integral type is expected.");
		return static_cast<IntegralType>(0);
	}

	template<>
	constexpr std::float_t default_tolerance<std::float_t>() {
		return GA_DEFAULT_FLT_TOLERANCE;
	}

	template<>
	constexpr std::double_t default_tolerance<std::double_t>() {
		return GA_DEFAULT_DBL_TOLERANCE;
	}

}

#endif // __GA_DEFAULT_TOLERANCE_HPP__
