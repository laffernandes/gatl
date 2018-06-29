#ifndef __GA_EXTRA_DEFAULT_TOLERANCE_HPP__
#define __GA_EXTRA_DEFAULT_TOLERANCE_HPP__

#ifndef GA_DEFAULT_FLT_TOLERANCE
	#define GA_DEFAULT_FLT_TOLERANCE 1.0e-8f
#else
	static_assert(GA_DEFAULT_FLT_TOLERANCE >= 0, "GA_DEFAULT_FLT_TOLERANCE must be a non-negative value.")
#endif // GA_DEFAULT_FLT_TOLERANCE

#ifndef GA_DEFAULT_DBL_TOLERANCE
	#define GA_DEFAULT_DBL_TOLERANCE 1.0e-8
#else
	static_assert(GA_DEFAULT_DBL_TOLERANCE >= 0, "GA_DEFAULT_DBL_TOLERANCE must be a non-negative value.")
#endif // GA_DEFAULT_DBL_TOLERANCE

namespace ga {

	template<class ValueType>
	constexpr decltype(auto) default_tolerance() {
		return c<0, ValueType>;
	}

	template<>
	constexpr decltype(auto) default_tolerance<std::float_t>() {
		return scalar(GA_DEFAULT_FLT_TOLERANCE);
	}

	template<>
	constexpr decltype(auto) default_tolerance<std::double_t>() {
		return scalar(GA_DEFAULT_DBL_TOLERANCE);
	}

}

#endif // __GA_EXTRA_DEFAULT_TOLERANCE_HPP__
